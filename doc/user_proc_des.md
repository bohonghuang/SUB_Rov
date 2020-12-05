# user_proc.dll

自定义库文件`user_proc.dll`放在程序根目录下，如有需要可以自行覆盖该库。

覆盖该库，请务必实现以下函数：

```
extern "C" int  __declspec(dllexport)  frameExchange(cv::Mat & src, cv::Mat & dct);
```

该函数的作用是传入一个`cv::Mat`类型的`src`，返回一个`cv::Mat`类型的`dct`。

参数的名字名没有意义。

程序并不关心覆盖者在该函数中实现了什么，对传入的mat做出了怎样的改变。

但是请注意，请将您实现的算法的时间耗时，控制在一个可以接受的范围之内。



# 使用源代码需要注意

可以将已经编译好的库文件放在路径 `$$PWD/libs/users`下，编译后会自动复制文件到输出路径。
