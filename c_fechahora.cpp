#include "c_fechahora.h"
c_fechahora::c_fechahora()
{

}

c_fechahora::c_fechahora(const int &d, const int &m, const int &y, const int &hh, const int &mm, const int &ss=00)
{
    day_=d;
    month_=m;
    year_=y;
    hora_=hh;
    minutos_=mm;
    segundos_=ss;
}

c_fechahora::~c_fechahora()
{

}

bool c_fechahora::valid() const{
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
    if (hora_>23 || hora_<0){
        return false;
    }
    if (minutos_>59 || minutos_<0){
        return false;
    }
    if (segundos_>59 || segundos_<0){
        return false;
    }
    return true;
}

int c_fechahora::day() const{
    return day_;
}

int c_fechahora::month() const{
    return month_;
}

int c_fechahora::year() const{
    return year_;
}

void c_fechahora::setDay(const int &day){
    day_=day;
}

void c_fechahora::setMonth(const int &month){
    month_=month;
}

void c_fechahora::setYear(const int &year){
    year_=year;
}
