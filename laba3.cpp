#include <iostream>
#include <limits>

int main()
{
	//Первая часть
	setlocale(LC_ALL, "Russian");
	int n;
	std::cout << "Введите количество чисел последовательности" << std::endl;
	std::cin >> n;

	if (n >= 0) {
		int product = 1;
		int min3 = std::numeric_limits<int>::max();
		int number = 0;
		for (int i = 0; i < n; ++i) {
			int x;
			std::cout << "Введите член последовательности" << std::endl;
			std::cin >> x;
			if (std::abs(x) % 10 == 3) {
				product = product * x;
				if (x < min3) {
					number = i;
				}
				min3 = std::min(min3, x);
			}
		}
		if (product == 1) {
			std::cout << "В последовательности нет членов, которые оканчиваются на 3" << std::endl;
		}
		else {
			std::cout << "Произведение всех чисел, оканчивающихся на 3: " << product << std::endl;
			std::cout << "Минимальное число, оканчивающееся на 3: " << min3 << std::endl;
			std::cout << "Номер минимального числа, оканчивающего на 3: " << number << std::endl;
		}
	}
	else {
		std::cout << "Количество членов последовательности не может быть отрицательным" << std::endl; 
	}

	//Вторая часть
	short y;
	std::cout << "Введите число, для которого нужно посчитать сумму цифр" << std::endl;
	std::cin >> y;
	short summ = 0;
	while (y > 0) {
		summ += std::abs(y) % 10;
		y = y / 10;
	}
	std::cout << "Cумма цифр = " << summ << std::endl;

}