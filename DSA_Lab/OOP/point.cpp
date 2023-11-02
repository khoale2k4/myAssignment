#include <iostream>

using namespace std;

class Point
{
private:
    double x, y;

public:
    Point()
    {
        x = 0;
        y = 0;
    }

    Point(double x, double y)
    {
        this->x = x;
        this->y = y;
    }

    void setX(double x)
    {
        this->x = x;
    }

    void setY(double y)
    {
        this->y = y;
    }

    double getX() const
    {
        return x;
    }

    double getY() const
    {
        return y;
    }

    double distanceToPoint(const Point& pointA)
    {
        double dx = pointA.x - this->x;
        double dy = pointA.y - this->y;
        dx *= dx;
        dy *= dy;
        return sqrt(dx + dy);
    }
};

class Circle
{
private:
    Point center;
    double radius;

public:
    Circle()
    {
        center.setX(0);
        center.setY(0);
        radius = 0;
    }

    Circle(Point center, double radius)
    {
        this->center = center;
        this->radius = radius;
    }

    Circle(const Circle& circle)
    {
        this->center = circle.center;
        this->radius = circle.radius;
    }

    void setCenter(Point point)
    {
        center = point;
    }

    void setRadius(double radius)
    {
        this->radius = radius;
    }

    Point getCenter() const
    {
        return center;
    }

    double getRadius() const
    {
        return radius;
    }

    bool containsPoint(const Point point)
    {
        return (center.distanceToPoint(point) < radius);
    }

    bool containsTriangle(const Point pointA, const Point pointB, const Point pointC)
    {
        if (center.distanceToPoint(pointA) >= radius
            || center.distanceToPoint(pointB) >= radius
            || center.distanceToPoint(pointC) >= radius) return false;
        double frac = pointA.getY() / pointA.getX();
        if (frac == pointB.getY() / pointB.getX()
            && frac == pointC.getY() / pointC.getX()) return false;
        else return true;
    }

    void operator=(const Circle& circle)
    {
        this->center = circle.center;
        this->radius = circle.radius;
    }

    bool operator==(const Circle& circle)
    {
        return (this->center.getX() == circle.center.getX()
            && this->center.getY() == circle.center.getY()
            && this->radius == circle.radius);
    }

    friend istream& operator >> (istream& in, Circle& circle)
    {
        double x, y, r;
        in >> x >> y >> r;
        Point nc(x, y);
        circle.center.setX(x);
        circle.center.setY(y);
        circle.radius = r;
        return in;
    }

    void printCircle()
    {
        printf("Center: {%.2f, %.2f} and Radius %.2f\n", this->center.getX(), this->center.getY(), this->radius);
    }
};

int main(){
}
