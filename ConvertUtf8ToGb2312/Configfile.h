#pragma once

#include <vector>
using namespace std;

static vector<string> system_filter = { "cpp", "h", "txt", "java", "hpp", "php" };

static vector<char> system_splits = {',',' '};//支持使用空格或者','分开

class Configfile
{
public:
	Configfile();
	explicit Configfile(const char* filters);
	
	//配置需要转换的文件类型(必须在system_filter中)，以‘,’或者' '分开
	//为空则是system_filter中所有的文件类型。
	void config_filter(const char* filters);
	
	//判断文件的类型是否在user_filter中
	bool check_file_support(const char* filename) const;
	~Configfile();
private:
	//判断类型是否在system_filter中
	bool check_filter(const char* filter) const;
	
	//使用system_splits中的分隔符分割字符串，返回指向字符串中第一个分隔符的指针，或者返回NULL
	char* filter_splite(char* filters) const;
	vector<string> user_filter;
};

