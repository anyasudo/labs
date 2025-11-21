#include <iostream>
#include <cstdlib>

const int ROWS = 2;
const int COLS = 2;

void print_matrix(int** matrix, int rows, int cols) {
    std::cout << "\nМатрица " << rows << "x" << cols << ":\n";
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void create_extended_matrix(int**& matrix, int& rows, int& cols) {
    int a = matrix[0][0];
    int b = matrix[0][1];
    int c = matrix[1][0];
    int d = matrix[1][1];

    int new_rows = ROWS + a;
    int new_cols = COLS + b;

    matrix = (int**)std::realloc(matrix, new_rows * sizeof(int*));

    for (int i = 0; i < new_rows; ++i) {
        if (i < ROWS) {
            matrix[i] = (int*)std::realloc(matrix[i], new_cols * sizeof(int));
        }
        else {
            matrix[i] = (int*)std::malloc(new_cols * sizeof(int));
        }
    }

    for (int i = 0; i < new_rows; ++i) {
        for (int j = 0; j < new_cols; ++j) {
            matrix[i][j] = i * c + j * d;
        }
    }

    rows = new_rows;
    cols = new_cols;
}

int* find_zero_rows(int** matrix, int rows, int cols, int& count) {
    count = 0;

    for (int i = 0; i < rows; i++) {
        bool has_zero = false;
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] == 0) {
                has_zero = true;
                break;
            }
        }
        if (has_zero) {
            count++;
        }
    }

    int* zero_rows = (int*)std::malloc(count * sizeof(int));

    int index = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] == 0) {
                zero_rows[index] = i;
                index++;
                break;
            }
        }
    }

    return zero_rows;
}

void remove_rows(int**& matrix, int& rows, int cols, int* rows_to_remove, int remove_count) {
    if (remove_count == 0 || rows_to_remove == nullptr) {
        return;
    }

    int new_rows = rows - remove_count;

    if (new_rows <= 0) {
        for (int i = 0; i < rows; i++) {
            std::free(matrix[i]);
        }
        std::free(matrix);
        matrix = nullptr;
        rows = 0;
        return;
    }

    int** temp_matrix = (int**)std::malloc(new_rows * sizeof(int*));
    int new_index = 0;

    for (int i = 0; i < rows; i++) {
        bool should_remove = false;
        for (int j = 0; j < remove_count; j++) {
            if (i == rows_to_remove[j]) {
                should_remove = true;
                break;
            }
        }

        if (!should_remove) {
            temp_matrix[new_index] = matrix[i];
            new_index++;
        }
        else {
            std::free(matrix[i]);
        }
    }

    matrix = (int**)std::realloc(matrix, new_rows * sizeof(int*));
    for (int i = 0; i < new_rows; i++) {
        matrix[i] = temp_matrix[i];
    }

    std::free(temp_matrix);
    rows = new_rows;
}

int main() {
    std::setlocale(LC_ALL, "Ru");

    int** matrix = (int**)std::malloc(ROWS * sizeof(int*));
    for (int i = 0; i < ROWS; ++i) {
        matrix[i] = (int*)std::malloc(COLS * sizeof(int));
    }

    std::cout << "Введите элементы матрицы " << ROWS << "x" << COLS << ":" << std::endl;
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            std::cout << "Элемент [" << i << "][" << j << "]: ";
            std::cin >> matrix[i][j];
            if (matrix[i][j] < 0) {
                std::cout << "Ошибка! Число не может быть отрицательным. Повторите ввод." << std::endl;
                j -= 1;
            }
        }
    }

    int rows = ROWS, cols = COLS;
    create_extended_matrix(matrix, rows, cols);

    int zero_count;
    int* zero_rows = find_zero_rows(matrix, rows, cols, zero_count);

    std::cout << "\nНайдено строк с нулевыми элементами: " << zero_count << std::endl;
    if (zero_count > 0) {
        std::cout << "Индексы строк с нулями: ";
        for (int i = 0; i < zero_count; i++) {
            std::cout << zero_rows[i] << " ";
        }
        std::cout << std::endl;
    }

    remove_rows(matrix, rows, cols, zero_rows, zero_count);

    if (matrix != nullptr && rows > 0) {
        print_matrix(matrix, rows, cols);
    }
    else {
        std::cout << "\nВсе строки были удалены!" << std::endl;
    }

    if (zero_rows != nullptr) {
        std::free(zero_rows);
    }

    if (matrix != nullptr) {
        for (int i = 0; i < rows; i++) {
            std::free(matrix[i]);
        }
        std::free(matrix);
    }


    // ВТОРОЙ пункт

    int a, b;
    std::cout << "Введите значение переменной a: ";
    std::cin >> a;
    std::cout << "Введите значение переменной b: ";
    std::cin >> b;
    std::cout << "Исходные значения: a = " << a << ", b = " << b << std::endl;

    int* pa = new int;
    int* pb = new int;
    *pa = a;
    *pb = b;
    std::cout << "После создания указателей: *pa = " << *pa << ", *pb = " << *pb << std::endl;

    *pa = *pa * 2;
    std::cout << "После увеличения a в 2 раза через pa: *pa = " << *pa << std::endl;
    
    int temp = *pa;
    *pa = *pb;
    *pb = temp;
    std::cout << "После обмена значениями через указатели: *pa = " << *pa << ", *pb = " << *pb << std::endl;

    a = *pa;
    b = *pb;
    std::cout << "Финальные значения переменных: a = " << a << ", b = " << b << std::endl;

    delete pa;
    delete pb;

    return 0;
}