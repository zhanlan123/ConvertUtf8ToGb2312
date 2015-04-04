#include <iostream>
#include "Utf8toGb2312.h"

int main()
{
	Configfile *config=new Configfile("cpp,h");

	Utf8toGb2312::GetInstance()->Conv_Utf8_files("D:/TeamTalk_master", config, NULL, true);

	cout << "all done\n";
	
	cout << "i just want to ne a new branch \n";
	system("pause");

	return 0;
}


