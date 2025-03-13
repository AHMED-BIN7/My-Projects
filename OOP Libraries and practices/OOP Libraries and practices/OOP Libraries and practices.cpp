#pragma warning (disable : 4996)
#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include "clsString.h"
#include "clsDate.h"
#include "clsPeriod.h"

using namespace std;

int main()
{
	clsDate::PrintDate(clsDate::GetSystemDate());
	
	return 0;
}

