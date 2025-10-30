#include <iostream>
#include <numeric>
#include <algorithm>
#include <string>

//Функции
//Первый пункт
int foo(int a, int b) { // функция суммы всех чисел двух цифр
    int c = 0;
    int d = 0;
    while (std::abs(a) > 0) {
        c += std::abs(a) % 10;
        a = a / 10;
    }
    while (std::abs(b) > 0) {
        d += std::abs(b) % 10;
        b = b / 10;
    }
    return c + d;
}

int foo(int a, int b, int c) { // для трех чисел наибольшее значение из них и 25
    return std::max({ a, b, c, 25 });
}

void func(int a, int b, int c) { // главная функция, которая не учитывает нулевые значения
    int good_nums[3]; // создаем массив, в который не добавляем нулевые значения
    int count = 0;
    if (a != 0) {
        good_nums[count] = a;
        count++;
    }
    if (b != 0) {
        good_nums[count] = b;
        count++;
    }
    if (c != 0) {
        good_nums[count] = c;
        count++;
    }
    if (count == 2) {
        std::cout << "Используется функция суммы чисел двух цифр. Результат для (" << a << ", " << b << ", " << c << "): " << \
           foo(good_nums[0], good_nums[1]) << std::endl;
    }
    else if (count == 3) {
        std::cout << "Используется функция нахождения максимума из трех чисел и 25. Результат для (" << a << ", " << b << ", " << c << "): " << \
            foo(good_nums[0], good_nums[1], good_nums[2]) << std::endl;
    }
    else {
        std::cout << "Результат для (" << a << ", " << b << ", " << c << "): " << "Количество ненулевых чисел не равно 2 или 3." << std::endl;
    }
}

//Второй пункт
void laba1(short h, short osn1, short osn2) { // Функция для вычисления площади трапеции
    float s;
    s = (osn1 + osn2) * h / 2.0;
    std::cout << "Площадь трапеции = " << s << std::endl;
}


int main()
{
    setlocale(LC_ALL, "Russian");
    int NomerPunkta;
    std::cout << "Введите номер пункта" << std::endl;
    std::cin >> NomerPunkta;

    if (NomerPunkta == 1) { // Первый пункт
        int a;
        int b;
        int c;
        std::cout << "Введите числа для функций подсчета суммы или максимума:" << std::endl;
        std::cin >> a;
        std::cin >> b;
        std::cin >> c;
        func(a, b, c);
    }



    else if (NomerPunkta == 2) { // Второй пункт
        short h;
        short osn1;
        short osn2;
        std::cout << "Введите высоту и два основания трапеции:" << std::endl;
        std::cin >> h;
        std::cin >> osn1;
        std::cin >> osn2;
        laba1(h, osn1, osn2);

    }

    else {
        std::cout << "Не существует пункта" << std::endl;
    }
}