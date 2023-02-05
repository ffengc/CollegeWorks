"""
1. 利用Python中的class实现图书信息储存，包括书名、作者、售价、出版日期、出版商信息，建立列表，存储2本图书内容，并打印相关信息。
2. 复现课件中利用Python实现栈的示例，并进行功能测试。
3. 参考栈的实现方法，用Python实现队列（队列的主要特性：数据先进先出，需实现入队、出队、判空，获取队列大小和队头元素这几项基本功能）。
"""


class Book:
    def __init__(self, name, author, price, publication_date, publicsher_info):
        self._name = name
        self._author = author
        self._price = price
        self._publication_date = publication_date
        self._publicsher_info = publicsher_info

    def print_book_info(self):
        print("书名为:", self._name)
        print("作者为:", self._author)
        print("售价为:", self._price)
        print("出版日期为:", self._publication_date)
        print("出版商信息:", self._publicsher_info)


class stack():
    def __init__(self):
        self.st_arr = []

    def push(self, x) -> None:
        self.st_arr.append(x)

    def pushListByOnce(self, arr) -> None:
        # 一般stack类不提供此接口
        self.st_arr.append(arr)

    def pop(self) -> None:
        if self.empty():
            print("error:stack empty,pop failed")
            return
        self.st_arr.pop()

    def size(self):
        return len(self.st_arr)

    def empty(self) -> (bool):
        return self.st_arr == []

    def top(self):
        if self.empty():
            print("error:stack empty")
            return None
        return self.st_arr[len(self.st_arr) - 1]

    def print_stack(self):
        # 一般stack类不提供打印接口
        for i in self.st_arr:
            print(i, end=' ')
        print()


class queue:
    def __init__(self):
        self.q_arr = []

    def push(self, x) -> None:
        self.q_arr.insert(0, x)

    def pop(self) -> None:
        if self.empty():
            print("error:queue empty,pop failed")
            return None
        self.q_arr.pop()

    def rear(self):
        if self.empty():
            print("error:queue empty")
            return None
        return self.q_arr[0]

    def front(self):
        if self.empty():
            print("error:queue empty")
            return None
        return self.q_arr[len(self.q_arr) - 1]

    def empty(self):
        return len(self.q_arr) == 0

    def size(self):
        return len(self.q_arr)
    def print_queue(self):
        # 一般queue类不提供这个接口
        for i in self.q_arr:
            print(i,end=' ')
        print()

def testBook():
    book1 = Book("新华", "小明", 30, "2022.1.1", "高等教育出版社")
    book2 = Book("大学物理", "张三", 99, "2022.1.2", "清华大学出版社")
    list_book = []
    list_book.append(book1)
    list_book.append(book2)

    for i in range(len(list_book)):
        list_book[i].print_book_info()


def testStack():
    st = stack()
    st.push(1)
    st.push(2)
    st.push(3)
    st.pop()
    print(st.empty())
    st.print_stack()


def testQueue():
    q=queue()
    q.push(1)
    q.push(2)
    q.push(3)
    q.push(4)
    q.pop()
    print(q.empty())
    print(q.size())
    q.print_queue()

# testBook()
# testStack()
testQueue()


dict={}
dict.