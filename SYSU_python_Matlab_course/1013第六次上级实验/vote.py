


class VoteSys:
    def __init__(self,file_path) -> None:
        print("这是投票统计系统")
        self.file_path=file_path
        self.fp=open(file_path,'r',encoding='utf-8')
    def is_Valid(self,str,arr):
        if len(str)!=1:
            return False
        if str in arr:
            return True
        else:
            return False
    def print_result(self):
        file_list=self.fp.readlines()    
        candidate_dict={}
        for i in range(0,len(file_list)): # 把换行符去掉
            file_list[i] = file_list[i].rstrip()
        # 初始化候选人字典
        candidate_list = file_list[1].split(' ')
        for i in range(0,len(candidate_list)):
            candidate_dict[candidate_list[i]]=0
        # 开始唱票
        voters_list=file_list[3].split(' ')
        # 检查投票合法性
        Invalid=0
        for i in range(0,len(voters_list)):
            if self.is_Valid(voters_list[i],candidate_list):
                candidate_dict[voters_list[i]]+=1
            else:
                Invalid+=1
        for i in range(0,len(candidate_list)):
            print(candidate_list[i]+":"+ str(candidate_dict[candidate_list[i]]))
        print("InValid: %d"%Invalid)