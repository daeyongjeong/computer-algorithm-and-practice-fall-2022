#include <iostream>
#include <random>
#include <vector>
#include <string>

using namespace std;

struct Point
{
    int x = 0;
    int y = 0;
    int z = 0;

    Point(){};
    Point(const int, const int, const int);
    string to_string() const;

    static bool comp(Point a, Point b)
    {
        if (a.x != b.x)
            return a.x < b.x;
        if (a.y != b.y)
            return a.y < b.y;
        return a.z < b.z;
    }

    static double distance(Point, Point);
};

struct ClosestPairOfPoints
{
    Point p1;
    Point p2;
    double d = 300;

    ClosestPairOfPoints(vector<Point>);
    double closest_pair_of_points(const vector<Point>, const int, const int);
    double merge_closest_pair_of_points(const vector<Point>, const int, const int, const int, const double);
};

Point::Point(const int x, const int y, const int z) : x(x), y(y), z(z)
{
    cout << "Point created " << to_string() << endl;
}

string Point::to_string() const
{
    return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
}

double Point::distance(Point a, Point b)
{
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z));
}

ClosestPairOfPoints::ClosestPairOfPoints(vector<Point> points)
{
    sort(points.begin(), points.end(), Point::comp);
    closest_pair_of_points(points, 0, points.size() - 1);
}

double ClosestPairOfPoints::merge_closest_pair_of_points(const vector<Point> points, const int low, const int mid, const int high, const double d_around)
{
    double res = d;
    int left = mid;
    while (left > mid - d && left > low + 1)
    {
        int right = mid + 1;
        while (right < mid + d && right < high - 1)
        {
            if (points[left].y - d <= points[right].y && points[right].y <= points[left].y + d && points[left].z - d <= points[right].z && points[right].z <= points[left].z + d)
                res = min(Point::distance(points[left], points[right]), res);
            right++;
        }
        left--;
    }
    return res;
}

double ClosestPairOfPoints::closest_pair_of_points(const vector<Point> points, const int low, const int high)
{
    int d_left, d_right, d_prime;
    if (low < high - 2)
    {
        int mid = (low + high) / 2;
        d_left = closest_pair_of_points(points, low, mid);
        d_right = closest_pair_of_points(points, mid + 1, high);
        d_prime = merge_closest_pair_of_points(points, low, mid, high, min(d_left, d_right));
        return min(min(d_left, d_right), d_prime);
    }
    double d1 = Point::distance(points[low], points[low + 1]);
    double d2 = Point::distance(points[low + 1], points[low + 2]);
    if (d1 < d2 && d1 < d)
    {
        p1 = points[low];
        p2 = points[low + 1];
        d = d1;
    }
    else if (d2 < d1 && d2 < d)
    {
        p1 = points[low + 1];
        p2 = points[low + 2];
        d = d2;
    }
    return min(d1, d2);
}

int main()
{
    const int N = 20;
    vector<Point> points;
    random_device rd;  // non-deterministic generator
    mt19937 gen(rd()); // to seed mersenne twister.
    uniform_int_distribution<> dist(0, 100);
    while (points.size() < N)
    {
        Point p = Point(dist(gen), dist(gen), dist(gen));
        points.push_back(p);
    }

    cout << "All pair of points" << endl;
    for (int i = 0; i < points.size(); ++i)
        for (int j = i + 1; j < points.size(); ++j)
            cout << points[i].to_string() << ", " << points[j].to_string() << ", " << Point::distance(points[i], points[j]) << endl;

    ClosestPairOfPoints cpp = ClosestPairOfPoints(points);
    cout << "Closest pair of points: " << cpp.p1.to_string() << ", " << cpp.p2.to_string() << ", " << cpp.d << endl;
}
