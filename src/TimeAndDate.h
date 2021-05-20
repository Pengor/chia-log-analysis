#ifndef TIME_AND_DATE_H
#define TIME_AND_DATE_H

#include <string>

class TimeAndDate {    
    public:
        static std::string FormatTime(std::string secs_str);
        static std::string FormatDate(std::string date_str);
};

#endif /* TIME_AND_DATE_H */
