#pragma once
#include <vector>

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
	std::vector<std::string> user_filter;
	
	//初始化system_filter，确定支持需要转换的文件类型，初始化system_splits
	void System_init();
	static bool inited;

	//此处可以改为使用set，但是在vs2008中set<std::string>报错，vs2013通过。
	static std::vector<std::string> system_filter; //系统默认转换的文件类型
	static std::vector<char> system_splits;//支持使用空格或者','分开
};

