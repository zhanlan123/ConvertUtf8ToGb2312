#pragma once
#include <stddef.h>
#include "Configfile.h"

const int BUFFERSIZE 1024

class Utf8toGb2312
{
public:
	static Utf8toGb2312* GetInstance();
	//转换目录下所有文件，cascade设置是否转换子目录下文件，config配置需要转换的文件类型(如cpp)，默认为系统支持的六种文件
	//不能包含中文目录，由于windows目录分隔符使用"\",在c语言系中文转义字符，可以将其改变为"/",或者使用"\\".
	void Conv_Utf8_files(const char* directory_old,const Configfile config,const char* directory_new=NULL,  bool cascade = false);
	//转换单个文件
	void Conv_Utf8_file(const char* directory_old,const char* directory_new, const char* filename);
private:
	static Utf8toGb2312* instance;
	Utf8toGb2312(){}

	bool UTF_8ToGB2312(char*pOut, char *pInput, int pLen);
	int UTF_8ToUnicode(char* pOutput, char *pInput);
	void UnicodeToGB2312(char*pOut, char *pInput);
	//获取utf编码长度
	int enc_get_utf8_size(const unsigned char pInput);
	//查找unicode对应的GB2312码,二分搜索
	unsigned short SearchCodeTable(unsigned short unicode);

};


