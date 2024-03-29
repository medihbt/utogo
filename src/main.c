#include "ui/qt_gui.h"
#include <stdio.h>
#include <string.h>

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

int main(int argc, char *argv[]){
    if ((argc >= 2) && (!strcmp(argv[1], "--help")))
    {
        puts("U.toGo -- UniLife的简单任务清单程序");
        printf("version %s\n", "0.0.1");
        puts("\n本应用程序使用GNU GPLv3许可证. 以下是法律信息（英文）:");
        gplinfo();
        return 0;
    }
    qt_gui_main(argc,argv);
    return 0;
}
