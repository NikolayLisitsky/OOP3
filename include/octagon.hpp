#pragma once

#include "figure.hpp"

class Octagon : public Figure {
public:
    Octagon() = default;
    Octagon(const Point& center, double radius);
    Octagon(Octagon&& other) noexcept;
    
    Point center() const override;
    operator double() const override;
    void print(std::ostream& os) const override;
    void read(std::istream& is) override;
    bool operator==(const Figure& other) const override;
    Octagon(const Octagon& other); 
    Figure* clone() const override;
    
    Octagon& operator=(const Octagon& other);
    Octagon& operator=(Octagon&& other) noexcept;
    
private:
    Point center_point;
    double radius;
    std::vector<Point> vertices;
};