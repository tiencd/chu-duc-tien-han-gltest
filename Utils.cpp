#include "Utils.h"
#include <Windows.h>

using namespace std;

Utils::Utils()
{
}

long Utils::getTimeNow() {
	return timeGetTime();
}

char* Utils::convertStringToCharArr(string str){
	char *strTmp =(char *)str.c_str();
	return strTmp;
}