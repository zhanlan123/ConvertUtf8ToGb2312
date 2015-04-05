#pragma once
#include <stddef.h>
#include "Configfile.h"

#define BUFFERSIZE 1024

using namespace std;


class Utf8toGb2312
{
public:
	static Utf8toGb2312* GetInstance();
	//转换目录下所有文件，cascade设置是否转换子目录下文件，type为转换文件类型(如*.cpp)，默认为*.*, 即所有文件
	void Conv_Utf8_files(const char* directory_old,const Configfile *config=NULL,const char* directory_new=NULL,  bool cascade = false);
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
	//获取文件后缀
};


