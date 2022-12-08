# U.toGo——The simple to-do app

---

一个简单的任务清单程序，由Imagine Studio PBLF小组驱动.

## 如何参与开发流程：

这个仓库现在是私有的.要参与开发, 你应该在这个项目组里(能见到这篇Markdown的应该都在里面了).

你可以直接在Web IDE上编辑代码(然而不推荐), 也可以使用`git`.

### 第一次使用

首先, 进入[这里](https://github.com/settings/tokens?type=beta)新建一个令牌(token).权限设置参考<a href="#permission">末尾</a>的图片. 注意保管好自己的令牌, 每次提交都要用到.

然后, 在你觉得可以的文件夹下打开终端, 克隆这个项目 *(没有`git`的同学在[这里](https://git-scm.com/download/win)下载)* :

```bash
git clone https://gitee.com/medihbt/utogo.git
```

然后`cd utogo`到项目文件夹,开始工作~

### 开发流程

- 纯命令行向:
  
  1. 如果新建了文件,需要`git add <相对路径>/<你的文件>`(太懒的话`cd`到项目根目录,然后`git add ./*`);
  
  2. 提交前记得pull:`git pull`获取最新变更;
  
  3. 然后执行`git commit`,把你的修改提交到本地仓库;
  
  4. 最后`git push`到GitHub仓库上.用户名为`git`,**密码就是你创建的令牌(token)!**

- 编辑器集成向
  
  大多数像VS Code, Visual Studio, QtCreator这样的编辑器/IDE集成了`git`,然而我还没摸熟它们的用法.

## 项目文件夹及作用(待补充)

- `docs`: 项目文档文件夹,存放项目说明及技术信息

- `bootstrap`: 初始化文件夹,用于存放临时代码及实验代码

- `src`: 项目的正式代码

- `build`: 编译生成的文件存放于此, 一般情况下生成的文件不能上传到GitHub

## 开发流程:

详见[`docs/dev-cycle.md`](docs/dev-cycle.md)

## <a id="permission">附: 参考的权限设置</a>