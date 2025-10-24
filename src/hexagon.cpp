#include "../include/hexagon.hpp"
#include <cmath>

const double PI = 3.14159265358979323846;

Hexagon::Hexagon(const Hexagon& other) 
    : center_point(other.center_point), radius(other.radius) {
    vertices = other.vertices;
}

Hexagon::Hexagon(const Point& center, double radius) 
    : center_point(center), radius(radius) {
    vertices.resize(6);
    for (int i = 0; i < 6; ++i) {
        double angle = 2 * PI * i / 6;
        vertices[i] = Point(center.x + radius * cos(angle), 
                           center.y + radius * sin(angle));
    }
}

Hexagon::Hexagon(Hexagon&& other) noexcept
    : center_point(std::move(other.center_point))
    , radius(other.radius)
    , vertices(std::move(other.vertices))
{
    other.radius = 0.0;
}

Point Hexagon::center() const {
    return center_point;
}

Hexagon::operator double() const {
    // Площадь правильного шестиугольника: (3√3/2) * R²
    return (3 * sqrt(3) / 2) * radius * radius;
}

void Hexagon::print(std::ostream& os) const {
    os << "Hexagon vertices: [";
    for (const auto& vertex : vertices) {
        os << "(" << vertex.x << ", " << vertex.y << ") ";
    }
    os << "]";
}

void Hexagon::read(std::istream& is) {
    std::cout << "Enter Hexagon center (x y): ";
    is >> center_point.x >> center_point.y;
    std::cout << "Enter radius: ";
    is >> radius;
    
    // Пересчитываем вершины
    vertices.resize(6);
    for (int i = 0; i < 6; ++i) {
        double angle = 2 * PI * i / 6;
        vertices[i] = Point(center_point.x + radius * cos(angle), 
                           center_point.y + radius * sin(angle));
    }
}

bool Hexagon::operator==(const Figure& other) const {
    const Hexagon* hexagon = dynamic_cast<const Hexagon*>(&other);
    if (!hexagon) return false;
    
    return center_point == hexagon->center_point && 
           std::abs(radius - hexagon->radius) < 1e-9;
}

Figure* Hexagon::clone() const {
    return new Hexagon(this->center_point, this->radius);
}

Hexagon& Hexagon::operator=(const Hexagon& other) {
    if (this != &other) {
        center_point = other.center_point;
        radius = other.radius;
        vertices = other.vertices;
    }
    return *this;
}

Hexagon& Hexagon::operator=(Hexagon&& other) noexcept {
    if (this != &other) {
        center_point = std::move(other.center_point);
        radius = other.radius;
        vertices = std::move(other.vertices);
        other.radius = 0;
    }
    return *this;
}