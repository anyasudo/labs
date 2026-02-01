#include "car.hpp"

namespace mt {

    // инициализация статического поля
    int Car::total_cars_ = 0;

    // проверка формата номера
    bool Car::check_license_format_(const std::string& plate) const {
        if (plate.length() != 6) {
            return false;
        }

        std::string allowed_letters = "АВЕКМНОРСТУХ";

        // первый символ должен быть буква из списка
        bool first_ok = false;
        for (char letter : allowed_letters) {
            if (plate[0] == letter) {
                first_ok = true;
                break;
            }
        }

        // 2-4 символы должны быть цифры
        bool digits_ok = true;
        for (int i = 1; i <= 3; i++) {
            if (plate[i] < '0' || plate[i] > '9') {
                digits_ok = false;
                break;
            }
        }

        // 5-6 символы должны быть буквы из списка
        bool last_ok = false;
        for (char letter1 : allowed_letters) {
            for (char letter2 : allowed_letters) {
                if (plate[4] == letter1 && plate[5] == letter2) {
                    last_ok = true;
                    break;
                }
            }
            if (last_ok) break;
        }

        return first_ok && digits_ok && last_ok;
    }

    // Конструктор по умолчанию
    Car::Car() : brand_("Неизвестно"), model_("Неизвестно"),
        body_number_("000000"), license_plate_("А000АА"),
        mileage_(0), fuel_level_(100.0) {
        total_cars_++;
        std::cerr << "Вызван конструктор по умолчанию" << std::endl;
        std::cerr << "Всего автомобилей создано: " << total_cars_ << std::endl;
    }

    // Конструктор полного заполнения
    Car::Car(const std::string& brand, const std::string& model,
        const std::string& body_number, const std::string& license_plate,
        int mileage, double fuel_level) :
        brand_(brand), model_(model), body_number_(body_number),
        license_plate_(license_plate), mileage_(mileage), fuel_level_(fuel_level) {

        if (!is_mileage_valid_(mileage)) {
            throw std::invalid_argument("Пробег должен быть неотрицательным");
        }

        if (!is_fuel_valid_(fuel_level)) {
            throw std::invalid_argument("Уровень топлива должен быть от 0 до 100%");
        }

        // проверка гос. номера
        if (!check_license_format_(license_plate)) {
            throw std::invalid_argument(
                "Гос. номер должен быть в формате: БУКВА + 3 ЦИФРЫ + 2 БУКВЫ\n"
                "Разрешенные буквы: А, В, Е, К, М, Н, О, Р, С, Т, У, Х\n"
                "Пример: А123ВС, М456ОР, Х789ТУ");
        }

        total_cars_++;
        std::cerr << "Вызван конструктор с параметрами" << std::endl;
        std::cerr << "Всего автомобилей создано: " << total_cars_ << std::endl;

        show_protected_info_();
    }

    // Конструктор копирования
    Car::Car(const Car& other) :
        brand_(other.brand_), model_(other.model_),
        body_number_(other.body_number_),
        license_plate_(other.license_plate_),
        mileage_(other.mileage_), fuel_level_(other.fuel_level_) {
        total_cars_++;
        std::cerr << "Вызван конструктор копирования" << std::endl;
        std::cerr << "Всего автомобилей создано: " << total_cars_ << std::endl;
    }

    // деструктор
    Car::~Car() {
        total_cars_--;
        std::cerr << "Вызван деструктор для " << brand_ << " " << model_ << std::endl;
        std::cerr << "Осталось автомобилей: " << total_cars_ << std::endl;
    }

    // оператор присваивания (правило трех)
    Car& Car::operator=(const Car& other) {
        std::cerr << "Вызван оператор присваивания" << std::endl;
        if (this != &other) {  // защита от самоприсваивания
            brand_ = other.brand_;
            model_ = other.model_;
            body_number_ = other.body_number_;
            license_plate_ = other.license_plate_;
            mileage_ = other.mileage_;
            fuel_level_ = other.fuel_level_;
            car_color_ = other.car_color_;
        }
        return *this;
    }

    // оператор + для заправки топлива
    Car Car::operator+(double fuel) const {
        std::cout << "Использован оператор + для заправки " << fuel << " литров" << std::endl;
        Car result = *this;  // копия
        result.refuel(fuel);  // заправка копии
        return result;
    }

    // оператор - для расхода топлива
    Car Car::operator-(double fuel) const {
        std::cout << "Использован оператор - для расхода " << fuel << " литров" << std::endl;
        Car result = *this;  // копия
        result.consume_fuel(fuel);  // расход топлива в копии
        return result;
    }

    // оператор сравнения ==
    bool Car::operator==(const Car& other) const {
        return (brand_ == other.brand_ &&
            model_ == other.model_ &&
            body_number_ == other.body_number_ &&
            license_plate_ == other.license_plate_ &&
            mileage_ == other.mileage_ &&
            fuel_level_ == other.fuel_level_);
    }

    // сеттер для гос. номера с проверкой
    void Car::set_license_plate(const std::string& license_plate) {
        // проверяем номер
        if (!check_license_format_(license_plate)) {
            throw std::invalid_argument(
                "Гос. номер должен быть в формате: БУКВА + 3 ЦИФРЫ + 2 БУКВЫ\n"
                "Разрешенные буквы: А, В, Е, К, М, Н, О, Р, С, Т, У, Х\n"
                "Пример: А123ВС, М456ОР, Х789ТУ");
        }

        license_plate_ = license_plate;
        std::cout << "Гос. номер успешно изменен на: " << license_plate_ << std::endl;
    }

    // сеттер для уровня топлива
    void Car::set_fuel_level(double fuel_level) {
        if (!is_fuel_valid_(fuel_level)) {
            throw std::invalid_argument("Уровень топлива должен быть от 0 до 100%");
        }
        fuel_level_ = fuel_level;
        std::cout << "Уровень топлива установлен: " << fuel_level_ << "%" << std::endl;
    }

    // метод для вывода всей информации
    void Car::print_info() const {
        std::cout << "=== Информация об автомобиле ===" << std::endl;
        std::cout << "Марка: " << brand_ << std::endl;
        std::cout << "Модель: " << model_ << std::endl;
        std::cout << "Номер кузова: " << body_number_ << std::endl;
        std::cout << "Гос. номер: " << license_plate_ << std::endl;
        std::cout << "Пробег: " << mileage_ << " км" << std::endl;
        std::cout << "Уровень топлива: " << fuel_level_ << "%" << std::endl;  // ДОБАВЛЕНО
        std::cout << "================================" << std::endl;
    }

    // метод для скручивания пробега на X
    void Car::rollback_mileage(int x) {
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
    void Car::drive(int distance) {
        if (distance < 0) {
            throw std::invalid_argument("Расстояние должно быть неотрицательным");
        }

        // расход топлива при поездке, условно 10 литров на 100 км
        double fuel_needed = distance * 0.1;
        if (fuel_needed > fuel_level_) {
            throw std::runtime_error("Недостаточно топлива для поездки!");
        }

        mileage_ += distance;
        fuel_level_ -= fuel_needed;
        std::cout << "Автомобиль проехал " << distance << " км" << std::endl;
        std::cout << "Расход топлива: " << fuel_needed << " литров" << std::endl;
    }

    // метод заправки
    void Car::refuel(double liters) {
        if (liters < 0) {
            throw std::invalid_argument("Количество топлива должно быть неотрицательным");
        }

        double new_fuel = fuel_level_ + liters;
        if (new_fuel > 100) {
            fuel_level_ = 100;
            std::cout << "Бак полностью заправлен (100%)" << std::endl;
        }
        else {
            fuel_level_ = new_fuel;
            std::cout << "Заправлено " << liters << " литров. Текущий уровень: " << fuel_level_ << "%" << std::endl;
        }
    }

    // метод расхода топлива
    void Car::consume_fuel(double liters) {
        if (liters < 0) {
            throw std::invalid_argument("Расход топлива должен быть неотрицательным");
        }

        if (liters > fuel_level_) {
            throw std::runtime_error("Недостаточно топлива!");
        }

        fuel_level_ -= liters;
        std::cout << "Израсходовано " << liters << " литров. Осталось: " << fuel_level_ << "%" << std::endl;
    }

    // проверка уровня топлива
    void Car::check_fuel_status() const {
        std::cout << "Уровень топлива: " << fuel_level_ << "%" << std::endl;
        if (fuel_level_ < 10) {
            std::cout << "ВНИМАНИЕ: Низкий уровень топлива! Рекомендуется заправиться." << std::endl;
        }
        else if (fuel_level_ > 90) {
            std::cout << "Бак почти полный." << std::endl;
        }
        else {
            std::cout << "Уровень топлива нормальный." << std::endl;
        }
    }

}