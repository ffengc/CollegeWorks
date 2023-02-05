
#define _CRT_SECURE_NO_WARNINGS 1

#ifdef __cplusplus
#elif
#endif

#include"Shape.h"


Polygon::Polygon(double center_x, double center_y, double height, double width)
{
	//允许用中心和长款 -- 构造一个矩形
	Point point1(center_x - height / 2.0, center_y - width / 2.0);
	Point point2(center_x - height / 2.0, center_y + width / 2.0);
	Point point3(center_x + height / 2.0, center_y - width / 2.0);
	Point point4(center_x + height / 2.0, center_y + width / 2.0);
	vector<shared_ptr<Edge>>tmp = {
		shared_ptr<Edge>(new Edge(point1,point2)),
		shared_ptr<Edge>(new Edge(point2,point4)),
		shared_ptr<Edge>(new Edge(point3,point4)),
		shared_ptr<Edge>(new Edge(point3,point1)),
	};
	_edges = tmp;
}
bool Polygon::is_rectangle()
{
	if (_edges.size() != 4)return false;
	//这里认为传入的矩阵中 -- 四条边长度有两组相互相等 -- 就是矩形
	set<double>s;
	for (size_t i = 0; i < _edges.size(); i++)
	{
		s.insert(_edges[i]->Length());
	}
	if (s.size() == 2)return true;
	if (s.size() == 1)return true;//正方形也是矩形
	return false;
}
double Polygon::Circumference() const 
{
	if (this->isValid() == false) { cerr << "The polygon is illegal" << endl; return 0; }
	//if (_edges.size() != 3 && _edges.size() != 4)return UnknownValue;
	double c_sum = 0;
	for (auto& e : this->_edges)
	{
		c_sum += e->Length();
	}
	return c_sum;
}
double Polygon::Area()const
{
	if (this->isValid() == false) { cerr << "The polygon is illegal" << endl; return 0; }
	if (_edges.size() != 3 && _edges.size() != 4)return UnknownValue;
	//这里仅认为矩形和三角形可以算面积 -- 其它的返回UnknownValue
	if (_edges.size() == 3)
	{
		//求三角形面积
		double half_c = _edges[0]->Length() + _edges[1]->Length() + _edges[2]->Length();
		half_c /= 2.0;
		return sqrt(half_c * (half_c - _edges[0]->Length()) *
			(half_c - _edges[1]->Length()) * (half_c - _edges[2]->Length()));
	}
	else
	{
		//矩形面积
		set<double>s;
		for (size_t i = 0; i < _edges.size(); i++)
		{
			s.insert(_edges[i]->Length());
		}
		//正方形
		if (s.size() == 1)return (*(s.begin())) * (*(s.begin()));
		//矩形
		else
		{
			double a = *(s.begin());
			auto it = s.begin();
			it++;
			double b = *it;
			return a * b;
		}
	}
}
void Polygon::Print() const
{
	if (this->isValid() == false) { cerr << "The polygon is illegal" << endl; return; }
	if (_edges.size() != 3 && _edges.size() != 4)
	{
		cout << "hard to print" << endl;
		//cout << "edges:" << _edges.size() << endl;
		return;
	}
	//打印edges的信息
	cout << "该多边形的信息为：" << endl;
	cout << "begin{" << endl;
	for (size_t i = 0; i < _edges.size(); i++)
	{
		_edges[i]->Print();
	}
	cout << "Area:" << this->Area() << endl;
	cout << "Circumference:" << this->Circumference() << endl;
	cout << "}end" << endl;
}
void Polygon::Move(double xoffset, double yoffset) 
{
	if (this->isValid() == false) { cerr << "The polygon is illegal" << endl; return; }
	//多边形的移动 -- 每条边都移动即可
	for (size_t i = 0; i < _edges.size(); i++)
	{
		_edges[i]->Move(xoffset, yoffset);
	}
}
bool Polygon::isValid() const
{
	if (_edges.size() < 3)return false;
	//这里仅仅认为矩形和三角形是合法的多边形
	if (_edges.size() == 3)
	{
		//判断三角形是否合法
		//把所有的点取出来 -- 如果去重后set.size()==3则合法
		set<Point, cmp>point_arr;
		for (size_t i = 0; i < _edges.size(); i++)
		{
			point_arr.insert(_edges[i]->_point1);
			point_arr.insert(_edges[i]->_point2);
		}
		if (point_arr.size() == 3)return true;
		return false;
	}
	else if (_edges.size() == 4)
	{
		//判断四边形是否合法
		set<Point, cmp>point_arr;
		for (size_t i = 0; i < _edges.size(); i++)
		{
			point_arr.insert(_edges[i]->_point1);
			point_arr.insert(_edges[i]->_point2);
		}
		if (point_arr.size() != 4)return false;
		return true;
	}
	else
	{
		//只有边的数量等于顶点数量的时候才合法
		set<Point, cmp>point_arr;
		for (size_t i = 0; i < _edges.size(); i++)
		{
			point_arr.insert(_edges[i]->_point1);
			point_arr.insert(_edges[i]->_point2);
		}
		if (point_arr.size() != _edges.size())return false;
		return true;
	}
}
bool Polygon::if_calculate()
{
	if (this->isValid() == false) { cerr << "The polygon is illegal" << endl; return false; }
	if (_edges.size() == 4)
	{
		if (is_rectangle())return true;
		return false;//不是矩形的 -- 难以计算
	}
	else if (_edges.size() == 3)return true;
	else return false;
}
//计算一个矩形的长和宽
pair<double, double> get_height_width(shared_ptr<Polygon>& ptr)
{
	assert(ptr->_edges.size() == 4);//先保证是矩形
	set<double>s;
	for (size_t i = 0; i < ptr->_edges.size(); i++)
	{
		s.insert(ptr->_edges[i]->Length());
	}
	if (s.size() == 1)
	{
		//正方形
		return make_pair(*(s.begin()), *(s.begin()));
	}
	else
	{
		//矩形
		double a = *(s.begin());
		auto it = s.begin(); ++it;
		double b = *it;
		return make_pair(a, b);
	}
}
ptr_shape operator&(const ptr_shape& ptr1, const ptr_shape& ptr2)
{
	if (ptr1 == nullptr || ptr2 == nullptr)return shared_ptr<Shape>(nullptr);
	//先识别是圆还是多边形
	if (ptr1->__type() == SHAPE || ptr2->__type() == SHAPE)
	{
		return shared_ptr<Shape>(nullptr);
	}
	else if (ptr1->__type() == CIRCLE && ptr2->__type() == CIRCLE)
	{
		//两个都是圆 -- 可以计算
		//两个圆相离
		//两圆的圆心距离之和大于两圆的半径之和
		auto p1 = dynamic_pointer_cast<Circle>(ptr1);
		auto p2 = dynamic_pointer_cast<Circle>(ptr2);
		double distance = sqrt(pow((p1->_center._x - p2->_center._x), 2)
			+ pow((p1->_center._y - p2->_center._y), 2));
		if (distance >= p1->_radius + p2->_radius)
		{
			return shared_ptr<Shape>(nullptr);//没有交集
		}
		//两个圆内含
		else if (distance <= abs(p1->_radius - p2->_radius))
		{
			auto min_ptr = p1->_radius < p2->_radius ? p1 : p2;
			return shared_ptr<Circle>(new Circle(min_ptr->_center, min_ptr->_radius));
		}
		//两个圆相交 -- 无法计算 -- 返回空
		else
		{
			return shared_ptr<Circle>(nullptr);
		}
	}
	else if (ptr1->__type() == POLYGON && ptr2->__type() == POLYGON)
	{
		//两个都是多边形
		auto p1 = dynamic_pointer_cast<Polygon>(ptr1);
		auto p2 = dynamic_pointer_cast<Polygon>(ptr2);
		if (p1->isValid() == false || p2->isValid() == false)
		{
			//其中之一不合法 -- 无法计算
			cerr << "more than one of the Polygon is isValid!" << endl;
			return shared_ptr<Polygon>(nullptr);
		}
		if (p1->if_calculate() == false || p2->if_calculate() == false)
		{
			//其中之一无法计算
			cerr << "more than one of the Polygon is unable to calculate!" << endl;
			return shared_ptr<Polygon>(nullptr);
		}
		//两个矩形形相交 -- 可以计算 -- 其它的无法计算
		if (p1->_edges.size() == 4 && p2->_edges.size() == 4)
		{
			//y1 + y2 - (max(八个点的y)-min(八个点的y)) = 相交的y
			//x1 + x2 - (max(八个点的x)-min(八个点的x)) = 相交的x
			//如果 y1 + y2 < (max(八个点的y)-min(八个点的y))且
			// x1 + x2 < (max(八个点的x)-min(八个点的x)) -- 没有交集
			vector<Point>points;
			for (size_t i = 0; i < p1->_edges.size(); i++)
			{
				points.push_back(p1->_edges[i]->_point1);
				points.push_back(p1->_edges[i]->_point2);
				points.push_back(p2->_edges[i]->_point1);
				points.push_back(p2->_edges[i]->_point2);
			}
			//计算两个四边形的长和宽
			pair<double, double>po1 = get_height_width(p1);
			pair<double, double>po2 = get_height_width(p2);
			double ymax = -1; double ymin = 10000000; double xmax = -1; double xmin = 1000000;
			for (size_t i = 0; i < points.size(); i++)
			{
				//points.size() == 16
				ymax = max(ymax, points[i]._y);
				ymin = min(ymin, points[i]._y);
				xmax = max(xmax, points[i]._x);
				xmin = min(xmin, points[i]._x);
			}
			if (po1.first + po2.first < (xmax - xmin)
				&& po1.second + po2.second < (ymax - ymin))
			{
				//没有交集
				return shared_ptr<Polygon>(nullptr);
			}
			else
			{
				//有交集 -- 交集是一个矩形
				double in_x = po1.first + po2.first - (xmax - xmin);
				double in_y = po1.second + po2.second - (ymax - ymin);
				//计算该矩形的中心
				double c_x = (xmax + xmin) / 2.0;
				double c_y = (ymax + ymin) / 2.0;
				return shared_ptr<Polygon>(new Polygon(c_x, c_y, in_x, in_y));
			}
		}
		else //无法计算
		{
			return shared_ptr<Polygon>(nullptr);
		}
	}
	else
	{
		return nullptr;
	}
}
ptr_shape operator|(const ptr_shape& ptr1, const ptr_shape& ptr2)
{
	//先识别是圆还是多边形
	if (ptr1 == nullptr || ptr2 == nullptr)return shared_ptr<Shape>(nullptr);
	if (ptr1->__type() == SHAPE || ptr2->__type() == SHAPE)
	{
		return shared_ptr<Shape>(nullptr);
	}
	else if (ptr1->__type() == CIRCLE && ptr2->__type() == CIRCLE)
	{
		//两个都是圆 -- 可以计算
		//两个圆相离
		//两圆的圆心距离之和大于两圆的半径之和
		auto p1 = dynamic_pointer_cast<Circle>(ptr1);
		auto p2 = dynamic_pointer_cast<Circle>(ptr2);
		double distance = sqrt(pow((p1->_center._x - p2->_center._x), 2)
			+ pow((p1->_center._y - p2->_center._y), 2));
		if (distance >= p1->_radius + p2->_radius)
		{
			return shared_ptr<Shape>(nullptr);//无法计算
		}
		//两个圆内含
		else if (distance <= abs(p1->_radius - p2->_radius))
		{
			//返回大圆
			auto max_ptr = p1->_radius > p2->_radius ? p1 : p2;
			return shared_ptr<Circle>(new Circle(max_ptr->_center, max_ptr->_radius));
		}
		//两个圆相交 -- 无法计算 -- 返回空
		else
		{
			return shared_ptr<Circle>(nullptr);
		}
	}
	else if (ptr1->__type() == POLYGON && ptr2->__type() == POLYGON)
	{
		//两个都是多边形
		auto p1 = dynamic_pointer_cast<Polygon>(ptr1);
		auto p2 = dynamic_pointer_cast<Polygon>(ptr2);
		if (p1->isValid() == false || p2->isValid() == false)
		{
			//其中之一不合法 -- 无法计算
			cerr << "more than one of the Polygon is isValid!" << endl;
			return shared_ptr<Polygon>(nullptr);
		}
		if (p1->if_calculate() == false || p2->if_calculate() == false)
		{
			//其中之一无法计算
			cerr << "more than one of the Polygon is unable to calculate!" << endl;
			return shared_ptr<Polygon>(nullptr);
		}
		//两个矩形相互包含 如果对齐了就可以计算，否则不能计算
		if (p1->_edges.size() == 4 && p2->_edges.size() == 4)
		{
			//计算每一个矩形的ymax,ymin,xmax,xmin
			double xmax1 = -1, ymax1 = -1, xmax2 = -1, ymax2 = -1;
			double xmin1 = 100000, ymin1 = 100000, xmin2 = 100000, ymin2 = 100000;
			for (size_t i = 0; i < 4; i++)
			{
				xmax1 = max({ xmax1,p1->_edges[i]->_point1._x,
					p1->_edges[i]->_point2._x });
				ymax1 = max({ ymax1,p1->_edges[i]->_point1._y,
					p1->_edges[i]->_point2._y });
				xmax2 = max({ xmax2,p2->_edges[i]->_point1._x,
					p2->_edges[i]->_point2._x });
				ymax2 = max({ ymax2,p2->_edges[i]->_point1._y,
					p2->_edges[i]->_point2._y });
				xmin1 = min({ xmin1,p1->_edges[i]->_point1._x,
					p1->_edges[i]->_point2._x });
				ymin1 = min({ ymin1,p1->_edges[i]->_point1._y,
					p1->_edges[i]->_point2._y });
				xmin2 = min({ xmin2,p2->_edges[i]->_point1._x,
					p2->_edges[i]->_point2._x });
				ymin2 = min({ ymin2,p2->_edges[i]->_point1._y,
					p2->_edges[i]->_point2._y });
			}
			if (xmax1 > xmax2 && ymax1 > ymax2 && xmin1 < xmin2 && ymin1 < ymin2)
			{
				//第一个矩形包含第二个矩形
				double height = ymax1 - ymin1;
				double width = xmax1 - xmin1;
				double c_x = (xmax1 + xmin1) / 2.0;
				double c_y = (ymax1 + ymin1) / 2.0;
				return shared_ptr<Polygon>(new Polygon(c_x, c_y, height, width));
			}
			else if (xmax1 < xmax2 && ymax1 < ymax2 && xmin1 > xmin2 && ymin1 > ymin2)
			{
				//第二个矩形包含第一个矩形
				double height = ymax2 - ymin2;
				double width = xmax2 - xmin2;
				double c_x = (xmax2 + xmin2) / 2.0;
				double c_y = (ymax2 + ymin2) / 2.0;
				return shared_ptr<Polygon>(new Polygon(c_x, c_y, height, width));
			}
			else
			{
				//无法计算
				return shared_ptr<Polygon>(nullptr);
			}
		}
		else //无法计算
		{
			return shared_ptr<Polygon>(nullptr);
		}
	}
	else
	{
		return nullptr;
	}
}

//放到这里来 -- 不然会报链接错误
ostream& operator<<(ostream& out, const Point& p)
{
	p.Print();
	return out;
}