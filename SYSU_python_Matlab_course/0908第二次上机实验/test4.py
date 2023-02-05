# 0908第二次上机
# 第三题


class Solution_0908_3:

    def __init__(self):
        print("0908人工智能编程语言第二次上机 第三题")

    def test(self):
        """
        1）	有如下字典:dict1 = {"key1":"value1","key2":"value2","key3":"value3"}，循环遍历输出所有的key。
        2）	请在字典中增加一个键值对,"key4":"value4"，输出添加后的字典。
        3）	请删除字典中键"key5"对应的键值对，如果字典中不存在键"key5",则输出None。
        4）	list1 = [1,2,3,4,5,6,7],list2 = [“Sun”,“Mon”,“Tue”,“Wed”,“Thu”,“Fri”,“Sat”]。
            以list1中的元素作为key，以list2中的元素作为value生成一个新的字典dict2。
        5）	有如下值集合[11,22,33,44,55,66,77,88,99,100，110,200,230,330],将所有大于66的值保存至字典的第一个key中，将等于小于66的值保存至第二个key中。
        即：{‘k1’:大于66,‘k2’:小于等于66}
        """
        dict1 = {"key1": "value1", "key2": "value2", "key3": "value3"}
        # 1)
        list_key = list(dict1.keys())
        for i in range(len(list_key)):
            print(list_key[i])
        # 2)
        dict1["keys4"] = "value4"
        print(dict1)
        # 3)
        if "keys5" in dict1:
            del dict1["keys5"]
        else:
            print(None)
        # 4)
        """
        list1 = [1,2,3,4,5,6,7],list2 = [“Sun”,“Mon”,“Tue”,“Wed”,“Thu”,“Fri”,“Sat”]。
        以list1中的元素作为key，以list2中的元素作为value生成一个新的字典dict2。
        """
        dict2 = {}
        list1 = [1, 2, 3, 4, 5, 6, 7]
        list2 = ["Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"]
        idx = 0
        for idx in range(len(list1)):
            dict2[list1[idx]] = list2[idx]
        print(dict2)
        # 5
        """
        有如下值集合[11,22,33,44,55,66,77,88,99,100，110,200,230,330],
        将所有大于66的值保存至字典的第一个key中，将等于小于66的值保存至第二个key中。
        即：{‘k1’:大于66,‘k2’:小于等于66}
        """
        dict3 = {}
        dict3['key1']=[]
        dict3['key2']=[]
        arr = [11, 22, 33, 44, 55, 66, 77, 88, 99, 100, 110, 200, 230, 330]
        for i in range(len(arr)):
            if arr[i] > 66:
                dict3['key1'].append(arr[i])
            else:
                dict3['key2'].append(arr[i])
        print(dict3)


s = Solution_0908_3()
s.test()
