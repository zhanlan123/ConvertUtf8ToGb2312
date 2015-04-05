#include "Configfile.h"
#include <string.h>
#include <stdio.h>

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
				user_filter.push_back(pstart);
			break;
		}
		else
		{
			*p = 0;
			if (check_filter(pstart))
				user_filter.push_back(pstart);
			pstart = p + 1;
		}
	}
}

bool Configfile::check_filter(const char* filter) const
{//判断给定的文件类型是否支持
	bool result=false;
	vector<string>::const_iterator iter = system_filter.begin();
	for (; iter != system_filter.end();iter++)
	{
		if (strcmp(iter->c_str(), filter) == 0)
		{
			result = true;
			break;
		}
	}
	return result;
}

char* Configfile::filter_splite(char* filters) const
{
	char* result = NULL,*p;
	vector<char>::const_iterator iter=system_splits.begin();
	for (; iter != system_splits.end();iter++)
	{
		p = strchr(filters, *iter);
		if ((p != NULL) && ((result == NULL) ||(p < result) ))
			result = p;
	}

	return result;
}

bool Configfile::check_file_support(const char* filename) const
{
	const char *pre = NULL, *p = filename;

	while ((p = strchr(p,'.'))!=NULL)
	{
		pre = ++p;
	}
	if (pre == NULL)
		return false;

	vector<string>::const_iterator iter=user_filter.begin();
	for (; iter != user_filter.end();iter++)
	{
		if (strcmp(iter->c_str(), pre) == 0)
			return true;
	}

	return false;

}


