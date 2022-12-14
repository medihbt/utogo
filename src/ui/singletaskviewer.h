#ifndef SINGLETASKVIEWER_H
#define SINGLETASKVIEWER_H
#include "ul_rebuild/utask_struct.h"

#include <QWidget>

namespace Ui {
class SingleTaskViewer;
}

class SingleTaskViewer : public QWidget
{
    Q_OBJECT

public:
    explicit SingleTaskViewer(QWidget *parent = nullptr);
    ~SingleTaskViewer();

    void SetTaskViewerValue(int _viewerid,int _id,bool isDone,int taskType,QString taskName,QString date,QString time,TaskInfo _info);
    void SetSelected(bool);

    int id;
    int viewerid;
    bool isSelected;
    TaskInfo info;

    //mouse event
    virtual void mousePressEvent(QMouseEvent *event);

private:
    Ui::SingleTaskViewer *ui;
    void* mainptr;
};

#endif // SINGLETASKVIEWER_H
