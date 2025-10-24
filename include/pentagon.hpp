#pragma once

#include "figure.hpp"

class Pentagon : public Figure {
public:
    Pentagon() = default;
    Pentagon(const Point& center, double radius);
    Pentagon(Pentagon&& other) noexcept;
    
    Point center() const override;
    operator double() const override;
    void print(std::ostream& os) const override;
    void read(std::istream& is) override;
    bool operator==(const Figure& other) const override;
    Pentagon(const Pentagon& other); 
    Figure* clone() const override;
    
    Pentagon& operator=(const Pentagon& other); // Копирование
    Pentagon& operator=(Pentagon&& other) noexcept; // Перемещение
    
private:
    Point center_point;
    double radius;
    std::vector<Point> vertices;
};
