#pragma once

#include"Vehicle.h"

/*
2.定义一个LaneSegment类，包含成员变量：float x_, float y_, float length_, float width_。
其中：(x_, y_)表示车道左上角的起始位置，length_分别表示车道和长度，单位m；
Vehicle对象数组；
static const int maxVehicles表示最大车辆数。
实现构造函数、复制构造函数和析构函数；其中：length_和width_的默认值分别为：100，3.5
实现成员函数IsInLane(const Vehicle &veh)：判断车道上是否存在车辆veh，如果存在返回1，否则返回0；
实现成员函数AddVehicle((Vehicle &veh)：在道路上生成新的车辆veh；
实现成员函数RemoveVehicle(Vehicle &veh)：在道路上删除车辆veh。
*/

/// <summary>
/// 因为需要频繁查找车道上的车辆是否存在 -- 使用哈希可以在车辆数多时提高效率
/// </summary>

//给哈希表指定模板(未能成功实现)
# if 0  //该问题还没解决 -- 自定义类型做key
struct hash_name {
	size_t operator()(const Vehicle& p) const {
		return hash<float>()(p._x) ^ hash<float>()(p._y)^hash<float>()(p._vx)^ 
			hash<float>()(p._vy)^ hash<float>()(p._width)^hash<float>()(p._height);
	}
};
class LaneSegment {
private:
	float _x;
	float _y;
	float _length;
	float _width;
	//vector<Vehicle>_arr; 选择使用哈希 -- 查找效率高
	unordered_map<Vehicle, int, hash_name>_hash;  //但是自定义类型不能直接哈希化 -- 需要进行模板定制
	static const int maxVehicles;
public:
	friend struct hash_name;
	LaneSegment(float x = 0, float y = 0, float length = 100, float width = 3.5)
		:_x(x), _y(y), _length(length), _width(width) {}
	LaneSegment(LaneSegment& l)
		: _x(l._x), _y(l._y), _length(l._length), _width(l._width) {}
	~LaneSegment() {
		cout << "删除该车道" << endl;
	}
	bool isInLane(const Vehicle& veh) {
		if (_hash.find(veh) != _hash.end()) { //查找效率:O(1)
			return true;
		}
		return false;
	}
	void AddVehicle(Vehicle& veh) {
		assert(_hash.size() != maxVehicles); //车道满了 -- 不能再加了
		++_hash[veh];
	}
	void RemoveVehicle(Vehicle& veh) {
		assert(_hash.find(veh) != _hash.end());//查找效率:O(1)
		--_hash[veh];
	}
	size_t size() const {
		return _hash.size();
	}
};
const int LaneSegment::maxVehicles = 10;//最多10辆车
#endif

//使用vector存放车
class LaneSegment {
private:
	float _x;
	float _y;
	float _length;
	float _width;
public:
	vector<Vehicle>_array;
	static const int maxVehicles;
public:
	LaneSegment(float x = 0, float y = 0, float length = 100, float width = 3.5)
		:_x(x), _y(y), _length(length), _width(width) {}
	LaneSegment(LaneSegment& l)
		: _x(l._x), _y(l._y), _length(l._length), _width(l._width) {}
	~LaneSegment() {
		cout << "删除该车道" << endl;
	}
	bool isInLane(const Vehicle& veh) {
		for (int i = 0; i < _array.size(); i++) {
			if (veh == _array[i])return true;//找到了
		}
		return false;//找不到
	}
	void AddVehicle(Vehicle& veh) {
		assert(_array.size() != maxVehicles); //车道满了 -- 不能再加了
		_array.push_back(veh);
	}
	void RemoveVehicle(Vehicle& veh) {
		for (int i = 0; i < _array.size(); i++) {
			if (_array[i] == veh) {
				_array.erase(_array.begin() + i);
			}
		}
		cout << "找不到该车" << endl;
	}
	size_t size() const { //车的数量
		return _array.size();
	}
};	
const int LaneSegment::maxVehicles = 10;