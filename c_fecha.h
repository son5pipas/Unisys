#ifndef C_FECHA_H
#define C_FECHA_H


class c_fecha{
private:
    int year_;
    int month_;
    int day_;

public:
    c_fecha();
    c_fecha(const int& d, const int& m, const int& y);
    ~c_fecha();

    bool valid() const;

    int day() const;
    int month() const;
    int year() const;

    void setDay (const int& day);
    void setMonth (const int& month);
    void setYear (const int& year);
};


#endif // C_FECHA_H
