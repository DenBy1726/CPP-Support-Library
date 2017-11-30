#include <ctime>
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

};
TimeClock::TimeClock()
{
	ini_data = clock();
}
unsigned int TimeClock::getCurrentTime()
{
	return clock();
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
		return (double(getData()) - double(t2.getData()))/1000;
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
	return clock() - ini_data;
}
double TimeClock::getElapsedSec()
{
	return (double(clock()) - double(ini_data))/1000;
}