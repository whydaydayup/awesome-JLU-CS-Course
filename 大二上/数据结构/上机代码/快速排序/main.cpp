#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;

void Qsort(int* arr,int m,int n)
{
    int i,j,k,temp;
    if(m < n)
    {
        i = m;
        j = n+1;
        k = arr[m];
        while(i<j)
        {
            i++;
            while(arr[i]<k)
                i++;
            j--;
            while(arr[j]>k)
                j--;
            if(i<j)
            {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        temp = arr[m];
        arr[m] = arr[j];
        arr[j] = temp;
        Qsort(arr,m,j-1);
        Qsort(arr,j+1,n);
    }
}

void Ssort(int* arr,int n)
{
    int t;
    int temp;
    for(int j=n;j>=2;j--)
    {
        t = 1;
        for(int i=2;i<=j;i++)
        {
            if(arr[t]<arr[i])
                t = i;
        }
        temp = arr[t];
        arr[t] = arr[j];
        arr[j] = temp;
    }
}

int main()
{
    srand(time(0));
    int* thearr,*thearr2;
    int number(0);
    cout << "ÊäÈë´ýÅÅÐòÔªËØÊý:" << endl;
    cin >> number;
    thearr = new int[number];
    for(int i=0;i<number;++i)
    {
        thearr[i] = rand()%(1000000-10+1) + 10;
        thearr2[i]=thearr[i];
    }
    ofstream outfile;
    outfile.open("text.txt");
    outfile << "´ýÅÅÐòÔªËØ:" << endl;
    for(int i=0;i<number;++i)
        outfile << thearr[i] << " ";
    Qsort(thearr,0,number-1);
    outfile << "ÅÅÐòºóÔªËØ:" << endl;
    for(int i=0;i<number;++i)
        outfile << thearr[i] << " ";
    Ssort(thearr2,number-1);
    outfile << "ÅÅÐòºóÔªËØ:" << endl;
    for(int i=0;i<number;++i)
        outfile << thearr[i] << " ";
    //rand()%(50-10+1) + 10
    return 0;
}
