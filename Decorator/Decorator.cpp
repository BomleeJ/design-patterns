#include <utility>
#include <string>
#include <sstream>
#include <iostream>
/*
* Decorators are a wrapper around a class that adds functionality to the class. 
* This can prevent combinatorial explosion of classes. (imagine if we needed to make)
* a colored square, a colored circle, a transparent square, a transparent circle, etc.)
*/

struct Shape {
    virtual std::string str() const = 0;
};

struct Circle : Shape {
    float radius;
    Circle(float radius) : radius(radius) {}
    std::string str() const override {
        return "Circle with radius " + std::to_string(radius);
    }
};

struct Square : Shape {
    float side;
    Square(float side) : side(side) {}
    std::string str() const override {
        return "Square with side length " + std::to_string(side);
    }
};

// mixin inheritance 
template <typename T>
struct ColoredShape : T {
    std::string color;

    std::string str() const override { 
        std::ostringstream oss;
        oss << T::str() << " has the color " << color;
        return oss.str();
    }
    
    template <typename... Args>
    ColoredShape(std::string color, Args... args) : T(args...), color(color) {}
};

template <typename T>
struct TransparentShape : T {
    float transparency;
    template <typename ...Args>
    TransparentShape(float transparency, Args...args) : transparency { transparency }, T(args...) { }

    std::string str() const override {
        std::ostringstream oss;
        oss << T::str() << " has the transperency " << transparency;
        return oss.str();
    }
};

int main() {
    ColoredShape<Circle> circle{"red", 5.0};
    TransparentShape<ColoredShape<Circle>> tcircle {2.0, "red", 9.0 };

    TransparentShape<ColoredShape<Square>> rect {10.0, "blue", 5.0 };

    std::cout << rect.str();
}