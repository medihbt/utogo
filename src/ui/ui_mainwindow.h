/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_4;
    QGroupBox *groupBoxActList;
    QHBoxLayout *horizontalLayout_2;
    QToolBox *toolBox;
    QWidget *page;
    QWidget *page_2;
    QGroupBox *groupBoxMainScene;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_sceneName;
    QLabel *label_hasOwari;
    QLabel *label_nokorimainTask;
    QLabel *label_nokoriLimitedTask;
    QLabel *label_nokoriImpTask;
    QFrame *line;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_11;
    QScrollArea *tasksViewScrollArea;
    QWidget *taskViewerWidgetContents;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *taskListVerticalLayout;
    QGroupBox *groupBox_29;
    QVBoxLayout *verticalLayout_22;
    QStackedWidget *taskEditorStack;
    QWidget *addTaskPage;
    QVBoxLayout *verticalLayout_12;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox_4;
    QHBoxLayout *horizontalLayout_5;
    QCheckBox *isDoneCheckBox;
    QLabel *label_7;
    QComboBox *taskTypeComboBox;
    QLabel *label_6;
    QGroupBox *groupBox_5;
    QVBoxLayout *verticalLayout_18;
    QTabWidget *timetabWidget;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_5;
    QGroupBox *groupBox_9;
    QVBoxLayout *verticalLayout_6;
    QGroupBox *groupBox_11;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_11;
    QDateTimeEdit *occurdateTimeEdit;
    QGroupBox *groupBox_10;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_10;
    QTimeEdit *notftimeEdit;
    QWidget *tab_3;
    QVBoxLayout *verticalLayout_8;
    QGroupBox *groupBox_13;
    QVBoxLayout *verticalLayout_9;
    QGroupBox *groupBox_14;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_12;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_4;
    QCheckBox *mon;
    QCheckBox *tue;
    QCheckBox *wed;
    QCheckBox *thu;
    QCheckBox *fri;
    QCheckBox *sat;
    QCheckBox *sun;
    QGroupBox *groupBox_15;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_13;
    QTimeEdit *mainichitimeEdit;
    QGroupBox *groupBox_6;
    QVBoxLayout *verticalLayout_10;
    QPlainTextEdit *taskNamePlainTextEdit;
    QTextEdit *taskDesTextEdit;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_21;
    QPushButton *confirmButton;
    QPushButton *backToEditButton;
    QWidget *editTaskPage;
    QHBoxLayout *horizontalLayout_19;
    QGroupBox *groupBox_16;
    QVBoxLayout *verticalLayout_13;
    QGroupBox *groupBox_17;
    QHBoxLayout *horizontalLayout_6;
    QCheckBox *isDoneCheckBox_edit;
    QLabel *label_14;
    QComboBox *taskTypeComboBox_edit;
    QLabel *tasknamelabel;
    QGroupBox *groupBox_18;
    QVBoxLayout *verticalLayout_3;
    QTabWidget *timetabWidget_edit;
    QWidget *tab_4;
    QVBoxLayout *verticalLayout_7;
    QGroupBox *groupBox_12;
    QVBoxLayout *verticalLayout_14;
    QGroupBox *groupBox_19;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_15;
    QDateTimeEdit *occurdateTimeEdit_edit;
    QGroupBox *groupBox_20;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_16;
    QTimeEdit *notftimeEdit_edit_2;
    QWidget *tab_5;
    QVBoxLayout *verticalLayout_15;
    QGroupBox *groupBox_21;
    QVBoxLayout *verticalLayout_16;
    QGroupBox *groupBox_22;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_17;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents_2;
    QVBoxLayout *verticalLayout_17;
    QCheckBox *mon_e;
    QCheckBox *tue_e;
    QCheckBox *wed_e;
    QCheckBox *thu_e;
    QCheckBox *fri_e;
    QCheckBox *sat_e;
    QCheckBox *sun_e;
    QGroupBox *groupBox_23;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_18;
    QTimeEdit *mainichitimeEdit_edit;
    QGroupBox *groupBox_28;
    QVBoxLayout *verticalLayout_21;
    QPlainTextEdit *taskNamePlainTextEdit_edit;
    QTextEdit *taskDesTextEdit_edit;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_20;
    QPushButton *addBtn;
    QPushButton *delBtn;
    QPushButton *editBtn;
    QMenuBar *menubar;
    QMenu *menuU_togo;
    QMenu *menu;
    QMenu *menu_2;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1172, 886);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        horizontalLayout_4 = new QHBoxLayout(centralwidget);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        groupBoxActList = new QGroupBox(centralwidget);
        groupBoxActList->setObjectName(QStringLiteral("groupBoxActList"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBoxActList->sizePolicy().hasHeightForWidth());
        groupBoxActList->setSizePolicy(sizePolicy);
        groupBoxActList->setMaximumSize(QSize(400, 16777215));
        horizontalLayout_2 = new QHBoxLayout(groupBoxActList);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        toolBox = new QToolBox(groupBoxActList);
        toolBox->setObjectName(QStringLiteral("toolBox"));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        page->setGeometry(QRect(0, 0, 102, 703));
        toolBox->addItem(page, QString::fromUtf8("\344\270\273\345\234\272\346\231\257"));
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        page_2->setGeometry(QRect(0, 0, 102, 703));
        toolBox->addItem(page_2, QString::fromUtf8("\345\205\266\344\273\226\344\275\215\347\275\256"));

        horizontalLayout_2->addWidget(toolBox);


        horizontalLayout_4->addWidget(groupBoxActList);

        groupBoxMainScene = new QGroupBox(centralwidget);
        groupBoxMainScene->setObjectName(QStringLiteral("groupBoxMainScene"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBoxMainScene->sizePolicy().hasHeightForWidth());
        groupBoxMainScene->setSizePolicy(sizePolicy1);
        groupBoxMainScene->setMinimumSize(QSize(0, 0));
        groupBoxMainScene->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        groupBoxMainScene->setFlat(false);
        groupBoxMainScene->setCheckable(false);
        verticalLayout = new QVBoxLayout(groupBoxMainScene);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        groupBox = new QGroupBox(groupBoxMainScene);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setMaximumSize(QSize(16777215, 100));
        horizontalLayout_3 = new QHBoxLayout(groupBox);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_sceneName = new QLabel(groupBox);
        label_sceneName->setObjectName(QStringLiteral("label_sceneName"));
        sizePolicy1.setHeightForWidth(label_sceneName->sizePolicy().hasHeightForWidth());
        label_sceneName->setSizePolicy(sizePolicy1);
        QFont font;
        font.setPointSize(19);
        label_sceneName->setFont(font);
        label_sceneName->setTextFormat(Qt::AutoText);

        horizontalLayout_3->addWidget(label_sceneName);

        label_hasOwari = new QLabel(groupBox);
        label_hasOwari->setObjectName(QStringLiteral("label_hasOwari"));

        horizontalLayout_3->addWidget(label_hasOwari);

        label_nokorimainTask = new QLabel(groupBox);
        label_nokorimainTask->setObjectName(QStringLiteral("label_nokorimainTask"));

        horizontalLayout_3->addWidget(label_nokorimainTask);

        label_nokoriLimitedTask = new QLabel(groupBox);
        label_nokoriLimitedTask->setObjectName(QStringLiteral("label_nokoriLimitedTask"));

        horizontalLayout_3->addWidget(label_nokoriLimitedTask);

        label_nokoriImpTask = new QLabel(groupBox);
        label_nokoriImpTask->setObjectName(QStringLiteral("label_nokoriImpTask"));

        horizontalLayout_3->addWidget(label_nokoriImpTask);


        verticalLayout->addWidget(groupBox);

        line = new QFrame(groupBoxMainScene);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        groupBox_2 = new QGroupBox(groupBoxMainScene);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        verticalLayout_11 = new QVBoxLayout(groupBox_2);
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        tasksViewScrollArea = new QScrollArea(groupBox_2);
        tasksViewScrollArea->setObjectName(QStringLiteral("tasksViewScrollArea"));
        tasksViewScrollArea->setWidgetResizable(true);
        tasksViewScrollArea->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        taskViewerWidgetContents = new QWidget();
        taskViewerWidgetContents->setObjectName(QStringLiteral("taskViewerWidgetContents"));
        taskViewerWidgetContents->setGeometry(QRect(0, 0, 562, 622));
        horizontalLayout = new QHBoxLayout(taskViewerWidgetContents);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        taskListVerticalLayout = new QVBoxLayout();
        taskListVerticalLayout->setObjectName(QStringLiteral("taskListVerticalLayout"));

        horizontalLayout->addLayout(taskListVerticalLayout);

        tasksViewScrollArea->setWidget(taskViewerWidgetContents);

        verticalLayout_11->addWidget(tasksViewScrollArea);


        verticalLayout->addWidget(groupBox_2);


        horizontalLayout_4->addWidget(groupBoxMainScene);

        groupBox_29 = new QGroupBox(centralwidget);
        groupBox_29->setObjectName(QStringLiteral("groupBox_29"));
        sizePolicy.setHeightForWidth(groupBox_29->sizePolicy().hasHeightForWidth());
        groupBox_29->setSizePolicy(sizePolicy);
        verticalLayout_22 = new QVBoxLayout(groupBox_29);
        verticalLayout_22->setObjectName(QStringLiteral("verticalLayout_22"));
        taskEditorStack = new QStackedWidget(groupBox_29);
        taskEditorStack->setObjectName(QStringLiteral("taskEditorStack"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(taskEditorStack->sizePolicy().hasHeightForWidth());
        taskEditorStack->setSizePolicy(sizePolicy2);
        taskEditorStack->setMaximumSize(QSize(114514, 16777215));
        addTaskPage = new QWidget();
        addTaskPage->setObjectName(QStringLiteral("addTaskPage"));
        verticalLayout_12 = new QVBoxLayout(addTaskPage);
        verticalLayout_12->setObjectName(QStringLiteral("verticalLayout_12"));
        groupBox_3 = new QGroupBox(addTaskPage);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy3);
        groupBox_3->setMaximumSize(QSize(400, 16777215));
        verticalLayout_2 = new QVBoxLayout(groupBox_3);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        groupBox_4 = new QGroupBox(groupBox_3);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        horizontalLayout_5 = new QHBoxLayout(groupBox_4);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        isDoneCheckBox = new QCheckBox(groupBox_4);
        isDoneCheckBox->setObjectName(QStringLiteral("isDoneCheckBox"));
        isDoneCheckBox->setMaximumSize(QSize(25, 16777215));
        isDoneCheckBox->setCheckable(false);
        isDoneCheckBox->setChecked(false);

        horizontalLayout_5->addWidget(isDoneCheckBox);

        label_7 = new QLabel(groupBox_4);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setMaximumSize(QSize(80, 16777215));
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_5->addWidget(label_7);

        taskTypeComboBox = new QComboBox(groupBox_4);
        taskTypeComboBox->setObjectName(QStringLiteral("taskTypeComboBox"));
        taskTypeComboBox->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_5->addWidget(taskTypeComboBox);

        label_6 = new QLabel(groupBox_4);
        label_6->setObjectName(QStringLiteral("label_6"));
        sizePolicy2.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy2);
        QFont font1;
        font1.setPointSize(15);
        label_6->setFont(font1);
        label_6->setInputMethodHints(Qt::ImhNone);
        label_6->setFrameShape(QFrame::Panel);
        label_6->setAlignment(Qt::AlignCenter);

        horizontalLayout_5->addWidget(label_6);


        verticalLayout_2->addWidget(groupBox_4);

        groupBox_5 = new QGroupBox(groupBox_3);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        verticalLayout_18 = new QVBoxLayout(groupBox_5);
        verticalLayout_18->setObjectName(QStringLiteral("verticalLayout_18"));
        timetabWidget = new QTabWidget(groupBox_5);
        timetabWidget->setObjectName(QStringLiteral("timetabWidget"));
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        verticalLayout_5 = new QVBoxLayout(tab_2);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        groupBox_9 = new QGroupBox(tab_2);
        groupBox_9->setObjectName(QStringLiteral("groupBox_9"));
        verticalLayout_6 = new QVBoxLayout(groupBox_9);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        groupBox_11 = new QGroupBox(groupBox_9);
        groupBox_11->setObjectName(QStringLiteral("groupBox_11"));
        horizontalLayout_10 = new QHBoxLayout(groupBox_11);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        label_11 = new QLabel(groupBox_11);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setAlignment(Qt::AlignCenter);

        horizontalLayout_10->addWidget(label_11);

        occurdateTimeEdit = new QDateTimeEdit(groupBox_11);
        occurdateTimeEdit->setObjectName(QStringLiteral("occurdateTimeEdit"));

        horizontalLayout_10->addWidget(occurdateTimeEdit);


        verticalLayout_6->addWidget(groupBox_11);

        groupBox_10 = new QGroupBox(groupBox_9);
        groupBox_10->setObjectName(QStringLiteral("groupBox_10"));
        groupBox_10->setFlat(false);
        groupBox_10->setCheckable(false);
        horizontalLayout_7 = new QHBoxLayout(groupBox_10);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_10 = new QLabel(groupBox_10);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setAlignment(Qt::AlignCenter);

        horizontalLayout_7->addWidget(label_10);

        notftimeEdit = new QTimeEdit(groupBox_10);
        notftimeEdit->setObjectName(QStringLiteral("notftimeEdit"));

        horizontalLayout_7->addWidget(notftimeEdit);


        verticalLayout_6->addWidget(groupBox_10);


        verticalLayout_5->addWidget(groupBox_9);

        timetabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        verticalLayout_8 = new QVBoxLayout(tab_3);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        groupBox_13 = new QGroupBox(tab_3);
        groupBox_13->setObjectName(QStringLiteral("groupBox_13"));
        verticalLayout_9 = new QVBoxLayout(groupBox_13);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        groupBox_14 = new QGroupBox(groupBox_13);
        groupBox_14->setObjectName(QStringLiteral("groupBox_14"));
        horizontalLayout_11 = new QHBoxLayout(groupBox_14);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        label_12 = new QLabel(groupBox_14);
        label_12->setObjectName(QStringLiteral("label_12"));
        sizePolicy.setHeightForWidth(label_12->sizePolicy().hasHeightForWidth());
        label_12->setSizePolicy(sizePolicy);
        label_12->setAlignment(Qt::AlignCenter);

        horizontalLayout_11->addWidget(label_12);

        scrollArea = new QScrollArea(groupBox_14);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(scrollArea->sizePolicy().hasHeightForWidth());
        scrollArea->setSizePolicy(sizePolicy4);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 197, 222));
        verticalLayout_4 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        mon = new QCheckBox(scrollAreaWidgetContents);
        mon->setObjectName(QStringLiteral("mon"));

        verticalLayout_4->addWidget(mon);

        tue = new QCheckBox(scrollAreaWidgetContents);
        tue->setObjectName(QStringLiteral("tue"));

        verticalLayout_4->addWidget(tue);

        wed = new QCheckBox(scrollAreaWidgetContents);
        wed->setObjectName(QStringLiteral("wed"));

        verticalLayout_4->addWidget(wed);

        thu = new QCheckBox(scrollAreaWidgetContents);
        thu->setObjectName(QStringLiteral("thu"));

        verticalLayout_4->addWidget(thu);

        fri = new QCheckBox(scrollAreaWidgetContents);
        fri->setObjectName(QStringLiteral("fri"));

        verticalLayout_4->addWidget(fri);

        sat = new QCheckBox(scrollAreaWidgetContents);
        sat->setObjectName(QStringLiteral("sat"));

        verticalLayout_4->addWidget(sat);

        sun = new QCheckBox(scrollAreaWidgetContents);
        sun->setObjectName(QStringLiteral("sun"));

        verticalLayout_4->addWidget(sun);

        scrollArea->setWidget(scrollAreaWidgetContents);

        horizontalLayout_11->addWidget(scrollArea);


        verticalLayout_9->addWidget(groupBox_14);

        groupBox_15 = new QGroupBox(groupBox_13);
        groupBox_15->setObjectName(QStringLiteral("groupBox_15"));
        horizontalLayout_12 = new QHBoxLayout(groupBox_15);
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        label_13 = new QLabel(groupBox_15);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setAlignment(Qt::AlignCenter);

        horizontalLayout_12->addWidget(label_13);

        mainichitimeEdit = new QTimeEdit(groupBox_15);
        mainichitimeEdit->setObjectName(QStringLiteral("mainichitimeEdit"));

        horizontalLayout_12->addWidget(mainichitimeEdit);


        verticalLayout_9->addWidget(groupBox_15);


        verticalLayout_8->addWidget(groupBox_13);

        timetabWidget->addTab(tab_3, QString());

        verticalLayout_18->addWidget(timetabWidget);


        verticalLayout_2->addWidget(groupBox_5);

        groupBox_6 = new QGroupBox(groupBox_3);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        verticalLayout_10 = new QVBoxLayout(groupBox_6);
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        taskNamePlainTextEdit = new QPlainTextEdit(groupBox_6);
        taskNamePlainTextEdit->setObjectName(QStringLiteral("taskNamePlainTextEdit"));
        taskNamePlainTextEdit->setMaximumSize(QSize(16777215, 30));
        taskNamePlainTextEdit->setInputMethodHints(Qt::ImhNone);
        taskNamePlainTextEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        taskNamePlainTextEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        taskNamePlainTextEdit->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);

        verticalLayout_10->addWidget(taskNamePlainTextEdit);

        taskDesTextEdit = new QTextEdit(groupBox_6);
        taskDesTextEdit->setObjectName(QStringLiteral("taskDesTextEdit"));
        taskDesTextEdit->setReadOnly(false);

        verticalLayout_10->addWidget(taskDesTextEdit);


        verticalLayout_2->addWidget(groupBox_6);

        widget_2 = new QWidget(groupBox_3);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        horizontalLayout_21 = new QHBoxLayout(widget_2);
        horizontalLayout_21->setObjectName(QStringLiteral("horizontalLayout_21"));
        confirmButton = new QPushButton(widget_2);
        confirmButton->setObjectName(QStringLiteral("confirmButton"));

        horizontalLayout_21->addWidget(confirmButton);

        backToEditButton = new QPushButton(widget_2);
        backToEditButton->setObjectName(QStringLiteral("backToEditButton"));

        horizontalLayout_21->addWidget(backToEditButton);


        verticalLayout_2->addWidget(widget_2);


        verticalLayout_12->addWidget(groupBox_3);

        taskEditorStack->addWidget(addTaskPage);
        editTaskPage = new QWidget();
        editTaskPage->setObjectName(QStringLiteral("editTaskPage"));
        horizontalLayout_19 = new QHBoxLayout(editTaskPage);
        horizontalLayout_19->setObjectName(QStringLiteral("horizontalLayout_19"));
        groupBox_16 = new QGroupBox(editTaskPage);
        groupBox_16->setObjectName(QStringLiteral("groupBox_16"));
        sizePolicy3.setHeightForWidth(groupBox_16->sizePolicy().hasHeightForWidth());
        groupBox_16->setSizePolicy(sizePolicy3);
        groupBox_16->setMaximumSize(QSize(114514, 16777215));
        verticalLayout_13 = new QVBoxLayout(groupBox_16);
        verticalLayout_13->setObjectName(QStringLiteral("verticalLayout_13"));
        groupBox_17 = new QGroupBox(groupBox_16);
        groupBox_17->setObjectName(QStringLiteral("groupBox_17"));
        horizontalLayout_6 = new QHBoxLayout(groupBox_17);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        isDoneCheckBox_edit = new QCheckBox(groupBox_17);
        isDoneCheckBox_edit->setObjectName(QStringLiteral("isDoneCheckBox_edit"));
        isDoneCheckBox_edit->setEnabled(true);
        isDoneCheckBox_edit->setMaximumSize(QSize(25, 16777215));
        isDoneCheckBox_edit->setCheckable(false);
        isDoneCheckBox_edit->setChecked(false);

        horizontalLayout_6->addWidget(isDoneCheckBox_edit);

        label_14 = new QLabel(groupBox_17);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setMaximumSize(QSize(80, 16777215));
        label_14->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_6->addWidget(label_14);

        taskTypeComboBox_edit = new QComboBox(groupBox_17);
        taskTypeComboBox_edit->setObjectName(QStringLiteral("taskTypeComboBox_edit"));
        taskTypeComboBox_edit->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_6->addWidget(taskTypeComboBox_edit);

        tasknamelabel = new QLabel(groupBox_17);
        tasknamelabel->setObjectName(QStringLiteral("tasknamelabel"));
        tasknamelabel->setFont(font1);
        tasknamelabel->setFrameShape(QFrame::Panel);
        tasknamelabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_6->addWidget(tasknamelabel);


        verticalLayout_13->addWidget(groupBox_17);

        groupBox_18 = new QGroupBox(groupBox_16);
        groupBox_18->setObjectName(QStringLiteral("groupBox_18"));
        verticalLayout_3 = new QVBoxLayout(groupBox_18);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        timetabWidget_edit = new QTabWidget(groupBox_18);
        timetabWidget_edit->setObjectName(QStringLiteral("timetabWidget_edit"));
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        verticalLayout_7 = new QVBoxLayout(tab_4);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        groupBox_12 = new QGroupBox(tab_4);
        groupBox_12->setObjectName(QStringLiteral("groupBox_12"));
        verticalLayout_14 = new QVBoxLayout(groupBox_12);
        verticalLayout_14->setObjectName(QStringLiteral("verticalLayout_14"));
        groupBox_19 = new QGroupBox(groupBox_12);
        groupBox_19->setObjectName(QStringLiteral("groupBox_19"));
        horizontalLayout_13 = new QHBoxLayout(groupBox_19);
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        label_15 = new QLabel(groupBox_19);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setAlignment(Qt::AlignCenter);

        horizontalLayout_13->addWidget(label_15);

        occurdateTimeEdit_edit = new QDateTimeEdit(groupBox_19);
        occurdateTimeEdit_edit->setObjectName(QStringLiteral("occurdateTimeEdit_edit"));

        horizontalLayout_13->addWidget(occurdateTimeEdit_edit);


        verticalLayout_14->addWidget(groupBox_19);

        groupBox_20 = new QGroupBox(groupBox_12);
        groupBox_20->setObjectName(QStringLiteral("groupBox_20"));
        groupBox_20->setFlat(false);
        groupBox_20->setCheckable(false);
        horizontalLayout_8 = new QHBoxLayout(groupBox_20);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_16 = new QLabel(groupBox_20);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setAlignment(Qt::AlignCenter);

        horizontalLayout_8->addWidget(label_16);

        notftimeEdit_edit_2 = new QTimeEdit(groupBox_20);
        notftimeEdit_edit_2->setObjectName(QStringLiteral("notftimeEdit_edit_2"));

        horizontalLayout_8->addWidget(notftimeEdit_edit_2);


        verticalLayout_14->addWidget(groupBox_20);


        verticalLayout_7->addWidget(groupBox_12);

        timetabWidget_edit->addTab(tab_4, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QStringLiteral("tab_5"));
        verticalLayout_15 = new QVBoxLayout(tab_5);
        verticalLayout_15->setObjectName(QStringLiteral("verticalLayout_15"));
        groupBox_21 = new QGroupBox(tab_5);
        groupBox_21->setObjectName(QStringLiteral("groupBox_21"));
        verticalLayout_16 = new QVBoxLayout(groupBox_21);
        verticalLayout_16->setObjectName(QStringLiteral("verticalLayout_16"));
        groupBox_22 = new QGroupBox(groupBox_21);
        groupBox_22->setObjectName(QStringLiteral("groupBox_22"));
        horizontalLayout_14 = new QHBoxLayout(groupBox_22);
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        label_17 = new QLabel(groupBox_22);
        label_17->setObjectName(QStringLiteral("label_17"));
        sizePolicy.setHeightForWidth(label_17->sizePolicy().hasHeightForWidth());
        label_17->setSizePolicy(sizePolicy);
        label_17->setAlignment(Qt::AlignCenter);

        horizontalLayout_14->addWidget(label_17);

        scrollArea_2 = new QScrollArea(groupBox_22);
        scrollArea_2->setObjectName(QStringLiteral("scrollArea_2"));
        QSizePolicy sizePolicy5(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(scrollArea_2->sizePolicy().hasHeightForWidth());
        scrollArea_2->setSizePolicy(sizePolicy5);
        scrollArea_2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QStringLiteral("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 197, 222));
        sizePolicy3.setHeightForWidth(scrollAreaWidgetContents_2->sizePolicy().hasHeightForWidth());
        scrollAreaWidgetContents_2->setSizePolicy(sizePolicy3);
        verticalLayout_17 = new QVBoxLayout(scrollAreaWidgetContents_2);
        verticalLayout_17->setObjectName(QStringLiteral("verticalLayout_17"));
        mon_e = new QCheckBox(scrollAreaWidgetContents_2);
        mon_e->setObjectName(QStringLiteral("mon_e"));

        verticalLayout_17->addWidget(mon_e);

        tue_e = new QCheckBox(scrollAreaWidgetContents_2);
        tue_e->setObjectName(QStringLiteral("tue_e"));

        verticalLayout_17->addWidget(tue_e);

        wed_e = new QCheckBox(scrollAreaWidgetContents_2);
        wed_e->setObjectName(QStringLiteral("wed_e"));

        verticalLayout_17->addWidget(wed_e);

        thu_e = new QCheckBox(scrollAreaWidgetContents_2);
        thu_e->setObjectName(QStringLiteral("thu_e"));

        verticalLayout_17->addWidget(thu_e);

        fri_e = new QCheckBox(scrollAreaWidgetContents_2);
        fri_e->setObjectName(QStringLiteral("fri_e"));

        verticalLayout_17->addWidget(fri_e);

        sat_e = new QCheckBox(scrollAreaWidgetContents_2);
        sat_e->setObjectName(QStringLiteral("sat_e"));

        verticalLayout_17->addWidget(sat_e);

        sun_e = new QCheckBox(scrollAreaWidgetContents_2);
        sun_e->setObjectName(QStringLiteral("sun_e"));

        verticalLayout_17->addWidget(sun_e);

        scrollArea_2->setWidget(scrollAreaWidgetContents_2);

        horizontalLayout_14->addWidget(scrollArea_2);


        verticalLayout_16->addWidget(groupBox_22);

        groupBox_23 = new QGroupBox(groupBox_21);
        groupBox_23->setObjectName(QStringLiteral("groupBox_23"));
        horizontalLayout_15 = new QHBoxLayout(groupBox_23);
        horizontalLayout_15->setObjectName(QStringLiteral("horizontalLayout_15"));
        label_18 = new QLabel(groupBox_23);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setAlignment(Qt::AlignCenter);

        horizontalLayout_15->addWidget(label_18);

        mainichitimeEdit_edit = new QTimeEdit(groupBox_23);
        mainichitimeEdit_edit->setObjectName(QStringLiteral("mainichitimeEdit_edit"));

        horizontalLayout_15->addWidget(mainichitimeEdit_edit);


        verticalLayout_16->addWidget(groupBox_23);


        verticalLayout_15->addWidget(groupBox_21);

        timetabWidget_edit->addTab(tab_5, QString());

        verticalLayout_3->addWidget(timetabWidget_edit);


        verticalLayout_13->addWidget(groupBox_18);

        groupBox_28 = new QGroupBox(groupBox_16);
        groupBox_28->setObjectName(QStringLiteral("groupBox_28"));
        verticalLayout_21 = new QVBoxLayout(groupBox_28);
        verticalLayout_21->setObjectName(QStringLiteral("verticalLayout_21"));
        taskNamePlainTextEdit_edit = new QPlainTextEdit(groupBox_28);
        taskNamePlainTextEdit_edit->setObjectName(QStringLiteral("taskNamePlainTextEdit_edit"));
        taskNamePlainTextEdit_edit->setMaximumSize(QSize(16777215, 30));
        taskNamePlainTextEdit_edit->setInputMethodHints(Qt::ImhNone);
        taskNamePlainTextEdit_edit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        taskNamePlainTextEdit_edit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        taskNamePlainTextEdit_edit->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);

        verticalLayout_21->addWidget(taskNamePlainTextEdit_edit);

        taskDesTextEdit_edit = new QTextEdit(groupBox_28);
        taskDesTextEdit_edit->setObjectName(QStringLiteral("taskDesTextEdit_edit"));
        taskDesTextEdit_edit->setReadOnly(false);

        verticalLayout_21->addWidget(taskDesTextEdit_edit);


        verticalLayout_13->addWidget(groupBox_28);

        widget = new QWidget(groupBox_16);
        widget->setObjectName(QStringLiteral("widget"));
        horizontalLayout_20 = new QHBoxLayout(widget);
        horizontalLayout_20->setObjectName(QStringLiteral("horizontalLayout_20"));
        addBtn = new QPushButton(widget);
        addBtn->setObjectName(QStringLiteral("addBtn"));

        horizontalLayout_20->addWidget(addBtn);

        delBtn = new QPushButton(widget);
        delBtn->setObjectName(QStringLiteral("delBtn"));

        horizontalLayout_20->addWidget(delBtn);

        editBtn = new QPushButton(widget);
        editBtn->setObjectName(QStringLiteral("editBtn"));

        horizontalLayout_20->addWidget(editBtn);


        verticalLayout_13->addWidget(widget);


        horizontalLayout_19->addWidget(groupBox_16);

        taskEditorStack->addWidget(editTaskPage);

        verticalLayout_22->addWidget(taskEditorStack);


        horizontalLayout_4->addWidget(groupBox_29);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1172, 28));
        menuU_togo = new QMenu(menubar);
        menuU_togo->setObjectName(QStringLiteral("menuU_togo"));
        menu = new QMenu(menubar);
        menu->setObjectName(QStringLiteral("menu"));
        menu_2 = new QMenu(menubar);
        menu_2->setObjectName(QStringLiteral("menu_2"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuU_togo->menuAction());
        menubar->addAction(menu->menuAction());
        menubar->addAction(menu_2->menuAction());

        retranslateUi(MainWindow);

        toolBox->setCurrentIndex(0);
        taskEditorStack->setCurrentIndex(0);
        timetabWidget->setCurrentIndex(0);
        timetabWidget_edit->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        groupBoxActList->setTitle(QApplication::translate("MainWindow", "\346\270\205\345\215\225\345\210\227\350\241\250", Q_NULLPTR));
        toolBox->setItemText(toolBox->indexOf(page), QApplication::translate("MainWindow", "\344\270\273\345\234\272\346\231\257", Q_NULLPTR));
        toolBox->setItemText(toolBox->indexOf(page_2), QApplication::translate("MainWindow", "\345\205\266\344\273\226\344\275\215\347\275\256", Q_NULLPTR));
        groupBoxMainScene->setTitle(QApplication::translate("MainWindow", "\344\273\273\345\212\241\346\270\205\345\215\225", Q_NULLPTR));
        groupBox->setTitle(QString());
        label_sceneName->setText(QApplication::translate("MainWindow", "\344\270\273\345\234\272\346\231\257", Q_NULLPTR));
        label_hasOwari->setText(QApplication::translate("MainWindow", "\345\267\262\345\256\214\346\210\220 */*", Q_NULLPTR));
        label_nokorimainTask->setText(QApplication::translate("MainWindow", "\345\211\251\344\275\231\344\270\273\347\272\277 *", Q_NULLPTR));
        label_nokoriLimitedTask->setText(QApplication::translate("MainWindow", "\351\231\220\346\227\266 *", Q_NULLPTR));
        label_nokoriImpTask->setText(QApplication::translate("MainWindow", "\351\207\215\345\244\247\344\272\213\344\273\266", Q_NULLPTR));
        groupBox_2->setTitle(QString());
        groupBox_29->setTitle(QApplication::translate("MainWindow", "\344\273\273\345\212\241\347\256\241\347\220\206", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "\346\267\273\345\212\240\344\273\273\345\212\241", Q_NULLPTR));
        groupBox_4->setTitle(QString());
        isDoneCheckBox->setText(QString());
        label_7->setText(QApplication::translate("MainWindow", "\344\273\273\345\212\241\347\261\273\345\236\213", Q_NULLPTR));
        taskTypeComboBox->clear();
        taskTypeComboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "\344\270\273\347\272\277", Q_NULLPTR)
         << QApplication::translate("MainWindow", "\351\231\220\346\227\266", Q_NULLPTR)
         << QApplication::translate("MainWindow", "\351\207\215\345\244\247\344\272\213\344\273\266", Q_NULLPTR)
        );
        label_6->setText(QApplication::translate("MainWindow", "\346\226\260\344\273\273\345\212\241", Q_NULLPTR));
        groupBox_5->setTitle(QApplication::translate("MainWindow", "\346\227\266\351\227\264\346\270\205\345\215\225", Q_NULLPTR));
        groupBox_9->setTitle(QString());
        groupBox_11->setTitle(QString());
        label_11->setText(QApplication::translate("MainWindow", "\345\217\221\347\224\237\344\272\216", Q_NULLPTR));
        groupBox_10->setTitle(QString());
        label_10->setText(QApplication::translate("MainWindow", "\346\217\220\345\211\215\346\217\220\351\206\222\346\227\266\351\227\264", Q_NULLPTR));
        timetabWidget->setTabText(timetabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "\345\215\225\346\254\241", Q_NULLPTR));
        groupBox_13->setTitle(QString());
        groupBox_14->setTitle(QString());
        label_12->setText(QApplication::translate("MainWindow", "\345\244\251", Q_NULLPTR));
        mon->setText(QApplication::translate("MainWindow", "\346\230\237\346\234\237\344\270\200", Q_NULLPTR));
        tue->setText(QApplication::translate("MainWindow", "\346\230\237\346\234\237\344\272\214", Q_NULLPTR));
        wed->setText(QApplication::translate("MainWindow", "\346\230\237\346\234\237\344\270\211", Q_NULLPTR));
        thu->setText(QApplication::translate("MainWindow", "\346\230\237\346\234\237\345\233\233", Q_NULLPTR));
        fri->setText(QApplication::translate("MainWindow", "\346\230\237\346\234\237\344\272\224", Q_NULLPTR));
        sat->setText(QApplication::translate("MainWindow", "\346\230\237\346\234\237\345\205\255", Q_NULLPTR));
        sun->setText(QApplication::translate("MainWindow", "\346\230\237\346\234\237\346\227\245", Q_NULLPTR));
        groupBox_15->setTitle(QString());
        label_13->setText(QApplication::translate("MainWindow", "\346\227\266\351\227\264", Q_NULLPTR));
        timetabWidget->setTabText(timetabWidget->indexOf(tab_3), QApplication::translate("MainWindow", "\346\257\217\345\244\251", Q_NULLPTR));
        groupBox_6->setTitle(QApplication::translate("MainWindow", "\344\273\273\345\212\241\346\217\217\350\277\260", Q_NULLPTR));
        taskNamePlainTextEdit->setPlainText(QString());
        taskNamePlainTextEdit->setPlaceholderText(QApplication::translate("MainWindow", "\344\273\273\345\212\241\345\220\215\347\247\260", Q_NULLPTR));
        //taskDesTextEdit->setMarkdown(QString());
        taskDesTextEdit->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'SimSun';\"><br /></p></body></html>", Q_NULLPTR));
        taskDesTextEdit->setPlaceholderText(QApplication::translate("MainWindow", "\346\217\217\350\277\260\346\226\207\345\255\227", Q_NULLPTR));
        confirmButton->setText(QApplication::translate("MainWindow", "\345\206\231\345\205\245\346\226\260\344\273\273\345\212\241", Q_NULLPTR));
        backToEditButton->setText(QApplication::translate("MainWindow", "\344\273\273\345\212\241\347\256\241\347\220\206", Q_NULLPTR));
        groupBox_16->setTitle(QApplication::translate("MainWindow", "\344\273\273\345\212\241*", Q_NULLPTR));
        groupBox_17->setTitle(QString());
        isDoneCheckBox_edit->setText(QString());
        label_14->setText(QApplication::translate("MainWindow", "\344\273\273\345\212\241\347\261\273\345\236\213", Q_NULLPTR));
        taskTypeComboBox_edit->clear();
        taskTypeComboBox_edit->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "\344\270\273\347\272\277", Q_NULLPTR)
         << QApplication::translate("MainWindow", "\351\231\220\346\227\266", Q_NULLPTR)
         << QApplication::translate("MainWindow", "\351\207\215\345\244\247\344\272\213\344\273\266", Q_NULLPTR)
        );
        tasknamelabel->setText(QApplication::translate("MainWindow", "\344\273\273\345\212\2411", Q_NULLPTR));
        groupBox_18->setTitle(QApplication::translate("MainWindow", "\346\227\266\351\227\264\346\270\205\345\215\225", Q_NULLPTR));
        groupBox_12->setTitle(QString());
        groupBox_19->setTitle(QString());
        label_15->setText(QApplication::translate("MainWindow", "\345\217\221\347\224\237\344\272\216", Q_NULLPTR));
        groupBox_20->setTitle(QString());
        label_16->setText(QApplication::translate("MainWindow", "\346\217\220\345\211\215\346\217\220\351\206\222\346\227\266\351\227\264", Q_NULLPTR));
        timetabWidget_edit->setTabText(timetabWidget_edit->indexOf(tab_4), QApplication::translate("MainWindow", "\345\215\225\346\254\241", Q_NULLPTR));
        groupBox_21->setTitle(QString());
        groupBox_22->setTitle(QString());
        label_17->setText(QApplication::translate("MainWindow", "\345\244\251", Q_NULLPTR));
        mon_e->setText(QApplication::translate("MainWindow", "\346\230\237\346\234\237\344\270\200", Q_NULLPTR));
        tue_e->setText(QApplication::translate("MainWindow", "\346\230\237\346\234\237\344\272\214", Q_NULLPTR));
        wed_e->setText(QApplication::translate("MainWindow", "\346\230\237\346\234\237\344\270\211", Q_NULLPTR));
        thu_e->setText(QApplication::translate("MainWindow", "\346\230\237\346\234\237\345\233\233", Q_NULLPTR));
        fri_e->setText(QApplication::translate("MainWindow", "\346\230\237\346\234\237\344\272\224", Q_NULLPTR));
        sat_e->setText(QApplication::translate("MainWindow", "\346\230\237\346\234\237\345\205\255", Q_NULLPTR));
        sun_e->setText(QApplication::translate("MainWindow", "\346\230\237\346\234\237\346\227\245", Q_NULLPTR));
        groupBox_23->setTitle(QString());
        label_18->setText(QApplication::translate("MainWindow", "\346\227\266\351\227\264", Q_NULLPTR));
        timetabWidget_edit->setTabText(timetabWidget_edit->indexOf(tab_5), QApplication::translate("MainWindow", "\346\257\217\345\244\251", Q_NULLPTR));
        groupBox_28->setTitle(QApplication::translate("MainWindow", "\344\273\273\345\212\241\346\217\217\350\277\260", Q_NULLPTR));
        taskNamePlainTextEdit_edit->setPlainText(QString());
        taskNamePlainTextEdit_edit->setPlaceholderText(QApplication::translate("MainWindow", "\344\273\273\345\212\241\345\220\215\347\247\260", Q_NULLPTR));
        //taskDesTextEdit_edit->setMarkdown(QString());
        taskDesTextEdit_edit->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'SimSun';\"><br /></p></body></html>", Q_NULLPTR));
        taskDesTextEdit_edit->setPlaceholderText(QApplication::translate("MainWindow", "\346\217\217\350\277\260\346\226\207\345\255\227", Q_NULLPTR));
        addBtn->setText(QApplication::translate("MainWindow", "\346\226\260\345\273\272\344\273\273\345\212\241", Q_NULLPTR));
        delBtn->setText(QApplication::translate("MainWindow", "\345\210\240\351\231\244\344\273\273\345\212\241", Q_NULLPTR));
        editBtn->setText(QApplication::translate("MainWindow", "\347\274\226\350\276\221\344\273\273\345\212\241", Q_NULLPTR));
        menuU_togo->setTitle(QApplication::translate("MainWindow", "U.togo", Q_NULLPTR));
        menu->setTitle(QApplication::translate("MainWindow", "\347\274\226\350\276\221", Q_NULLPTR));
        menu_2->setTitle(QApplication::translate("MainWindow", "\345\270\256\345\212\251", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
