#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <chrono>
using namespace std;

class datetime
{
public:
	int second;
	int minute;
	int hour;
	int day;
	int month;
	int year;

	datetime NextDate(int& i, int n, datetime*& arrd, int key);
	datetime PrevDate(int& i, int n, datetime*& arrd);
	void SysTime();
	int charToNum(char str);
};

void datetime::SysTime()
{
	auto const time = chrono::system_clock::now();
	time_t seconds = chrono::system_clock::to_time_t(time);

	std::stringstream ss;
	ss << ctime(&seconds);
	std::string sysDate = ss.str();

	if (charToNum(sysDate[8]) != 404) day = charToNum(sysDate[8]);
	else day = 0;
	day = day * 10 + charToNum(sysDate[9]);

	if (sysDate[4] == 'J')
	{
		if (sysDate[5] == 'a') month = 1;
		else
		{
			if (sysDate[6] == 'n') month = 6;
			else month = 7;
		}
	}
	else if (sysDate[4] == 'F') month = 2;
	else if (sysDate[4] == 'M')
	{
		if (sysDate[6] == 'r') month = 3;
		else month = 5;
	}
	else if (sysDate[4] == 'A')
	{
		if (sysDate[5] == 'p') month = 4;
		else month = 8;
	}
	else if (sysDate[4] == 'S') month = 9;
	else if (sysDate[4] == 'O') month = 10;
	else if (sysDate[4] == 'N') month = 11;
	else if (sysDate[4] == 'D') month = 12;

	year = charToNum(sysDate[20]) * 10;
	year = (year + charToNum(sysDate[21])) * 10;
	year = (year + charToNum(sysDate[22])) * 10;
	year += charToNum(sysDate[23]);

	hour = charToNum(sysDate[11]) * 10;
	hour += charToNum(sysDate[12]);

	minute = charToNum(sysDate[14]) * 10;
	minute += charToNum(sysDate[15]);

	second = charToNum(sysDate[17]) * 10;
	second += charToNum(sysDate[18]);
}

int datetime::charToNum(char str)
{
	if (str == '0') return 0;
	else if (str == '1') return 1;
	else if (str == '2') return 2;
	else if (str == '3') return 3;
	else if (str == '4') return 4;
	else if (str == '5') return 5;
	else if (str == '6') return 6;
	else if (str == '7') return 7;
	else if (str == '8') return 8;
	else if (str == '9') return 9;

	return 404;
}

datetime datetime::NextDate(int& i, int n, datetime*& arrd, int key)
{
	datetime d1 = { 0,0,0,0,0,0 };
	if (key == 1)
	{
		i = i + 1;
		if (i < (n / 6))
		{
			return arrd[i];
		}
		return d1;
	}
	if (key == 2)
	{
		if (i < (n / 6) - 1)
		{
			if (arrd[i].year != arrd[i + 1].year)
			{
				return arrd[i + 1];
			}
		}
		return d1;
	}
	return d1;
}

datetime datetime::PrevDate(int& i, int n, datetime*& arrd)
{
	datetime d1 = { 0,0,0,0,0,0 };
	if (i - 1 != 0)
	{
		return arrd[i - 2];
	}
	return d1;
}

class timedelta
{
public:
	int second;
	int minute;
	int hour;
	int day;
	int month;
	int year;

	void minus(datetime t1, datetime t2);
	datetime timePlus(datetime t1);
	void DeltaPlusDelta(timedelta d);
};

void timedelta::minus(datetime t1, datetime t2)
{
	second = t1.second - t2.second;
	minute = t1.minute - t2.minute;
	hour = t1.hour - t2.hour;
	day = t1.day - t2.day;
	month = t1.month - t2.month;
	year = t1.year - t2.year;
}

datetime timedelta::timePlus(datetime t1)
{
	t1.second -= second;
	t1.minute -= minute;
	t1.hour -= hour;
	t1.day -= day;
	t1.month -= month;
	t1.year -= year;
	return t1;
}

void timedelta::DeltaPlusDelta(timedelta t2)
{
	second += t2.second;
	minute += t2.minute;
	hour += t2.hour;
	day += t2.day;
	month += t2.month;
	year += t2.year;
}

class application
{
	datetime temp, data, d1 , d2;
	timedelta delta, t2;
	int* arr;
	datetime* arrd;
	int n = 0, i = 0;
	int key = 0;
public:
	application()
	{

	}
	application(datetime &temp, int& k, int*& arr)
	{
		
		temp.day = arr[k];
		temp.month = arr[k + 1];
		temp.year = arr[k + 2];
		temp.hour = arr[k + 3];
		temp.minute = arr[k + 4];
		temp.second = arr[k + 5];
	}
	application(int n, int*& arr, datetime*& arrd)
	{
		arr = new int[n];
		arrd = new datetime[n / 6];
	}
	application(datetime& d1, datetime& d2, datetime*& arrd)
	{

		d1 = arrd[i];
		d2 = arrd[i + 1];
	}
	void start();
	bool DimArr(int& n);
	void allinfo(int& i, int n, datetime*& arrd);
	void sortinfo(int& i, int n, datetime*& arrd);
	bool GetFile(int*& arr, datetime*& arrd);
};

void application::start()
{
	DimArr(n);
	application(n, arr, arrd);
	GetFile(arr, arrd);
	do
	{
		cout << "1) Info output" << endl
			<< "2) Op. 2 Info output" << endl
			<< "3) System Date" << endl
			<< "4) Timedelta" << endl
			<< "0) Exit" << endl;
		cout << endl << "Select an action: ";
		cin >> key;
		cout << endl;
		switch (key)
		{
		case 1:
			i = 0;
			allinfo(i, n, arrd);
			cout << endl;
			break;
		case 2:
			i = 0;
			sortinfo(i, n, arrd);
			cout << endl;
			break;
		case 3:
			data.SysTime();
			cout << data.day << ":";
			cout << data.month << ":";
			cout << data.year << " ";
			cout << data.hour << ":";
			cout << data.minute << ":";
			cout << data.second;
			cout << endl << endl;
			break;
		case 4:
			application(d1, d2, arrd);
			delta.minus(d1, d2);
			cout << delta.day << ":";
			cout << delta.month << ":";
			cout << delta.year << " ";
			cout << delta.hour << ":";
			cout << delta.minute << ":";
			cout << delta.second;
			cout << endl;
			d1 = delta.timePlus(d1);
			cout << d1.day << ":";
			cout << d1.month << ":";
			cout << d1.year << " ";
			cout << d1.hour << ":";
			cout << d1.minute << ":";
			cout << d1.second;
			cout << endl;
			t2.day = 3;
			t2.month = 5;
			t2.year = -1;
			t2.hour = -4;
			t2.minute = 5;
			t2.second = -15;
			delta.DeltaPlusDelta(t2);
			cout << delta.day << ":";
			cout << delta.month << ":";
			cout << delta.year << " ";
			cout << delta.hour << ":";
			cout << delta.minute << ":";
			cout << delta.second;
			cout << endl << endl;
			break;
		default:
			if (key != 0)
			{
				cout << "There is no such action !" << endl << endl;
			}
			break;
		}
	} while (key != 0);
	delete[] arr;
}

bool application::DimArr(int& n)
{
	int temp;
	ifstream F("Date.txt");
	if (!F)
	{
		cout << "Cant find file" << endl;
		return false;
	}
	while (F >> temp)
	{
		n++;
	}
	F.close();
	return true;
}

void application::allinfo(int& i, int n, datetime*& arrd)
{
	while (i < (n / 6))
	{
		cout << arrd[i].day << ":";
		cout << arrd[i].month << ":";
		cout << arrd[i].year << ":";
		cout << arrd[i].second << ":";
		cout << arrd[i].minute << ":";
		cout << arrd[i].hour;
		d1 = data.NextDate(i, n, arrd, 1);
		if (d1.day > 0)
		{
			cout << " - ";
			cout << d1.day << ":";
			cout << d1.month << ":";
			cout << d1.year << ":";
			cout << d1.second << ":";
			cout << d1.minute << ":";
			cout << d1.hour;
		}
		d1 = data.PrevDate(i, n, arrd);
		if (d1.day > 0)
		{
			cout << " - ";
			cout << d1.day << ":";
			cout << d1.month << ":";
			cout << d1.year << ":";
			cout << d1.second << ":";
			cout << d1.minute << ":";
			cout << d1.hour;
		}
		cout << endl;
	}
}

void application::sortinfo(int& i, int n, datetime*& arrd)
{
	while (i < (n / 6) - 1)
	{
		data = data.NextDate(i, n, arrd, 2);
		if (data.day > 0)
		{
			cout << arrd[i].day << ":";
			cout << arrd[i].month << ":";
			cout << arrd[i].year << ":";
			cout << arrd[i].second << ":";
			cout << arrd[i].minute << ":";
			cout << arrd[i].hour;
			cout << " - ";
			cout << data.day << ":";
			cout << data.month << ":";
			cout << data.year << ":";
			cout << data.second << ":";
			cout << data.minute << ":";
			cout << data.hour;
			cout << endl;
		}
		i = i + 1;
	}
}

bool application::GetFile(int*& arr, datetime*& arrd)
{
	int temp1, i = 0;
	ifstream F("Date.txt");
	if (!F)
	{
		cout << "Cant find file" << endl;
		return false;
	}
	while (F >> temp1)
	{
		arr[i] = temp1;
		i++;
	}
	int k = 0;
	for (int j = 0; j < (i / 6); j++)
	{
		application(temp, k, arr);
		k = k + 6;
		arrd[j] = temp;
	}
	F.close();
	return true;
}

int main()
{
	application app;
	app.start();
}