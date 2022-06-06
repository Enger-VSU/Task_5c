#include <iostream>
#include <string>
#include <clocale> //Обязательно для функции setlocale()
#include <Windows.h> // Обязательно для SetConsoleCP() и SetConsoleOutputCP()

using namespace std;

struct Matriculant { // Описание структуры абитуриента
    string fullName; // Имя абитуриент
    int direction; // Направление
    union
    {
        struct { int physics, mathematics; } InfSystems; // Баллы для предметов по ИСиТу
        struct { int chemistry, biology; } Medical; // Баллы для предметов по физфаку
    };
    int russian; // Баллы по русскому
    string telephoneNumber; // Телефонный номер
};

Matriculant createMatriculant(int direction) { // Описание метода создания экземпляра абитуриента
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Matriculant matriculant;

    cout << "Введите ФИО: ";
    while (matriculant.fullName == "") { // Если ничего не введено, то повторяем процедуру
        getline(cin, matriculant.fullName); // через getline
    }

    matriculant.direction = direction; // Ввод данных
    if (direction == 1) {
        cout << "Баллы по физике: ";
        cin >> matriculant.InfSystems.physics;
        cout << "Баллы по математике: ";
        cin >> matriculant.InfSystems.mathematics;
    }
    else {
        cout << "Баллы по химии: ";
        cin >> matriculant.Medical.chemistry;
        cout << "Баллы по биологии: ";
        cin >> matriculant.Medical.biology;
    }

    cout << "Баллы по русскому: ";
    cin >> matriculant.russian;
    cout << "Номер телефона: ";
    while (matriculant.telephoneNumber == "") { // Аналогично предыдущему
        getline(cin, matriculant.telephoneNumber);
    }
    return matriculant; // Возвращаем экземпляр структуры
}

void printMatriculant(Matriculant matriculant) { // Метод, описывающий вывод данных структуры
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    cout << "Name: " << matriculant.fullName << "\n";
    if (matriculant.direction == 1) {
        cout << "Направление: Информационные системы и технологии\n";
        cout << "Баллы: " << matriculant.InfSystems.physics << ", " << matriculant.InfSystems.mathematics << ", ";
    }
    else {
        cout << "Направление: Медецинское\n";
        cout << "Баллы: " << matriculant.Medical.chemistry << ", " << matriculant.Medical.biology << ", ";
    }
    cout << matriculant.russian << "\n";
    cout << "Номер телефона: " << matriculant.telephoneNumber << "\n";
}

int main() {
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Matriculant dataBase[10], matriculant = { "", 0, {0, 0}, 0, "" }; // Создаем массив структур, который заполняем нулевыми данными

    int i, j;
    for (i = 0; i < sizeof(dataBase) / sizeof(matriculant); i++) { // Заполнение массива стукурами
        dataBase[i] = matriculant;
    }

    while (true) {
        cout << "    Выбор действия:\n"
            << "1. Ввести информацию.\n"
            << "2. Вывести информацию об абитуриенте.\n"
            << "3. Вывести информацию всех абитуриентов.\n"
            << "4. Удалить информацию об абитуриенте.\n"
            << "5. Удалить всю информацию.\n"
            << "6. Завершить работу.\n"
            << ">";
        cin >> i;

        switch (i) { // Через оператор switch делаем вариативное меню
        case 1:
            cout << "Номер абитуриента: "; cin >> i;
            cout << "Направление (1 - Информационные системы и технологии, 2 - Медецинское): "; cin >> j;
            dataBase[i - 1] = createMatriculant(j);
            break;
        case 2:
            cout << "Номер абитуриента: "; cin >> i;
            printMatriculant(dataBase[i - 1]);
            break;
        case 3:
            for (i = 0; i < sizeof(dataBase) / sizeof(matriculant); i++) {
                if (dataBase[i].direction != 0) {
                    cout << "Абитуриент номер " << i + 1 << ':' << "\n";
                    printMatriculant(dataBase[i]);
                }
            }
            break;
        case 4:
            cout << "Номер абитуриента: "; cin >> i;
            dataBase[i - 1] = matriculant;
            break;
        case 5:
            for (i = 0; i < sizeof(dataBase) / sizeof(matriculant); i++) {
                dataBase[i] = matriculant;
            }
            break;
        case 6:
            return 0;
        default: cout << "Действие неверно, повторите.\n"; // Если что-то введено неверно по дефолту выводим надпись
        }
    }
}