#include <iostream>
#include <string>
#include <typeinfo>
#include <vector>

namespace hse::cpp {

class Circle;
class Square;
class Rectangle;

class Shape {
public:
    virtual ~Shape() = default;
    virtual const char *type_name() = 0;
};

class Circle final : public Shape {
public:
    Circle(float radius) : radius_(radius) {
    }

    const char *type_name() {
        return typeid(Circle).name();
    }

public:
    float radius_;
};

class Square final : public Shape {
public:
    Square(float side_length) : side_length_(side_length) {
    }

    const char *type_name() {
        return typeid(Square).name();
    }

public:
    float side_length_;
};

class Rectangle final : public Shape {
public:
    Rectangle(float width, float height) : width_(width), height_(height) {
    }

    const char *type_name() {
        return typeid(Rectangle).name();
    }

public:
    float width_;
    float height_;
};

enum class Type { kCircle, kSquare, kRectangle };

std::unique_ptr<Shape> create_shape(Type type,
                                    float width,
                                    float height = 0.f) {
    if (type == Type::kCircle) {
        return std::make_unique<Circle>(width);
    } else if (type == Type::kSquare) {
        return std::make_unique<Square>(width);
    } else if (type == Type::kRectangle) {
        return std::make_unique<Rectangle>(width, height);
    }

    assert(false && "Unregistered shape type");
    return nullptr;
}

void pretty_print(Shape *shape) {
    if (auto p = dynamic_cast<Circle *>(shape)) {
        std::cout << "Circle with radius " << p->radius_ << std::endl;
    }
    if (auto p = dynamic_cast<Square *>(shape)) {
        std::cout << "Square with side " << p->side_length_ << std::endl;
    }
    if (auto p = dynamic_cast<Rectangle *>(shape)) {
        std::cout << "Rectangle with width " << p->width_ << " and height "
                  << p->height_ << std::endl;
    }
}

}  // namespace hse::cpp

int main() {
    using namespace hse::cpp;
    Shape *shape = new Circle(3.14f);
    delete shape;
}