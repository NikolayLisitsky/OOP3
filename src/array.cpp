#include "../include/array.hpp"

Array::Array() : figures(nullptr), capacity(10), size(0) {
    figures = new Figure*[capacity];
    for (size_t i = 0; i < capacity; ++i) {
        figures[i] = nullptr;
    }
}

Array::~Array() {
    clear();
    delete[] figures;
}

void Array::resize() {
    capacity *= 2;
    Figure** newFigures = new Figure*[capacity];
    
    // Копируем старые указатели
    for (size_t i = 0; i < size; ++i) {
        newFigures[i] = figures[i];
    }
    
    // Инициализируем остальные как nullptr
    for (size_t i = size; i < capacity; ++i) {
        newFigures[i] = nullptr;
    }
    
    delete[] figures;
    figures = newFigures;
}

void Array::add(Figure* figure) {
    if (size >= capacity) {
        resize();
    }
    figures[size++] = figure;
}

void Array::remove(size_t index) {
    if (index >= size) return;
    
    delete figures[index];  // Удаляем саму фигуру
    
    // Сдвигаем остальные элементы
    for (size_t i = index; i < size - 1; ++i) {
        figures[i] = figures[i + 1];
    }
    
    figures[--size] = nullptr;
}

Figure* Array::get(size_t index) const {
    if (index >= size) return nullptr;
    return figures[index];
}

size_t Array::getSize() const {
    return size;
}

void Array::clear() {
    for (size_t i = 0; i < size; ++i) {
        delete figures[i];
        figures[i] = nullptr;
    }
    size = 0;
}