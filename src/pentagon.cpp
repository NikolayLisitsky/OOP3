#include "../include/pentagon.hpp"
#include <cmath>

const double PI = 3.14159265358979323846;

Pentagon::Pentagon(const Pentagon& other) 
    : center_point(other.center_point), radius(other.radius) {
    vertices = other.vertices;
}

Pentagon::Pentagon(const Point& center, double radius) 
    : center_point(center), radius(radius) {
    vertices.resize(5);
    for (int i = 0; i < 5; ++i) {
        double angle = 2 * PI * i / 5;
        vertices[i] = Point(center.x + radius * cos(angle), 
                           center.y + radius * sin(angle));
    }
}

Pentagon::Pentagon(Pentagon&& other) noexcept
    : center_point(std::move(other.center_point))
    , radius(other.radius)
    , vertices(std::move(other.vertices))
{
    other.radius = 0.0;
}

Point Pentagon::center() const {
    return center_point;
}

Pentagon::operator double() const {
    // Площадь правильного пятиугольника: (5/2) * R² * sin(72°)
    double side = 2 * radius * sin(PI / 5);
    return 0.25 * sqrt(5 * (5 + 2 * sqrt(5))) * side * side;
}

void Pentagon::print(std::ostream& os) const {
    os << "Pentagon vertices: [";
    for (const auto& vertex : vertices) {
        os << "(" << vertex.x << ", " << vertex.y << ") ";
    }
    os << "]";
}

void Pentagon::read(std::istream& is) {
    std::cout << "Enter Pentagon center (x y): ";
    is >> center_point.x >> center_point.y;
    std::cout << "Enter radius: ";
    is >> radius;
    
    // Пересчитываем вершины
    vertices.resize(5);
    for (int i = 0; i < 5; ++i) {
        double angle = 2 * PI * i / 5;
        vertices[i] = Point(center_point.x + radius * cos(angle), 
                           center_point.y + radius * sin(angle));
    }
}

bool Pentagon::operator==(const Figure& other) const {
    const Pentagon* pentagon = dynamic_cast<const Pentagon*>(&other); // если не 5-угольник - nullptr
    if (!pentagon) return false;
    
    return center_point == pentagon->center_point && 
           std::abs(radius - pentagon->radius) < 1e-9;
}

Figure* Pentagon::clone() const {
    return new Pentagon(this->center_point, this->radius);
}

Pentagon& Pentagon::operator=(const Pentagon& other) {
    if (this != &other) {
        center_point = other.center_point;
        radius = other.radius;
        vertices = other.vertices;
    }
    return *this;
}

Pentagon& Pentagon::operator=(Pentagon&& other) noexcept {
    if (this != &other) {
        center_point = std::move(other.center_point);
        radius = other.radius;
        vertices = std::move(other.vertices);
        other.radius = 0;
    }
    return *this;
}