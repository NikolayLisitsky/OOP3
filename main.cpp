#include <iostream>
#include "include/array.hpp"
#include "include/pentagon.hpp"
#include "include/hexagon.hpp"
#include "include/octagon.hpp"

// Выводит главное меню программы
void showMenu() {
    std::cout << "\n=== Система управления фигурами ===\n";
    std::cout << "Выберите действие:\n";
    std::cout << "1. Добавить пятиугольник\n";
    std::cout << "2. Добавить шестиугольник\n";
    std::cout << "3. Добавить восьмиугольник\n";
    std::cout << "4. Показать все фигуры\n";
    std::cout << "5. Посчитать общую площадь\n";
    std::cout << "6. Удалить фигуру\n";
    std::cout << "7. Получить фигуру по номеру\n";
    std::cout << "0. Выйти\n";
    std::cout << "Ваш выбор: ";
}

// Выводит все фигуры из массива
void displayFigures(const Array& arr) {
    if (arr.getSize() == 0) {
        std::cout << "Массив пуст.\n";
        return;
    }

    for (size_t i = 0; i < arr.getSize(); ++i) {
        Figure* f = arr.get(i);
        std::cout << "Фигура #" << (i + 1) << ": " << *f
                  << " | Площадь: " << static_cast<double>(*f)
                  << " | Центр: (" << f->center().x << ", " << f->center().y << ")\n";
    }
}

// Считает суммарную площадь всех фигур
double computeTotalArea(const Array& arr) {
    double sum = 0.0;
    for (size_t i = 0; i < arr.getSize(); ++i) {
        sum += static_cast<double>(*arr.get(i));
    }
    return sum;
}

int main() {
    Array container;
    int option;

    do {
        showMenu();
        std::cin >> option;

        switch (option) {
            case 1: {
                auto* p = new Pentagon();
                std::cout << "Введите данные для пятиугольника:\n";
                std::cin >> *p;
                container.add(p);
                std::cout << "Пятиугольник успешно добавлен!\n";
                break;
            }
            case 2: {
                auto* h = new Hexagon();
                std::cout << "Введите данные для шестиугольника:\n";
                std::cin >> *h;
                container.add(h);
                std::cout << "Шестиугольник успешно добавлен!\n";
                break;
            }
            case 3: {
                auto* o = new Octagon();
                std::cout << "Введите данные для восьмиугольника:\n";
                std::cin >> *o;
                container.add(o);
                std::cout << "Восьмиугольник успешно добавлен!\n";
                break;
            }
            case 4:
                displayFigures(container);
                break;
            case 5:
                std::cout << "Общая площадь: " << computeTotalArea(container) << "\n";
                break;
            case 6: {
                size_t idx;
                std::cout << "Номер фигуры для удаления (от 1 до " << container.getSize() << "): ";
                std::cin >> idx;
                if (idx >= 1 && idx <= container.getSize()) {
                    container.remove(idx - 1);
                    std::cout << "Фигура удалена.\n";
                } else {
                    std::cout << "Неверный номер.\n";
                }
                break;
            }
            case 7: {
                size_t idx;
                std::cout << "Номер фигуры для просмотра (от 1 до " << container.getSize() << "): ";
                std::cin >> idx;
                if (idx >= 1 && idx <= container.getSize()) {
                    Figure* f = container.get(idx - 1);
                    std::cout << "Фигура #" << idx << ": " << *f
                              << " | Площадь: " << static_cast<double>(*f)
                              << " | Центр: (" << f->center().x << ", " << f->center().y << ")\n";
                } else {
                    std::cout << "Неверный номер.\n";
                }
                break;
            }
            case 0:
                std::cout << "Завершение работы.\n";
                break;
            default:
                std::cout << "Такого пункта нет. Попробуйте снова.\n";
        }
    } while (option != 0);

    return 0;
}