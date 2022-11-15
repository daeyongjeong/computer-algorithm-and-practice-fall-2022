#include <iostream>
#include <random>
#include <vector>
#include <set>
using namespace std;

struct Point
{
    int x;
    int y;
    char c;
};

struct Line
{
    Point p1;
    Point p2;
};

struct Polygon
{
    vector<Point> points;
    Polygon(vector<Point>);
    float compute_degree(Point, Point);
    void print_points();
    void add_point(Point p1);
};

struct SimpleClosedPath : Polygon
{
    SimpleClosedPath(set<Point> points);
};

/* Data declarations */
int comparison = 0;

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

/* Function definitions */
Polygon::Polygon(vector<Point> points)
{

    // 최소 y를 갖는 점 찾기
    // 이 점과 나머지 점 사이의 각도 모두 계산해서 float 배열에 넣기
    // float 배열 insertion sort로 정렬한 다음
    // 아 그럼 원래 점에 대한 정보를 잃어버리겠구나
    // 큰 점부터 차례대로 Point 배열에 집어넣기
    // TODO: 입력을 Set Q로 바꾸기. 겹치는 점이 있으면 동작 안할 가능성 큼
}

void Polygon::add_point(Point p1)
{
    points.push_back(p1);
}

float Polygon::compute_degree(Point p1, Point p2)
{
    int dx = p2.x - p1.x;
    int dy = p2.y - p1.y;
    int ax = abs(dx);
    int ay = abs(dy);
    int t = 0;
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
        cout << p.c << "(" << p.x << ", " << p.y << "), ";
    }
    cout << endl;
}
