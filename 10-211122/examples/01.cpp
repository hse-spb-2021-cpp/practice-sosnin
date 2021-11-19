#include <iostream>
#include <string>
#include <vector>

namespace hse::cpp {

class Circle;
class Square;
class Rectangle;

class ShapeVisitor
{
public:
    void visit(Circle* shape);
    void visit(Square* shape);
    void visit(Rectangle* shape);
};

class Shape
{
public:
    virtual ~Shape() {}

    virtual void accept(ShapeVisitor* visitor) = 0;
};

class Circle final : public Shape
{
public:
    Circle(float radius) : radius_(radius) {}

    float radius() const { return radius_; }

    void accept(ShapeVisitor* visitor)
    {
        visitor->visit(this);
    }

private:
    float radius_;
};

class Square final : public Shape
{
public:
    Square(float side_length) : side_length_(side_length) {}

    float side_length() const { return side_length_; }

    void accept(ShapeVisitor* visitor)
    {
        visitor->visit(this);
    }

private:
    float side_length_;
};

class Rectangle final : public Shape
{
public:
    Rectangle(float width, float height) : width_(width), height_(height) {}

    float width() const { return width_; }
    float height() const { return height_; }

    void accept(ShapeVisitor* visitor)
    {
        visitor->visit(this);
    }

private:
    float width_;
    float height_;
};

void ShapeVisitor::visit(Circle* shape)
{
    std::cout << "Circle with radius " << shape->radius() << std::endl;
}

void ShapeVisitor::visit(Square* shape)
{
    std::cout << "Square with side " << shape->side_length() << std::endl;
}

void ShapeVisitor::visit(Rectangle* shape)
{
    std::cout << "Rectangle with width " << shape->width() 
                << " and height " << shape->height() << std::endl;
}

constexpr const char* kCircle = "circle";
constexpr const char* kSquare = "square";
constexpr const char* kRectangle = "rectangle";

std::unique_ptr<Shape> create_shape(const std::string& type, float width, float height = 0.f)
{
    if(type == kCircle)
    {
        return std::make_unique<Circle>(width);
    }
    else if(type == kSquare)
    {
        return std::make_unique<Square>(width);
    }
    else if(type == kRectangle)
    {
        return std::make_unique<Rectangle>(width, height);
    }

    assert(false && "Unregistered shape type");
    return nullptr;    
}

}

int main()
{
    using namespace hse::cpp;
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.emplace_back(create_shape(kCircle, 3.14));
    shapes.emplace_back(create_shape(kSquare, 2.71));
    shapes.emplace_back(create_shape(kRectangle, 42, 28));

    ShapeVisitor visitor;

    for(const auto& shape : shapes)
        shape->accept(&visitor);
}