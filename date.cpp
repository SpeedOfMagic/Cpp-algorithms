struct Date {
    int day;
    int month;
    int year;

    const int kDaysInMonth[13] = {-1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    int getDaysInMonth() { return kDaysInMonth[month] + (month == 2 && leap(year)); }

    bool leap(int year) { return (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0)); }

    int countDays() {
        int res = 0;
        for (int i = 1970; i < year; i++)
            res += 365 + leap(i);

        for (int i = 1; i < month; i++)
            res += kDaysInMonth[i] + (i == 2 && leap(year));

        res += day;

        return res;
    }

    bool valid() { return (day <= getDaysInMonth()) && (this -> countDays() >= 0); }

    void printRaw(int format) {
        if (format == 0)
            cout << year << "-" << (month < 10 ? "0" : "") << month << "-" << (day < 10 ? "0" : "") << day;
        else if (format == 1)
            cout << (month < 10 ? "0" : "") << month << "-" << (day < 10 ? "0" : "") << day << "-" << year;
        else if (format == 2)
            cout << (day < 10 ? "0" : "") << day << "-" << (month < 10 ? "0" : "") << month << "-" << year;
        cout << endl;
    }

    Date(int d, int m, int y): day(d), month(m), year(y) {}

    /**
    * format = 0: YYYY-MM-DD
    * format = 1: MM-DD-YYYY
    * format = 2: DD-MM-YYYY
    * returns {DD, MM, YYYY}
    **/
    Date(string dateRaw, unsigned int format) {
        int p = 0;
        if (format == 0) {
            year = (dateRaw[p] - '0') * 1000 + (dateRaw[p + 1] - '0') * 100 +
                   (dateRaw[p + 2] - '0') * 10 + (dateRaw[p + 3] - '0');
            p = 5;
        }

        rep(z, 0, 2) {
            int v = (dateRaw[p] - '0') * 10 + (dateRaw[p + 1] - '0');
            if (z)
                day = v;
            else
                month = v;
            p += 3;
        }

        if (format > 0) {
            if (format == 2)
                swap(day, month);
            year = (dateRaw[p] - '0') * 1000 + (dateRaw[p + 1] - '0') * 100 +
                   (dateRaw[p + 2] - '0') * 10 + (dateRaw[p + 3] - '0');
        }
    }

    bool operator==(const Date& other) { return tie(day, month, year) == tie(other.day, other.month, other.year); }

    bool operator!=(const Date& other) { return !((*this) == other); }

    bool operator<(const Date& other) { return this -> countDays() < other.countDays(); }

    bool operator>(const Date& other) { return other < (*this); }

    void operator++() {
        int daysMax = getDaysInMonth();
        day++;
        if (day > daysMax) {
            day = 1;
            month++;
            if (month == 13) {
                month = 1;
                year++;
            }
        }
    }

    void operator++(int) {
        Date temp = *this;
        this -> operator++();
        return temp;
    }
};
