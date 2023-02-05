
#define _CRT_SECURE_NO_WARNINGS 1

#ifdef __cplusplus
#elif
#endif



//#include"Edge.h"
//#include"Shape.h"
#include"ShapeFile.h"

#if 0 //第一个main()的条件编译
#if 1
void test1()
{
	Point p1(0, 0);
	Point p2(3, 4);
	cout << p1 << " " << p2 << endl;
	Point p3(p1);
	p3.Move(1, 1);
	cout << p3 << endl;
	Edge e1(p1, p2);
	e1.Print();
	cout << e1.Length() << endl;

	Circle c1(p2, 3);
	c1.Print();
	c1.Move(-3, -4);
	c1.Print();
}
#endif

#if 1
void test2()
{
	//Point p1_(0, 0);
	//Point p2_(0, 3);
	//Point p3_(1, 0);
	//Point p4_(1, 3);
	//Edge e1_(p1, p2);
	//Edge e2_(p2, p4);
	//Edge e3_(p3, p4);
	//Edge e4_(p3, p1);
	Point p1(0, 0);
	Point p2(3, 0);
	Point p3(0, 4);
	Edge e1(p1, p2);
	Edge e2(p1, p3);
	Edge e3(p2, p3);
	//以后要注意 -- 智能指针的构造一定要是new的 -- 不能是栈上的空间
	shared_ptr<Edge>ptr1(new Edge(p1, p2));
	shared_ptr<Edge>ptr2(new Edge(p1, p3));
	shared_ptr<Edge>ptr3(new Edge(p2, p3));
	vector<shared_ptr<Edge>>arr = { ptr1,ptr2,ptr3 };
	//vector<shared_ptr<Edge>>arr = { make_shared<Edge>(e1),make_shared<Edge>(e2),make_shared<Edge>(e3) };
	//vector<Edge*>arr = { &e1,&e2,&e3 };
	Polygon p(arr);
	cout << p.Area() << endl;
	cout << "print Polygon info" << endl;
	p.Print();
}
#endif


#if 1
void test3()
{
	//测试交并
#if 0
	shared_ptr<Polygon>ptr1(new Polygon(0, 0, 4, 4));
	shared_ptr<Polygon>ptr2(new Polygon(0, 0, 2, 2));
	shared_ptr<Polygon>ptr0(new Polygon(0, 0, 6, 6));
	ptr_shape ptr3 = ptr1 | ptr2 | ptr0;
	if (ptr3 == nullptr)
	{
		cout << "null" << endl;
		return;
	}
	ptr3->Print();
	ptr_shape ptr4 = ptr1 & ptr2 | ptr0;
	if (ptr4 == nullptr)
	{
		cout << "null" << endl;
		return;
	}
	ptr4->Print();
#endif
#if 1
	shared_ptr<Circle>ptr1(new Circle(Point(0, 0), 1.5));
	shared_ptr<Circle>ptr2(new Circle(Point(0, 0), 2));
	shared_ptr<Circle>ptr0(new Circle(Point(0, 0), 1));
	ptr_shape ptr3 = ptr1 | (ptr2 & ptr0);
	if (ptr3 == nullptr)
	{
		cout << "null" << endl;
		return;
	}
	ptr3->Print();
#endif
}
#endif

int main()
{
	//test1();
	//test2();
	test3();
	return 0;
}
#endif

//测试ShapeFile
#if 1
void runFileQuery(ifstream& infile)
{
	ShapeFile sfile(infile);
	sfile.Generate();
	sfile.Print();
	cout << endl;
}
int main(int argc, char** argv)
{
	// open the file from which user will query words
	if (argc >= 2)
	{
		ifstream infile(argv[1]);
		if (infile.is_open())
		{
			runFileQuery(infile);
		}
		else
		{
			cerr << "Failed opening input file!" << endl;
			return -1;
		}
	}
	else {
		cerr << "No input file name!" << endl;
	}
	return 0;
}
#endif
