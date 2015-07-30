#include <iostream>
#include "Utf8toGb2312.h"

int main()
{
	Configfile config("cpp,h");

        
        //不能包含中文目录，由于windows目录分隔符使用"\",在c语言系中文转义字符，可以将其改变"/",或者使用"\\".
	Utf8toGb2312::GetInstance()->Conv_Utf8_files("D:/shuju", config, NULL, true);


	cout << "all done\n";

	system("pause");

	return 0;
}


