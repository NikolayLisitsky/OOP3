#include "../include/octagon.hpp"
#include <cmath>

const double PI = 3.14159265358979323846;

Octagon::Octagon(const Octagon& other) 
    : center_(other.center_), radius(other.radius) {
    vertices = other.vertices;
}

Octagon::Octagon(const Point& center, double radius) 
    : center_(center), radius(radius) {
    vertices.resize(8);
    for (int i = 0; i < 8; ++i) {
        double angle = 2 * PI * i / 8;
        vertices[i] = Point(center.x + radius * cos(angle), 
                           center.y + radius * sin(angle));
    }
}

Octagon::Octagon(Octagon&& other) noexcept
    : center_(std::move(other.center_))
    , radius(other.radius)
    , vertices(std::move(other.vertices))
{
    other.radius = 0.0;
}

Point Octagon::center() const {
    return center_;
}

Octagon::operator double() const {
    // Площадь правильного восьмиугольника: 2 * (1 + √2) * R²
    return 2 * (1 + sqrt(2)) * radius * radius;
}

void Octagon::print(std::ostream& os) const {
    os << "Octagon vertices: [";
    for (const auto& vertex : vertices) {
        os << "(" << vertex.x << ", " << vertex.y << ") ";
    }
    os << "]";
}

void Octagon::read(std::istream& is) {
    std::cout << "Enter Octagon center (x y): ";
    is >> center_.x >> center_.y;
    std::cout << "Enter radius: ";
    is >> radius;
    
    // Пересчитываем вершины
    vertices.resize(8);
    for (int i = 0; i < 8; ++i) {
        double angle = 2 * PI * i / 8;
        vertices[i] = Point(center_.x + radius * cos(angle), 
                           center_.y + radius * sin(angle));
    }
}

bool Octagon::operator==(const Figure& other) const {
    const Octagon* octagon = dynamic_cast<const Octagon*>(&other);
    if (!octagon) return false;
    
    return center_ == octagon->center_ && 
           std::abs(radius - octagon->radius) < 1e-9;
}

Figure* Octagon::clone() const {
    return new Octagon(this->center_, this->radius);
}

Octagon& Octagon::operator=(const Octagon& other) {
    if (this != &other) {
        center_ = other.center_;
        radius = other.radius;
        vertices = other.vertices;
    }
    return *this;
}

Octagon& Octagon::operator=(Octagon&& other) noexcept {
    if (this != &other) {
        center_ = std::move(other.center_);
        radius = other.radius;
        vertices = std::move(other.vertices);
        other.radius = 0;
    }
    return *this;
}