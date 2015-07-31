#include "Configfile.h"
#include <string.h>
#include <stdio.h>

using std::string;
using std::set;

bool Configfile::inited = false;
set<string> Configfile::system_filter;
set<char> Configfile::system_splits;

Configfile::Configfile(const char* filters)
{
	config_filter(filters);
}

Configfile::Configfile()
{
	config_filter(NULL);
}


Configfile::~Configfile()
{
}

void Configfile::config_filter(const char* filters_in)
{
	if (!inited)
		System_init();
	if (filters_in == NULL || strcmp(filters_in, "*") == 0)
	{
		user_filter = system_filter;
		return;
	}
	user_filter.clear();

	char filter_buf[100];
	sprintf_s(filter_buf, sizeof(filter_buf), "%s", filters_in);

	char *p = 0, *pstart = filter_buf;
	for (;;)
	{
		p = filter_splite(pstart);	//找到第一个分割符
		if (p == NULL)
		{
			if (check_filter(pstart))
				user_filter.insert(pstart);
			break;
		}
		else
		{
			*p = 0;
			if (check_filter(pstart))
				user_filter.insert(pstart);
			pstart = p + 1;
		}
	}
}

bool Configfile::check_filter(const char* filter) const
{//判断给定的文件类型是否支持

	set<string>::const_iterator iter = system_filter.find(filter);
	if (iter == system_filter.end())
		return false;
	return true;
}

char* Configfile::filter_splite(char* filters) const
{
	char* result = NULL, *p;
	set<char>::const_iterator iter = system_splits.begin();
	for (; iter != system_splits.end(); iter++)
	{
		p = strchr(filters, *iter);
		if ((p != NULL) && ((result == NULL) || (p < result)))
			result = p;
	}

	return result;
}
void Configfile::System_init()
{
	system_filter.insert("h");	
	system_filter.insert("c");
	system_filter.insert("cxx");
	system_filter.insert("hpp");
	system_filter.insert("cpp");
	system_filter.insert("txt");
	system_filter.insert("java");
	system_filter.insert("php");


	system_splits.insert(',');
	system_splits.insert(' ');

	inited = true;
}

bool Configfile::check_file_support(const char* filename) const
{
	const char *p = NULL;

	if ((p = strrchr(filename, '.')) == NULL)
		return false;
	p++;

	set<string>::const_iterator iter = user_filter.find(p);;

	if (iter == user_filter.end())
		return false;
	return true;
}


