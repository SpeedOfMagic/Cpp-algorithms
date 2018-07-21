/**
* accepts both HH:MM and HH:MM:SS
* returns {HH, MM} or {HH, MM, SS}
**/
vector<int> decomposeTime(string time) {
    vector<int> res;
    for (int i = 0; i < time.size(); i += 3) {
        int v = (time[i] - '0') * 10 + (time[i + 1] - '0');
        res.push_back(v);
    }

    return res;
}

bool validTime(vector<int> timeDecomposed) {
    return timeDecomposed[0] < 24 && timeDecomposed[1] < 60;
}

bool validTime(string time) { return validTime(decomposeTime(time)); }

int timeInMinutes(string time) {
    vector<int> decomposedTime = decomposeTime(time);
    return decomposedTime[0] * 60 + decomposedTime[1];
}

int differenceInMinutes(string time1, string time2) {
    return abs(timeInMinutes(time1) - timeInMinutes(time2));
}

int timeInSeconds(string time) {
    vector<int> decomposedTime = decomposeTime(time);

    int res = decomposedTime[0] * 3600 + decomposedTime[1] * 60;
    if (decomposedTime.size() == 3)
        res += decomposedTime[2];
    return res;
}

int differenceInSeconds(string time1, string time2) {
    return abs(timeInSeconds(time1) - timeInSeconds(time2));
}
