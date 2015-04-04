# ConvertUtf8ToGb2312
ConvertUtf8ToGb2312

由于linux上使用utf-8编码，sourceinsight并不支持utf-8，使用sourceinsight阅读linux项目源代码时，经常会出现中文乱码，本工程主要用于实现转码功能，将utf-8文件转换为sourceinsight可识别的gb2312编码。

主要有以下功能：
1. 转换当前目录和子目录的文件。
2. 系统默认转换txt, cpp, h, java, hpp, php 六种常见的文件类型。用户可以设置转换六种文件中的一种或者几种，此时系统默认配置失效。当用户配置的文件类型不再这六种之中时，不进行转换。

使用vs2013可直接打开工程，若版本较低新建工程后直接copy添加源文件即可。
