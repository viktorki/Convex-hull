#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
using namespace std;
const int MAXN = 20000;
class Point
{
public:
	Point();
	Point(double, double);
	double getX() const;
	double getY() const;
	double distance(const Point&) const;
private:
	double x, y;
} p0;
Point::Point()
{
	x = 0;
	y = 0;
}
Point::Point(double x, double y)
{
	this->x = x;
	this->y = y;
}
double Point::getX() const
{
	return x;
}
double Point::getY() const
{
	return y;
}
double Point::distance(const Point &p) const
{
	return sqrt((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y));
}
bool compare_cos(const Point &p1, const Point &p2)
{
	return (p0.getX() - p1.getX()) * p0.distance(p2) < (p0.getX() - p2.getX()) * p0.distance(p1);
}
bool convex(const Point &p1, const Point &p2, const Point &p3)
{
	return (p2.getX() - p1.getX()) * (p3.getY() - p2.getY()) >(p3.getX() - p2.getX()) * (p2.getY() - p1.getY());
}
void graham_scan(Point points[], int n, Point result[], int &m)
{
	int i, min_i = 0, top = 0;
	Point stack[MAXN];
	for (i = 1; i < n; i++)
		if (points[min_i].getY() > points[i].getY())
			min_i = i;
	swap(points[0], points[min_i]);
	sort(points + 1, points + n, compare_cos);
	for (i = 0; i < n; i++)
	{
		while (top > 1 && !convex(stack[top - 2], stack[top - 1], points[i]))
			top--;
		stack[top++] = points[i];
	}
	m = top;
	for (i = 0; i < m; i++)
		result[i] = stack[i];
}
int main()
{
	int n, i, m;
	double x, y;
	Point points[MAXN], result[MAXN];
	while (1)
	{
		cout << "Points count: ";
		cin >> n;
		if (n < 1 || n > MAXN)
			cout << "Points count must be between 2 and " << MAXN << "!" << endl;
		else
			break;
	}
	cout << "Enter coordinates:" << endl;
	for (i = 0; i < n; i++)
	{
		cin >> x >> y;
		points[i] = Point(x, y);
	}
	graham_scan(points, n, result, m);
	cout << fixed << setprecision(5);
	cout << endl;
	cout << "Convex hull:" << endl;
	for (i = 0; i < m; i++)
		cout << result[i].getX() << " " << result[i].getY() << endl;
	return 0;
}
