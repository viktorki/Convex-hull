#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
const int MAXN = 20000;
struct point
{
	int n;
	double x, y;
} p[MAXN], stack[MAXN];
int n, top;
double d(point p1, point p2)
{
	return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}
bool compare_cos(point p1, point p2)
{
	return (p[0].x - p1.x) * d(p[0], p2) < (p[0].x - p2.x) * d(p[0], p1);
}
bool convex(point p1, point p2, point p3)
{
	return (p2.x - p1.x) * (p3.y - p2.y) >(p3.x - p2.x) * (p2.y - p1.y);
}
void graham_scan()
{
	int i, min = 0;
	for (i = 1; i < n; i++)
	if (p[min].y > p[i].y)
		min = i;
	swap(p[0], p[min]);
	sort(p + 1, p + n, compare_cos);
	for (i = 0; i < n; i++)
		p[i].n = i;
	for (i = 0; i < n; i++)
	{
		while (top > 1 && !convex(stack[top - 2], stack[top - 1], p[i]))
			top--;
		stack[top++] = p[i];
	}
}
int main()
{
	int i;
	scanf("%d", &n);
	for (i = 0; i < n; i++)
		scanf("%lf%lf", &p[i].x, &p[i].y);
	graham_scan();
	for (i = 0; i < top; i++)
		printf("%.5lf %.5lf\n", stack[i].x, stack[i].y);
	return 0;
}
