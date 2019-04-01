#include <iostream>
#include <string>
using namespace std;
void getNext(string& s,int next[]);
int KMPmatch(string& text,string& pattern);
int main()
{
    string str1;
    string str2;
    string str3;
    cout << "please input str1:" << endl;
    getline(cin,str1);
    cout << "please input str2:" << endl;
    getline(cin,str2);
    cout << "please input str3:" << endl;
    getline(cin,str3);
    const int n = KMPmatch(str1,str2);
    if(n!=-1)
    {
        cout << "str2 is the substring of str1." << endl;
        str1.erase(n,str2.length());
        str1.insert(n,str3);
    }
    else
    {
        cout << "str2 isn't the substring of str1." << endl;
        //求str3的逆串temp
        string temp;
        temp.resize(str3.length());
        for(int i=0,j=str3.length()-1;i<str3.length();++i,--j)
        {
            temp[i] = str3[j];
        }
        int j(0);
        j = str1.length()-temp.length();
        str1.erase(j,temp.length());
        str1 += temp;
    }
    cout << "the result is:" << endl;
    cout << str1;
    return 0;
}
void getNext(string& s,int next[])  //求解next数组：next[i]的含义是当模式串p的i+1位匹配失败时
{                                   //i应该退回到的最佳位置(对传统KMP算法做了略微改进)
    int j(-1);
    next[0] = -1;
    for(int i=1;i<s.length();++i)  //求解next[1]--next[s.length()-1]
    {
        while(j!=-1 && s[i]!=s[j+1])
        {
            j = next[j];  //j反复赋值成next[j],直到s[i]==s[j+1]或是j退回到-1
        }
        if(s[i]==s[j+1])
            j++;          //另j指向原next[i]的位置
        //对传统KMP的改进之处从以下开始
        if(j==-1 || s[i+1]!=s[j+1])
            next[i] = j;
        else              //s[i+1]==s[j+1]意味着回退一次其实不够
        {
            next[i] = next[j];   //next[i]直接继承自next[j],节省了一次没必要的回退
        }
    }
}
int KMPmatch(string& text,string& pattern)
{
    int next[pattern.length()];
    getNext(pattern,next);            //计算pattern的next数组
    int j=-1;
    for(int i=0;i<text.length();++i)  //试图匹配next[i]
    {
        while(j!=-1 && text[i]!=pattern[j+1])
        {
            j=next[j];
        }
        if(text[i]==pattern[j+1])
        {
            j++;
        }
        if(j==pattern.length()-1)         //pattern完全匹配，返回匹配模式串的首字符下标
        {
            return i-j;
        }
    }
    return -1;     //匹配失败
}
