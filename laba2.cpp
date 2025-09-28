#include <iostream>

int main()
{
	setlocale(LC_ALL, "Russian");
	// Первая часть
	int A;
	int i;
	std::cout << "Введите число A" << std::endl;
	std::cin >> A;
	std::cout << "Введите номер бита i" << std::endl;
	std::cin >> i;

	int bit = (A >> i) & 1;

	if (bit == 1) {
		std::cout << "Три последовательных сдвига вправо числа A:" << std::endl;
		std::cout << (A >> 1) << std::endl;
		std::cout << (A >> 2) << std::endl;
		std::cout << (A >> 3) << std::endl;
	}

	else {
		int M;
		std::cout << "Введите число M" << std::endl;
		std::cin >> M;
		if (M > 5) {
			std::cout << "M больше 5 на " << M - 5 << std::endl;
		}
		else if (M == 5) {
			std::cout << "M равно пяти" << std::endl;
		}
		else {
			std::cout << "M меньше 5 на " << 5 - M << std::endl;
		}

	}

	// Вторая часть
	short N;
	std::cout << "Введите номер дня недели" << std::endl;
	std::cin >> N;
	switch (N)
	{
	case 1: std::cout << "Понедельник"; break;
	case 2: std::cout << "Вторник"; break;
	case 3: std::cout << "Среда"; break;
	case 4: std::cout << "Четверг"; break;
	case 5: std::cout << "Пятница"; break;
	case 6: std::cout << "Суббота"; break;
	case 7: std::cout << "Воскресенье"; break;
	default: std::cout << "Неверно указан день недели"; break;
	}
	return 0;

}
