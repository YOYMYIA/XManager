#ifndef __MODUO_DATA_H__
#define __MODUO_DATA_H__

#include "copyable.h"
#include "Types.h"

struct tm;

namespace muduo
{

class Date : public muduo::copyable
{
public:
    struct YearMonthDay
    {
        int year;   //[1900, +NAN)
        int month;
        int day;
    };

    static const int kDaysPerWeek = 7;
    static const int kJulianDayOf1970_01_01;

    Date () : julianDayNumber_(0) {}

    //constucts a yyyy-mm-dd Date
    Date (int year, int month, int day);

    //constucts a date from julian Day Number
    explicit Date(int julianDayNum) : julianDayNumber_(julianDayNum) {}

    //constucts a Date from struct tm
    explicit Date(const struct tm&);

    void swap(Date& that)
    {
        std::swap(julianDayNumber_, that.julianDayNumber_);
    }

    bool valid() const {return julianDayNumber_ > 0;}

    string toIsoString() const;
    struct YearMonthDay yearMonthDay() const;

    int year() const
    {
        return YearMonthDay().year;
    }

    int month() const
    {
        return YearMonthDay().month;
    }

    int day() const
    {
        return YearMonthDay().day;
    }

    int weekDay() const
    {
        return (julianDayNumber_+1) % kDaysPerWeek;
    }

    int julianDayNumber() const {return julianDayNumber_; }

private:
    int julianDayNumber_;
};//Data

inline bool operator<(Date x, Date y)
{
    return x.julianDayNumber() < y.julianDayNumber();
}

inline bool operator== (Date x, Date y)
{
    return x.julianDayNumber() == y.julianDayNumber();
}


}// muduo

#endif