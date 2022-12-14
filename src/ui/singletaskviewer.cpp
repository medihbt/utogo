#include "singletaskviewer.h"
#include "ui_singletaskviewer.h"
#include "../include/utask_struct.h"
#include "mainwindow.h"

#include <QDebug>

SingleTaskViewer::SingleTaskViewer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SingleTaskViewer)
{
    ui->setupUi(this);
    mainptr=parent;
    isSelected=false;
}

SingleTaskViewer::~SingleTaskViewer()
{
    delete ui;
}

void SingleTaskViewer::SetTaskViewerValue(int _viewerid,int _id,bool isDone, int taskType, QString taskName, QString date, QString time,TaskInfo _info){
    viewerid=_viewerid;
    id=_id;
    info=_info;
    if(isDone){
        ui->isDoneIndicatorLabel->setText("🮱");// ✓
    }else{
        ui->isDoneIndicatorLabel->setText("▢");// ×
    }
    switch(taskType){
        case _STATIC:
            ui->taskTypeLabel->setText("主线");
            break;
        case _TIME_LIMIT:
            ui->taskTypeLabel->setText("限时");
            break;
        case _BIG_EVENT:
            ui->taskTypeLabel->setText("重要");
            break;
        default:
            ui->taskTypeLabel->setText("*");
            break;
    }
    ui->taskNameLabel->setText(taskName);
    ui->taskTimeLabel->setText(date+" | "+time);
}

void SingleTaskViewer::mousePressEvent(QMouseEvent *event){
    MainWindow::currentSelectedTaskID=viewerid;
    ((MainWindow*)mainptr)->ViewTask(viewerid);
}

void SingleTaskViewer::SetSelected(bool _isSelected){
    isSelected=_isSelected;
    if(_isSelected){
        ui->frame->setFrameShape(QFrame::StyledPanel);
    }else{
        ui->frame->setFrameStyle(QFrame::NoFrame);
    }
}
