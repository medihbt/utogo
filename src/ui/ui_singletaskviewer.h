/********************************************************************************
** Form generated from reading UI file 'singletaskviewer.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SINGLETASKVIEWER_H
#define UI_SINGLETASKVIEWER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SingleTaskViewer
{
public:
    QHBoxLayout *horizontalLayout;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_2;
    QLabel *isDoneIndicatorLabel;
    QLabel *taskTypeLabel;
    QLabel *taskNameLabel;
    QLabel *taskTimeLabel;

    void setupUi(QWidget *SingleTaskViewer)
    {
        if (SingleTaskViewer->objectName().isEmpty())
            SingleTaskViewer->setObjectName(QStringLiteral("SingleTaskViewer"));
        SingleTaskViewer->resize(1005, 58);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SingleTaskViewer->sizePolicy().hasHeightForWidth());
        SingleTaskViewer->setSizePolicy(sizePolicy);
        SingleTaskViewer->setMaximumSize(QSize(16777215, 200));
        horizontalLayout = new QHBoxLayout(SingleTaskViewer);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        frame = new QFrame(SingleTaskViewer);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::NoFrame);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(2, 2, 2, 2);
        isDoneIndicatorLabel = new QLabel(frame);
        isDoneIndicatorLabel->setObjectName(QStringLiteral("isDoneIndicatorLabel"));
        isDoneIndicatorLabel->setMaximumSize(QSize(50, 16777215));
        isDoneIndicatorLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(isDoneIndicatorLabel);

        taskTypeLabel = new QLabel(frame);
        taskTypeLabel->setObjectName(QStringLiteral("taskTypeLabel"));
        taskTypeLabel->setMaximumSize(QSize(100, 16777215));
        taskTypeLabel->setFrameShape(QFrame::StyledPanel);
        taskTypeLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(taskTypeLabel);

        taskNameLabel = new QLabel(frame);
        taskNameLabel->setObjectName(QStringLiteral("taskNameLabel"));
        QFont font;
        font.setPointSize(20);
        taskNameLabel->setFont(font);

        horizontalLayout_2->addWidget(taskNameLabel);

        taskTimeLabel = new QLabel(frame);
        taskTimeLabel->setObjectName(QStringLiteral("taskTimeLabel"));
        taskTimeLabel->setFrameShape(QFrame::StyledPanel);
        taskTimeLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(taskTimeLabel);


        horizontalLayout->addWidget(frame);


        retranslateUi(SingleTaskViewer);

        QMetaObject::connectSlotsByName(SingleTaskViewer);
    } // setupUi

    void retranslateUi(QWidget *SingleTaskViewer)
    {
        SingleTaskViewer->setWindowTitle(QApplication::translate("SingleTaskViewer", "Form", Q_NULLPTR));
        isDoneIndicatorLabel->setText(QApplication::translate("SingleTaskViewer", "*", Q_NULLPTR));
        taskTypeLabel->setText(QApplication::translate("SingleTaskViewer", "task type", Q_NULLPTR));
        taskNameLabel->setText(QApplication::translate("SingleTaskViewer", "Task*", Q_NULLPTR));
        taskTimeLabel->setText(QApplication::translate("SingleTaskViewer", "date | time ", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SingleTaskViewer: public Ui_SingleTaskViewer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SINGLETASKVIEWER_H
