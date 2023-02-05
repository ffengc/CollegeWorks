#include <iostream>
using namespace std;

class Point {
public:

	Point() {}
	Point(float x, float y) : x_(x), y_(y) {}
	Point(const Point& p) : x_(p.x_), y_(p.y_) {}

	float GetDistance(const Point& p) const {
		return sqrt((x_ - p.x_) * (x_ - p.x_) + (y_ - p.y_) * (y_ - p.y_));
	}

	Point GetMidPoint(const Point& p) const {
		return Point((x_ + p.x_) / 2.0f, (y_ + p.y_) / 2.0f);
	}

	float GetX() const { return x_; }
	float GetY() const { return y_; }
	
private:
	float x_ = 0;
	float y_ = 0;
};

class Line {
public:
	enum Color { Red, Yellow, Blue, Green };

	Line() {}
	Line(const Point& start, const Point& end) : start_(start), end_(end) {}

	Line(float x1, float y1, float x2, float y2) :
		start_(x1, y1), end_(x2, y2) {}

	Line(const Line& line) :
		start_(line.start_), end_(line.end_), color_(line.color_) {}
	
	float GetLen()	{
		return start_.GetDistance(end_);
	}

	void draw() {}

private:
	Point start_;
	Point end_;
	Color color_ = Red;
};

class Rectangle
{
public:
	Rectangle() {}

	Rectangle(Line* lines) //std::array is better
		: edge0_(lines[0]), edge1_(lines[1]), edge2_(lines[2]), edge3_(lines[3])
	{}

	Rectangle(const Rectangle& rect) : 
		edge0_(rect.edge0_), edge1_(rect.edge1_), 
		edge2_(rect.edge2_), edge3_(rect.edge3_)
	{}

	Line GetLine(int i) const
	{
		if (i == 0)
			return edge0_;
		else if (i == 1)
			return edge1_;
		else if (i == 2)
			return edge2_;
		else if (i == 3)
			return edge3_;
		else
			return Line();
	}

	void Draw() {}

private:
	Line edge0_, edge1_, edge2_, edge3_;
};

void CombineRectangles(Rectangle& rect1, Rectangle& rect2, Line* lines)
{
	for (int i = 0; i < 4; i++)	{
		lines[i] = rect1.GetLine(i);
	}
	for (int i = 0; i < 4; i++)	{
		lines[i + 4] = rect2.GetLine(i);
	}
}

int main()
{
	float xx[4] = { 0, 0, 1, 1 };
	float yy[4] = { 0, 1, 1, 0 };

	Point points1[4];
	Point points2[4];
	for (int i = 0; i < 4; i++)	{
		points1[i] = Point(xx[i], yy[i]);
	}
	for (int i = 0; i < 4; i++)	{
		points2[i] = points1[i].GetMidPoint(points1[(i + 1) % 4]);
	}

	Line lines1[4];
	Line lines2[4];
	for (int i = 0; i < 4; ++i)
	{
		int next = (i + 1) % 4;
		lines1[i] = Line(points1[i], points1[next]);
		lines2[i] = Line(points2[i], points2[next]);
	}

	Rectangle rect1(lines1);
	Rectangle rect2(lines2);

	cout << "rect1:" << endl;
	rect1.Draw();
	cout << endl;

	cout << "rect2:" << endl;
	rect2.Draw();
	cout << endl;

	cout << "combine:" << endl;
	Line combine[8];
	CombineRectangles(rect1, rect2, combine);
	for (int i = 0; i < 8; ++i)
	{
		combine[i].draw();
	}

	return 0;
}
