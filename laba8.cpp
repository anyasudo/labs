#include <iostream>
#include <string>

struct Book {
    std::string title;
    int volume;
    int pages;
};

struct AuthorCollection {
    std::string author;
    Book* books;    // динамический массив книг чтобы можно было добавлять книги
    int count;
    int capacity;

    AuthorCollection(std::string name) : author(name), books(nullptr), count(0), capacity(0) {}
};

struct ReadingQueue {
    std::string* authors;
    std::string* titles;
    int* volumes;
    int count;
    int capacity;

    ReadingQueue() : authors(nullptr), titles(nullptr), volumes(nullptr), count(0), capacity(0) {}
};

AuthorCollection* collections[4];
ReadingQueue summer_queue;

void add_book_to_collection(AuthorCollection* author, std::string title, int volume, int pages) {
    for (int i = 0; i < author->count; i++) {
        if (author->books[i].volume == volume) {
            std::cout << "Том " << volume << " уже существует!\n";
            return;
        }
    }

    // увеличиваем массив
    if (author->count >= author->capacity) {
        int new_capacity = author->capacity == 0 ? 2 : author->capacity * 2;
        Book* new_books = new Book[new_capacity];

        for (int i = 0; i < author->count; i++) {
            new_books[i] = author->books[i];
        }

        delete[] author->books;
        author->books = new_books;
        author->capacity = new_capacity;
    }

    // находим позицию для вставки по возрастанию номера
    int pos = author->count;
    for (int i = 0; i < author->count; i++) {
        if (author->books[i].volume > volume) {
            pos = i;
            break;
        }
    }

    for (int i = author->count; i > pos; i--) {
        author->books[i] = author->books[i - 1];
    }

    author->books[pos].title = title;
    author->books[pos].volume = volume;
    author->books[pos].pages = pages;
    author->count++;
}

void show_author_books(AuthorCollection* author) {
    std::cout << "\n" << author->author << ":\n";
    if (author->count == 0) {
        std::cout << "  Нет книг\n";
        return;
    }

    for (int i = 0; i < author->count; i++) {
        std::cout << "  " << author->books[i].title << ", том "
            << author->books[i].volume << ", "
            << author->books[i].pages << " стр.";

        if (i < author->count - 1) {
            std::cout << " -> след. том: " << author->books[i + 1].volume;
        }
        std::cout << "\n";
    }
}

void show_all_books() {
    std::cout << "\n=== ВСЕ СОБРАНИЯ ===\n";
    for (int i = 0; i < 4; i++) {
        show_author_books(collections[i]);
    }
}

void add_new_book_menu() {
    int author_num;
    std::cout << "\nВыберите автора:\n";
    for (int i = 0; i < 4; i++) {
        std::cout << i + 1 << ". " << collections[i]->author << "\n";
    }
    std::cin >> author_num;

    if (author_num < 1 || author_num > 4) {
        std::cout << "Неверный выбор!\n";
        return;
    }

    AuthorCollection* author = collections[author_num - 1];

    std::string title;
    int volume, pages;

    std::cout << "Название книги: ";
    std::cin.ignore();
    std::getline(std::cin, title);

    std::cout << "Номер тома: ";
    std::cin >> volume;

    std::cout << "Количество страниц: ";
    std::cin >> pages;

    add_book_to_collection(author, title, volume, pages);
}

void find_hard_or_easy_book(int type) {
    int author_num;
    std::cout << "\nВыберите автора:\n";
    for (int i = 0; i < 4; i++) {
        std::cout << i + 1 << ". " << collections[i]->author << "\n";
    }
    std::cin >> author_num;

    if (author_num < 1 || author_num > 4) {
        std::cout << "Неверный выбор!\n";
        return;
    }

    AuthorCollection* author = collections[author_num - 1];

    if (author->count == 0) {
        std::cout << "У автора нет книг!\n";
        return;
    }

    int result_idx = 0;
    for (int i = 1; i < author->count; i++) {
        if (type == 1) {
            if (author->books[i].pages > author->books[result_idx].pages) {
                result_idx = i;
            }
        }
        else {
            if (author->books[i].pages < author->books[result_idx].pages) {
                result_idx = i;
            }
        }
    }

    if (type == 1) {
        std::cout << "\nСамая сложная книга: ";
    }
    else {
        std::cout << "\nСамая легкая книга: ";
    }

    std::cout << author->books[result_idx].title << " (том "
        << author->books[result_idx].volume << ", "
        << author->books[result_idx].pages << " стр.)\n";
}

void add_to_reading_queue() {
    show_all_books();

    int author_num, volume_num;
    std::cout << "\nВыберите автора (1-4): ";
    std::cin >> author_num;

    if (author_num < 1 || author_num > 4) {
        std::cout << "Неверный выбор!\n";
        return;
    }

    AuthorCollection* author = collections[author_num - 1];

    std::cout << "Введите номер тома: ";
    std::cin >> volume_num;

    int book_idx = -1;
    for (int i = 0; i < author->count; i++) {
        if (author->books[i].volume == volume_num) {
            book_idx = i;
            break;
        }
    }

    if (book_idx == -1) {
        std::cout << "Книга не найдена!\n";
        return;
    }

    if (summer_queue.count >= summer_queue.capacity) {
        int new_capacity = summer_queue.capacity == 0 ? 2 : summer_queue.capacity * 2;

        std::string* new_authors = new std::string[new_capacity];
        std::string* new_titles = new std::string[new_capacity];
        int* new_volumes = new int[new_capacity];

        for (int i = 0; i < summer_queue.count; i++) {
            new_authors[i] = summer_queue.authors[i];
            new_titles[i] = summer_queue.titles[i];
            new_volumes[i] = summer_queue.volumes[i];
        }

        delete[] summer_queue.authors;
        delete[] summer_queue.titles;
        delete[] summer_queue.volumes;

        summer_queue.authors = new_authors;
        summer_queue.titles = new_titles;
        summer_queue.volumes = new_volumes;
        summer_queue.capacity = new_capacity;
    }

    summer_queue.authors[summer_queue.count] = author->author;
    summer_queue.titles[summer_queue.count] = author->books[book_idx].title;
    summer_queue.volumes[summer_queue.count] = author->books[book_idx].volume;
    summer_queue.count++;

    std::cout << "Книга добавлена в очередь чтения!\n";
}

void show_reading_queue() {
    if (summer_queue.count == 0) {
        std::cout << "\nОчередь чтения пуста!\n";
        return;
    }

    std::cout << "\n=== ОЧЕРЕДЬ ЧТЕНИЯ НА ЛЕТО ===\n";
    for (int i = 0; i < summer_queue.count; i++) {
        std::cout << i + 1 << ". " << summer_queue.authors[i] << " - "
            << summer_queue.titles[i] << " (том "
            << summer_queue.volumes[i] << ")";

        if (i < summer_queue.count - 1) {
            std::cout << " -> следующая: " << summer_queue.titles[i + 1];
        }
        std::cout << "\n";
    }
}

int main() {
    setlocale(LC_ALL, "Ru");

    collections[0] = new AuthorCollection("Лев Толстой");
    collections[1] = new AuthorCollection("Фёдор Достоевский");
    collections[2] = new AuthorCollection("Антон Чехов");
    collections[3] = new AuthorCollection("Михаил Булгаков");

    add_book_to_collection(collections[0], "Война и мир часть 1", 1, 450);
    add_book_to_collection(collections[0], "Война и мир часть 2", 2, 420);
    add_book_to_collection(collections[0], "Анна Каренина", 7, 380);
    add_book_to_collection(collections[0], "Воскресение", 9, 350);

    add_book_to_collection(collections[1], "Преступление и наказание", 1, 550);
    add_book_to_collection(collections[1], "Идиот", 3, 480);
    add_book_to_collection(collections[1], "Братья Карамазовы", 5, 620);

    add_book_to_collection(collections[2], "Рассказы", 1, 280);
    add_book_to_collection(collections[2], "Вишневый сад", 4, 120);
    add_book_to_collection(collections[2], "Три сестры", 7, 150);

    add_book_to_collection(collections[3], "Белая гвардия", 1, 350);
    add_book_to_collection(collections[3], "Мастер и Маргарита", 3, 480);
    add_book_to_collection(collections[3], "Собачье сердце", 6, 220);

    std::cout << "=== БИБЛИОТЕКА СОБРАНИЙ СОЧИНЕНИЙ ===\n";

    while (true) {
        std::cout << "\n========= МЕНЮ =========\n";
        std::cout << "1. Показать все книги\n";
        std::cout << "2. Добавить новую книгу\n";
        std::cout << "3. Найти самую сложную книгу\n";
        std::cout << "4. Найти самую легкую книгу\n";
        std::cout << "5. Добавить в очередь чтения\n";
        std::cout << "6. Показать очередь чтения\n";
        std::cout << "0. Выход\n";
        std::cout << "=======================\n";

        int choice;
        std::cout << "Введите номер: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            show_all_books();
            break;
        case 2:
            add_new_book_menu();
            break;
        case 3:
            find_hard_or_easy_book(1);
            break;
        case 4:
            find_hard_or_easy_book(0);
            break;
        case 5:
            add_to_reading_queue();
            break;
        case 6:
            show_reading_queue();
            break;
        case 0:
            std::cout << "Выход...\n";

            for (int i = 0; i < 4; i++) {
                delete[] collections[i]->books;
                delete collections[i];
            }
            delete[] summer_queue.authors;
            delete[] summer_queue.titles;
            delete[] summer_queue.volumes;

            return 0;
        default:
            std::cout << "Неверный выбор!\n";
        }
    }

    return 0;
}