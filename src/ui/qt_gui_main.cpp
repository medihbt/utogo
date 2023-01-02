#include "mainwindow.h"
#include "qt_gui.h"

#include <QApplication>
#include <QStyleFactory>
#include <QDebug>

int qt_gui_main(int argc, char *argv[])
{ 
    QApplication a(argc, argv);  
    QApplication::setStyle(QStyleFactory::create("Fusion"));
    QFont font;
    font.setFamily("Microsoft YaHei");
    a.setFont(font);
    MainWindow w;
    w.show();
    return a.exec();
}
