#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

bool task1(string &str) {
    return str.find('>') == string::npos && str.find('<') == string::npos && str.find('=') == string::npos;
}

string task2(string &str) {
    string res = "", tmp = "";

    for (char c : str) {
        if (isalnum(c)) {
            tmp += c;
        } else {
            if (!tmp.empty() && tmp.length() > res.length()) {
                res = tmp;
            }
            tmp = "";
        }
    }

    if (!tmp.empty() && tmp.length() > res.length()) {
        res = tmp;
    }

    return res;
}


void task3(string &str) {
    size_t pos;
    while ((pos = str.find("/*")) != string::npos) {
        str.erase(pos, 2);
    }
    while ((pos = str.find("*/")) != string::npos) {
        str.erase(pos, 2);
    }
}

int main(void) {
    int n;
    cout << "Entrer number of strings: ";
    cin >> n;
    cin.ignore();

    vector<string> inputStrings(n);
    vector<string> taskOneStrs;

    cout << "Input strings: " << endl;
    for (auto i = 0; i < n; i++) {
        getline(cin, inputStrings[i]);
        if (task1(inputStrings[i])) {
            taskOneStrs.push_back(inputStrings[i]);
        }
    }

    if (taskOneStrs.empty()) {
        cout << "There are no strings with without special symbols." << endl;
        return 0;
    }

    cout << "Task 1: " << endl;
    for (string &str : taskOneStrs) {
        cout << str << endl;
    }

    string targetSubstr = "";
    int idx = -1;

    for (auto i = 0; i < taskOneStrs.size(); ++i) {
        string candidate = task2(taskOneStrs[i]);
        if (!candidate.empty() && candidate.length() > targetSubstr.length()) {
            targetSubstr = candidate;
            idx = i;
        }
    }

    if (targetSubstr.empty()) {
        cout << "There are no substrings with only latin letters and numbers" << endl;
        return 0;
    }

    cout << "Task 2: " << targetSubstr << endl;

    task3(taskOneStrs[idx]);

    cout << "Task 3: " << taskOneStrs[idx] << endl;

    return 0;
}