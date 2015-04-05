#include <iostream>
#include "Utf8toGb2312.h"

int main()
{
	Configfile *config=new Configfile("cpp,h");


	Utf8toGb2312::GetInstance()->Conv_Utf8_files("D:/shuju", config, NULL, true);

	cout << "all done\n";

	system("pause");

	return 0;
}


