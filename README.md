# SUB ROV

## *Sub Rov是一个校园水下机器人（上位机）项目*

在opencv分支下，与其他分支最大的不同点是在于：

1. 代码量更少
2. 更容易理解
3. 更容易使用

在opencv分支，我们放弃了之前参考的qgc对于视频流的拉流方法，转而使用opencv来进行拉流。

目前对于udp的测试是通过的，尽管如果你看到详细的代码会觉得我们处理得很直白，但我们相信，只要他是有用的，那就是好的。

</br>

</br>

~~**因为opencv高版本对于库的支持出现了修改，所以我们使用的是如下的依赖:**~~

~~1. opencv：3.4.10~~
~~（很遗憾，尝试了很多次4.5版本都无法正常open VideoCapture）~~

#### 补正：
导致opencv4无法使用Gstreamer模块的原因是官网所下载的opencv环境包里，并没有对于Gstreamer的支持（或者说并没有进行同Gstreamer的交叉编译）。
只需要使用Cmake对Opencv4源码进行编译，增加Gstreamer的选项以及添加Gstreamer的库路径等。
编译、构建后产生的新的opencv库文件，就可以使用了。

> 我猜测是Opencv的官方可能正在逐渐取消对于各个视频流相关套件（FFMPEG、GStreamer）的硬支持。亦或者只是因为使用的人过少，没有进行交叉编译的必要。
> 有需要的人自然会去自己编译。

</br>
</br>
</br>

1. gstreamer：1.18.x（GStreamer版本大于1.16之后便对于项目的影响不大了，我的测试是都可）

	> 尽管在qmake文件里并没有写出对于gstreamer的include、libs依赖路径，但是gstreamer仍然是必须的。
	>
	> 请将其bin文件夹路径存入计算机的环境变量中从而方便识别。

2. OpenCV 3.14（已经可以支持4+版本）

#### *目前存在的问题*

1. 暂时不支持tcp和H265
   > TCP链接在整体框架下是支持的（毕竟只是字符串的修改），基于RTMP和RTSP，

2. 虽然使用QML进行前端设计，但是对于安卓的支持还是很糟糕，在安卓上的运行效果很差。并且安卓OpenCV+GStreamer库的使用存在很多问题。（这可能需要使用Linux进行环境重建才能解决了。

</br>

</br>

</br>

欢迎您在issue中提出意见。