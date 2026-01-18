#include <iostream>
#include <string>
#include <stdexcept>

namespace mt {

    class Car {
    private:
        std::string brand_;
        std::string model_;
        std::string body_number_;
        std::string license_plate_;
        int mileage_;

        bool is_mileage_valid_(int mileage) const {
            return mileage >= 0;
        }

    public:
        // конструктор по умолчанию
        Car() : brand_("Неизвестно"), model_("Неизвестно"),
            body_number_("000000"), license_plate_("А000АА"),
            mileage_(0) {
            std::cerr << "Вызван конструктор по умолчанию" << std::endl;
        }

        // конструктор полного заполнения
        Car(const std::string& brand, const std::string& model,
            const std::string& body_number, const std::string& license_plate,
            int mileage) :
            brand_(brand), model_(model), body_number_(body_number),
            license_plate_(license_plate), mileage_(mileage) {

            if (!is_mileage_valid_(mileage)) {
                throw std::invalid_argument("Пробег должен быть неотрицательным");
            }
            std::cerr << "Вызван конструктор с параметрами" << std::endl;
        }

        // конструктор копирования
        Car(const Car& other) :
            brand_(other.brand_), model_(other.model_),
            body_number_(other.body_number_),
            license_plate_(other.license_plate_),
            mileage_(other.mileage_) {
            std::cerr << "Вызван конструктор копирования" << std::endl;
        }

        // деструктор
        ~Car() {
            std::cerr << "Вызван деструктор для " << brand_ << " " << model_ << std::endl;
        }

        // геттеры
        std::string get_brand() const { return brand_; }
        std::string get_model() const { return model_; }
        std::string get_body_number() const { return body_number_; }
        std::string get_license_plate() const { return license_plate_; }
        int get_mileage() const { return mileage_; }

        // сеттер для номера кузова
        void set_body_number(const std::string& body_number) {
            body_number_ = body_number;
        }

        // сеттер для гос. номера
        void set_license_plate(const std::string& license_plate) {
            license_plate_ = license_plate;
        }

        // метод для вывода всей информации
        void print_info() const {
            std::cout << "=== Информация об автомобиле ===" << std::endl;
            std::cout << "Марка: " << brand_ << std::endl;
            std::cout << "Модель: " << model_ << std::endl;
            std::cout << "Номер кузова: " << body_number_ << std::endl;
            std::cout << "Государственный номер: " << license_plate_ << std::endl;
            std::cout << "Пробег: " << mileage_ << " км" << std::endl;
            std::cout << "================================" << std::endl;
        }

        // метод для скручивания пробега на X
        void rollback_mileage(int x) {
            if (x < 0) {
                throw std::invalid_argument("Значение скручивания должно быть неотрицательным");
            }

            if (mileage_ - x < 0) {
                throw std::invalid_argument("Нельзя скрутить больше, чем текущий пробег");
            }

            mileage_ -= x;
            std::cout << "Пробег уменьшен на " << x << " км" << std::endl;
        }

        // метод для увеличения пробега
        void drive(int distance) {
            if (distance < 0) {
                throw std::invalid_argument("Расстояние должно быть неотрицательным");
            }
            mileage_ += distance;
            std::cout << "Автомобиль проехал " << distance << " км" << std::endl;
        }
    };

}

int main() {
    setlocale(LC_ALL, "Ru");
    try {
        std::cout << "=== Создание car1 с конструктором по умолчанию ===" << std::endl;
        mt::Car car1;
        car1.print_info();

        std::cout << "\n=== Создание car2 с конструктором с параметрами ===" << std::endl;
        mt::Car car2("Toyota", "Camry", "123456789", "А123ВС", 50000);
        car2.print_info();

        std::cout << "\n=== Создание car3 как копии car2 ===" << std::endl;
        mt::Car car3 = car2;
        car3.print_info();

        std::cout << "\n=== Тестирование сеттеров на car1 ===" << std::endl;
        car1.set_body_number("987654321");
        car1.set_license_plate("В456СД");
        car1.print_info();

        std::cout << "\n=== Тестирование метода поездки ===" << std::endl;
        car1.drive(100);
        car1.print_info();

        std::cout << "\n=== Тестирование скручивания пробега ===" << std::endl;
        car1.rollback_mileage(50);
        car1.print_info();

        std::cout << "\n=== Тестирование геттеров ===" << std::endl;
        std::cout << "Марка: " << car2.get_brand() << std::endl;
        std::cout << "Модель: " << car2.get_model() << std::endl;
        std::cout << "Пробег: " << car2.get_mileage() << " км" << std::endl;

        // тест на ошибки
        std::cout << "\n=== Тестирование обработки ошибок ===" << std::endl;
        try {
            car1.rollback_mileage(1000); // больше чем пробег
        }
        catch (const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << std::endl;
        }

        // тесты
        std::cout << "\n=== Тесты ===" << std::endl;
        try {
            std::cout << "\nПопытка создать машину с отрицательным пробегом:" << std::endl;
            mt::Car error_car("BMW", "X5", "555555", "Х555ХХ", -100);
        }
        catch (const std::exception& e) {
            std::cout << "Ошибка при создании: " << e.what() << std::endl;
        }

        try {
            std::cout << "\nПопытка проехать отрицательное расстояние:" << std::endl;
            car2.drive(-50);
        }
        catch (const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << std::endl;
        }

        std::cout << "\n=== Создание автомобиля в локальном блоке ===" << std::endl;
        {
            mt::Car local_car("Lada", "Vesta", "111222333", "У777УУ", 15000);
            local_car.drive(200);
            local_car.print_info();
        } // вызывается деструктор для local_car
        std::cout << "Выйти из локального блока" << std::endl;

    }
    catch (const std::exception& e) {
        std::cerr << "Исключение: " << e.what() << std::endl;
    }

    std::cout << "\n=== Конец программы ===" << std::endl;
    return 0;
}