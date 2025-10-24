#include <gtest/gtest.h>
#include "../include/figure.hpp"
#include "../include/pentagon.hpp"
#include "../include/hexagon.hpp"
#include "../include/octagon.hpp"

#include <sstream>
#include "../include/array.hpp"

// Тесты для Array
TEST(ArrayTest, AddAndGet) {
    Array arr;
    Pentagon* p = new Pentagon(Point(0, 0), 2.0);
    Hexagon* h = new Hexagon(Point(1, 1), 3.0);
    Octagon* o = new Octagon(Point(2, 2), 4.0);

    arr.add(p);
    arr.add(h);
    arr.add(o);

    EXPECT_EQ(arr.getSize(), 3);
    EXPECT_TRUE(dynamic_cast<Pentagon*>(arr.get(0)) != nullptr);
    EXPECT_TRUE(dynamic_cast<Hexagon*>(arr.get(1)) != nullptr);
    EXPECT_TRUE(dynamic_cast<Octagon*>(arr.get(2)) != nullptr);
}

TEST(ArrayTest, Remove) {
    Array arr;
    Pentagon* p1 = new Pentagon(Point(0, 0), 1.0);
    Pentagon* p2 = new Pentagon(Point(1, 1), 1.0);
    Pentagon* p3 = new Pentagon(Point(2, 2), 1.0);

    arr.add(p1);
    arr.add(p2);
    arr.add(p3);

    arr.remove(1); // удаляем p2

    EXPECT_EQ(arr.getSize(), 2);
    EXPECT_TRUE(*dynamic_cast<Pentagon*>(arr.get(0)) == *p1);
    EXPECT_TRUE(*dynamic_cast<Pentagon*>(arr.get(1)) == *p3);

    // Удалим всё
    arr.remove(0);
    arr.remove(0);
    EXPECT_EQ(arr.getSize(), 0);
}

TEST(ArrayTest, Clear) {
    Array arr;
    arr.add(new Pentagon(Point(0, 0), 1.0));
    arr.add(new Hexagon(Point(1, 1), 2.0));
    arr.clear();
    EXPECT_EQ(arr.getSize(), 0);
}

TEST(ArrayTest, OutOfBounds) {
    Array arr;
    EXPECT_EQ(arr.get(0), nullptr);
    arr.remove(0); // должно безопасно игнорироваться
    EXPECT_EQ(arr.getSize(), 0);
}

TEST(ArrayTest, Resize) {
    Array arr;
    // capacity = 10 по умолчанию
    for (int i = 0; i < 15; ++i) {
        arr.add(new Pentagon(Point(i, i), 1.0));
    }
    EXPECT_EQ(arr.getSize(), 15);
    EXPECT_GE(arr.get(14) != nullptr, true);
}

// Тесты клонирования
TEST(CloneTest, PentagonClone) {
    Pentagon orig(Point(1, 2), 3.5);
    Figure* clone = orig.clone();
    Pentagon* p_clone = dynamic_cast<Pentagon*>(clone);
    ASSERT_NE(p_clone, nullptr);
    EXPECT_TRUE(orig == *p_clone);
    delete clone;
}

TEST(CloneTest, HexagonClone) {
    Hexagon orig(Point(-1, -2), 2.5);
    Figure* clone = orig.clone();
    Hexagon* h_clone = dynamic_cast<Hexagon*>(clone);
    ASSERT_NE(h_clone, nullptr);
    EXPECT_TRUE(orig == *h_clone);
    delete clone;
}

TEST(CloneTest, OctagonClone) {
    Octagon orig(Point(5, 5), 4.0);
    Figure* clone = orig.clone();
    Octagon* o_clone = dynamic_cast<Octagon*>(clone);
    ASSERT_NE(o_clone, nullptr);
    EXPECT_TRUE(orig == *o_clone);
    delete clone;
}

// Тесты потокового ввода/вывода
TEST(IOStreamTest, PentagonPrint) {
    Pentagon p(Point(0, 0), 1.0);
    std::ostringstream oss;
    oss << p;
    std::string output = oss.str();
    EXPECT_NE(output.find("Pentagon vertices:"), std::string::npos);
    EXPECT_NE(output.find("(1"), std::string::npos); // первая вершина ~ (1,0)
}

TEST(IOStreamTest, HexagonPrint) {
    Hexagon h(Point(0, 0), 1.0);
    std::ostringstream oss;
    oss << h;
    std::string output = oss.str();
    EXPECT_NE(output.find("Hexagon vertices:"), std::string::npos);
}

TEST(IOStreamTest, OctagonPrint) {
    Octagon o(Point(0, 0), 1.0);
    std::ostringstream oss;
    oss << o;
    std::string output = oss.str();
    EXPECT_NE(output.find("Octagon vertices:"), std::string::npos);
}

// Тесты move-семантики
TEST(MoveTest, PentagonMoveConstructor) {
    Pentagon p1(Point(0, 0), 5.0);
    double area1 = static_cast<double>(p1);
    Pentagon p2(std::move(p1));
    EXPECT_NEAR(static_cast<double>(p2), area1, 0.1);
    // p1 после move может быть в неопределённом, но валидном состоянии
    // (в твоей реализации radius = 0, так что площадь = 0)
    EXPECT_NEAR(static_cast<double>(p1), 0.0, 0.1);
}

TEST(MoveTest, HexagonMoveAssignment) {
    Hexagon h1(Point(1, 1), 3.0);
    Hexagon h2;
    h2 = std::move(h1);
    EXPECT_NEAR(static_cast<double>(h2), 23.38, 0.1);
    EXPECT_NEAR(static_cast<double>(h1), 0.0, 0.1);
}

TEST(MoveTest, OctagonMoveAssignment) {
    Octagon o1(Point(2, 2), 4.0);
    Octagon o2;
    o2 = std::move(o1);
    EXPECT_NEAR(static_cast<double>(o2), 77.25, 0.1);
    EXPECT_NEAR(static_cast<double>(o1), 0.0, 0.1);
}

// Тесты сравнения разных типов
TEST(EqualityTest, DifferentTypes) {
    Pentagon p(Point(0, 0), 5.0);
    Hexagon h(Point(0, 0), 5.0);
    Octagon o(Point(0, 0), 5.0);

    EXPECT_FALSE(p == h);
    EXPECT_FALSE(h == o);
    EXPECT_FALSE(p == o);

    // Сравнение через указатели на Figure
    Figure* fp = &p;
    Figure* fh = &h;
    EXPECT_FALSE(*fp == *fh);
}

// Тест площадей (более точные значения)
TEST(AreaTest, PentagonArea) {
    Pentagon p(Point(0, 0), 1.0);
    // Формула: (5/4) * s^2 * cot(π/5), где s = 2R sin(π/5)
    // Или: (5 * R^2 / 2) * sin(2π/5)
    double expected = (5.0 / 2.0) * 1.0 * sin(2 * M_PI / 5);
    EXPECT_NEAR(static_cast<double>(p), expected, 1e-6);
}

TEST(AreaTest, HexagonArea) {
    Hexagon h(Point(0, 0), 1.0);
    // Правильный шестиугольник: (3√3 / 2) * R²
    double expected = (3 * sqrt(3) / 2) * 1.0;
    EXPECT_NEAR(static_cast<double>(h), expected, 1e-6);
}

TEST(AreaTest, OctagonArea) {
    Octagon o(Point(0, 0), 1.0);
    // 2 * (1 + √2) * R²
    double expected = 2 * (1 + sqrt(2));
    EXPECT_NEAR(static_cast<double>(o), expected, 1e-6);
}