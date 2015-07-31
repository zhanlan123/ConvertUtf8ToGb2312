# ConvertUtf8ToGb2312

sourceinsight是windows上少有的优秀源码阅读工具，由于linux文件经常使用utf-8编码，而sourceinsight并不支持utf-8，源码中的中文，会因为编码原因难以识别，会出现常见的中文乱码。本工程实现转码功能，将utf-8编码文件转换为Windows平台常见的gb2312编码文件。解决sourceinsight中文乱码问题

### Instructions：
> 1. 转换当前目录和子目录的文件。
> 2. 系统默认转换txt, cpp, h, java, hpp,php
六种常见的文件类型。用户可以设置转换六种文件中的一种或者几种，此时默认配置失效。当自定义配置的文件类型不再这六种之中时，不进行转换。

### Notes：
> 1. 使用vs2013可直接打开工程，若版本较低新建工程后直接copy添加源文件即可。
> 2. 由于使用了windows平台的struct _finddata_t结构，故需要在vc环境下编译。
