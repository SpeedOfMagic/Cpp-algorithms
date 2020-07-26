struct Time {
    int hour;
    int minute;
    int second = 0;
    bool usingSeconds = 0;

    bool valid() { return hour < 24 && minute < 60 && second < 60; }

    int timeInMinutes() { return hour * 60 + minute; }
    int timeInSeconds() { return hour * 3600 + minute * 60 + second; }

    void printRaw() {
        cout << (hour < 10 ? "0" : "") << hour << ":"
             << (minute < 10 ? "0" : "") << minute;
        if (usingSeconds)
            cout << ":" << (second < 10 ? "0" : "") << second;
        cout << endl;
    }

    Time(string timeRaw) {
        vector<int> res;
        for (int i = 0; i < timeRaw.size(); i += 3) {
            int v = (timeRaw[i] - '0') * 10 + (timeRaw[i + 1] - '0');
            res.push_back(v);
        }

        this -> hour = res[0];
        this -> minute = res[1];
        if (res.size() == 3) {
            this -> second = res[2];
            this -> usingSeconds = 1;
        }
    }

    int operator-(Time other) {
        if (other.second == 0 && this -> second == 0)
            return abs(other.timeInMinutes() - this -> timeInMinutes());
        else
            return abs(other.timeInSeconds() - this -> timeInSeconds());
    }

    void operator++(int32_t k) { k = 0; k++;
        if (usingSeconds) {
            second++;
            if (second == 60)
                second = 0;
            else
                return;
        }
        minute++;
        if (minute == 60) {
            minute = 0;
            hour++;
            if (hour == 24)
                hour = 0;
        }
    }
};
