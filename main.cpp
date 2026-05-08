#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <chrono>
using namespace std;
using namespace chrono;

struct List {
    int data;
    List* head;
    List* tail;
};

void clearInput();
List* createRandomList(int n);
List* createFreeList();
int listLength(List* beg);
List* findByIndex(List* beg, int index);
List* findByValue(List* beg, int value);
void insertAtIndex(List*& beg, int index, int value);
void deleteAtIndex(List*& beg, int index);
bool deleteByValue(List*& beg, int value);
void swapElements(List* beg, int idx1, int idx2);
void printList(List* beg);
void clearList(List*& beg);

int* createRandomArray(int n, int& size);
void printArray(int* arr, int size);
void insertInArray(int*& arr, int& size, int index, int value);
void deleteFromArray(int*& arr, int& size, int index);
bool deleteByValueFromArray(int*& arr, int& size, int value);
void swapInArray(int* arr, int size, int idx1, int idx2);
int findByIndexInArray(int* arr, int size, int index);
int findByValueInArray(int* arr, int size, int value);
void clearArray(int*& arr, int& size);

int main() {
    srand(time(0));
    List* list = nullptr;
    int* arr = nullptr;
    int arrSize = 0;
    int choice;

    while (true) {
        cout << "1. Создать двусвязный список" << endl;
        cout << "2. Вставка, удаление, обмен, получение элемента" << endl;
        cout << "0. Выход" << endl;
        cout << "Выбор: ";
        cin >> choice;

        if (cin.fail()) {
            clearInput();
            cout << "Неверный ввод" << endl;
            continue;
        }

        if (choice == 0) {
            clearList(list);
            clearArray(arr, arrSize);
            cout << "Выход" << endl;
            break;
        }
        else if (choice == 1) {
            int subChoice;
            cout << "1) Случайные числа\n2) Ввод с клавиатуры\nВыбор: ";
            cin >> subChoice;

            if (cin.fail()) {
                clearInput();
                cout << "Неверный ввод" << endl;
                continue;
            }

            clearList(list);

            if (subChoice == 1) {
                int n;
                cout << "Количество элементов: ";
                cin >> n;
                if (cin.fail() || n <= 0) {
                    clearInput();
                    cout << "Неверный ввод\n";
                    continue;
                }
                auto start = steady_clock::now();
                list = createRandomList(n);
                auto end = steady_clock::now();
                cout << "Список (создание): " << duration_cast<microseconds>(end - start).count() << " мкс\n";
                cout << "Список: ";
                printList(list);
            }
            else if (subChoice == 2) {
                auto start = steady_clock::now();
                list = createFreeList();
                auto end = steady_clock::now();
                if (list) {
                    cout << "Список (создание): " << duration_cast<microseconds>(end - start).count() << " мкс\n";
                    cout << "Список: ";
                    printList(list);
                }
            }
        }
        else if (choice == 2) {
            if (list == nullptr) {
                cout << "Список пуст! Сначала создайте список (пункт 1).\n";
                continue;
            }

            int n = listLength(list);

            clearArray(arr, arrSize);
            auto startArr = steady_clock::now();
            arr = createRandomArray(n, arrSize);
            auto endArr = steady_clock::now();
            cout << "\nСоздан массив (время): " << duration_cast<microseconds>(endArr - startArr).count() << " мкс\n";
            cout << "Массив: ";
            printArray(arr, arrSize);

            cout << "\nТекущий список: ";
            printList(list);

            int opChoice;
            while (true) {
                cout << "\n0) Назад\n1) Вставить элемент\n2) Удалить по индексу\n3) Удалить по значению\n4) Обменять элементы\n5) Получить по индексу\n6) Получить по значению\nВыбор: ";
                cin >> opChoice;

                if (cin.fail()) {
                    clearInput();
                    cout << "Неверный ввод\n";
                    continue;
                }

                if (opChoice == 0) break;
                else if (opChoice == 1) {
                    int idx, val;
                    cout << "Индекс и значение: ";
                    cin >> idx >> val;
                    if (cin.fail()) {
                        clearInput();
                        cout << "Неверный ввод\n";
                        continue;
                    }

                    auto startList = steady_clock::now();
                    insertAtIndex(list, idx, val);
                    auto endList = steady_clock::now();
                    cout << "\nСПИСОК - Вставка: " << duration_cast<microseconds>(endList - startList).count() << " мкс\n";
                    cout << "Список: ";
                    printList(list);

                    auto startArr = steady_clock::now();
                    insertInArray(arr, arrSize, idx, val);
                    auto endArr = steady_clock::now();
                    cout << "МАССИВ - Вставка: " << duration_cast<microseconds>(endArr - startArr).count() << " мкс\n";
                    cout << "Массив: ";
                    printArray(arr, arrSize);
                }
                else if (opChoice == 2) {
                    int idx;
                    cout << "Индекс: ";
                    cin >> idx;
                    if (cin.fail()) {
                        clearInput();
                        cout << "Неверный ввод\n";
                        continue;
                    }

                    auto startList = steady_clock::now();
                    deleteAtIndex(list, idx);
                    auto endList = steady_clock::now();
                    cout << "\nСПИСОК - Удаление по индексу: " << duration_cast<microseconds>(endList - startList).count() << " мкс\n";
                    cout << "Список: ";
                    printList(list);

                    auto startArr = steady_clock::now();
                    deleteFromArray(arr, arrSize, idx);
                    auto endArr = steady_clock::now();
                    cout << "МАССИВ - Удаление по индексу: " << duration_cast<microseconds>(endArr - startArr).count() << " мкс\n";
                    cout << "Массив: ";
                    printArray(arr, arrSize);
                }
                else if (opChoice == 3) {
                    int val;
                    cout << "Значение: ";
                    cin >> val;
                    if (cin.fail()) {
                        clearInput();
                        cout << "Неверный ввод\n";
                        continue;
                    }

                    auto startList = steady_clock::now();
                    bool foundList = deleteByValue(list, val);
                    auto endList = steady_clock::now();
                    cout << "\nСПИСОК - Удаление по значению: " << duration_cast<microseconds>(endList - startList).count() << " мкс\n";
                    if (!foundList) cout << "Элемент не найден\n";
                    cout << "Список: ";
                    printList(list);

                    auto startArr = steady_clock::now();
                    bool foundArr = deleteByValueFromArray(arr, arrSize, val);
                    auto endArr = steady_clock::now();
                    cout << "МАССИВ - Удаление по значению: " << duration_cast<microseconds>(endArr - startArr).count() << " мкс\n";
                    if (!foundArr) cout << "Элемент не найден\n";
                    cout << "Массив: ";
                    printArray(arr, arrSize);
                }
                else if (opChoice == 4) {
                    int idx1, idx2;
                    cout << "Индексы: ";
                    cin >> idx1 >> idx2;
                    if (cin.fail()) {
                        clearInput();
                        cout << "Неверный ввод\n";
                        continue;
                    }

                    auto startList = steady_clock::now();
                    swapElements(list, idx1, idx2);
                    auto endList = steady_clock::now();
                    cout << "\nСПИСОК - Обмен: " << duration_cast<microseconds>(endList - startList).count() << " мкс\n";
                    cout << "Список: ";
                    printList(list);

                    auto startArr = steady_clock::now();
                    swapInArray(arr, arrSize, idx1, idx2);
                    auto endArr = steady_clock::now();
                    cout << "МАССИВ - Обмен: " << duration_cast<microseconds>(endArr - startArr).count() << " мкс\n";
                    cout << "Массив: ";
                    printArray(arr, arrSize);
                }
                else if (opChoice == 5) {
                    int idx;
                    cout << "Индекс: ";
                    cin >> idx;
                    if (cin.fail()) {
                        clearInput();
                        cout << "Неверный ввод\n";
                        continue;
                    }

                    auto startList = steady_clock::now();
                    List* foundList = findByIndex(list, idx);
                    auto endList = steady_clock::now();
                    cout << "\nСПИСОК - Поиск по индексу: " << duration_cast<microseconds>(endList - startList).count() << " мкс\n";
                    if (foundList) cout << "Значение: " << foundList->data << endl;

                    auto startArr = steady_clock::now();
                    int foundArr = findByIndexInArray(arr, arrSize, idx);
                    auto endArr = steady_clock::now();
                    cout << "МАССИВ - Поиск по индексу: " << duration_cast<microseconds>(endArr - startArr).count() << " мкс\n";
                    if (foundArr != -1) cout << "Значение: " << foundArr << endl;
                }
                else if (opChoice == 6) {
                    int val;
                    cout << "Значение: ";
                    cin >> val;
                    if (cin.fail()) {
                        clearInput();
                        cout << "Неверный ввод\n";
                        continue;
                    }

                    auto startList = steady_clock::now();
                    List* foundList = findByValue(list, val);
                    auto endList = steady_clock::now();
                    cout << "\nСПИСОК - Поиск по значению: " << duration_cast<microseconds>(endList - startList).count() << " мкс\n";
                    if (foundList) cout << "Найден\n";

                    auto startArr = steady_clock::now();
                    int foundArr = findByValueInArray(arr, arrSize, val);
                    auto endArr = steady_clock::now();
                    cout << "МАССИВ - Поиск по значению: " << duration_cast<microseconds>(endArr - startArr).count() << " мкс\n";
                    if (foundArr != -1) cout << "Найден\n";
                }
            }
        }
    }

    return 0;
}

void clearInput() {
    cin.clear();
    cin.ignore(10000, '\n');
}

List* createRandomList(int n) {
    if (n <= 0) return nullptr;
    List* curr = nullptr;
    List* next = nullptr;
    for (int i = 0; i < n; i++) {
        curr = new List;
        curr->data = rand() % 100;
        curr->tail = next;
        if (next) next->head = curr;
        next = curr;
    }
    if (curr) curr->head = nullptr;
    return curr;
}

List* createFreeList() {
    string line;
    cin.ignore();
    getline(cin, line);
    stringstream ss(line);
    List* curr = nullptr;
    List* next = nullptr;
    int value;
    while (ss >> value) {
        curr = new List;
        curr->data = value;
        curr->tail = next;
        if (next) next->head = curr;
        next = curr;
    }
    if (curr) curr->head = nullptr;
    return curr;
}

int listLength(List* beg) {
    int len = 0;
    while (beg) {
        len++;
        beg = beg->tail;
    }
    return len;
}

List* findByIndex(List* beg, int index) {
    while (beg && index--) beg = beg->tail;
    if (!beg) cout << "Элемент не найден\n";
    return beg;
}

List* findByValue(List* beg, int value) {
    while (beg && beg->data != value) beg = beg->tail;
    if (!beg) cout << "Элемент не найден\n";
    return beg;
}

void insertAtIndex(List*& beg, int index, int value) {
    int len = listLength(beg);
    if (index < 0 || index > len) {
        cout << "Неверный индекс\n";
        return;
    }
    List* newNode = new List;
    newNode->data = value;
    if (index == 0 || !beg) {
        newNode->tail = beg;
        newNode->head = nullptr;
        if (beg) beg->head = newNode;
        beg = newNode;
    } else {
        List* prev = findByIndex(beg, index - 1);
        newNode->tail = prev->tail;
        newNode->head = prev;
        if (prev->tail) prev->tail->head = newNode;
        prev->tail = newNode;
    }
}

void deleteAtIndex(List*& beg, int index) {
    int len = listLength(beg);
    if (len == 0) {
        cout << "Список пуст\n";
        return;
    }
    if (index < 0 || index >= len) {
        cout << "Неверный индекс\n";
        return;
    }
    if (index == 0) {
        List* temp = beg;
        beg = beg->tail;
        if (beg) beg->head = nullptr;
        delete temp;
    } else {
        List* prev = findByIndex(beg, index - 1);
        List* toDel = prev->tail;
        prev->tail = toDel->tail;
        if (toDel->tail) toDel->tail->head = prev;
        delete toDel;
    }
}

bool deleteByValue(List*& beg, int value) {
    List* current = beg;
    int index = 0;
    while (current) {
        if (current->data == value) {
            deleteAtIndex(beg, index);
            return true;
        }
        current = current->tail;
        index++;
    }
    return false;
}

void swapElements(List* beg, int idx1, int idx2) {
    int len = listLength(beg);
    if (idx1 < 0 || idx1 >= len || idx2 < 0 || idx2 >= len) {
        cout << "Неверные индексы\n";
        return;
    }
    if (idx1 == idx2) return;
    List* a = findByIndex(beg, idx1);
    List* b = findByIndex(beg, idx2);
    int temp = a->data;
    a->data = b->data;
    b->data = temp;
}

void printList(List* beg) {
    if (!beg) {
        cout << "Список пуст\n";
        return;
    }
    while (beg) {
        cout << beg->data;
        if (beg->tail) cout << " ";
        beg = beg->tail;
    }
    cout << endl;
}

void clearList(List*& beg) {
    while (beg) {
        List* temp = beg;
        beg = beg->tail;
        delete temp;
    }
}

int* createRandomArray(int n, int& size) {
    if (n <= 0) return nullptr;
    int* arr = new int[n];
    size = n;
    for (int i = 0; i < n; i++) arr[i] = rand() % 100;
    return arr;
}

void printArray(int* arr, int size) {
    if (size == 0) {
        cout << "Массив пуст\n";
        return;
    }
    for (int i = 0; i < size; i++) {
        cout << arr[i];
        if (i < size - 1) cout << " ";
    }
    cout << endl;
}

void insertInArray(int*& arr, int& size, int index, int value) {
    if (index < 0 || index > size) {
        cout << "Неверный индекс\n";
        return;
    }
    int* newArr = new int[size + 1];
    for (int i = 0; i < index; i++) newArr[i] = arr[i];
    newArr[index] = value;
    for (int i = index; i < size; i++) newArr[i + 1] = arr[i];
    delete[] arr;
    arr = newArr;
    size++;
}

void deleteFromArray(int*& arr, int& size, int index) {
    if (size == 0) {
        cout << "Массив пуст\n";
        return;
    }
    if (index < 0 || index >= size) {
        cout << "Неверный индекс\n";
        return;
    }
    int* newArr = new int[size - 1];
    for (int i = 0; i < index; i++) newArr[i] = arr[i];
    for (int i = index + 1; i < size; i++) newArr[i - 1] = arr[i];
    delete[] arr;
    arr = newArr;
    size--;
}

bool deleteByValueFromArray(int*& arr, int& size, int value) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == value) {
            deleteFromArray(arr, size, i);
            return true;
        }
    }
    return false;
}

void swapInArray(int* arr, int size, int idx1, int idx2) {
    if (idx1 < 0 || idx1 >= size || idx2 < 0 || idx2 >= size) {
        cout << "Неверные индексы\n";
        return;
    }
    int temp = arr[idx1];
    arr[idx1] = arr[idx2];
    arr[idx2] = temp;
}

int findByIndexInArray(int* arr, int size, int index) {
    if (index < 0 || index >= size) {
        cout << "Элемент не найден\n";
        return -1;
    }
    return arr[index];
}

int findByValueInArray(int* arr, int size, int value) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == value) return i;
    }
    cout << "Элемент не найден\n";
    return -1;
}

void clearArray(int*& arr, int& size) {
    if (arr) delete[] arr;
    arr = nullptr;
    size = 0;
}