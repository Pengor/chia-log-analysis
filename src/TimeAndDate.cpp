// Convert date and time strings to a friendlier format for .csv files

#include "TimeAndDate.h"
#include <map>

using namespace std;

const map<string,string> MONTHS = {
    {"Jan", "01"},
    {"Feb", "02"},
    {"Mar", "03"},
    {"Apr", "04"},
    {"May", "05"},
    {"Jun", "06"},
    {"Jul", "07"},
    {"Aug", "08"},
    {"Sep", "09"},
    {"Oct", "10"},
    {"Nov", "11"},
    {"Dec", "12"}
};

// Converts a time string to the format hh:mm:ss.mil
string TimeAndDate::FormatTime(string secs_str) {
    string rtn_str = "";

    int seconds = stoi(secs_str);

    // hours
    int hours = seconds / 3600;
    if (hours < 10)
        rtn_str.append("0");
    rtn_str.append(to_string(hours) + ":");

    // minutes
    int minutes = seconds / 60 % 60;
    if (minutes < 10)
        rtn_str.append("0");
    rtn_str.append(to_string(minutes) + ":");

    // seconds
    seconds = seconds % 60;
    if (seconds < 10)
        rtn_str.append("0");
    rtn_str.append(to_string(seconds));
    
    // milliseconds
    rtn_str.append(secs_str.substr(secs_str.find('.')));

    return rtn_str;
}

// Converts a date string to the format YYYY-MM-DD hh:mm:ss
string TimeAndDate::FormatDate(string date_str) {
    string rtn_str = "";
    
    rtn_str.append(date_str.substr(20, 4)); // Year
    rtn_str.append("-");
    rtn_str.append(MONTHS.at(date_str.substr(4, 3))); // Month
    rtn_str.append("-");
    string day = date_str.substr(8, 2); // Day
    if (day[0] == ' ')
        day[0] = '0';
    rtn_str.append(day);
    rtn_str.append(date_str.substr(10, 9)); // Time

    return rtn_str;
}
