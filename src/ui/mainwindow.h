#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../include/utask_struct.h"
#include "singletaskviewer.h"

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QPushButton>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



    void Refresh();
    void ViewTask(int id);
    void EditTask(TaskNode *L,int id);
    void DelTask(TaskNode *L,int id);
    void ConfirmTask(TaskNode *L, int id);

    //-1:nothing selected
    static int currentSelectedTaskID;
    static QList<SingleTaskViewer*> viewerList;
    Ui::MainWindow *ui;

private:

    void SoloTaskViewer(int id);
    TaskList mainList;
    TaskNode* headNode;

    //system tray
    QSystemTrayIcon *m_sysTrayIcon;
    void initSysTrayIcon();
    QMenu *m_menu;
    QAction *m_showMainAction;
    QAction *m_showWindowAction;
    QAction *m_exitAppAction;

    void createActions();
    void createMenu();
    void switchTaskEditWidget(int index);
    void taskEditFormClr();
    QDateTime dateAndTimeExtract(int* duedate,int* duetime);
    void dateAndTimeInput(QDateTime dateAndTime,int* duedate,int* duetime);

    int hasDoneTaskCount,yetToBeDoneTaskCount;
    int statTaskCount,limitedTaskCount,impTaskCount;

    QLabel* statLabel;

signals:
    void transferData(QList<SingleTaskViewer*>*);

private slots:
    void on_showWindowAction();
    void on_showMainAction();
    void on_exitAppAction();

protected:
    void closeEvent (QCloseEvent *event) override;
    void CheckCurrentTime();
};
#endif // MAINWINDOW_H
