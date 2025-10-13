#include <iostream>

int main() {
    setlocale(LC_ALL, "Russian");

    // Первая часть

    const int razmer = 5; // номер варианта = 2 
    int x[razmer];
    std::cout << "Введите " << razmer << " чисел массива:" << std::endl;
    for (int i = 0; i < razmer; ++i) {
        std::cin >> x[i];
    }

    bool summa = false; // Проверяем, есть ли сумма больше 25
    for (int i = 0; i < razmer - 1; ++i) {
        for (int j = i + 1; j < razmer; ++j) {
            if (x[i] + x[j] > 25) {
                std::cout << "Сумма двух чисел массива превышает 25. Сортировка по возрастанию: " << std::endl;
                summa = true;
                break;
            }
        }
        if (summa) {
            break;
        }
    }

    if (summa == false) {
        std::cout << "В массиве нет чисел, сумма которых больше 25." << std::endl;
    }
    else {
        for (int i = 0; i < razmer - 1; ++i) {
            for (int j = i + 1; j < razmer; ++j) {
                if (x[i] > x[j]) {
                    std::swap(x[i], x[j]);
                }
            }
        }
        for (int i = 0; i < razmer; ++i) {
            std::cout << x[i] << std::endl;
        }
    }

    // Вторая часть

    const int str = 3;
    const int stolb = 4;
    int matrix[str][stolb];
    std::cout << "Введите 12 чисел матрицы 3х4." << std::endl;
    for (int i = 0; i < str; ++i) {
        for (int j = 0; j < stolb; ++j) {
            std::cin >> matrix[i][j];
        }
    }

    int StolbMinKolPolozh = 0; // Столбец с минимальным количеством положительных чисел
    int MinKolPolozh = 12; // Переменная для хранения инимального количества положительных чисел
    for (int j = 0; j < stolb; j++) {
        int KolPolozh = 0; // Количество положительных чисел в столбце
        for (int i = 0; i < str; i++) {
            if (matrix[i][j] > 0) {
                ++KolPolozh;
            }
        }

        if (KolPolozh < MinKolPolozh) { // Сохраняем столбец с наименьшем количеством положительных чисел
            MinKolPolozh = KolPolozh;
            StolbMinKolPolozh = j;
        }
    }
    for (int i = 0; i < str; i++) {
        matrix[i][StolbMinKolPolozh] = 100;
    }

    std::cout << "Обновленная матрица: " << std::endl;
    for (int i = 0; i < str; i++) {
        for (int j = 0; j < stolb; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}