#include <iostream>
#include "include/array.hpp"
#include "include/pentagon.hpp"
#include "include/hexagon.hpp"
#include "include/octagon.hpp"

void printMenu() {
    std::cout << "\n=== Figure Management System ===" << std::endl;
    std::cout << "Menu:" << std::endl;
    std::cout << "1. Add Pentagon" << std::endl;
    std::cout << "2. Add Hexagon" << std::endl;
    std::cout << "3. Add Octagon" << std::endl;
    std::cout << "4. Print All Figures" << std::endl;
    std::cout << "5. Calculate Total Area" << std::endl;
    std::cout << "6. Remove Figure" << std::endl;
    std::cout << "7. Get Figure by Index" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << "Enter your choice: ";
}

void printAllFigures(const Array& array) {
    if (array.getSize() == 0) {
        std::cout << "No figures in array." << std::endl;
        return;
    }
    
    for (size_t i = 0; i < array.getSize(); ++i) {
        Figure* fig = array.get(i);
        std::cout << "Figure " << i + 1 << ": " << *fig 
                  << ", Area: " << static_cast<double>(*fig) 
                  << ", Center: (" << fig->center().x 
                  << ", " << fig->center().y << ")" << std::endl;
    }
}

double totalArea(const Array& array) {
    double total = 0;
    for (size_t i = 0; i < array.getSize(); ++i) {
        total += static_cast<double>(*array.get(i));
    }
    return total;
}

int main() {
    Array figuresArray;
    int choice;
    
    do {
        printMenu();
        std::cin >> choice;
        
        switch (choice) {
            case 1: {
                Pentagon* pentagon = new Pentagon();
                std::cin >> *pentagon;
                figuresArray.add(pentagon);
                std::cout << "Pentagon added successfully!" << std::endl;
                break;
            }
            case 2: {
                Hexagon* hexagon = new Hexagon();
                std::cin >> *hexagon;
                figuresArray.add(hexagon);
                std::cout << "Hexagon added successfully!" << std::endl;
                break;
            }
            case 3: {
                Octagon* octagon = new Octagon();
                std::cin >> *octagon;
                figuresArray.add(octagon);
                std::cout << "Octagon added successfully!" << std::endl;
                break;
            }
            case 4:
                printAllFigures(figuresArray);
                break;
            case 5:
                std::cout << "Total area of all figures: " << totalArea(figuresArray) << std::endl;
                break;
            case 6: {
                size_t index;
                std::cout << "Enter index to remove (1-" << figuresArray.getSize() << "): ";
                std::cin >> index;
                if (index >= 1 && index <= figuresArray.getSize()) {
                    figuresArray.remove(index - 1);
                    std::cout << "Figure removed successfully!" << std::endl;
                } else {
                    std::cout << "Invalid index!" << std::endl;
                }
                break;
            }
            case 7: {
                size_t index;
                std::cout << "Enter index to get (1-" << figuresArray.getSize() << "): ";
                std::cin >> index;
                if (index >= 1 && index <= figuresArray.getSize()) {
                    Figure* fig = figuresArray.get(index - 1);
                    std::cout << "Figure " << index << ": " << *fig 
                              << ", Area: " << static_cast<double>(*fig) 
                              << ", Center: (" << fig->center().x 
                              << ", " << fig->center().y << ")" << std::endl;
                } else {
                    std::cout << "Invalid index!" << std::endl;
                }
                break;
            }
            case 0:
                std::cout << "Exit" << std::endl;
                break;
            default:
                std::cout << "Invalid choice!" << std::endl;
        }
    } while (choice != 0);
    
    return 0;
}