#pragma once
#include <tchar.h>


//Ñ¡ÔñÄ¿Â¼
const char*  Get_directory(const char* filter);

const char* Get_filters();

void TcharToChar(const TCHAR * tchar, char * _char);
void pcharToWStr(const char *pchar, wchar_t *wchar);