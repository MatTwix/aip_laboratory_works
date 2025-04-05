#include <iostream>
#include <vector>
#include <string>
#include <regex>

using namespace std;

// Функция выделяет подстроки без символов '>', '<', '='
vector<string> extractSubstrings(const string& str) {
    vector<string> substrings;
    string current;
    
    for (char ch : str) {
        if (ch != '>' && ch != '<' && ch != '=') {
            current += ch;
        } else {
            if (!current.empty()) {
                substrings.push_back(current);
                current.clear();
            }
        }
    }
    if (!current.empty()) substrings.push_back(current); // Добавляем последнюю подстроку

    return substrings;
}

// Функция ищет первую подстроку, содержащую только латинские буквы и цифры
string findValidSubstring(const vector<string>& substrings) {
    regex pattern("^[a-zA-Z0-9]+$");
    
    for (const string& sub : substrings) {
        if (regex_match(sub, pattern)) {
            return sub;
        }
    }
    return "";
}

// Функция удаляет комментарии вида /* ... */ в строке
string removeComments(const string& str) {
    regex commentPattern("/\\*.*?\\*/");
    return regex_replace(str, commentPattern, "");
}

int main() {
    int n;
    cout << "Введите количество строк: ";
    cin >> n;
    cin.ignore(); // Очищаем буфер ввода

    vector<string> strings(n);
    vector<vector<string>> extractedSubstrings(n);
    string foundSubstring;
    int foundIndex = -1;

    // Ввод строк и выделение подстрок
    for (int i = 0; i < n; i++) {
        cout << "Введите строку #" << i + 1 << ": ";
        getline(cin, strings[i]);
        
        extractedSubstrings[i] = extractSubstrings(strings[i]);

        // Вывод найденных подстрок
        cout << "Подстроки без >, <, =: " << endl;
        for (const string& sub : extractedSubstrings[i]) {
            cout << sub << endl;
        }

        // Поиск подстроки с латинскими буквами и цифрами
        if (foundSubstring.empty()) {
            foundSubstring = findValidSubstring(extractedSubstrings[i]);
            if (!foundSubstring.empty()) {
                foundIndex = i;
            }
        }
    }

    // Проверка наличия нужной подстроки
    if (foundSubstring.empty()) {
        cout << "Не найдена подстрока, содержащая только латинские буквы и цифры." << endl;
    } else {
        cout << "Первая подходящая подстрока: " << foundSubstring << endl;
        
        // Преобразование строки с найденной подстрокой
        strings[foundIndex] = removeComments(strings[foundIndex]);
        cout << "Измененная строка #" << foundIndex + 1 << ": " << strings[foundIndex] << endl;
    }

    return 0;
}