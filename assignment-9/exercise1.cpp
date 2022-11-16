#include <iostream>
#include <random>
#include <vector>
#include <string>

using namespace std;

// Type definitions

struct Point
{
    int x;
    int y;

    Point(const int, const int);
    string to_string() const;
};

struct Line
{
    Point p1;
    Point p2;
    float degree;

    Line(const Point, const Point);
    float compute_degree(const Point, const Point);
    string to_string() const;

    static int comparison_degree(Line, Line);
};

struct Polygon
{
    vector<Point> points;

    string to_string() const;
};

struct SimplePolygon : Polygon
{
    SimplePolygon(const vector<Point>);
    void sort_by_y(vector<Point> &);
    void sort_by_degree(vector<Line> &);
};

// Data declarations

int computations = 0;
int comparisons = 0;

//  Main function

int main()
{
    const int N = 20;
    vector<Point> points;

    // C++ style random number generator
    random_device rd;  // non-deterministic generator
    mt19937 gen(rd()); // to seed mersenne twister.
    uniform_int_distribution<> dist(0, 100);

    for (int i = 0; i < N; ++i)
    {
        Point p(dist(gen), dist(gen));
        points.push_back(p); // what if duplicate occurs?
        cout << "Point created " << p.to_string() << endl;
    }

    SimplePolygon poly(points);
    cout << "Simple polygon created " << poly.to_string() << endl;
    cout << "Degree-computations " << computations << endl;
    cout << "Comparisons " << comparisons << endl;
    return 0;
}

// struct Point

Point::Point(const int x, const int y) : x{x}, y{y} {}

string Point::to_string() const
{
    return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
}

// struct Line

Line::Line(const Point p1, const Point p2) : p1{p1}, p2{p2}
{
    degree = compute_degree(p1, p2);
}

float Line::compute_degree(Point p1, Point p2)
{
    int dx = p2.x - p1.x;
    int dy = p2.y - p1.y;
    int ax = abs(dx);
    int ay = abs(dy);
    float t = 0;
    computations += 1;
    if (ax + ay != 0)
        t = (float)dy / (ax + ay);
    if (dx < 0)
        t = 2 - t;
    else if (dy < 0)
        t = 4 + t;
    return t * 90.0;
}

string Line::to_string() const
{
    return "{" + p1.to_string() + ", " + p2.to_string() + ", " + std::to_string(degree) + "}";
}

int Line::comparison_degree(Line l1, Line l2)
{
    comparisons += 1;
    if (l1.degree > l2.degree)
        return 1;
    else if (l1.degree < l2.degree)
        return -1;
    return 0;
}

// struct Polygon

string Polygon::to_string() const
{
    string polygon_string = "";
    for (Point p : points)
    {
        polygon_string = polygon_string + p.to_string() + " ";
    }
    return polygon_string;
}

// struct SimplePolygon

SimplePolygon::SimplePolygon(vector<Point> points)
{
    sort_by_y(points);
    Point p0 = points.back();
    points.pop_back();
    vector<Point> remaining(points);
    cout << "Point with minimum y " << p0.to_string() << endl;

    points.clear();
    this->points.push_back(p0);

    vector<Line> lines;
    for (Point p : remaining)
    {
        Line l(p0, p);
        lines.push_back(l);
    }

    sort_by_degree(lines);
    cout << "Lines sorted by degree" << endl;
    for (Line l : lines)
    {
        cout << l.to_string() << endl;
    }
    for (Line l : lines)
    {
        this->points.push_back(l.p2);
    }
}

// Insertion sort in descending order for pop_back()
void SimplePolygon::sort_by_y(vector<Point> &vec)
{
    for (int j = 1; j < vec.size(); ++j)
    {
        Point key = vec[j];
        int i = j - 1;
        while (i >= 0 && vec[i].y < key.y)
        {
            vec[i + 1] = vec[i];
            i = i - 1;
        }
        vec[i + 1] = key;
    }
}

// Insertion sort in ascending order
void SimplePolygon::sort_by_degree(vector<Line> &vec)
{
    for (int j = 1; j < vec.size(); ++j)
    {
        Line key = vec[j];
        int i = j - 1;
        while (i >= 0 && Line::comparison_degree(vec[i], key) > 0)
        {
            vec[i + 1] = vec[i];
            i = i - 1;
        }
        vec[i + 1] = key;
    }
}
