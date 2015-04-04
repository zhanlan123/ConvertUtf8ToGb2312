#pragma once

#include <vector>
using namespace std;

static vector<string> system_filter = { "cpp", "h", "txt", "java", "hpp", "php" };

static vector<char> system_splits = {',',' '};//支持使用空格或者','分开

class Configfile
{
public:
	Configfile();
	Configfile(const char* filters);
	void config_filter(const char* filters);//解析初始客户输入，以‘,’或者' '分开
	bool check_file_support(const char* filename);	//判断是否需要解析文件
	~Configfile();
private:
	bool check_filter(const char* filter);//判断给定的文件类型是否支持
	char* filter_splite(char* filters);
	vector<string> user_filter;

};

