#include <iostream>

/*
Bridge is a structural design pattern that allows you to separate the interface (abstraction) and the implementation (implementation) of a class.
This is useful when you want to be able to change the implementation of a class without changing the interface.
For example, you can have a class that can be rendered in different ways, such as OpenGL or Vulkan.
You can create a bridge between the class and the renderer, so that the class can be rendered in different ways.
The bridge pattern is also known as the handle/body pattern or the interface/implementation pattern.
*/

/*
BRIDGE PATTERN (WHY THIS EXISTS)

Problem:
- We have two things that vary independently:
  1) Shapes (Circle, Rectangle, Square)
  2) Renderers (OpenGL, Vulkan, etc.)
- Using inheritance for both would cause class explosion and tight coupling.

Solution (Bridge):
- Separate the high-level abstraction (Shape)
  from the low-level implementation (Renderer).
- Shape *has a* Renderer and delegates drawing to it.
- Renderers handle *how* drawing is done.
- Shapes handle *what* is being drawn.

Result:
- New Shapes can be added without modifying Renderers.
- New Renderers can be added without modifying Shapes.
- Both hierarchies evolve independently.

Key rule:
- Abstraction decides WHAT.
- Implementation decides HOW.
*/
class Renderer {
    
    public:
    virtual void drawCircle(float x, float y, float r) = 0;
    virtual void drawRectangle(float x, float y) = 0;
};

class OpenGLRenderer : public Renderer {
    void drawCircle(float x, float y, float r) override {
        std::cout << "Drawing circle with OpenGL" << std::endl;
    }
    void drawRectangle(float x, float y) override {
        std::cout << "Drawing rectangle with OpenGL" << std::endl;
    }
};

class VulkanRenderer : public Renderer {
    void drawCircle(float x, float y, float r) override {
        std::cout << "Drawing circle with Vulkan" << std::endl;
    }
    void drawRectangle(float x, float y) override {
        std::cout << "Drawing rectangle with Vulkan" << std::endl;
    }
};

class Shape {
    protected:
    std::string name;
    Renderer& renderer;
    public:
    virtual void draw() = 0;
    Shape(std::string name, Renderer& renderer): 
        name{ name }, 
        renderer{ renderer } 
    { }
};

class Circle : public Shape {
    float x, y, r;
    public:
    Circle(float x, float y, float r, Renderer& renderer): Shape("Circle", renderer), x(x), y(y), r(r) {
        this->x = x;
        this->y = y;
        this->r = r;
    }
    void draw() override {
        renderer.drawCircle(x, y, r);
    }
};

class Rectangle : public Shape {
    float x, y;
    public:
    Rectangle(float x, float y, Renderer& renderer): Shape("Rectangle", renderer), x(x), y(y) {
    }
    void draw() override {
        renderer.drawRectangle(x, y);
    }
};

class Square : public Rectangle {
    public:
    Square(float x, float y, Renderer& renderer): Rectangle(x, y, renderer) {
    }
};



int main() {
    OpenGLRenderer openglRenderer;
    VulkanRenderer vulkanRenderer;
    Circle circle(10, 10, 10, openglRenderer);
    Rectangle rectangle(10, 10, openglRenderer);
    Square square(10, 10, openglRenderer);
    circle.draw();
    rectangle.draw();
    square.draw();

    Circle circle2(10, 10, 10, vulkanRenderer);
    Rectangle rectangle2(10, 10, vulkanRenderer);
    Square square2(10, 10, vulkanRenderer);
    circle2.draw();
    rectangle2.draw();
    square2.draw();
    return 0;
}