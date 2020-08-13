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

==因为opencv高版本对于库的支持出现了修改，所以我们使用的是如下的依赖：==

1. opencv：3.4.10

2. gstreamer：1.16

	> 尽管在qmake文件里并没有写出对于gstreamer的include、libs依赖路径，但是gstreamer仍然是必须的。
	>
	> 请将其bin文件夹路径存入计算机的环境变量中从而方便识别。



欢迎您在issue中提出意见。