# U.toGo——UniLife任务管理模块

---

一个简单的任务清单程序，由Imagine Studio PBLF小组驱动.

## 构建这个项目

构建之前，请确保你的计算机上安装了Qt5以上的库与`qmake`，或者成套的[QtCreator](https://qt.io).

QtCreator可以在[官网](https://qt.io)下载。对于Ubuntu用户，如果不想安装QtCreator，可以安装Qt库与`qmake`.以Qt6为例:

```shell
sudo apt install qt6-base-dev-tools qmake6 qmake6-bin # qmake6
sudo apt install qt6-base-dev libqt6opengl6-dev qt6-wayland-dev libfcitx5-qt6-dev # 编译所需的库
sudo apt install libqt6core6 libqt6gui6 libqt6dbus6 qt6-wayland # 运行所需的库
```

然后，克隆我的项目：

```bash
git clone https://gitee.com/medihbt/utogo.git
```

**对于QtCreator用户**，使用QtCreator打开本地仓库下的`utogo.pro`，构建这个项目即可。

使用QMake：

```bash
# 在项目根目录下:
mkdir build/
qmake6 -o build/Makefile
cd build
make
```

或者直接运行项目根目录下的`build.sh`即可。

拷贝生成的`utogo-bin`可执行文件到你喜欢的目录，然后就可以使用它了！

## 鸣谢

我在我们的PBLF大作业立项以前就有写一个任务管理程序的想法，而这个项目的实现离不开以下几位同学（以下示Gitee网名）。他们在PBLF期间作出了很大贡献:

[[楚楚](https://gitee.com/aimvim)] -- 任务清单的数据结构实现

[[yudanzhizhi](https://gitee.com/yudanz)] -- 文件IO部分与杂项代码的实现

[[田所浩二](https://gitee.com/tadokoro_kouji)] -- 前端代码的实现

[[丁嘉茵](https://gitee.com/johndingjiayin)] -- 文档的编写
