#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Student {
    string secondName;
    string name;
    string surname;
    string group;
    int grades[5];
    int avg;

    Student* next;
};

Student* readFromFile(const string& filename) {
    ifstream fin(filename);
    if (!fin.is_open()) {
        cout << "Ошибка открытия файла" << endl;
        return nullptr;
    }

    Student* head = nullptr;

    while (!fin.eof()) {
        Student* s = new Student;
        if (!(fin >> s->secondName >> s->name >> s->surname)) break;
        fin >> s->group;
        int sum = 0;
        for (int i = 0; i < 5; i++) {
            fin >> s->grades[i];
            sum += s->grades[i];
        }
        s->avg = sum / 5.0;
        s->next = head;
        head = s;
    }

    fin.close();
    return head;
}

Student* filterByMaxGrade(Student* head, int maxAllowedGrade) {
    Student* queueHead = nullptr;
    Student* queueTail = nullptr;

    while (head) {
        bool flag = false;
        for (int i = 0; i < 5; ++i) {
            if (head->grades[i] > maxAllowedGrade) {
                flag = true;
                break;
            }
        }

        if (!flag) {
            Student* newNode = new Student(*head);
            newNode->next = nullptr;

            if (!queueHead)
                queueHead = queueTail = newNode;
            else {
                queueTail->next = newNode;
                queueTail = newNode;
            }
        }

        head = head->next;
    }

    return queueHead;
}

void printToFile(Student* head, const string& filename) {
    ofstream fout(filename);

    while (head) {
        fout << head->secondName << " " << head->name << " " << head->surname << endl;
        fout << head->group << endl;
        for (int i = 0; i < 5; ++i)
            fout << head->grades[i] << " ";
        fout << endl;
        fout << head->avg << endl;
        head = head->next;
    }

    fout.close();
}

void freeList(Student* head) {
    while (head) {
        Student* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    string filename;
    cout << "Введите название входного файла: " << endl;
    cin >> filename;

    Student* stack = readFromFile("input.txt");

    if (!stack) {
        cout << "Файл пуст." << endl;
        return 1;
    }

    int maxGrade;
    cout << "Введите максимальную оценку: " << endl;
    cin >> maxGrade;

    Student* queue = filterByMaxGrade(stack, maxGrade);

    printToFile(queue, "output.txt");

    freeList(stack);
    freeList(queue);

    cout << "Результат записан." << endl;
    return 0;
}