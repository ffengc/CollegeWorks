

#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

// L1-002 打印沙漏
#if 0
int get_sum(int begin, int end)
{
    int res = 0;
    for (int i = begin; i <= end; i += 2)
    {
        res += i;
    }
    return res;
}
int get_start_num(int size, int *rest)
{
    int j = 0;
    for (j = 1;; j += 2)
    {
        int sum = get_sum(1, j) * 2 - 1;
        int next_sum = get_sum(1, j + 2) * 2 - 1;
        if (sum <= size && next_sum > size)
        {
            // 此时符合要求！
            *rest = size - sum;
            return j;
        }
    }
}
void print(int length, char syb)
{
    for (int i = 0; i < length / 2; i++)
    {
        // 打印空格+打印符号+打印空格
        for (int j = 0; j < i; j++)
        {
            cout << " ";
        }
        for (int j = 0; j < length - 2 * i; j++)
        {
            cout << syb;
        }
        for (int j = 0; j < i; j++)
        {
            cout << " ";
        }
        cout << endl;
    }
    for(int i = 0;i<(length-1)/2;i++)cout<<" ";
    cout << syb << endl;
    for (int i = 0; i < length / 2; i++)
    {
        // 打印空格+打印符号+打印空格
        for (int j = 0; j < (length - (2 * i + 3)) / 2; j++)
        {
            cout << " ";
        }
        for (int j = 0; j < 2 * i + 3; j++)
        {
            cout << syb;
        }
        for (int j = 0; j < (length - (2 * i + 3)) / 2; j++)
        {
            cout << " ";
        }
        cout << endl;
    }
}
int main()
{
    int input = 0;
    cin >> input;
    if(input == 0)return 0;
    char syb;
    cin >> syb;
    int rest = 0;
    int start = get_start_num(input, &rest);
    // 开始打印
    print(start, syb);
    cout<<rest;
    return 0;
}
#endif

// L1-005 考试座位号
#if 0
class info
{
private:
    unordered_map<int,string>hash1;
    unordered_map<int,int>hash2;
public:
    void add(string str,int key,int num)
    {
        hash1[key] = str;
        hash2[key] = num;
    }
    pair<string,int> get_by_key(int key)
    {
        return make_pair(hash1[key],hash2[key]);
    }
};
int main()
{
    info db;
    int num = 0;
    cin>>num;
    for(int i = 0;i<num;i++)
    {
        string str;
        int key = 0;
        int num = 0;
        cin >> str >> key >> num;
        db.add(str,key,num);
    }
    int input = 0;
    cin>>input;
    for(int i = 0;i<input;i++)
    {
        int key = 0;
        cin>>key;
        cout<<db.get_by_key(key).first<<" "<<db.get_by_key(key).second<<endl;
    }
    return 0;
}
#endif

// L1-006 连续因子
#if 0
int isPrime(int n)
{
    int i;
    for (i = 2; i <= sqrt(n) + 1; i++) // 重点：sqrt(n)+1
    {
        if (n % i == 0)
            return 0;
    }
    return 1;
}
int main()
{
    int i, n, s, maxs = 0, maxl = 0, j;
    scanf("%d", &n);
    if (isPrime(n))
    {
        printf("1\n");
        printf("%d\n", n);
        return 0;
    } // 若为素数则不符合题意
    for (i = 2; i <= sqrt(n) + 1; i++)
    {
        if (n % i == 0)
        {
            s = i;
            for (j = i + 1; j <= sqrt(n) + 1; j++)
            {
                s *= j;
                if (n % s != 0)
                    break;
            }                 // 判断因子是否连续 ，若不连续则寻找下一个
            if (maxs < j - i) // 判断j-i>0，说明有连续
            {
                maxs = j - i; // 给maxs赋值，继续循环找出最长的
                maxl = i;
            }
        }
    }
    printf("%d\n", maxs);
    for (i = maxl; i <= maxs + maxl - 1; i++)
    {
        if (i != maxl)
            printf("*");
        printf("%d", i);
    }
    return 0;
}
#endif

// L1-007 念数字
#if 0
int main()
{
    unordered_map<char, string> hash = {{'0', "ling"}, {'1', "yi"}, {'2', "er"}, 
                {'3', "san"}, {'4', "si"}, {'5', "wu"}, {'6', "liu"}, 
                {'7', "qi"}, {'8', "ba"}, {'9', "jiu"}, {'-', "fu"}};
    string input;
    cin >> input;
    string res;
    for(const auto& e : input)
    {
        res+=hash[e];
        res+=" ";
    }
    res.pop_back();
    cout<<res;
    return 0;
}
#endif

// L1-008 求整数段和
#if 0
int main()
{
    int A,B;

    scanf("%d %d",&A,&B);

    int sum=0;
    int count=0;//记录输出5哥输出个回车
    for(int i=A;i<=B;i++)
    {
        count++;
        sum+=i;
        printf("%5d",i);
        if(count%5==0||i==B)
            printf("\n");
    }

    printf("Sum = %d",sum);

    return 0;
}
#endif

// L1-010 比较大小
#if 0
int main()
{
    vector<int>arr;
    for(int i = 0; i < 3;i++)
    {
        int num = 0;
        cin >> num;
        arr.push_back(num);
    }
    sort(arr.begin(),arr.end());
    for(int i = 0;i<arr.size();i++)
    {
        cout<<arr[i];
        if(i!=arr.size()-1)
        {
            cout<<"->";
        }
    }
    return 0;
}
#endif

// L1-011 A-B
#if 0
int main()
{
    unordered_map<char,bool>hash;
    string str1;
    string str2;
    getline(cin,str1);
    getline(cin,str2);
    for(const auto& e: str2)
    {
        hash[e] = true;
    }
    string ret;
    for(const auto& e : str1)
    {
        if(hash[e] == false)
        {
            ret+=e;
        }
    }
    cout<<ret;
    return 0;
}
/*
I love GPLT!  It's a fun game!
aeiou
*/
#endif

// L1-013 计算阶乘和
#if 0
int factorial(int n)
{
    int res = 1;
    for (int i = 1; i <= n; i++)
    {
        res *= i;
    }
    return res;
}
int main()
{
    int n = 0;
    cin >> n;
    int sum = 0;
    for(int i = 1;i<=n;i++)
    {
        sum+=factorial(i);
    }
    cout<<sum;
    return 0;
}
#endif


//L1-015 跟奥巴马一起画方块
#if 0
int main()
{
	int i,j,n;
	char c;
	scanf("%d %c",&n,&c);
	for(i=0;i<(n+1)/2;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("%c",c);
		}
		if(i<(n+1)/2-1)
			printf("\n");
	}
	return 0;
}
#endif
