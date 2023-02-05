#pragma once

#include"LaneSegment.h"


/*
3.定义一个RoadSegment类，包含：
实现构造函数和析构函数；
设置static const int maxLanes成员，表示最大车道数；
构建Lane对象数组；
实现成员函数AddLane(Lane & lane)：在道路中增加车道lane。
*/

/*
1、	新建RoadSegment，自下而上生成三个车道
2、	通过随机函数在每个车道中生成至少2辆车
3、	生成过程中，如果车辆发生了碰撞，则重新生成，直至不发生碰撞
4、	删除最下面的车道及其车道内的车辆
文件组织：每一个类都单独实现为h文件和cpp文件，在main函数内部进行测试。
*/

#if 1
class RoadSegment {
public:
	RoadSegment() {}
	~RoadSegment() {}
	void AddLane(LaneSegment*lane) {
		_lane.push_back(lane);
	}
	void pop_back() {
		_lane.pop_back();
	}
private:
	vector<LaneSegment*>_lane;
public:
	static const int maxLanes;
};
const int RoadSegment::maxLanes = 10;//最多10条车道
#endif