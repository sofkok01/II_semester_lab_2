#include <iostream>
#include <string>
using namespace std;

struct Group {
    int number;
    int studentsCount;
    float averageScore;
};

struct List {
    Group data;
    List* head;
    List* tail;
};

void clearInput();
void addGroup(List*& beg, List*& end);
void printList(List* beg);
void clearList(List*& beg, List*& end);

int main() {
    setlocale(LC_ALL, "ru");

    List* sourceBeg = nullptr;
    List* sourceEnd = nullptr;

    List* highBeg = nullptr;
    List* highEnd = nullptr;
    List* lowBeg = nullptr;
    List* lowEnd = nullptr;

    int choice;

    while (true) {
        cout << "\n1. Добавить группу\n2. Разделить группы по среднему баллу (>4.0 и <=4.0)\n0. Выход\n";
        cin >> choice;

        if (cin.fail()) {
            clearInput();
            cout << "Неверный ввод\n";
            continue;
        }

        if (choice == 0) {
            break;
        }
        else if (choice == 1) {
            addGroup(sourceBeg, sourceEnd);
        }
        else if (choice == 2) {
            if (sourceBeg == nullptr) {
                cout << "Нет добавленных групп\n";
                continue;
            }

            clearList(highBeg, highEnd);
            clearList(lowBeg, lowEnd);

            List* current = sourceBeg;
            while (current != nullptr) {
                if (current->data.averageScore > 4.0) {
                    if (highBeg == nullptr) {
                        highBeg = highEnd = new List;
                        highBeg->data = current->data;
                        highBeg->head = nullptr;
                        highBeg->tail = nullptr;
                    } else {
                        List* newNode = new List;
                        newNode->data = current->data;
                        newNode->head = highEnd;
                        newNode->tail = nullptr;
                        highEnd->tail = newNode;
                        highEnd = newNode;
                    }
                } else {
                    if (lowBeg == nullptr) {
                        lowBeg = lowEnd = new List;
                        lowBeg->data = current->data;
                        lowBeg->head = nullptr;
                        lowBeg->tail = nullptr;
                    } else {
                        List* newNode = new List;
                        newNode->data = current->data;
                        newNode->head = lowEnd;
                        newNode->tail = nullptr;
                        lowEnd->tail = newNode;
                        lowEnd = newNode;
                    }
                }
                current = current->tail;
            }

            cout << "\nГруппы со средним баллом > 4.0:\n";
            printList(highBeg);
            cout << "\nГруппы со средним баллом <= 4.0:\n";
            printList(lowBeg);
        }
        else {
            cout << "Неверный выбор\n";
        }
    }

    clearList(sourceBeg, sourceEnd);
    clearList(highBeg, highEnd);
    clearList(lowBeg, lowEnd);

    return 0;
}

void clearInput() {
    cin.clear();
    cin.ignore(10000, '\n');
}

void addGroup(List*& beg, List*& end) {
    Group g;

    cout << "Введите номер группы: ";
    cin >> g.number;
    if (cin.fail()) {
        clearInput();
        cout << "Неверный ввод\n";
        return;
    }

    cout << "Введите количество студентов: ";
    cin >> g.studentsCount;
    if (cin.fail() || g.studentsCount < 0) {
        clearInput();
        cout << "Неверный ввод\n";
        return;
    }

    cout << "Введите средний балл (0-5): ";
    cin >> g.averageScore;
    if (cin.fail() || g.averageScore < 0 || g.averageScore > 5) {
        clearInput();
        cout << "Неверный ввод\n";
        return;
    }

    List* newNode = new List;
    newNode->data = g;
    newNode->head = nullptr;
    newNode->tail = nullptr;

    if (beg == nullptr) {
        beg = end = newNode;
    } else {
        end->tail = newNode;
        newNode->head = end;
        end = newNode;
    }

    cout << "Группа добавлена\n";
}

void printList(List* beg) {
    if (beg == nullptr) {
        cout << "  Пусто\n";
        return;
    }

    List* current = beg;
    while (current != nullptr) {
        cout << "--Группа " << current->data.number << ": студентов " << current->data.studentsCount << ", средний балл " << current->data.averageScore << endl;
        current = current->tail;
    }
}

void clearList(List*& beg, List*& end) {
    while (beg != nullptr) {
        List* temp = beg;
        beg = beg->tail;
        delete temp;
    }
    end = nullptr;
}