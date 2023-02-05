#define _CRT_SECURE_NO_WARNINGS 1

#include"Vehicle.h"
#include"LaneSegment.h"
#include"RoadSegment.h"
#include<random>
void test_Vehicle() {
	Vehicle v1;
	cout << v1 << endl;
	Vehicle v2 = v1;
	cout << v2;
	cout << v2.isCollision(v1) << endl;
	cout <<"现在目前车辆数:"<< Vehicle::_vCount << endl;
}


void test() {
	unordered_map<int, int>hash;
	vector<int>arr = { 1,2,3,4,5 };
	for (int i = 0; i < arr.size(); i++) {
		++hash[arr[i]];
	}
	cout << hash.size() << endl;
}
/*
1、	新建RoadSegment，自下而上生成三个车道
2、	通过随机函数在每个车道中生成至少2辆车
3、	生成过程中，如果车辆发生了碰撞，则重新生成，直至不发生碰撞
4、	删除最下面的车道及其车道内的车辆
文件组织：每一个类都单独实现为h文件和cpp文件，在main函数内部进行测试。
*/
bool is_valid(const LaneSegment& l, Vehicle v) {
	//现在判断v会不会和l里面的车碰撞
	for (int i = 0; i < l._array.size(); i++) {
		if (l._array[i].isCollision(v)) {
			return false;
		}
	}
	return true;
}
void add_cars_in_lanes(LaneSegment& l, float y_min, float y_max) {
	///(y_min,y_max)表示车道从上到下的宽度
	//随机生成三辆车
	default_random_engine e(time(0));
	for (int i = 0; i < 2; i++) {//表示生成两辆车
		bool flag = false;//表示生成的车辆是否合法
		do {
			uniform_real_distribution<float>u(y_min, y_max);//y的范围
			uniform_real_distribution<float>ux(2.0, 8.0); //x的范围
			float x = ux(e);
			float y = u(e);
			Vehicle v(x, y);
			if (is_valid(l,v)) {
				flag = true;
				l.AddVehicle(v);//把v加进去
			}
		} while (!flag);//当车辆合法之后  --  跳出循环，准备生成第二辆车
	}
}
void test_homework() {
	LaneSegment l1(0, 0);
	LaneSegment l2(0, 5);
	LaneSegment l3(0, 10);
	add_cars_in_lanes(l1, 1, 2.5);
	add_cars_in_lanes(l2, 6, 7.5);//在这个范围内生成 -- 因为车辆有宽度
	add_cars_in_lanes(l3, 11, 12.5);
	RoadSegment r;
	r.AddLane(&l1);
	r.AddLane(&l2);
	r.AddLane(&l3);
	r.pop_back();
}
int main() {
	//test_Vehicle();
	test_homework();
	return 0;
}