#ifndef _TIME
#define _TIME
#define _CRT_SECURE_NO_WARNINGS
#include <ctime>
#include <string>

class TimeClock
{
	unsigned int ini_data;
public:
	TimeClock();
	static unsigned int getCurrentTime();
	unsigned int getData();
	int getDifferentMsec(TimeClock t2);
	double getDifferentSec(TimeClock t2);
	int getElapsedMsec();
	double getElapsedSec();
	void restart()
	{
		ini_data = GetTickCount();
	}

};
TimeClock::TimeClock()
{
	ini_data = GetTickCount();
}
unsigned int TimeClock::getCurrentTime()
{
	return GetTickCount();
}
unsigned int TimeClock::getData()
{
	return ini_data;
}
double TimeClock::getDifferentSec(TimeClock t2)
{
	int val1 = ini_data;
	int val2 = t2.ini_data;
	if (val1 > val2)
		return (double(getData()) - double(t2.getData())) / 1000;
	else
		return (double(t2.getData()) - double(getData())) / 1000;
}
int TimeClock::getDifferentMsec(TimeClock t2)
{
	int val1 = ini_data;
	int val2 = t2.ini_data;
	if (val1 > val2)
		return getData() - t2.getData();
	else
		return t2.getData() - getData();
}
int TimeClock::getElapsedMsec()
{
	return GetTickCount() -ini_data;
}
double TimeClock::getElapsedSec()
{
	return (double(GetTickCount()) - double(ini_data)) / 1000;
}

class Time
{
public:
	static std::string CurrentDate()
	{
		char buffer[16];
		char mounth[16];
		time_t seconds = time(NULL);
		tm* timeinfo = localtime(&seconds);
		char* format = "%d";
		strftime(buffer, 16, format, timeinfo);
		format = "%B";
		strftime(mounth, 16, format, timeinfo);
		std::string rez(buffer);
		rez += mounth[0];
		rez += mounth[1];
		rez += mounth[2];
		return rez;
	}
	static std::string Now()
	{
		char buffer[80];
		time_t seconds = time(NULL);
		tm* timeinfo = localtime(&seconds);
		char* format = "%H:%M:%S";
		strftime(buffer, 80, format, timeinfo);
		return std::string(buffer);
	}
};
#endif
