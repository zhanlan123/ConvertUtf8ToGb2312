#pragma once

#include <vector>
using namespace std;

static vector<string> system_filter = { "cpp", "h", "txt", "java", "hpp", "php" };

static vector<char> system_splits = {',',' '};//֧��ʹ�ÿո����','�ֿ�

class Configfile
{
public:
	Configfile();
	Configfile(const char* filters);
	void config_filter(const char* filters);//������ʼ�ͻ����룬�ԡ�,������' '�ֿ�
	bool check_file_support(const char* filename);	//�ж��Ƿ���Ҫ�����ļ�
	~Configfile();
private:
	bool check_filter(const char* filter);//�жϸ������ļ������Ƿ�֧��
	char* filter_splite(char* filters);
	vector<string> user_filter;

};

