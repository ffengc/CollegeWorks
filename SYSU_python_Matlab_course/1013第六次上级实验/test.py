
import os
from Student import Student
import vote
class Solution:
    def __init__(self) -> None:
        print("1013第六次上机实验")
    def test1(self):
        '''
        1. 在文件夹中创建一个haha.txt，输入123，保存并关闭。
            用python程序打开haha.txt,用于写，输出此时的文件名，
            文件状态（是否关闭），访问方式。
        '''
        fp=open(r'haha.txt','w')
        print(fp.name)
        print(fp.closed)
        print(fp.mode)
        fp.close()
    def test2(self):
        """
        2. 文件的访问练习：
            1）创建一个hei.txt,写入自己的姓名，学号，性别，爱好，保存并关闭；
            2）读取hei.txt文件中的前11个字符，并输出；
            3）定位并输出hei.txt的位置，并将hei.txt重命名为 python.txt；
            4）输出当前目录的所有文件名，删除python.txt.。
        """
        fp=open('hei.txt','r',encoding='utf-8')
        print(fp.read(11))
        file_path = os.path.dirname(os.path.abspath('hei.txt'))
        print(file_path)
        # 要关闭文件才能改名吗？
        fp.close
        os.rename('hei.txt','python.txt')
        def walk_Dir():
            rootdir = file_path
            # 递归返回条件
            for parent,dirnames,filenames in os.walk(rootdir):
                # 三个参数：分别返回
                # 1.父目录
                # 2.所有文件夹名字（不含路径）
                # 3.所有文件名字
                for dirname in dirnames:
                    print("parent is:"+parent)
                    print("dirname is:"+dirname)
                for filename in filenames:
                    print("parent is:"+parent)
                    print("filename is:"+filename)
                    print("the full name of the file is:",os.path.join(parent,filename))
        walk_Dir()
    def test3(self):
        path='vote.txt'
        v=vote.VoteSys(path)
        v.print_result()
    def test4(self):
        path='Course_Selection_List.txt'
        s=Student(path)
        s.start_sys()




def main():
    s=Solution()
    # s.test1()
    s.test2()
    # s.test3()
    # s.test4()

if __name__=='__main__':
    main()        