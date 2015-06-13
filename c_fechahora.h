#ifndef C_FECHAHORA_H
#define C_FECHAHORA_H


class c_fechahora{
        private:
            int year_;
            int month_;
            int day_;
            int hora_;
            int minutos_;
            int segundos_;

        public:
            c_fechahora();
            c_fechahora(const int& d, const int& m, const int& y, const int& hh, const int& mm, const int& ss);
            ~c_fechahora();

            bool valid() const;

            int day() const;
            int month() const;
            int year() const;

            void setDay (const int& day);
            void setMonth (const int& month);
            void setYear (const int& year);
        };

#endif // C_FECHAHORA_H
