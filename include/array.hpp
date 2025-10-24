#pragma once

#include "figure.hpp"

class Array {
private:
    Figure** figures;       // Массив указателей на фигуры
    size_t capacity;        // Вместимость массива
    size_t size;           // Текущий размер

    void resize();         // Увеличение размера массива

public:
    Array();
    ~Array();
    
    void add(Figure* figure); 
    void remove(size_t index);  
    Figure* get(size_t index) const; 
    size_t getSize() const;       
    void clear(); 
    
    // Запрещаем копирование и присваивание 
    Array(const Array&) = delete;
    Array& operator=(const Array&) = delete;
};