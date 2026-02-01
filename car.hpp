#ifndef CAR_HPP
#define CAR_HPP

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
        double fuel_level_;  // новое поле уровень топлива
        static int total_cars_;  // статическое поле для подсчета объектов

        bool is_mileage_valid_(int mileage) const {
            return mileage >= 0;
        }

        bool is_fuel_valid_(double fuel) const {  // проверка уровня топлива
            return fuel >= 0 && fuel <= 100;
        }

        bool check_license_format_(const std::string& plate) const;

    protected:
        void show_protected_info_() const {
            std::cout << "[Protected доступ] Марка авто: " << brand_ << std::endl;
        }

        std::string car_color_ = "Не указан";

    public:
        // конструкторы и деструктор
        Car();  // конструктор по умолчанию
        Car(const std::string& brand, const std::string& model,
            const std::string& body_number, const std::string& license_plate,
            int mileage, double fuel_level = 100.0);  // добавлен параметр fuel_level
        Car(const Car& other);  // конструктор копирования
        ~Car();  // деструктор

        // операторы
        Car& operator=(const Car& other);  // оператор присваивания
        Car operator+(double fuel) const;  // оператор + для заправки
        Car operator-(double fuel) const;  // оператор - для расхода топлива
        bool operator==(const Car& other) const;  // оператор сравнения

        // геттеры
        std::string get_brand() const { return brand_; }
        std::string get_model() const { return model_; }
        std::string get_body_number() const { return body_number_; }
        std::string get_license_plate() const { return license_plate_; }
        int get_mileage() const { return mileage_; }
        double get_fuel_level() const { return fuel_level_; }
        static int get_total_cars() { return total_cars_; }

        // сеттеры
        void set_body_number(const std::string& body_number) {
            body_number_ = body_number;
        }

        void set_license_plate(const std::string& license_plate);
        void set_fuel_level(double fuel_level);

        // методы
        void print_info() const;
        void rollback_mileage(int x);
        void drive(int distance);
        void refuel(double liters);  // метод заправки
        void consume_fuel(double liters);  // метод расхода топлива
        void check_fuel_status() const;  // проверка уровня топлива

        void set_color(const std::string& color) {
            car_color_ = color;
            std::cout << "Цвет автомобиля установлен: " << car_color_ << std::endl;
        }

        void show_color() const {
            std::cout << "Цвет автомобиля: " << car_color_ << std::endl;
        }
    };

} 

#endif