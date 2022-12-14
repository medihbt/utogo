#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ul_rebuild/utask_struct.h"
#include "singletaskviewer.h"
#include "ul_rebuild/utask_io.h"

#include <QtGui>
#include <QMessageBox>
#include <QDebug>
#include <QPushButton>
#include <QTimer>

#define CONFIG_FILE_PATH "main.scene"

//define static variable
int MainWindow::currentSelectedTaskID=-1;
QList<SingleTaskViewer*> MainWindow::viewerList;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //set status bar content
    statLabel=new QLabel(this);
    statusBar()->addWidget(statLabel);

    //set window title
    this->setWindowTitle(QString("时间线")+" - U.toGo");

    //add buttons at the status bar(debug feature)
    QPushButton* statBtn=new QPushButton(this);
    statBtn->setText("Refresh");
    statusBar()->addPermanentWidget(statBtn);

    //init list
//    headNode=(TaskNode *)malloc(sizeof(TaskNode));
//    if (headNode == nullptr){
//        qDebug()<<"error occured when initializing list";
//        return;
//    }
//    headNode->next=nullptr;
   mainList=new_tasklist(CONFIG_FILE_PATH);
   headNode=mainList.head;

    //set signals and slots for the widgets
    connect(ui->confirmButton,&QPushButton::clicked,[=]{
        ConfirmTask(headNode, mainList.max_task_id + 1);
        mainList.max_task_id++;
    });
    connect(statBtn,&QPushButton::clicked,[=]{
        Refresh();
    });
    connect(ui->addBtn,&QPushButton::clicked,[=]{
        switchTaskEditWidget(1);
        MainWindow::currentSelectedTaskID=-1;
        taskEditFormClr();
        ui->taskEditorStack->setCurrentIndex(0);
    });
    connect(ui->backToEditButton,&QPushButton::clicked,[=]{
        ui->taskEditorStack->setCurrentIndex(1);
    });
    connect(ui->editBtn,&QPushButton::clicked,[=]{
        if(currentSelectedTaskID<0){
            QMessageBox::warning(this,"编辑错误","不存在待编辑的项");
            return;
        }
        EditTask(headNode,viewerList[currentSelectedTaskID]->id);
    });
    connect(ui->delBtn,&QPushButton::clicked,[=]{
        if(currentSelectedTaskID<0){
            QMessageBox::warning(this,"删除错误","不存在待删除的项");
            return;
        }
        DelTask(headNode,viewerList[currentSelectedTaskID]->id);
    });

    //display add task page
    ui->taskEditorStack->setCurrentIndex(0);
    Refresh();

    //change app icon
    this->setWindowIcon(QIcon(":/icon/asset/icons/icon1.png"));

    //init system tray
    initSysTrayIcon();

    //init time checker
    QTimer* timer=new QTimer(this);
    timer->setInterval(1000);
    connect(timer,&QTimer::timeout,[=]{
        CheckCurrentTime();
    });
    timer->start();
    //debug

}
void MainWindow::CheckCurrentTime()
{
    QDateTime curDateTime=QDateTime::currentDateTime();
    foreach(SingleTaskViewer* i,MainWindow::viewerList){
        TaskInfo info=i->info;
        if(info.finished)continue;
        else if(!(0x80000000==(info.t_duedate_type&0x80000000))){
            //once
            if(QDate(info.t_duedate[0],info.t_duedate[1],info.t_duedate[2])==curDateTime.date()){
                if(!info.isNearArrive&&QTime(info.t_duetime[0]-info.time_ahead[0],info.t_duetime[1]-info.time_ahead[1],info.t_duetime[2]-info.time_ahead[2])==QTime(curDateTime.time().hour(),curDateTime.time().minute(),curDateTime.time().second()) ){
                    //time of ahead arrived
                    QMessageBox::information(this,"任务提醒",QString("一项名为%1的任务即将到达提醒时间").arg(info.name));
                    info.isNearArrive=true;
                    change_node_by_id(headNode, info, info.t_id);
                    Refresh();
                }
                if(QTime(info.t_duetime[0],info.t_duetime[1],info.t_duetime[2])==QTime(curDateTime.time().hour(),curDateTime.time().minute(),curDateTime.time().second())){
                    //time arrived
                    QMessageBox::information(this,"任务提醒",QString("一项名为%1的任务到达提醒时间").arg(info.name));
                    info.finished=true;
                    change_node_by_id(headNode,info, info.t_id);
                    Refresh();
                }
            }
        }else{
            for(int byt=1;byt<=7;byt++){
                if((0x01 << byt)&info.t_duedate_type){
                    if(QTime(info.t_duetime[0],info.t_duetime[1],info.t_duetime[2])==QTime(curDateTime.time().hour(),curDateTime.time().minute(),curDateTime.time().second())){
                        //time arrived
                        qDebug()<<"arrived";
                        QMessageBox::information(this,"任务提醒",QString("一项名为%1的任务按照约定在%2提醒").arg(info.name).arg(curDateTime.toString("ddd")));
                        info.finished=true;
                        change_node_by_id(headNode,info, info.t_id);
                        Refresh();
                    }
                }
            }
        }
    }
}



MainWindow::~MainWindow()
{
    delete ui;
}

//confirm a new task
void MainWindow::ConfirmTask(TaskNode *L, int id){
    TaskInfo info={
        .desciption=(char* )malloc(sizeof(char)*MAX_DESCRIPTION_SIZE),
        .priv_data=NULL,
    };
    info.t_id = id;
    QByteArray nameby = ui->taskNamePlainTextEdit->toPlainText().toUtf8();
    strncpy(info.name,nameby.data(),256);
    if(!strncmp(info.name,"",2)){
        QMessageBox::warning(this,"未输入任务名","请补全任务信息");
        return;
    }
    info.ttype=ui->taskTypeComboBox->currentIndex();
    info.finished=ui->isDoneCheckBox->isChecked();
    QByteArray decby=ui->taskDesTextEdit->toPlainText().toUtf8();
    strncpy(info.desciption,decby.data(), MAX_DESCRIPTION_SIZE);

    info.t_duedate_type=ui->timetabWidget->currentIndex();
    if(!info.t_duedate_type){
        //once
        dateAndTimeInput(ui->occurdateTimeEdit->dateTime(),info.t_duedate,info.t_duetime);
        info.time_ahead[0]=ui->notftimeEdit->time().hour();
        info.time_ahead[1]=ui->notftimeEdit->time().minute();
        info.time_ahead[2]=ui->notftimeEdit->time().second();
    }else{
        //per week
        info.t_duetime[0]=ui->mainichitimeEdit->time().hour();
        info.t_duetime[1]=ui->mainichitimeEdit->time().minute();
        info.t_duetime[2]=ui->mainichitimeEdit->time().second();
    }
    if(ui->mon->isChecked())info.t_duedate_type|=0b00000010;
    if(ui->tue->isChecked())info.t_duedate_type|=0b00000100;
    if(ui->wed->isChecked())info.t_duedate_type|=0b00001000;
    if(ui->thu->isChecked())info.t_duedate_type|=0b00010000;
    if(ui->fri->isChecked())info.t_duedate_type|=0b00100000;
    if(ui->sat->isChecked())info.t_duedate_type|=0b01000000;
    if(ui->sun->isChecked())info.t_duedate_type|=0b10000000;


    if(!utask_insert(L, info, 0)){
        qDebug()<<"error occured when adding node";
    }
    Refresh();
}


//view task message at the task edit area
void MainWindow::ViewTask(int id){
    TaskInfo info=viewerList[id]->info;
    ui->taskEditorStack->setCurrentIndex(1);

    ui->tasknamelabel->setText(QString::fromUtf8(info.name));

    ui->isDoneCheckBox_edit->setChecked(info.finished);
    ui->taskTypeComboBox_edit->setCurrentIndex(info.ttype);
    ui->taskNamePlainTextEdit_edit->setPlainText(QString::fromUtf8(info.name));
    ui->taskDesTextEdit_edit->setPlainText(QString::fromUtf8(info.desciption));

    ui->timetabWidget_edit->setCurrentIndex(_CIRCULATE_WEEKLY==(info.t_duedate_type&_CIRCULATE_WEEKLY));
    if(!ui->timetabWidget_edit->currentIndex()){
        //once
        ui->notftimeEdit_edit_2->setTime(QTime(info.time_ahead[0],info.time_ahead[1],info.time_ahead[2]));
        ui->occurdateTimeEdit_edit->setDateTime(dateAndTimeExtract(info.t_duedate,info.t_duetime));
    }else{
        //per week & everyday
        ui->mainichitimeEdit_edit->setTime(QTime(info.time_ahead[0],info.time_ahead[1],info.time_ahead[2]));
    }

    ui->mon_e->setChecked(0x02==(info.t_duedate_type&0x02));
    ui->tue_e->setChecked(0x04==(info.t_duedate_type&0x04));
    ui->wed_e->setChecked(0x08==(info.t_duedate_type&0x08));
    ui->thu_e->setChecked(0x10==(info.t_duedate_type&0x10));
    ui->fri_e->setChecked(0x20==(info.t_duedate_type&0x20));
    ui->sat_e->setChecked(0x40==(info.t_duedate_type&0x40));
    ui->sun_e->setChecked(0x80==(info.t_duedate_type&0x80));

    SoloTaskViewer(id);
}

//confirm a task edit
void MainWindow::EditTask(TaskNode *L, int id){
    TaskInfo info={
        .desciption=search_node_by_id(L,id)->task.desciption,
        .priv_data=search_node_by_id(L,id)->task.priv_data,
    };
    info.t_id = id;
    info.isNearArrive=false;
    info.finished=ui->isDoneCheckBox_edit->isChecked();
    info.ttype= ui->taskTypeComboBox_edit->currentIndex();
    QByteArray nameby = ui->taskNamePlainTextEdit_edit->toPlainText().toUtf8();
    strncpy(info.name,nameby.data(),256);
    QByteArray desby = ui->taskDesTextEdit_edit->toPlainText().toUtf8();
    strncpy(info.desciption,desby.data(),MAX_DESCRIPTION_SIZE);

    dateAndTimeInput(ui->occurdateTimeEdit_edit->dateTime(),info.t_duedate,info.t_duetime);

    info.t_duedate_type=ui->timetabWidget_edit->currentIndex()<<31;
    if(!info.t_duedate_type){
        //once
        dateAndTimeInput(ui->occurdateTimeEdit_edit->dateTime(),info.t_duedate,info.t_duetime);
        info.time_ahead[0]=ui->notftimeEdit_edit_2->time().hour();
        info.time_ahead[1]=ui->notftimeEdit_edit_2->time().minute();
        info.time_ahead[2]=ui->notftimeEdit_edit_2->time().second();
    }else{
        //per week
        info.t_duetime[0]=ui->mainichitimeEdit_edit->time().hour();
        info.t_duetime[1]=ui->mainichitimeEdit_edit->time().minute();
        info.t_duetime[2]=ui->mainichitimeEdit_edit->time().second();
    }
    if(ui->mon_e->isChecked())info.t_duedate_type|=0b00000010;
    if(ui->tue_e->isChecked())info.t_duedate_type|=0b00000100;
    if(ui->wed_e->isChecked())info.t_duedate_type|=0b00001000;
    if(ui->thu_e->isChecked())info.t_duedate_type|=0b00010000;
    if(ui->fri_e->isChecked())info.t_duedate_type|=0b00100000;
    if(ui->sat_e->isChecked())info.t_duedate_type|=0b01000000;
    if(ui->sun_e->isChecked())info.t_duedate_type|=0b10000000;
    change_node_by_id(L,info, id);
    Refresh();
}

//delete a task
void MainWindow::DelTask(TaskNode *L,int id){
    utask_delet_one_node(L,id);
    Refresh();
    if(MainWindow::currentSelectedTaskID>0)
    {
        MainWindow::currentSelectedTaskID--;
        ViewTask(currentSelectedTaskID);
    }
    if(currentSelectedTaskID==0)currentSelectedTaskID--;
    SoloTaskViewer(currentSelectedTaskID);
    taskEditFormClr();
}

//refresh list view
void MainWindow::Refresh(){
    //save config file
    if(write_tasklist(&mainList, CONFIG_FILE_PATH)!=0){
        QMessageBox::warning(this,"保存配置文件错误","请检查你的文件夹权限设置");
    }

    //delete current task viewer widgets
    QList<SingleTaskViewer*> taskviewers=ui->taskViewerWidgetContents->findChildren<SingleTaskViewer*>();
    foreach(SingleTaskViewer* i,taskviewers){
        delete i;
    }
    while(viewerList.length()>0){
        viewerList.removeLast();
    }

    //reset variables
    hasDoneTaskCount=0;
    yetToBeDoneTaskCount=0;
    statTaskCount=0;
    impTaskCount=0;
    limitedTaskCount=0;

    //refresh new task viewers
    int i=0;
    TaskNode* currentNode=headNode;
    while(currentNode->next!=nullptr){
        currentNode=currentNode->next;

        //add new task viewer
        TaskInfo info=currentNode->task;
        SingleTaskViewer* viewer=new SingleTaskViewer(this);
        if(!(0x80000000==(info.t_duedate_type&0x80000000))){
            //once
            viewer->SetTaskViewerValue(i,info.t_id,info.finished,info.ttype,QString::fromUtf8(info.name)," "+QString::number(info.t_duetime[0])+":"+QString::number(info.t_duetime[1])+":"+QString::number(info.t_duetime[2]),QString::number(info.t_duedate[0])+"/"+QString::number(info.t_duedate[1])+"/"+QString::number(info.t_duedate[2]),currentNode->task);
        }else{
            //per week
            viewer->SetTaskViewerValue(i,info.t_id,info.finished,info.ttype,QString::fromUtf8(info.name),QString::number(info.t_duetime[0])+":"+QString::number(info.t_duetime[1])+":"+QString::number(info.t_duetime[2])+" "," 重复任务",currentNode->task);
        }
        if(info.finished){
            hasDoneTaskCount++;
        }else{
            yetToBeDoneTaskCount++;
            switch (info.ttype) {
            case _STATIC:
                statTaskCount++;
                break;
            case _TIME_LIMIT:
                limitedTaskCount++;
                break;
            case _BIG_EVENT:
                impTaskCount++;
                break;
            }
        }
        ui->taskListVerticalLayout->addWidget(viewer);
        viewerList.append(viewer);
        i++;
    }
    ui->label_hasOwari->setText(QString("已完成 %1 / 未完成 %2").arg(hasDoneTaskCount).arg(yetToBeDoneTaskCount));
    ui->label_nokoriImpTask->setText(QString("剩余重要任务：%1").arg(impTaskCount));
    ui->label_nokorimainTask->setText(QString("剩余主线任务：%1").arg(statTaskCount));
    ui->label_nokoriLimitedTask->setText(QString("剩余限时任务：%1").arg(limitedTaskCount));
    statLabel->setText("你还有"+QString::number(yetToBeDoneTaskCount)+"项任务");

}

void MainWindow::SoloTaskViewer(int id){
    for(int i=0;i<viewerList.length();i++){
        if(i==id){
            viewerList[i]->SetSelected(true);
            currentSelectedTaskID=i;
        }else{
            viewerList[i]->SetSelected(false);
        }
    }
}

void MainWindow::switchTaskEditWidget(int index){
    switch (index){
    case 0:
        ui->addTaskPage->show();
        ui->editTaskPage->hide();
        break;
    case 1:
        ui->addTaskPage->hide();
        ui->editTaskPage->show();
        break;
    }
    ui->taskEditorStack->setCurrentIndex(index);
}

void MainWindow::taskEditFormClr(){
    ui->isDoneCheckBox->setChecked(false);
    ui->taskTypeComboBox->setCurrentIndex(0);
    ui->taskNamePlainTextEdit->setPlainText("");
    ui->taskDesTextEdit->setPlainText("");
    ui->isDoneCheckBox_edit->setChecked(false);
    ui->taskTypeComboBox_edit->setCurrentIndex(0);
    ui->taskNamePlainTextEdit_edit->setPlainText("");
    ui->taskDesTextEdit_edit->setPlainText("");
}

QDateTime MainWindow::dateAndTimeExtract(int* duedate,int* duetime){
    return QDateTime (QDate(duedate[0],duedate[1],duedate[2]),QTime(duetime[0],duetime[1],duetime[2]));
}

void MainWindow::dateAndTimeInput(QDateTime dateAndTime, int *duedate, int *duetime){
    duedate[0]=dateAndTime.date().year();
    duedate[1]=dateAndTime.date().month();
    duedate[2]=dateAndTime.date().day();
    duetime[0]=dateAndTime.time().hour();
    duetime[1]=dateAndTime.time().minute();
    duetime[2]=dateAndTime.time().second();
}

//functions about system tray
void MainWindow::initSysTrayIcon()
{
    this->hide();

    m_sysTrayIcon = new QSystemTrayIcon(this);

    QIcon icon = QIcon(":/icon/asset/icons/icon1.png");
    m_sysTrayIcon->setIcon(icon);

    m_sysTrayIcon->setToolTip("U.togo");

    connect(m_sysTrayIcon, &QSystemTrayIcon::activated,
            [=](QSystemTrayIcon::ActivationReason reason)
    {
        switch(reason)
        {
        case QSystemTrayIcon::Trigger:
            //clicked
            break;
        case QSystemTrayIcon::DoubleClick:
            //double clicked
            this->show();
            break;
        default:
            break;
        }
    });

    createActions();
    createMenu();
    m_sysTrayIcon->show();
}

void MainWindow::createActions()
{
    m_showWindowAction=new QAction("恢复窗口",this);
    connect(m_showWindowAction,SIGNAL(triggered()),this,SLOT(on_showWindowAction()));
    m_showMainAction = new QAction("关于系统", this);
    connect(m_showMainAction,SIGNAL(triggered()),this,SLOT(on_showMainAction()));
    m_exitAppAction = new QAction("退出", this);
    connect(m_exitAppAction,SIGNAL(triggered()),this,SLOT(on_exitAppAction()));
}

void MainWindow::createMenu()
{
    m_menu = new QMenu(this);
    m_menu->addAction(m_showWindowAction);
    m_menu->addAction(m_showMainAction);
    m_menu->addSeparator();
    m_menu->addAction(m_exitAppAction);

    m_sysTrayIcon->setContextMenu(m_menu);
}

void MainWindow::on_showWindowAction(){
    this->show();
}

void MainWindow::on_showMainAction()
{
    QApplication::setQuitOnLastWindowClosed( false );
    QMessageBox::information(nullptr, "关于", "U.toGo -- UniLife的简单任务清单程序\n"
                                             "version 0.0.1\n\n"
                                             "由Imagine Studio PBLF小组强力驱动.\n\n"
                                             "  此应用程序采用GPLv3许可证: 本软件是\n"
                                             "自由软件，您可以自由地更改和重新发布。\n\n"
                                             "在法律许可的情况下特此明示，本软件不提\n"
                                             "供任何担保。GPL许可证的信息详见\n"
                                             "<https://www.gnu.org/licenses/>.");
}

void MainWindow::on_exitAppAction()
{
    qApp->exit();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    //ignore window close event
    QApplication::setQuitOnLastWindowClosed( true );
    this->hide();
    event->ignore();
}
