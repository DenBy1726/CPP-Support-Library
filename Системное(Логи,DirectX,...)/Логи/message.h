#ifndef _MESSAGE
#define _MESSAGE
#include <string.h>
#include <stdarg.h>
#include <iostream>
#include "timeclock.h"
#include <vector>

class Message
{
public :
	static std::string GetLog(std::string message, ...)
	{
		va_list args;
		int first = 0;
		int int_val = 0;
		double d_val = 0;
		std::string s_val("");
		va_start(args, message);
		std::string res;
		for (int i = 0; i < message.size(); i++)
		{
			if (message[i] == '%')
			{
				if (++i < message.size())
				{
					switch (message[i])
					{
					case 'i':
					{
								int_val = va_arg(args, int);
								res += ItoS(int_val);
								break;
					}
					case 'd':
					{
								d_val = va_arg(args, double);
								res += ItoS(d_val);
								break;
					}
					case 's':
					{
								s_val = va_arg(args, std::string);
								res += s_val;
								break;
					}
					default:
					{
							   res += ("%" + message[i]);
					}
					}
				}
			}
			else res += message[i];
		}
		res += '\n';
		return std::string(Time::CurrentDate() + " " + Time::Now() +  " | " +res);
	}
	static void Log(std::string message,...)
	{
		va_list args;
		int first = 0;
		int int_val = 0;
		double d_val = 0;
		std::string s_val("");
		va_start(args, message);
		std::string res;
		std::cout << Time::CurrentDate() << " " << Time::Now() << " | ";
		for (int i = 0; i < message.size(); i++)
		{
			if (message[i] == '%')
			{
				if (++i < message.size())
				{
					switch (message[i])
					{
					case 'i':
					{
								int_val = va_arg(args, int);
								res += ItoS(int_val);
								break;
					}
					case 'd':
					{
								d_val = va_arg(args, double);
								res += ItoS(d_val);
								break;
					}
					case 's':
					{
								s_val = va_arg(args, std::string);
								res += s_val;
								break;
					}
					default:
					{
							   res += "%";
							   res += message[i];
					}
					}
				}
			}
			else res += message[i];
		}
		res += '\n';
		HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
		
		for (int i = 0; i < res.size(); i++)
		{
			if (res[i] == '%')
			{
				if (++i < res.size())
				{
					switch (res[i])
					{
					case 'r':
					{
								SetConsoleTextAttribute(console, FOREGROUND_RED);
								break;
					}
					case 'g':
					{
								SetConsoleTextAttribute(console, FOREGROUND_GREEN);
								break;
					}
					case 'w':
					{
								SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
								break;
					}
					default:
					{
							   std::cout << "%" << res[i];
					}
					}
				}
			}
			else
			{
				std::cout << res[i];
			}
			
		}
		SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	}
	static void printTable(std::vector<std::string> data, int columns, int rows, std::vector<std::string> headerAr, std::vector<std::string> leafterAr)
	{
		std::cout << "   ";
		for (int i = 0; i < columns; i++)
		{
			std::cout << headerAr[i] << "   ";
		}
		std::cout << std::endl;
		for (int i = 0,counter = 0; i < rows; i++)
		{
			std::cout << leafterAr[i] << "   ";
			for (int j = 0; j < columns; j++,counter++)
			{
				std::cout << data[counter] << "   ";
			}
			std::cout << std::endl;
		}

	}

};
#endif