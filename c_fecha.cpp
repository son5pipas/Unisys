#include "c_fecha.h"

c_fecha::c_fecha()
{

}
c_fecha::c_fecha(const int &d, const int &m, const int &y)
{
    day_=d;
    month_=m;
    year_=y;
}

c_fecha::~c_fecha()
{

}

bool c_fecha::valid() const{
    if (year_<0){
        return false;
    }
    if (month_>12 || month_<1){
        return false;
    }
    if (day_>31 || day_<1){
        return false;
    }
    if ((day_==31 && (month_==2 || month_==4 || month_==6 || month_==9 || month_==11 ))){
        return false;
    }
    if (day_==30 && month_==2){
        return false;
    }
    if (year_<2000){
        if ((day_==29 && month_==2) && !((year_-1900)%4==0)){
            return false;
        }
    }
    if (year_>2000){
        if ((day_==29 && month_==2) && !((year_-2000)%4==0)){
            return false;
        }
    }
    return true;
}

int c_fecha::day() const{
    return day_;
}

int c_fecha::month() const{
    return month_;
}

int c_fecha::year() const{
    return year_;
}

void c_fecha::setDay(const int &day){
    day_=day;
}

void c_fecha::setMonth(const int &month){
    month_=month;
}

void c_fecha::setYear(const int &year){
    year_=year;
}
