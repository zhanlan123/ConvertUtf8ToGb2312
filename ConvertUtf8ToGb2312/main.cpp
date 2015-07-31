#include <iostream>
#include "Utf8toGb2312.h"
#include "Configfile.h"

int main()
{
	Configfile config("cpp,h");

    //不能包含中文目录，由于windows目录分隔符使用"\",在c语言系中文转义字符，可以将其改变"/",或者使用"\\".
	Utf8toGb2312::GetInstance()->Conv_Utf8_files("F:/chrome download/Compressed/ConvertUtf8ToGb2312-master/ConvertUtf8ToGb2312", config, NULL, true);

	std::cout << "all done\n";

	system("pause");

	return 0;
}


