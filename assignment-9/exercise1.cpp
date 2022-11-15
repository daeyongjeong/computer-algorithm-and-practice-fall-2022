#include <iostream>
#include <random>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

struct Point
{
public:
    Point(int, int);
    int x;
    int y;
};

struct Line
{
    Line(Point, Point);
    static int comparison_degree(Line, Line);
    Point p1;
    Point p2;
    float degree;
    float compute_degree(Point, Point);
};

struct Polygon
{
    vector<Point> points;
    Polygon(vector<Point>);
    void print_points();
    void add_point(Point p1);
};

struct SimpleClosedPath : Polygon
{
    SimpleClosedPath(set<Point> points);
};

/* Data declarations */
int computations = 0;
int comparisons = 0;

/* Main function */
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
        Point p = {dist(gen), dist(gen)};
        points.push_back(p); // what if duplicate occurs?
    }

    Polygon poly(points);
    poly.print_points();

    return 0;
}

Point::Point(int x = 0, int y = 0) {}

void sort_by_y(vector<Point> vec)
{
    for (int j = 1; j < vec.size(); ++j)
    {
        Point key = vec[j];
        int i = j - 1;
        while (i > 0 && key.y > vec[i].y)
        {
            vec[i + 1] = vec[i];
            i = i - 1;
        }
        vec[i + 1] = key;
    }
}

Line::Line(Point p1, Point p2)
{
    degree = compute_degree(p1, p2);
}

void sort_by_degree(vector<Line> &vec)
{
    for (int j = 1; j < vec.size(); ++j)
    {
        Line key = vec[j];
        int i = j - 1;
        while (i > 0 && Line::comparison_degree(vec[i], key) > 0)
        {
            vec[i + 1] = vec[i];
            i = i - 1;
        }
        vec[i + 1] = key;
    }
}

/* Function definitions */
Polygon::Polygon(vector<Point> points)
{
    sort_by_y(points);
    Point p0 = points.back();
    points.pop_back();
    vector<Point> remaining(points);

    points.clear();
    points.push_back(p0);

    vector<Line> lines;
    for (Point p : remaining)
    {
        Line l(p0, p);
        lines.push_back(l);
    }

    sort_by_degree(lines);
    for (Line l : lines)
    {
        points.push_back(l.p2);
    }
}

void Polygon::add_point(Point p1)
{
    points.push_back(p1);
}

float Line::compute_degree(Point p1, Point p2)
{
    int dx = p2.x - p1.x;
    int dy = p2.y - p1.y;
    int ax = abs(dx);
    int ay = abs(dy);
    int t = 0;
    computations += 1;
    if (ax + ay != 0)
        t = (float)dy / (ax + ay);
    if (dx < 0)
        t = 2 - t;
    else if (dy < 0)
        t = 4 + t;
    return t * 90.0;
}

void Polygon::print_points()
{
    for (Point p : points)
    {
        cout << "(" << p.x << ", " << p.y << "), ";
    }
    cout << endl;
}
