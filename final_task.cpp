#include <iostream>
#include <string>
#include <set>
#include <map>
#include <stdexcept>
#include <sstream>
#include <iomanip>
using namespace std;
struct Date{

	int year = 0,
	    month = 0,
	    day = 0;
}; 
bool operator< (const Date& lhs, const Date& rhs)
{
	if (lhs.year != rhs.year)
        return lhs.year < rhs.year;
    if (lhs.month != rhs.month)
        return lhs.month < rhs.month;
    return lhs.day < rhs.day;
}
istream& operator>> (istream& stream, Date& date)
{
	int year = 0, month = 0, day = 0;
	char d; 
	string input;
	stream >> input;
	stringstream error;
	stringstream input_st(input);
	
	input_st >> year;
	if (input_st.peek() < 0)
	{
		error << "Wrong date format: " << input;
		throw invalid_argument (error.str());
	}
	input_st >> d;
	if (input_st.peek() < 0 || d != '-')
	{
		error << "Wrong date format: " << input;
		throw invalid_argument (error.str());
	}
	input_st >> month;
	if (input_st.peek() < 0)
	{
		error << "Wrong date format: " << input;
		throw invalid_argument (error.str());
	}
	input_st >> d;
	if (input_st.peek() < 0 || d != '-')
	{
		error << "Wrong date format: " << input;
		throw invalid_argument (error.str());
	}
	input_st >> day;
	if (input_st.peek() >= 0)
	{
		error << "Wrong date format: " << input;
		throw invalid_argument (error.str());
	}
	//cout << year << '/' << month << '/' << day << endl;
	if (month < 1 || month > 12)
	{
		error << "Month value is invalid: " << month;
		throw invalid_argument (error.str());
	}
	if (day > 31 || day < 1)
	{
		error << "Day value is invalid: " << day;
		throw invalid_argument (error.str());
	}
	date.year = year;
	date.month = month;
	date.day = day;
	return stream;
}
// ostream& operator<< (ostream& stream, const Date& date)
// {
// 	stream << date.year << "-" << date.month << "-" << date.day;
// 	return stream;
// }

class Calendar
{
public:
	void add_event (const Date& date, const string& event)
	{
		if (event != "")
			data[date].insert(event);
		// for (auto i : data[date])
		// 	cout << i << " ";
		// cout << endl;
	}
	bool del_event (const Date& date, const string& event)
	{
		//cout << "dal event started with date = " << date << " and event = " << event << endl;
		//cout << "&" << data[date].count(event) << endl;
		 if (data.count(date) == 0|| data[date].count(event) == 0)
		{
			cout << "Event not found" << endl;
			return 0;
		}
		else
		{
			data[date].erase(event);
			cout << "Deleted successfully" << endl;
			return 1;
		}
		
	}
	int del_date (const Date& date)
	{
		if (data.count(date) == 0)
		{
			cout << "Deleted 0 events" << endl;
			return 0;
		}
		int n = 0;
		n = data[date].size();
		cout << "Deleted " << n << " events" << endl;
		data.erase(date);
		return n;

		
	}
	void find_event(const Date& date) 
	{
		if (data.count(date) == 0)
			return;
		for (const auto& i : data[date])
		{
			cout << i << endl;
		}
	}
	void print_event() 
	{
		for (auto i : data)
		{
			for (const auto& j : i.second)
			{
				cout << setw(4) << setfill('0') << i.first.year << '-' << setw(2) << setfill('0') << i.first.month << '-' << setw(2) << setfill('0') << i.first.day << ' ';
				cout << j << endl;
			}
		}
		//cout << endl;
	}
private:
	map<Date, set<string>> data;
};

int main() {
	Calendar db;
	Date date;
	string command, event, str;
	while (getline(cin, str)) 
	{
		stringstream stream(str);	
		stream >> command;
		//cout << "command: " << command << endl;
		if (command == "Add")
		{
			try
			{
			stream >> date;
			}
			catch(invalid_argument& report)
			{
				cout << report.what() << endl;
				break;
			}
			stream >> event;
			db.add_event(date, event);
			command = "";
		}
		else if (command == "Del")
		{
			try
			{
			stream >> date;
			}
			catch(invalid_argument& report)
			{
				cout << report.what() << endl;
				break;
			}
			if (stream >> event)
				db.del_event(date, event);
			else
				db.del_date(date);
			command = "";
		}
		else if (command == "Find")
		{
			try
			{
			stream >> date;
			}
			catch(invalid_argument& report)
			{
				cout << report.what() << endl;
				break;
			}
			db.find_event(date);
			command = "";
		}
		else if (command == "Print")
		{
			db.print_event();
			command = "";
		}
		else if (command == "")
			continue;
		else
		{
			cout << "Unknown command: " << command << endl;
			break;
		}
	}

	return 0;
}

/*
Add 1-12-3 e1
Add 1-12-3 e2
Print
Add 1-12-3 e2
Print
Add 12-12-21 e3
Print

Add -1234-1-+23 e1
Add -134-+1-+3 e2
Add -1-1-+2 e3
Add 1234-1-23 e4
Add -1234-1-+23 e5
Add -1234-1-+23 e6
Print
Del 1234-1-23 e4
Print
Del -1234-1-+23


Add -1234-1-+23 e1
Add -134-+1-+3 e2
Add -1-1-+2 e3
Add -1234-1-+23 e5
Add -1234-1-+23 e6
Find -1234-1-+23
Find -1-1-+2
*/