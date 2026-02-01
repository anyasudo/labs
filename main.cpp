#include "car.hpp"

int main() {
    setlocale(LC_ALL, "Ru");
    try {
        std::cout << "=== Создание car1 с конструктором по умолчанию ===" << std::endl;
        mt::Car car1;
        car1.print_info();

        // работа с protected данными через публичные методы
        car1.show_color();
        car1.set_color("Красный");
        car1.show_color();

        std::cout << "\n=== Создание car2 с конструктором с параметрами ===" << std::endl;
        mt::Car car2("Toyota", "Camry", "123456789", "А123ВС", 50000, 75.5);
        car2.print_info();

        std::cout << "\n=== Создание car3 как копии car2 ===" << std::endl;
        mt::Car car3 = car2;
        car3.print_info();

        std::cout << "\n=== Тестирование оператора присваивания ===" << std::endl;
        mt::Car car4;
        car4 = car2;  // использование оператора =
        std::cout << "После присваивания car4 = car2:" << std::endl;
        car4.print_info();

        std::cout << "\n=== Тестирование операторов + и - ===" << std::endl;
        car1.set_fuel_level(50.0);
        std::cout << "car1 до заправки: ";
        car1.check_fuel_status();

        // использование оператора +
        mt::Car car5 = car1 + 30.0;
        std::cout << "car5 после заправки: ";
        car5.check_fuel_status();

        // использование оператора -
        mt::Car car6 = car5 - 20.0;
        std::cout << "car6 после расхода: ";
        car6.check_fuel_status();

        std::cout << "\n=== Тестирование оператора сравнения ===" << std::endl;
        std::cout << "car2 == car3: " << (car2 == car3 ? "true" : "false") << std::endl;
        std::cout << "car2 == car4: " << (car2 == car4 ? "true" : "false") << std::endl;
        std::cout << "car1 == car2: " << (car1 == car2 ? "true" : "false") << std::endl;

        std::cout << "\n=== Тестирование сеттеров на car1 ===" << std::endl;
        car1.set_body_number("987654321");
        car1.set_license_plate("М456ОР");
        car1.print_info();

        std::cout << "\n=== Тестирование метода поездки ===" << std::endl;
        car1.set_fuel_level(100.0);
        car1.drive(100);
        car1.print_info();

        std::cout << "\n=== Тестирование скручивания пробега ===" << std::endl;
        car1.rollback_mileage(50);
        car1.print_info();

        std::cout << "\n=== Тестирование методов работы с топливом ===" << std::endl;
        car1.set_fuel_level(30.0);
        car1.check_fuel_status();
        car1.refuel(40.0);
        car1.check_fuel_status();
        car1.consume_fuel(25.0);
        car1.check_fuel_status();

        std::cout << "\n=== Тестирование геттеров ===" << std::endl;
        std::cout << "Марка: " << car2.get_brand() << std::endl;
        std::cout << "Модель: " << car2.get_model() << std::endl;
        std::cout << "Пробег: " << car2.get_mileage() << " км" << std::endl;
        std::cout << "Топливо: " << car2.get_fuel_level() << "%" << std::endl;
        std::cout << "Всего автомобилей: " << mt::Car::get_total_cars() << std::endl;

        // тест на ошибки с пробегом
        std::cout << "\n=== Тестирование обработки ошибок ===" << std::endl;
        try {
            car1.rollback_mileage(1000); // больше чем пробег
        }
        catch (const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << std::endl;
        }

        // тесты с созданием авто с ошибками
        std::cout << "\n=== Тесты создания авто с ошибками ===" << std::endl;
        try {
            std::cout << "\nПопытка создать машину с отрицательным пробегом:" << std::endl;
            mt::Car error_car("BMW", "X5", "555555", "Х555ХХ", -100, 50.0);
        }
        catch (const std::exception& e) {
            std::cout << "Ошибка при создании: " << e.what() << std::endl;
        }

        try {
            std::cout << "\nПопытка создать машину с неправильным уровнем топлива:" << std::endl;
            mt::Car error_car("BMW", "X5", "555555", "Х555ХХ", 10000, 150.0);
        }
        catch (const std::exception& e) {
            std::cout << "Ошибка при создании: " << e.what() << std::endl;
        }

        try {
            std::cout << "\nПопытка проехать без достаточного топлива:" << std::endl;
            car2.set_fuel_level(5.0);
            car2.drive(100);
        }
        catch (const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << std::endl;
        }

        std::cout << "\n=== Примеры правильных номеров ===" << std::endl;
        std::cout << "Правильные номера: А123ВС, Е456КМ, О789РТ, Х123СТ" << std::endl;
        std::cout << "Неправильные: Я123ВС (Я не разрешена), АБВ123 (буквы не там), 123АВС (начинается с цифры)" << std::endl;

    }
    catch (const std::exception& e) {
        std::cerr << "Исключение: " << e.what() << std::endl;
    }

    std::cout << "\n=== Конец программы ===" << std::endl;
    return 0;
}