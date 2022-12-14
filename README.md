# U.toGo——UniLife任务管理模块

---

一个简单的任务清单程序，由Imagine Studio PBLF小组驱动.

## 构建这个项目

构建之前，请确保你的计算机上安装了Qt5以上的库与`qmake`，或者成套的[QtCreator](https://qt.io).

QtCreator可以在[官网](https://qt.io)下载。对于Ubuntu用户，如果不想安装QtCreator，可以安装Qt库与`qmake`.以Qt6为例:

```shell
sudo apt install qmake6 qmake6-bin # qmake6
sudo apt install qt6-base-dev 
```

然后，克隆我的项目：

```bash
git clone https://gitee.com/medihbt/utogo.git
```

**对于QtCreator用户**，使用QtCreator打开本地仓库下的`utogo.pro`，构建这个项目即可。

使用QMake：

```bash
qmake6 -o build/Makefile
cd build
make
```

拷贝生成的`utogo-bin`可执行文件到你喜欢的目录，然后就可以使用它了！