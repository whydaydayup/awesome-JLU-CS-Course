//《数据结构（C++版）（第3版）》 作者：叶核亚
//3.3   串的模式匹配

#include "MyString.h"                             //字符串类

int main() 
{
    //3.3.1   Brute-Force算法
//    MyString target("ababdabcd"), pattern("abc");          //C++第3版图3.8，匹配
//    MyString target("ababdabc"), pattern("abc");         //C++第3版图3.8，匹配
//    MyString target("ababdacab"), pattern("abc");        //C++第3版图3.8，不匹配
//    MyString target("abbabaaba"), pattern("aba");
//    MyString target("aaaaaa"), pattern("aab");
//    MyString target("aaabaaab"), pattern("aaaa");        //习题解答图3.2
//    cout<<target<<".search("<<pattern<<")="<<target.search(pattern)<<endl;

/*    //删除子串
    MyString target("ababccdefabcabcgh"), pattern("abc"),target2(target);      //C++第3版图3.9，匹配
//    MyString target("ababccdefabcabcgh"), pattern("ac"),target2(target);       //没有匹配子串，则不操作，所以remove(int i, int n)不能抛出异常
//    MyString target("aaa"), pattern("a"),target2(target);
//    MyString target(""), pattern("a"),target2(target);
    cout<<target<<".removeFirst("<<pattern<<")=";
    target.removeFirst(pattern);
    cout<<target<<endl;
    cout<<target2<<".removeAll("<<pattern<<")=";
    target2.removeAll(pattern);
    cout<<target2<<endl;

    //替换子串
/*    MyString target("ababccdefabcabcgh"), pattern("abc"),replacement("wxyz"); //C++第3版图3.9，匹配
//    MyString target("abbabaabaabac"), pattern("aba"), replacement("wxyz");
//    MyString target("aaa"), pattern("a"), replacement("aaa");
    cout<<target<<".replaceFirst("<<pattern<<", "<<replacement<<")=";
    target.replaceFirst(pattern, replacement);
    cout<<target<<endl;
    cout<<target<<".replaceAll("<<pattern<<", "<<replacement<<")=";
    target.replaceAll(pattern, replacement);
    cout<<target<<endl;
*/

    //3.3.2 KMP
//    MyString target="abdabcabbabcabc", pattern="abcabcaad";  //图3.11，执行MyString(char *str)构造函数
//    MyString target="aaaaaba", pattern="aabaabc";                //最坏情况
//    MyString target="aaaaaaaaaba", pattern="abcabcaaa";                //"abcabcaaa" 习3-9
//    MyString target="aaaaaaaaaaabdabcabbabcabc", pattern="abcabdabcabcaa";
//    MyString target="aaaaaaaaaaabdabcabbabcabc", pattern="aaaabaaabc";
//    cout<<target<<".index("<<pattern<<")="<<target.index(pattern)<<endl;
//    cout<<target<<".index("<<pattern<<")="<<target.index("aab")<<endl;


    //2011级习题解答 习3.3  2012-7-27
/*    //删除子串
    MyString target("ababccdefabcabcgh"), pattern("abc");   //习图3-3
//    MyString target="aaaababaaabaab", pattern="aaba";       //删除后结果："aaaababaaabaab".removeAll("aaba")="aabaab"
    cout<<target<<".removeAll("<<pattern<<")=";
    target.removeAll(pattern);
    cout<<target<<"，target.length()="<<target.length()<<endl;

    //替换子串 
//    MyString target("aabab"), pattern("a"), replacement("aba");   //替换后结果："aabab".replaceAll("a", "aba")="abaabababab"
//    MyString target("aabcabcdbcd"), pattern("abc"), replacement("abcabc");   //替换后结果："aabcabcdbcd".replaceAll("abc", "abcabc")="aabcabcabcabcdbcd"
/*    MyString target("aabcabcdbcd"), pattern("abc"), replacement("xyz");   //替换后结果："aabcabcdbcd".replaceAll("abc", "xyz")="axyzxyzdbcd"
    cout<<target<<".replaceAll("<<pattern<<", "<<replacement<<")=";
    target.replaceAll(pattern, replacement);
    cout<<target<<endl;    */                         

    system("pause");
    return 0;
}

/*
程序运行结果如下：
//BF
count=8
"abbabaaba".index("aba")=3

count=12
"aaaaab".index("aab")=3

count=12
"aaaaaa".index("aab")=-1                       //最坏情况，比较m*(n-m+1)=12次，O(n*m)

count=3
"aaaaaa".index("aaa")=0                        //最好情况，比较3次


//替换子串
target="abbabaabaabac"                         
target.replace("aba", "xy"),    target="abbxyabaabac"
target.replaceAll("aba", "xy"), target="abbxyxyxyc"
  
target="aaa"                         
target.replaceAll("a", "ab"),   target="ababab" 
  
//删除子串
target="abbabaabaxyabac"                         
target.remove("aba"),    target="abbabaxyabac"
target.removeAll("aba"), target="abbxyc"

//KMP
next[]:  -1 0 0 -1 0 0 
count=17
"abdabcabbabcabc".indexOf("abcabc")=9            //图4.11

next[]:  -1 -1 1 
count=9
"aaaaab".indexOf("aab")=3;                       //最坏情况，O(n+m)

*/

/*
KMP.index("aabcbabcaabcaababc", "abcaababc")=9   //张乃孝书
nextk[]: -1 0 0 0 1 1 2 1 2 
next[]:  -1 0 0 -1 1 0 2 0 0 
KMP.count=20

KMP.index("aaabaaaab", "aaaab")=4                //严蔚敏
nextk[]: -1 0 1 2 3 
next[]:  -1 -1 -1 -1 3 
KMP.count=9

KMP.index("aabaaab", "aaab")=3
nextk[]: -1 0 1 2 
next[]:  -1 -1 -1 2 
KMP.count=7

KMP.index("abbabaaba", "aba")=3                 //BF用例
nextk[]: -1 0 0 
next[]:  -1 0 -1 
KMP.count=6

*/
