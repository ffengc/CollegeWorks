

## 关于多边形类的实现框架和规则解释

在本次大作业实现的多边形类中
1. 仅有三角形和矩形（包括正方形）可以完成面积的计算，其它多边形面积认为是-1，所有合法多边形均可以完成周长计算
2. 合法性检验（当顶点个数等于边的个数的时候认为是合法多边形）
3. 为了更好的在后续代码中构造多边形类，类中提供了
	get_height_width()得到一个矩形长和宽的接口
	if_calculate()判断该多边形是否能计算面积 -- 前提是合法
	is_rectangle()判断该多边形是否是hi矩形


## 交并运算规则
//在Shape及其派生类中提供了__type()函数 -- 可以获取当前Shape的具体类型
1. 仅有矩形和矩形，圆和圆之间可以进行交并运算 -- 其余交并运算返回nullptr
2. 圆和圆的运算 -- 仅计算两圆相离，内含，相切的情况，相交的情况不做运算 -- 返回nullptr
3. 矩形和矩形的运算，如果其中一个多边形不合法或其中一个多边形不能计算面积 -- 返回nullptr
	其它细节请见代码~

## ShapeFile类实现的一些思路
1. 如何判断当前是在识别什么东西，是Shape还是Point？是Shape的哪种类型？
	通过提供类型**枚举** -- 如果在注释行找到相应提示，即更改当前录入信息的状态
2. 	通过实现一些字符串相关的接口来进行文本的处理
	//处理字符串的一些接口
	double find_first_digit(const string& str);
	double find_last_digit(const string& str);
	vector<int> get_idx(const string& str);
	void erase_the_first_idx(string& arr);