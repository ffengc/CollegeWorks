


# 封装



# 继承
class Person:
    def __init__(self,name) -> None:
        self.name=name
    def print_messaage(self):
        print("我是{}".format(self.name))
class Student(Person):
    def __init__(self, name,student_id) -> None:
        super().__init__(name)
        self.student_id=student_id
    def print_messaage(self):
        # # return super().print_messaage()
        # print("我的名字是{},我的学号是{}".format(self.name,self.student_id))

        # 也可以用子类调用父类的方法
        super().print_messaage()
        print(f"我的学号是{self.student_id}")

'''
父类实例无法调用子类中的成员函数
子类实例能够访问父类中的成员函数
'''

s1 = Person("Xiao Li")
s1.print_messaage()
s2 = Student("Xiao Li",20219009)
s2.print_messaage()


'''类的字段'''
# 普通字段，保存于对象，基于对象来访问
# 静态字段，为所有类的对象共享，可以通过对象和类来访问
# （一般定义在__init__函数之前）

'''类的方法'''
# 普通方法，由对象调用，至少一个self参数
# 静态方法，由类直接调用，根据需要定义，加上装饰器@staticmethod
# 类方法，与静态方法类似，需要至少一个参数cls，加上装饰器@classmethod