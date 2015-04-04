#include "Utf8toGb2312.h"
#include "Unicode_Gb2312_Table.h"
#include "File_manage.h"
#include <io.h>
#include <string>
#include <iostream>

Utf8toGb2312* Utf8toGb2312::instance = 0;
Utf8toGb2312* Utf8toGb2312::GetInstance()
{
	if (instance == NULL)
		instance = new Utf8toGb2312();
	return instance;
}

void Utf8toGb2312::Conv_Utf8_files(const char* directory_old,const Configfile* config, const char* directory_new /*= NULL*/, bool cascade /*= false*/)
{
	Configfile *conf = (Configfile *)config;
	if (conf == NULL)
		conf = new Configfile;
	//文件句柄
	long   hFile = 0;
	//文件信息
	struct _finddata_t fileinfo;
	string filespec = string(directory_old).append("/*");
	if ((hFile = _findfirst(filespec.c_str(), &fileinfo)) == -1)
		return;
	do
	{
		if (fileinfo.attrib& _A_SUBDIR)
		{//目录
			if (strcmp(fileinfo.name, ".") == 0 ||			//当前目录
				strcmp(fileinfo.name, "..") == 0 ||			//上级目录
				!cascade)
				continue;
			string cas_old_directory = string(directory_old).append("/").append(fileinfo.name);
			const char* cas_new_directory = NULL;
			if (directory_new != NULL){
				string cas_new_directory_s=string(directory_new).append("/").append(fileinfo.name);
				cas_new_directory = cas_new_directory_s.c_str();
			}
			Conv_Utf8_files(cas_old_directory.c_str(), conf, cas_new_directory, cascade);
		}
		else
		{
			if (conf->check_file_support(fileinfo.name))
				Conv_Utf8_file(directory_old, directory_new, fileinfo.name);
		}
	} while (_findnext(hFile, &fileinfo) == 0);

	_findclose(hFile);
}


void Utf8toGb2312::Conv_Utf8_file(const char* directory_old,const char* directory_new, const char* filename)
{
	string path_old = string(directory_old).append("/").append(filename);
	string tmpfile_name = string(filename).append(".tmp");
	string path_new = directory_new == NULL ? string(path_old).append(".tmp") : string(directory_new).append("/").append(tmpfile_name);
	FILE *tmpfile,*file;
	tmpfile = File_manage::file_open(path_new.c_str(), "w");
	file = File_manage::file_open(path_old.c_str(), "r");
	if ((tmpfile == NULL) || (file==NULL))
		return;

	char buf[BUFFERSIZE], buf2[BUFFERSIZE*6];
	while (fgets(buf, BUFFERSIZE, file))
	{
		memset(buf2, 0, sizeof(buf2));
		UTF_8ToGB2312(buf2, buf, strlen(buf));
		fputs(buf2, tmpfile);
	}
	File_manage::file_close(tmpfile);
	File_manage::file_close(file);

	if ((directory_new==NULL)||(strcmp(directory_old,directory_new)==0))
	{//此处需要替换原文件
		string filename_pre=string(filename).append(".pre");
		string path_pre = string(directory_old).append("/").append(filename_pre);
		File_manage::file_rename(directory_old, filename, filename_pre.c_str());
		File_manage::file_rename(directory_old, tmpfile_name.c_str(), filename);
		File_manage::file_delete(path_pre.c_str());
	}
	else{
		File_manage::file_rename(directory_old, tmpfile_name.c_str(), filename);
	}
}

unsigned short Utf8toGb2312::SearchCodeTable(unsigned short unicode)
{
	int mid, start = 0, end = TABLE_LEN - 1;
	while (start <= end)
	{
		mid = (start + end) / 2;
		if (unicode_gb_table[mid].unicode == unicode)
			return unicode_gb_table[mid].gb2312;
		else if (unicode_gb_table[mid].unicode < unicode)
			start = mid + 1;
		else
			end = mid - 1;
	}
	return 0;
}

int Utf8toGb2312::enc_get_utf8_size(const unsigned char pInput)
{
	int num = 0, temp = 0x80;
	while (temp&pInput)
	{
		num++;
		temp = (temp >> 1);
	}
	return num;
}

int Utf8toGb2312::UTF_8ToUnicode(char* pOutput, char *pInput)
{
	char b1, b2, b3, b4, b5, b6;
	int len = enc_get_utf8_size(*pInput);
	switch (len)
	{
	case 0:
		*pOutput = *pInput;
		len += 1;
		break;
	case 2:
		b1 = *pInput;
		b2 = *(pInput + 1);
		if ((b2 & 0xC0) != 0x80)
			return 0;
		*pOutput = (b1 << 6) + (b2 & 0x3F);
		*(pOutput + 1) = (b1 >> 2) & 0x07;
		break;
	case 3:
		b1 = *pInput;
		b2 = *(pInput + 1);
		b3 = *(pInput + 2);
		if (((b2 & 0xC0) != 0x80) || ((b3 & 0xC0) != 0x80))
			return 0;
		*pOutput = ((b2 & 0x03) << 6) + (b3 & 0x3F);
		*(pOutput + 1) = ((b1 & 0x0F) << 4) | ((b2 >> 2) & 0x0F);
		break;
	case 4:
		b1 = *pInput;
		b2 = *(pInput + 1);
		b3 = *(pInput + 2);
		b4 = *(pInput + 3);
		if (((b2 & 0xC0) != 0x80) || ((b3 & 0xC0) != 0x80)
			|| ((b4 & 0xC0) != 0x80))
			return 0;
		*pOutput = (b3 << 6) + (b4 & 0x3F);
		*(pOutput + 1) = (b2 << 4) + ((b3 >> 2) & 0x0F);
		*(pOutput + 2) = ((b1 << 2) & 0x1C) + ((b2 >> 4) & 0x03);
		break;
	case 5:
		b1 = *pInput;
		b2 = *(pInput + 1);
		b3 = *(pInput + 2);
		b4 = *(pInput + 3);
		b5 = *(pInput + 4);
		if (((b2 & 0xC0) != 0x80) || ((b3 & 0xC0) != 0x80)
			|| ((b4 & 0xC0) != 0x80) || ((b5 & 0xC0) != 0x80))
			return 0;
		*pOutput = (b4 << 6) + (b5 & 0x3F);
		*(pOutput + 1) = (b3 << 4) + ((b4 >> 2) & 0x0F);
		*(pOutput + 2) = (b2 << 2) + ((b3 >> 4) & 0x03);
		*(pOutput + 3) = (b1 << 6);
		break;
	case 6:
		b1 = *pInput;
		b2 = *(pInput + 1);
		b3 = *(pInput + 2);
		b4 = *(pInput + 3);
		b5 = *(pInput + 4);
		b6 = *(pInput + 5);
		if (((b2 & 0xC0) != 0x80) || ((b3 & 0xC0) != 0x80)
			|| ((b4 & 0xC0) != 0x80) || ((b5 & 0xC0) != 0x80)
			|| ((b6 & 0xC0) != 0x80))
			return 0;
		*pOutput = (b5 << 6) + (b6 & 0x3F);
		*(pOutput + 1) = (b5 << 4) + ((b6 >> 2) & 0x0F);
		*(pOutput + 2) = (b3 << 2) + ((b4 >> 4) & 0x03);
		*(pOutput + 3) = ((b1 << 6) & 0x40) + (b2 & 0x3F);
		break;
	default:
		break;
	}
	return len;
}

void Utf8toGb2312::UnicodeToGB2312(char*pOut, char *pInput)
{
	unsigned short tmp, gb2312_tmp;
	memcpy(&tmp, pInput, 2);
	gb2312_tmp = SearchCodeTable(tmp);

	gb2312_tmp = (gb2312_tmp >> 8 | gb2312_tmp << 8);//调整为大端，大地址存高位，小地址存低位

	memcpy(pOut, &gb2312_tmp, 2);
}

void Utf8toGb2312::UTF_8ToGB2312(char*pOut, char *pInput, int pLen)
{
	int res, i = 0, j = 0, num = 0;
	char tempbuf[2];
	memset(tempbuf, 0, sizeof(tempbuf));
	while (i < pLen)
	{
		res = UTF_8ToUnicode(tempbuf, pInput + i);
		if (res <= 0)
			return;
		else if (res == 1)
		{
			*(pOut + j) = *(pInput + i);
			j += 1;

		}
		else{
			UnicodeToGB2312(pOut + j, tempbuf);
			j += 2;
			num++;
		}
		i += res;
	}
}


