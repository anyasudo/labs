#include <iostream>
#include <vector>
#include <array>
#include <cstdlib>
#include <ctime>

// ПУНКТ 1

void viewArray(const std::vector<int>& arr) {
    std::cout << "[";
    for (size_t i = 0; i < arr.size(); i++) {
        std::cout << arr[i];
        if (i != arr.size() - 1) {
            std::cout << " ";
        }
    }
    std::cout << "]" << std::endl;
}

void searchElement(const std::vector<int>& arr, int element) {
    std::cout << "[";
    bool found = false;
    for (size_t i = 0; i < arr.size(); i++) {
        if (arr[i] == element) {
            if (found) {
                std::cout << ",";
            }
            std::cout << i;
            found = true;
        }
    }
    if (!found) {
        std::cout << "] - элемент не найден" << std::endl;
    }
    else {
        std::cout << "]" << std::endl;
    }
}

// второй вариант
void variantTask(std::vector<int>& arr) {
    std::cout << "До: ";
    viewArray(arr);

    if (arr.size() % 2 == 0) {
        if (!arr.empty()) {
            arr.erase(arr.begin());
        }
    }
    else {
        int elementsToRemove = std::min(4, static_cast<int>(arr.size()));
        for (int i = 0; i < elementsToRemove && !arr.empty(); i++) {
            arr.pop_back();
        }
    }

    std::cout << "После: ";
    viewArray(arr);
}

// 1 пункт функция
void menuPunkt1() {
    std::vector<int> arr;
    int choice;

    do {
        std::cout << "\n=== Меню (Пункт 1) ===" << std::endl;
        std::cout << "0. Выход в главное меню" << std::endl;
        std::cout << "1. Просмотр массива" << std::endl;
        std::cout << "2. Добавить элемент в начало" << std::endl;
        std::cout << "3. Добавить элемент в конец" << std::endl;
        std::cout << "4. Очистка всего массива" << std::endl;
        std::cout << "5. Поиск элемента в массиве" << std::endl;
        std::cout << "6. Задание варианта" << std::endl;
        std::cout << "Выберите пункт: ";
        std::cin >> choice;

        switch (choice) {
        case 0:
            std::cout << "Выход в главное меню..." << std::endl;
            break;

        case 1:
            viewArray(arr);
            break;

        case 2: {
            int element;
            std::cout << "Введите элемент: ";
            std::cin >> element;
            arr.insert(arr.begin(), element);
            std::cout << "После добавления: ";
            viewArray(arr);
            break;
        }

        case 3: {
            int element;
            std::cout << "Введите элемент: ";
            std::cin >> element;
            arr.push_back(element);
            std::cout << "После добавления: ";
            viewArray(arr);
            break;
        }

        case 4:
            arr.clear();
            std::cout << "Массив очищен" << std::endl;
            break;

        case 5: {
            int element;
            std::cout << "Введите элемент для поиска: ";
            std::cin >> element;
            searchElement(arr, element);
            break;
        }

        case 6:
            variantTask(arr);
            break;

        default:
            std::cout << "Неверный выбор!" << std::endl;
        }
    } while (choice != 0);
}

// ПУНКТ 2

const int SIZE = 10;

void sortByValue(std::array<int, SIZE> arr, bool ascending) {
    for (int i = 0; i < SIZE - 1; i++) {
        for (int j = i + 1; j < SIZE; j++) {
            if ((ascending && arr[i] > arr[j]) || (!ascending && arr[i] < arr[j])) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
    std::cout << "Внутри функции (по значению): ";
    for (int i = 0; i < SIZE; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

void sortByReference(std::array<int, SIZE>& arr, bool ascending) {
    for (int i = 0; i < SIZE - 1; i++) {
        for (int j = i + 1; j < SIZE; j++) {
            if ((ascending && arr[i] > arr[j]) || (!ascending && arr[i] < arr[j])) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

void sortByPointer(std::array<int, SIZE>* arr, bool ascending) {
    for (int i = 0; i < SIZE - 1; i++) {
        for (int j = i + 1; j < SIZE; j++) {
            if ((ascending && (*arr)[i] > (*arr)[j]) || (!ascending && (*arr)[i] < (*arr)[j])) {
                int temp = (*arr)[i];
                (*arr)[i] = (*arr)[j];
                (*arr)[j] = temp;
            }
        }
    }
}

void printArray(const std::array<int, SIZE>& arr) {
    for (int i = 0; i < SIZE; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

// пункт 2 функция
void menuPunkt2() {
    std::srand(std::time(0));
    std::array<int, SIZE> arr;

    for (int i = 0; i < SIZE; i++) {
        arr[i] = std::rand() % 21 - 10;
    }

    std::cout << "Исходный массив: ";
    printArray(arr);

    std::cout << "\n=== Передача по ЗНАЧЕНИЮ ===" << std::endl;
    std::cout << "До вызова функции: ";
    printArray(arr);
    sortByValue(arr, true);
    std::cout << "После вызова функции: ";
    printArray(arr);
    std::cout << "Вывод: массив НЕ изменился, так как передавалась КОПИЯ" << std::endl;

    std::cout << "\n=== Передача по ССЫЛКЕ ===" << std::endl;
    std::cout << "До вызова функции: ";
    printArray(arr);
    sortByReference(arr, true);
    std::cout << "После вызова функции: ";
    printArray(arr);
    std::cout << "Вывод: массив ИЗМЕНИЛСЯ, так как передавалась ССЫЛКА на оригинал" << std::endl;

    std::cout << "\n=== Передача по УКАЗАТЕЛЮ ===" << std::endl;
    for (int i = 0; i < SIZE; i++) {
        arr[i] = std::rand() % 21 - 10;
    }
    std::cout << "Новый исходный массив: ";
    printArray(arr);
    sortByPointer(&arr, false);
    std::cout << "После вызова функции: ";
    printArray(arr);
    std::cout << "Вывод: массив ИЗМЕНИЛСЯ, так как передавался УКАЗАТЕЛЬ на оригинал" << std::endl;
}

// ГЛАВНОЕ МЕНЮ

int main() {
    setlocale(LC_ALL, "Russian");
    int mainChoice;

    do {
        std::cout << "\n=== ГЛАВНОЕ МЕНЮ ===" << std::endl;
        std::cout << "1. Пункт 1 - Работа с динамическим массивом (vector)" << std::endl;
        std::cout << "2. Пункт 2 - Сравнение способов передачи (array)" << std::endl;
        std::cout << "3. Пункт 3 - Объяснение выбора" << std::endl;
        std::cout << "0. Выход из программы" << std::endl;
        std::cout << "Выберите пункт: ";
        std::cin >> mainChoice;

        switch (mainChoice) {
        case 0:
            std::cout << "Выход из программы..." << std::endl;
            break;
        case 1:
            menuPunkt1();
            break;
        case 2:
            menuPunkt2();
            break;
        case 3:
            std::cout << "\n=== Пункт 3 - Объяснение выбора ===" << std::endl;
            std::cout << "В Пункте 1 использован std::vector потому что:" << std::endl;
            std::cout << "- Нужно динамически изменять размер массива" << std::endl;
            std::cout << "- Выполняются операции добавления и удаления элементов" << std::endl;
            std::cout << "- vector может менять размер во время выполнения программы" << std::endl;
            std::cout << std::endl;
            std::cout << "В Пункте 2 использован std::array потому что:" << std::endl;
            std::cout << "- Размер массива фиксированный (10 элементов)" << std::endl;
            std::cout << "- Размер известен на этапе компиляции" << std::endl;
            std::cout << "- array более эффективен для массивов постоянного размера" << std::endl;
            std::cout << std::endl;
            std::cout << "Почему здесь нет выбора:" << std::endl;
            std::cout << "- В Пункте 1 НЕВОЗМОЖНО использовать array, потому что array" << std::endl;
            std::cout << "  имеет фиксированный размер и не может его менять" << std::endl;
            std::cout << "- В Пункте 2 можно было использовать vector, но array" << std::endl;
            std::cout << "  более подходит для массивов с известным размером" << std::endl;
            std::cout << std::endl;
            std::cout << "Когда vector и array выполняют одинаковую роль:" << std::endl;
            std::cout << "- Только когда размер массива известен и не меняется" << std::endl;
            std::cout << "- В остальных случаях vector более гибкий" << std::endl;
            break;
        default:
            std::cout << "Неверный выбор!" << std::endl;
        }
    } while (mainChoice != 0);

    return 0;
}