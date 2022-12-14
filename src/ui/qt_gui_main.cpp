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

void gplinfo(void)
{
    puts("Copyright (c) 2022-2023 Imagine Studio PBLF Group.");
    puts("This program is free software: you can redistribute it and/or modify");
    puts("it under the terms of the GNU General Public License as published by");
    puts("the Free Software Foundation, either version 3 of the License, or");
    puts("(at your option) any later version.");

    puts("This program is distributed in the hope that it will be useful,");
    puts("but WITHOUT ANY WARRANTY; without even the implied warranty of");
    puts("MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the");
    puts("GNU General Public License for more details.");

    puts("You should have received a copy of the GNU General Public License");
    puts("along with this program.  If not, see <https://www.gnu.org/licenses/>.");
}
