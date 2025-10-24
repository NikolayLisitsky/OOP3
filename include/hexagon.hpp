#pragma once

#include "figure.hpp"

class Hexagon : public Figure {
public:
    Hexagon() = default;
    Hexagon(const Point& center, double radius);
    Hexagon(Hexagon&& other) noexcept;
    Point center() const override;
    operator double() const override;
    void print(std::ostream& os) const override;
    void read(std::istream& is) override;
    bool operator==(const Figure& other) const override;
    Hexagon(const Hexagon& other); 
    Figure* clone() const override;
    
    Hexagon& operator=(const Hexagon& other);
    Hexagon& operator=(Hexagon&& other) noexcept;
    
private:
    Point center_;
    double radius;
    std::vector<Point> vertices;
};
