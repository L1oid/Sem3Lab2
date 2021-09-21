#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <chrono>
using namespace std;

int charToNum(char);
bool DimArr(int&);
bool GetFile(int*&);
void allinfo(int&, int, int*&);
void sortinfo(int&, int, int*&);

class datetime
{
public:
	int second;
	int minute;
	int hour;
	int day;
	int month;
	int year;
	void Out();
	void NextDate(int& i, int n, int*& arr, int key);
	void PrevDate(int& i, int n, int*& arr);
	void SysTime();
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

	if(sysDate[4] == 'J') 
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

void datetime::Out()
{
	cout << "Date: " << day << "." << month << "." << year << " Time: " << hour << ":" << minute << ":" << second;
}

void datetime::NextDate(int& i, int n, int*& arr, int key)
{
	datetime temp;
	if (key == 1)
	{
		i = i + 6;
		if (i < n)
		{
			cout << " - ";
			day = arr[i];
			month = arr[i + 1];
			year = arr[i + 2];
			hour = arr[i + 3];
			minute = arr[i + 4];
			second = arr[i + 5];
			Out();
		}
	}
	if (key == 2)
	{
		temp.day = arr[i];
		temp.month = arr[i + 1];
		temp.year = arr[i + 2];
		temp.hour = arr[i + 3];
		temp.minute = arr[i + 4];
		temp.second = arr[i + 5];
		i = i + 6;
		if (i < n)
		{
			day = arr[i];
			month = arr[i + 1];
			year = arr[i + 2];
			hour = arr[i + 3];
			minute = arr[i + 4];
			second = arr[i + 5];
			if (temp.year < year || temp.year > year)
			{
				temp.Out();
				cout << " - ";
				Out();
				cout << endl;
			}
		}
	}
}

void datetime::PrevDate(int& i, int n, int*& arr)
{
	if (i - 6 != 0)
	{
		i = i - 12;
		cout << " - ";
		day = arr[i];
		month = arr[i + 1];
		year = arr[i + 2];
		hour = arr[i + 3];
		minute = arr[i + 4];
		second = arr[i + 5];
		i = i + 12;
		Out();
	}
}

struct timedelta 
{
	int second;
	int minute;
	int hour;
	int day;
	int month;
	int year;

	void Out();
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

void timedelta::Out()
{
	cout << "Date: " << day << "." << month << "." << year << " Time: " << hour << ":" << minute << ":" << second;
}

int main()
{
	datetime data;
	datetime d1, d2;
	timedelta delta, t2;
	int n = 0, i = 0;
	DimArr(n);
	int *arr = new int[n];
	GetFile(arr);
	int key = 0;
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
			allinfo(i, n, arr);
			cout << endl;
			break;
		case 2:
			i = 0;
			sortinfo(i, n, arr);
			cout << endl;
			break;
		case 3:
			data.SysTime();
			data.Out();
			cout << endl;
			break;
		case 4:
			d1.day = arr[i];
			d1.month = arr[i + 1];
			d1.year = arr[i + 2];
			d1.hour = arr[i + 3];
			d1.minute = arr[i + 4];
			d1.second = arr[i + 5];
			d2.day = arr[i + 6];
			d2.month = arr[i + 7];
			d2.year = arr[i + 8];
			d2.hour = arr[i + 9];
			d2.minute = arr[i + 10];
			d2.second = arr[i + 11];
			delta.minus(d1, d2);
			delta.Out();
			cout << endl;
			d1 = delta.timePlus(d1);
			d1.Out();
			cout << endl;
			t2.day = 3;
			t2.month = 5;
			t2.year = -1;
			t2.hour = -4;
			t2.minute = 5;
			t2.second = -15;
			delta.DeltaPlusDelta(t2);
			delta.Out();
			cout << endl;
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

int charToNum(char str) 
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

void allinfo(int& i, int n, int*& arr)
{
	datetime data;
	while (i < n)
	{
		data.day = arr[i];
		data.month = arr[i + 1];
		data.year = arr[i + 2];
		data.hour = arr[i + 3];
		data.minute = arr[i + 4];
		data.second = arr[i + 5];
		data.Out();
		data.NextDate(i, n, arr, 1);
		data.PrevDate(i, n, arr);
		cout << endl;
	}
}

void sortinfo(int& i, int n, int*& arr)
{
	datetime data;
	while (i < n)
	{
		data.NextDate(i, n, arr, 2);
	}
}

bool DimArr(int& n)
{
	datetime data;
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

bool GetFile(int*& arr)
{
	datetime data;
	int temp, i = 0;
	ifstream F("Date.txt");
	if (!F)
	{
		cout << "Cant find file" << endl;
		return false;
	}
	while (F >> temp)
	{
		arr[i] = temp;
		i++;
	}
	F.close();
	return true;
}