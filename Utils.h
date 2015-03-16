#pragma once
#include <time.h>
#include <string>

using namespace std;

class Utils
{
	public:
		Utils();
		static double getTimeToSeconds();
		static char* convertStringToCharArr(string str);
};

