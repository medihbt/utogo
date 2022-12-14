#include "ui/qt_gui.h"
#include <stdio.h>
#include <string.h>

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
