

# 没必要用继承，这里也不应该用继承

from ast import main
from curses.ascii import isdigit, islower, isupper
import pandas as pd
import sys

# =================================== 个人信息类 =================================== #
# ================================ User_Information =============================== #


class User_Information:
    def __init__(self) -> None:
        self.__Password_Rating_list = ['very_secure', 'secure', 'very_strong',
                                       'strong', 'general', 'weak', 'very_weak']  # 类里面访问足够了 - 设为私有属性
        self.user_name = None
        self.pass_word = None
        self.name = None
        self.Student_ID = 0
        self.Password_Rating = None

    def __Get_security_level(self, string='') -> str:  # 类里面访问足够了 - 设为私有方法
        score = 0
        length = len(string)
        digit_cnt = 0  # 数字个数
        upper_cnt = 0  # 大写字母个数
        lower_cnt = 0  # 小写字母个数
        sym_cnt = 0  # 符号的个数
        # 遍历字符串
        for i in range(0, len(string)):
            if string[i].isdigit():
                digit_cnt += 1
            elif string[i].isupper():
                upper_cnt += 1
            elif string[i].islower():
                lower_cnt += 1
        sym_cnt = length-digit_cnt-upper_cnt-lower_cnt
        # 计算得分
        # 密码长度
        if length <= 4:
            score += 5
        elif length <= 7 and length >= 5:
            score += 10
        elif length >= 8:
            score += 25
        # 字母
        if upper_cnt == 0 and lower_cnt == 0:
            score += 0  # 没有字母
        elif (upper_cnt and lower_cnt == 0) or (upper_cnt == 0 and lower_cnt):
            score += 10  # 全都是小（大）写字母
        elif upper_cnt and lower_cnt:
            score += 20  # 大小写混合字母
        # 数字
        if digit_cnt == 0:
            score += 0
        elif digit_cnt == 1:
            score += 10
        elif digit_cnt > 1:
            score += 20
        # 符号
        if sym_cnt == 0:
            score += 0
        elif sym_cnt == 1:
            score += 10
        elif sym_cnt > 1:
            score += 25
        # 额外加分
        if sym_cnt == 0 and upper_cnt and lower_cnt and digit_cnt:
            score += 2
        elif ((sym_cnt and upper_cnt == 0 and lower_cnt and digit_cnt) or
              (sym_cnt and upper_cnt and lower_cnt == 0 and digit_cnt)):
            score += 3
        else:
            score += 5
        # 计算等级
        if score >= 90:
            return self.__Password_Rating_list[0]
        elif score >= 80:
            return self.__Password_Rating_list[1]
        elif score >= 70:
            return self.__Password_Rating_list[2]
        elif score >= 60:
            return self.__Password_Rating_list[3]
        elif score >= 50:
            return self.__Password_Rating_list[4]
        elif score >= 25:
            return self.__Password_Rating_list[5]
        elif score >= 0:
            return self.__Password_Rating_list[6]

    def __set_pass_word(self) -> tuple:  # 类里面访问足够了 - 设为私有方法
        '''密码设置'''
        pass_word = None
        while True:
            pass_word = input("请设置密码:>")
            level = self.__Get_security_level(pass_word)
            print(f"当前的密码等级为: {level} ,如果不需要重新输入请按q退出！")
            choose = input()
            if choose == 'q':
                break
        return pass_word, level

    def set_user_info(self):
        '''设置用户人信息'''
        self.name = input("请输入用户人姓名:>")
        self.Student_ID = input("请输入学号:>")
        self.user_name = input("请设置账户用户名:>")
        self.pass_word, self.Password_Rating = self.__set_pass_word()

    def modify_pass_word(self):
        '''修改密码'''
        print("请修改")
        self.pass_word, self.Password_Rating = self.__set_pass_word()
        print("修改成功!")

# =================================== 账户管理系统类 =================================== #
# =================================== Account_System ================================== #


class Account_System:
    def __init__(self) -> None:
        self.account_list = []

    def add_person_info(self):
        person = User_Information()
        print("============== 添加信息 ==============")
        person.set_user_info()  # 设置该对象信息
        self.account_list.append(person)
        print("============== 添加成功 ==============")
        print()
    def delete_person_info(self):
        user_name=input("请输入要删除的用户名:>")
        for i in range(0,len(self.account_list)):
            if self.account_list[i].user_name == user_name:
                self.account_list.pop(i)
                print("删除成功！")
                return
        print("找不到该账户信息！")

    def search_person_info(self):
        user_name=input("请输入要查找的用户名:>")
        for i in range(0,len(self.account_list)):
            if self.account_list[i].user_name == user_name:
                tmp = self.__to_dict(self.account_list[i])
                print()
                s = pd.Series(tmp)
                print(s)
                print()
                return
        print("找不到该账户信息！")
            
    def modify_person_password(self):
        user_name=input("请输入要修改密码的用户名:>")
        for i in range(0,len(self.account_list)):
            if self.account_list[i].user_name == user_name:
                self.account_list[i].modify_pass_word()
                return
        print("找不到该账户信息！")

    def print_sys_info(self):
        print("============= 当前账户信息 =============")
        print(f"当前账户人数为:{len(self.account_list)}人")
        info_dict_list = []
        for i in range(0, len(self.account_list)):
            tmp = self.__to_dict(self.account_list[i])
            info_dict_list.append(tmp)
        # 最后用Dataframe打印比较好
        print()
        df = pd.DataFrame(info_dict_list)
        df.index=df.index+1

        # 解决打印不对齐问题
        pd.set_option('display.unicode.ambiguous_as_wide', True)
        pd.set_option('display.unicode.east_asian_width', True)
        pd.set_option('display.width', 180) # 设置打印宽度(**重要**)

        print(df) # 打印DataFrame
        print()

    def __to_dict(self, user: User_Information) -> dict:
        ans = {}
        ans['用户名'] = user.user_name
        ans['密码等级'] = user.Password_Rating
        ans['姓名'] = user.name
        ans['学号'] = user.Student_ID
        return ans
    
    def menu(self):
        print("==== 学生账户管理系统 ====")
        print("*       1.添加用户       *")
        print("*       2.删除用户       *")
        print("*       3.查找用户       *")
        print("*       4.修改密码       *")
        print("*       5.打印信息       *")
        print("*       0.退出系统       *")
        print("==== 学生账户管理系统 ====")
        input_ch = int(input("请选择:>"))
        return input_ch

    def start_account_sys(self):
        input_ch = self.menu()
        while input_ch:
            if input_ch==1:
                self.add_person_info()
            elif input_ch==2:
                self.delete_person_info()
            elif input_ch==3:
                self.search_person_info()
            elif input_ch==4:
                self.modify_person_password()
            elif input_ch==5:
                self.print_sys_info()
            elif input_ch==0:
                sys.exit()
            else:
                print("err,请重新选择")
            input_ch = self.menu()



# ======================================= 测试 ======================================= #

def main() -> None:
    stu_sys = Account_System()
    stu_sys.start_account_sys()



if __name__=='__main__':
    main()