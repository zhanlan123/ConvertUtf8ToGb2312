#include <iostream>
#include "Utf8toGb2312.h"
#include "Configfile.h"
#include "Conv_util.h"

int main()
{
	const char* filter = "h,cpp,cxx,c";
	//TODO: 添加一个文本输入框。
	Configfile config(filter);

	const char *directory = Get_directory(filter);

	if (directory == NULL)
		return 0;

	Utf8toGb2312::GetInstance()->Conv_Utf8_files(directory, config, NULL, true);

	std::cout << "all done\n";

	system("pause");

	return 0;
}


