#include "StudentList.h"

void menu();
int main(){
    StudentList alist;//实例化
    int n;
    menu();
    cin>>n;
    alist.readfile();
	while(n){
		switch(n){
		case 1:alist.read_file();break;
		case 2:alist.interaction();break;
		case 3:alist.insertstudent();break;
		case 4:alist.changemessage();break;
		case 5:alist.deletestudent();break;
		case 6:alist.searchstudent();break;
		case 7:alist.gradesort();break;
		case 8:alist.substatistics();break;
		case 9:alist.display();break;
		case 0:break;
		}
		menu();
		cin>>n;
	}    //主菜单
}

void menu()
{
	system("cls");
	cout<<"\n\n\n\n\n";
	cout<<"\t\t|---------------------学生信息管理系统-------------------|\n";
	cout<<"\t\t|\t 1. 从文件导入信息                               |\n";
	cout<<"\t\t|\t 2. 交互式录入学生信息                           |\n";
	cout<<"\t\t|\t 3. 插入学生信息                                 |\n";
	cout<<"\t\t|\t 4. 修改学生信息                                 |\n";
	cout<<"\t\t|\t 5. 删除学生信息                                 |\n";
	cout<<"\t\t|\t 6. 查询学生信息                                 |\n";
	cout<<"\t\t|\t 7. 成绩排序                                     |\n";
	cout<<"\t\t|\t 8. 科目数据统计                                 |\n";
	cout<<"\t\t|\t 9. 浏览学生信息                                 |\n";
	cout<<"\t\t|\t 0. 退出                                         |\n";
	cout<<"\t\t|--------------------------------------------------------|\n\n";
	cout<<"\t\t\t请输入(0-9):";
}
