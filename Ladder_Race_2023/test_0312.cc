

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>
#include <set>
using namespace std;

// L1-018 大笨钟
#if 0
pair<int, int> extraction_time(const string &str)
{
    int ptr = 0;
    while (1)
    {
        if (str[ptr] == ':')
            break;
        ptr++;
    }
    string h(str.begin(), str.begin() + ptr + 1);
    string m(str.begin() + ptr + 1, str.end());
    pair<int, int> res;
    res.first = stoi(h);
    res.second = stoi(m);
    return res;
}
int get_number_of_blows(const pair<int, int> &time)
{
    int h = time.first;
    int m = time.second;
    if (h >= 0 && h <= 11)
        return -1;
    if (h == 12 && m == 0)
        return -1;
    // 此时就是要完成敲击的了
    if (h == 12)
    {
        return 1;
    }
    if (m != 0)
        h++;
    return h - 12;
}
int main()
{
    string str;
    cin >> str;
    pair<int, int> time = extraction_time(str);
    // cout << time.first << " " << time.second << endl;
    int num = get_number_of_blows(time);
    // cout << num << endl;
    if (num == -1)
    {
        cout << "Only " << str << ".  Too early to Dang." << endl;
    }
    else
    {
        for (int i = 0; i < num; i++)
        {
            cout << "Dang";
        }
    }
    return 0;
}
#endif

// L1-022 奇偶分家
#if 0
int main()
{
    int input = 0;
    cin >> input;
    int even = 0;
    int odd = 0;
    for(int i = 0;i < input; i++)
    {
        int x = 0;
        cin >> x;
        if(x % 2 == 0)
            even++;
        else odd++;
    }
    cout << odd << " " << even << endl;
    return 0;
}
#endif

// L1-023 输出GPLT
// 没通过
#if 0
int main()
{
    string str;
    cin >> str;
    int G = 0, P = 0, L = 0, T = 0;
    for (const auto &e : str)
    {
        if (e == 'G')
            G++;
        else if (e == 'P')
            P++;
        else if (e == 'L')
            L++;
        else if (e == 'T')
            T++;
    }
    while (true)
    {
        if (G)
        {
            cout << 'G';
            G--;
        }
        if (P)
        {
            cout << 'P';
            P--;
        }
        if (L)
        {
            cout << 'L';
            L--;
        }
        if (T)
        {
            cout << 'T';
            T--;
        }
        if (!G && !P && !L && !T)
            break;
    }
    return 0;
}
#endif
