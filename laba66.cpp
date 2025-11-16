#include <iostream>
#include <cstdlib>

// функция для поиска строк с нулями
// используем указатели тк нужно вернуть два значения: сколько и какие строки содержат нули
int* findZeroRows(int** mat, int r, int c, int* count) {
    *count = 0;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (mat[i][j] == 0) {
                (*count)++;
                break;
            }
        }
    }

    // создаем массив для индексов строк с нулями
    int* zero_rows = (int*)std::malloc((*count) * sizeof(int));

    // заполняем массив индексами
    int index = 0;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (mat[i][j] == 0) {
                zero_rows[index++] = i;
                break;
            }
        }
    }

    return zero_rows;
}

int main() {
    setlocale(LC_ALL, "Russian");
    int rows = 2, cols = 2;
    int** matrix = (int**)std::malloc(rows * sizeof(int*)); // для строк

    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)std::malloc(cols * sizeof(int)); // для столбцов
    }

    std::cout << "Введите 4 числа для матрицы 2x2:" << std::endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int num;
            std::cin >> num;

            while (num < 0) {
                std::cout << "Ошибка. Введите неотрицательное число: ";
                std::cin >> num;
            }

            matrix[i][j] = num;
        }
    }

    int A = matrix[0][0];  // первое число массива
    int B = matrix[0][1];  // второе число массива  
    int C = matrix[1][0];  // третье число массива
    int D = matrix[1][1];  // четвертое число массива

    std::cout << "\nВзяли значения из массива:" << std::endl;
    std::cout << "A = matrix[0][0] = " << A << " (строки сверху)" << std::endl;
    std::cout << "B = matrix[0][1] = " << B << " (столбцы слева)" << std::endl;
    std::cout << "C = matrix[1][0] = " << C << " (коэффициент C)" << std::endl;
    std::cout << "D = matrix[1][1] = " << D << " (коэффициент D)" << std::endl;

    int new_rows = rows + A;
    int new_cols = cols + B;

    // новая матрица большего размера
    int** new_matrix = (int**)std::malloc(new_rows * sizeof(int*));
    for (int i = 0; i < new_rows; i++) {
        new_matrix[i] = (int*)std::malloc(new_cols * sizeof(int));
    }

    std::cout << "\nЗаполняем новую матрицу по формуле:" << std::endl;
    for (int i = 0; i < new_rows; i++) {
        for (int j = 0; j < new_cols; j++) {
            new_matrix[i][j] = i * C + j * D;
            std::cout << i << "*" << C << " + " << j << "*" << D << " = " << new_matrix[i][j] << "\t";
        }
        std::cout << std::endl;
    }

    // старую матрицу в правый нижний угол новой
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            new_matrix[i + A][j + B] = matrix[i][j];
        }
    }

    std::cout << "\nПосле копирования исходной матрицы:" << std::endl;
    for (int i = 0; i < new_rows; i++) {
        for (int j = 0; j < new_cols; j++) {
            std::cout << new_matrix[i][j] << "\t";
        }
        std::cout << std::endl;
    }

    int zero_count;
    int* zero_rows = findZeroRows(new_matrix, new_rows, new_cols, &zero_count);

    std::cout << "\nНайдено строк с нулями: " << zero_count << std::endl;
    if (zero_count > 0) {
        std::cout << "Индексы строк с нулями: ";
        for (int i = 0; i < zero_count; i++) {
            std::cout << zero_rows[i] << " ";
        }
        std::cout << std::endl;
    }

    // удаляем строки с нулями
    if (zero_count > 0) {
        int final_rows = new_rows - zero_count;
        int** final_matrix = (int**)std::malloc(final_rows * sizeof(int*));

        int new_i = 0;
        for (int i = 0; i < new_rows; i++) {
            bool should_skip = false;

            for (int z = 0; z < zero_count; z++) {
                if (i == zero_rows[z]) {
                    should_skip = true;
                    break;
                }
            }

            if (!should_skip) {
                final_matrix[new_i] = (int*)std::malloc(new_cols * sizeof(int));
                for (int j = 0; j < new_cols; j++) {
                    final_matrix[new_i][j] = new_matrix[i][j];
                }
                new_i++;
            }
        }

        std::cout << "\nИтоговая матрица после удаления строк с нулями:" << std::endl;
        for (int i = 0; i < final_rows; i++) {
            for (int j = 0; j < new_cols; j++) {
                std::cout << final_matrix[i][j] << "\t";
            }
            std::cout << std::endl;
        }

        for (int i = 0; i < final_rows; i++) {
            std::free(final_matrix[i]);
        }
        std::free(final_matrix);
    }
    else {
        std::cout << "В матрице нет строк с нулевыми значениями." << std::endl;
    }

    for (int i = 0; i < rows; i++) {
        std::free(matrix[i]);
    }
    std::free(matrix);

    for (int i = 0; i < new_rows; i++) {
        std::free(new_matrix[i]);
    }
    std::free(new_matrix);

    std::free(zero_rows);

    return 0;
}