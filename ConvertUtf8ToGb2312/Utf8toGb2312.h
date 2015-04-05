#pragma once
#include <stddef.h>
#include "Configfile.h"

#define BUFFERSIZE 1024

using namespace std;


class Utf8toGb2312
{
public:
	static Utf8toGb2312* GetInstance();
	//ת��Ŀ¼�������ļ���cascade�����Ƿ�ת����Ŀ¼���ļ���typeΪת���ļ�����(��*.cpp)��Ĭ��Ϊ*.*, �������ļ�
	void Conv_Utf8_files(const char* directory_old,const Configfile *config=NULL,const char* directory_new=NULL,  bool cascade = false);
	void Conv_Utf8_file(const char* directory_old,const char* directory_new, const char* filename);
private:
	static Utf8toGb2312* instance;

	Utf8toGb2312(){}
	bool UTF_8ToGB2312(char*pOut, char *pInput, int pLen);
	int UTF_8ToUnicode(char* pOutput, char *pInput);
	void UnicodeToGB2312(char*pOut, char *pInput);
	//��ȡutf���볤��
	int enc_get_utf8_size(const unsigned char pInput);
	//����unicode��Ӧ��GB2312��,��������
	unsigned short SearchCodeTable(unsigned short unicode);
	//��ȡ�ļ���׺
};


