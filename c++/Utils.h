#pragma once
#include <time.h>
#include <string>

using namespace std;

class Utils
{
	public:
		Utils();
		static long getTimeNow();
		static char* convertStringToCharArr(string str);
};

