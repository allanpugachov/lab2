
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// ----------------------- Класс Point -----------------------
class Point {
private:
    int x, y; // координаты точки
public:
    Point() : x(0), y(0) {
        cout << "[Point] Конструктор по умолчанию (" << x << "," << y << ")" << endl;
    }

    Point(int xVal, int yVal) : x(xVal), y(yVal) {
        cout << "[Point] Конструктор с параметрами (" << x << "," << y << ")" << endl;
    }

    Point(const Point& p) : x(p.x), y(p.y) {
        cout << "[Point] Конструктор копирования (" << x << "," << y << ")" << endl;
    }

    ~Point() {
        cout << "[Point] Деструктор (" << x << "," << y << ")" << endl;
    }

    void setX(int xVal) { x = xVal; }
    void setY(int yVal) { y = yVal; }
    int getX() { return x; }
    int getY() { return y; }
    void print() const { cout << "(" << x << "," << y << ")"; }
};

// ----------------------- Класс Shape -----------------------
class Shape {
protected:
    string name;
public:
    Shape() : name("Shape") { cout << "[Shape] Конструктор по умолчанию" << endl; }
    Shape(string n) : name(n) { cout << "[Shape] Конструктор с именем " << name << endl; }
    virtual ~Shape() { cout << "[Shape] Деструктор " << name << endl; }

    virtual void draw() { cout << "[Shape] Рисуем " << name << endl; }
};

// ----------------------- Класс Circle -----------------------
class Circle : public Shape {
private:
    Point center;
    int radius;
public:
    Circle() : Shape("Circle"), center(Point(0, 0)), radius(1) {
        cout << "[Circle] Конструктор по умолчанию" << endl;
    }

    Circle(Point c, int r) : Shape("Circle"), center(c), radius(r) {
        cout << "[Circle] Конструктор с параметрами, центр ";
        center.print();
        cout << ", радиус " << radius << endl;
    }

    Circle(const Circle& c) : Shape("Circle"), center(c.center), radius(c.radius) {
        cout << "[Circle] Конструктор копирования" << endl;
    }

    ~Circle() { cout << "[Circle] Деструктор" << endl; }

    void draw() override {
        cout << "[Circle] Рисуем круг с центром "; center.print();
        cout << " и радиусом " << radius << endl;
    }

    void move(int dx, int dy) {
        center.setX(center.getX() + dx);
        center.setY(center.getY() + dy);
        cout << "[Circle] Передвинули центр на (" << dx << "," << dy << "), новый центр ";
        center.print();
        cout << endl;
    }

    Circle& operator=(const Circle& c) {
        cout << "[Circle] Оператор присваивания" << endl;
        if (this != &c) {
            center = c.center;
            radius = c.radius;
        }
        return *this;
    }
};

// ----------------------- Класс Rectangle -----------------------
class Rectangle : public Shape {
private:
    Point topLeft;
    int width, height;
public:
    Rectangle() : Shape("Rectangle"), topLeft(Point(0, 0)), width(1), height(1) {
        cout << "[Rectangle] Конструктор по умолчанию" << endl;
    }

    Rectangle(Point p, int w, int h) : Shape("Rectangle"), topLeft(p), width(w), height(h) {
        cout << "[Rectangle] Конструктор с параметрами, верхний левый "; topLeft.print();
        cout << ", ширина " << width << ", высота " << height << endl;
    }

    ~Rectangle() { cout << "[Rectangle] Деструктор" << endl; }

    void draw() override {
        cout << "[Rectangle] Рисуем прямоугольник в "; topLeft.print();
        cout << ", ширина " << width << ", высота " << height << endl;
    }
};

// ----------------------- Класс Triangle -----------------------
class Triangle : public Shape {
private:
    Point p1, p2, p3;
public:
    Triangle() : Shape("Triangle"), p1(Point(0, 0)), p2(Point(1, 0)), p3(Point(0, 1)) {
        cout << "[Triangle] Конструктор по умолчанию" << endl;
    }

    Triangle(Point a, Point b, Point c) : Shape("Triangle"), p1(a), p2(b), p3(c) {
        cout << "[Triangle] Конструктор с параметрами, точки "; p1.print(); cout << " "; p2.print(); cout << " "; p3.print(); cout << endl;
    }

    ~Triangle() { cout << "[Triangle] Деструктор" << endl; }

    void draw() override {
        cout << "[Triangle] Рисуем треугольник с точками "; p1.print(); cout << " "; p2.print(); cout << " "; p3.print(); cout << endl;
    }
};

// ----------------------- Класс ShapeGroup -----------------------
class ShapeGroup : public Shape {
private:
    vector<Shape*> shapes;
public:
    ShapeGroup() : Shape("ShapeGroup") { cout << "[ShapeGroup] Конструктор" << endl; }

    ~ShapeGroup() {
        cout << "[ShapeGroup] Деструктор" << endl;
        for (auto s : shapes) delete s;
    }

    void addShape(Shape* s) {
        shapes.push_back(s);
        cout << "[ShapeGroup] Добавлена фигура в группу" << endl;
    }

    void draw() override {
        cout << "[ShapeGroup] Рисуем группу фигур" << endl;
        for (auto s : shapes) s->draw();
    }
};

// ----------------------- Класс Vector -----------------------
class Vector {
private:
    vector<Point> points;
public:
    Vector() { cout << "[Vector] Конструктор" << endl; }
    ~Vector() { cout << "[Vector] Деструктор" << endl; }

    void addPoint(const Point& p) {
        points.push_back(p);
        cout << "[Vector] Добавлена точка "; p.print(); cout << endl;
    }

    void print() {
        cout << "[Vector] Текущие точки: ";
        for (auto& p : points) { p.print(); cout << " "; }
        cout << endl;
    }
};

// ----------------------- Главная функция -----------------------
int main() {
    setlocale(LC_ALL, "Russian");
   
    cout << "=== Начало лабораторной работы 2 ===" << endl;

    // ===== Статические объекты =====
    cout << "\n=== Статические объекты ===" << endl;
    Circle c1;
    c1.draw();

    Rectangle r1(Point(1, 2), 5, 3);
    r1.draw();

    Triangle t1(Point(0, 0), Point(1, 2), Point(3, 0));
    t1.draw();

    // ===== Динамические объекты =====
    cout << "\n=== Динамические объекты ===" << endl;
    Circle* c2 = new Circle(Point(5, 5), 10);
    c2->draw();
    c2->move(2, 3);
    delete c2;

    Rectangle* r2 = new Rectangle(Point(2, 3), 7, 4);
    r2->draw();
    delete r2;

    // ===== Копирование объектов =====
    cout << "\n=== Копирование объектов ===" << endl;
    Point p1(10, 20);
    Point p2 = p1;
    cout << "[Point] Копированная точка p2: "; p2.print(); cout << endl;

    Circle c3(c1);
    c3.draw();

    Circle c4;
    c4 = c1;
    c4.draw();

    // ===== Полиморфизм =====
    cout << "\n=== Полиморфизм ===" << endl;
    Shape* s = new Circle(Point(2, 3), 4);
    s->draw();
    delete s;

    // ===== Группа фигур =====
    cout << "\n=== Группа фигур ===" << endl;
    ShapeGroup* group = new ShapeGroup();
    group->addShape(new Circle(Point(1, 1), 5));
    group->addShape(new Rectangle(Point(2, 2), 3, 6));
    group->addShape(new Triangle(Point(0, 0), Point(1, 2), Point(3, 0)));
    group->draw();
    delete group;

    // ===== Вектор точек =====
    cout << "\n=== Вектор точек ===" << endl;
    Vector vec;
    vec.addPoint(Point(1, 1));
    vec.addPoint(Point(2, 2));
    vec.addPoint(Point(3, 3));
    vec.print();

    cout << "\n=== Конец лабораторной работы 2 ===" << endl;
    return 0;
}
