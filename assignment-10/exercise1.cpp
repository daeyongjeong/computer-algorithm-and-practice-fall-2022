#include <iostream>
#include <random>
#include <vector>
#include <string>
#include <stack>

using namespace std;

// Type definitions

struct Point
{
    int x;
    int y;

    Point(const int, const int);
    string to_string() const;

    static int direction(Point, Point, Point);
    static void sort_by_y(vector<Point> &);
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
    static int intersection(Line, Line);
    static void sort_by_degree(vector<Line> &);
};

struct Polygon
{
    vector<Point> points;

    string to_string() const;
    bool is_inside(Point) const;
};

struct ConvexHull : Polygon
{
    ConvexHull(const vector<Point>);
    stack<Point> graham_scan(vector<Point>);
    Point pop_minimum_y(vector<Point> &);
    void sort_by_polar_angle(Point, vector<Point> &);
    bool is_nonleft_turn(Point, Point, Point);
};

// Data declarations

int computations = 0;
int comparisons = 0;

//  Main function

int main()
{
    // Test 1
    vector<Point> sample;
    sample.push_back(Point(3, 4));
    sample.push_back(Point(1, 2));
    sample.push_back(Point(2, 5));
    sample.push_back(Point(2, 6));
    sample.push_back(Point(9, 3));
    sample.push_back(Point(5, 3));
    sample.push_back(Point(6, 4));
    sample.push_back(Point(8, 4));

    ConvexHull ch = ConvexHull(sample);
    cout << "ConvexHull: " << ch.to_string() << endl;
    cout << "Degree-computations " << computations << endl;
    cout << "Comparisons " << comparisons << endl;
    cout << "Points inside " << sample.size() - ch.points.size() << endl;

    // Test 2
    computations = 0;
    comparisons = 0;
    const int N = 20;
    vector<Point> points;
    random_device rd;  // non-deterministic generator
    mt19937 gen(rd()); // to seed mersenne twister.
    uniform_int_distribution<> dist(0, 100);
    while (points.size() < N)
    {
        Point p = Point(dist(gen), dist(gen));
        points.push_back(p);
    }

    ConvexHull ch2 = ConvexHull(points);
    cout << "ConvexHull: " << ch2.to_string() << endl;
    cout << "Degree-computations " << computations << endl;
    cout << "Comparisons " << comparisons << endl;
    cout << "Points inside " << points.size() - ch2.points.size() << endl;

    return 0;
}

// struct Point

Point::Point(const int x, const int y) : x(x), y(y)
{
    cout << "Point created " << to_string() << endl;
}

string Point::to_string() const
{
    return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
}

int Point::direction(Point a, Point b, Point c)
{
    int dxab, dxac, dyab, dyac, direction;
    dxab = b.x - a.x;
    dyab = b.y - a.y;
    dxac = c.x - a.x;
    dyac = c.y - a.y;
    if (dxab * dyac < dyab * dxac)
        return 1;
    if (dxab * dyac > dyab * dxac)
        return -1;
    if (dxab == 0 && dyab == 0)
        direction = 0;
    if ((dxab * dxac < 0) || (dyab * dyac < 0))
        direction = -1;
    else if ((dxab * dxab + dyab * dyab) >= (dxac * dxac + dyac * dyac))
        direction = 0;
    else
        direction = 1;
    return direction;
}

// Insertion sort in descending order for pop_back()
void Point::sort_by_y(vector<Point> &vec)
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

// struct Line

Line::Line(const Point p1, const Point p2) : p1(p1), p2(p2)
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

int Line::intersection(Line a, Line b)
{
    if ((Point::direction(a.p1, a.p2, b.p1) * Point::direction(a.p1, a.p2, b.p2) <= 0) && (Point::direction(b.p1, b.p2, a.p1) * Point::direction(b.p1, b.p2, a.p2) <= 0))
        return true;
    return false;
}

// Insertion sort in ascending order
void Line::sort_by_degree(vector<Line> &vec)
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

// Struct Convex Hull

ConvexHull::ConvexHull(const vector<Point> q)
{
    vector<Point> points_q;
    for (Point p : q)
    {
        points_q.push_back(p);
    }
    stack<Point> s = graham_scan(points_q);
    while (s.size() > 0)
    {
        Point top = s.top();
        s.pop();
        points.insert(points.begin(), top);
    }
}

stack<Point> ConvexHull::graham_scan(vector<Point> points)
{
    stack<Point> s;
    Point p0 = pop_minimum_y(points);
    vector<Point> remaining(points);
    sort_by_polar_angle(p0, remaining);

    s.push(p0);
    s.push(remaining[0]);
    s.push(remaining[1]);
    for (int i = 2; i < remaining.size(); ++i)
    {
        Point top = s.top();
        s.pop();
        Point next_to_top = s.top();
        s.push(top);
        while (s.size() > 1 && is_nonleft_turn(next_to_top, top, remaining[i]))
        {
            s.pop();
            top = s.top();
            s.pop();
            next_to_top = s.top();
            s.push(top);
        }
        s.push(remaining[i]);
    }
    return s;
}

Point ConvexHull::pop_minimum_y(vector<Point> &q)
{
    int minimum_index = 0;
    for (int i = 0; i < q.size(); ++i)
        if (q[i].y < q[minimum_index].y)
            minimum_index = i;
    Point temp = q[minimum_index];
    q[minimum_index] = q[q.size() - 1];
    q[q.size() - 1] = temp;
    Point back = q.back();
    q.pop_back();
    return back;
}

// Sort points by polar angle in counterclockwise order around p0
void ConvexHull::sort_by_polar_angle(Point p0, vector<Point> &points)
{
    vector<Line> lines;
    for (Point p : points)
    {
        Line l(p0, p);
        lines.push_back(l);
    }
    Line::sort_by_degree(lines);
    for (Line l : lines)
        cout << l.to_string() << endl;
    vector<Point> sorted;
    for (Line l : lines)
        sorted.push_back(l.p2);
    points.clear();
    for (Point p : sorted)
    {
        points.push_back(p);
    }
}

bool ConvexHull::is_nonleft_turn(Point a, Point b, Point c)
{
    return Point::direction(a, b, c) >= 0;
}
