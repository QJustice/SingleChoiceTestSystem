#include "testHead.h"
#include <iostream>
#include <fstream>
#include "systemHead.h"
#include <vector>
#include <string>
#include "errorExceptionHead.h"
#include <algorithm>
#include <map>
#include <utility>
#include <cstdlib>

using std::cout;
using std::cin;
using std::endl;
using std::fstream;
using std::ios;
using std::vector;
using std::getline;
using std::stoi;
using std::to_string;
using std::find;
using std::map;
using std::pair;
using std::sort;
using std::size_t;

void CAdmin::menu()
{
	system("cls");
	//管理员菜单
	cout << "================================================\n";
	cout << endl;
	cout << "=                 1.查看题库                   =\n";
	cout << "=                 2.增加题目                   =\n";
	cout << "=                 3.删减题目                   =\n";
	cout << "=                 4.用户管理                   =\n";
	cout << "=                 5.清空题库                   =\n";
	cout << "=                 6.修改密码                   =\n";
	cout << "=                 7.注销账号                   =\n";
	cout << "=                 8.退出系统                   =\n";
	cout << endl;
	cout << "================================================\n";
}

CAdmin::CAdmin()
{
	identity = admintype;		//初始化管理员标签
}

bool CAdmin::viewQuestions()
{
	CProblem tmpProblem;				//临时存储题目数据
	//临时存储题目编号，标题，选项A,选项B,选项C,选项D,答案
	string tmpNum, tmpTitle, tmpA, tmpB, tmpC, tmpD, tmpAnswer;
	vector<CProblem>vccp;				//临时存储题库文件内容
	fstream foi(pathProblem, ios::in);		//打开题库文件
	if (!foi)				//文件异常处理
	{
		cout << "用户文件打开失败！请联系系统管理员。\n" << endl;
		system("pause");						//暂停
		exitErrorTheSystem();				//系统异常终止
		return false;
	}
	if (foi.peek() == EOF)			//文件空时特殊处理
	{
		cout << "题库文件空\n";
		return false;
	}
	while (!foi.eof())					//遍历文件
	{
		getline(foi, tmpNum);			//获取题目编号
		getline(foi, tmpTitle);			//获取题目标题
		getline(foi, tmpA);				//获取选项A
		getline(foi, tmpB);				//获取选项B
		getline(foi, tmpC);				//获取选项C
		getline(foi, tmpD);				//获取选项D
		getline(foi, tmpAnswer);		//获取答案
		tmpProblem.setNum(tmpNum);		//临时存储题目编号
		tmpProblem.setTitle(tmpTitle);	//临时存储题目标题
		tmpProblem.setA(tmpA);			//临时存储选项A
		tmpProblem.setB(tmpB);			//临时存储选项B
		tmpProblem.setC(tmpC);			//临时存储选项C
		tmpProblem.setD(tmpD);			//临时存储选项D
		tmpProblem.setAnswer(tmpAnswer);//临时存储标准答案
		vccp.push_back(tmpProblem);		//题目内容存入vetor容器
	}
	cout << "----------------------------------------------\n\n";
	for (auto it = vccp.begin(); it != vccp.end(); it++)	//遍历vetor容器打印题库
	{
		cout << it->getNum() << " ";
		cout << it->getTitle() << endl;
		cout << it->getA() << endl;
		cout << it->getB() << endl;
		cout << it->getC() << endl;
		cout << it->getD() << endl;
		cout << it->getAnswer() << endl << endl;
	}
	foi.close();		//关闭文件

	return true;
}

bool CAdmin::addQuestions(CProblem problemData)
{
	CProblem tmpProblem;				//临时存储题目数据
	//临时存储题目编号，标题，选项A,选项B,选项C,选项D,答案
	string tmpNum, tmpTitle, tmpA, tmpB, tmpC, tmpD, tmpAnswer;
	vector<CProblem>vccp;				//临时存储题库文件内容
	fstream foi(pathProblem, ios::in | ios::out);		//打开题库文件
	if (!foi)				//文件异常处理
	{
		cout << "用户文件打开失败！请联系系统管理员。\n" << endl;
		system("pause");						//暂停
		exitErrorTheSystem();				//系统异常终止
		return false;
	}
	if (foi.peek() == EOF)					//文件空时特殊处理
	{
		foi.clear();						//更改cin状态标识符
		problemData.setNum("1");
		foi << problemData.getNum() << endl;
		foi << problemData.getTitle() << endl;
		foi << problemData.getA() << endl;
		foi << problemData.getB() << endl;
		foi << problemData.getC() << endl;
		foi << problemData.getD() << endl;
		foi << problemData.getAnswer();
		foi.close(); //关闭文件

		return true;
	}
	while (!foi.eof())					//遍历文件
	{
		getline(foi, tmpNum);			//获取题目编号
		getline(foi, tmpTitle);			//获取题目标题
		getline(foi, tmpA);				//获取选项A
		getline(foi, tmpB);				//获取选项B
		getline(foi, tmpC);				//获取选项C
		getline(foi, tmpD);				//获取选项D
		getline(foi, tmpAnswer);		//获取答案
		tmpProblem.setNum(tmpNum);		//临时存储题目编号
		tmpProblem.setTitle(tmpTitle);	//临时存储题目标题
		tmpProblem.setA(tmpA);			//临时存储选项A
		tmpProblem.setB(tmpB);			//临时存储选项B
		tmpProblem.setC(tmpC);			//临时存储选项C
		tmpProblem.setD(tmpD);			//临时存储选项D
		tmpProblem.setAnswer(tmpAnswer);//临时存储标准答案
		vccp.push_back(tmpProblem);		//题目内容存入vetor容器
	}
	tmpProblem = vccp.back();			//获取题库最后一个题目
	//根据最后题目编号更新当前题目编号
	problemData.setNum(to_string(stoi((tmpProblem.getNum())) + 1));
	foi.clear();						//更改cin状态标识符
	//题目数据写入文件
	foi << endl << problemData.getNum() << endl;
	foi << problemData.getTitle() << endl;
	foi << problemData.getA() << endl;
	foi << problemData.getB() << endl;
	foi << problemData.getC() << endl;
	foi << problemData.getD() << endl;
	foi << problemData.getAnswer();
	foi.close(); //关闭文件

	return true;
}

bool CAdmin::deleteQuestions(string num)
{
	CProblem tmpProblem;				//临时存储题目数据
	//临时存储题目编号，标题，选项A,选项B,选项C,选项D,答案
	string tmpNum, tmpTitle, tmpA, tmpB, tmpC, tmpD, tmpAnswer;
	vector<CProblem>vccp;				//临时存储题库文件内容
	fstream foi(pathProblem, ios::in);		//打开题库文件
	if (!foi)				//文件异常处理
	{
		cout << "用户文件打开失败！请联系系统管理员。\n" << endl;
		system("pause");						//暂停
		exitErrorTheSystem();				//系统异常终止
		return false;
	}
	if (foi.peek() == EOF)			//文件空时特殊处理
	{
		cout << "题库文件空, 不需要删除\n";
		return false;
	}
	while (!foi.eof())					//遍历文件
	{
		getline(foi, tmpNum);			//获取题目编号
		getline(foi, tmpTitle);			//获取题目标题
		getline(foi, tmpA);				//获取选项A
		getline(foi, tmpB);				//获取选项B
		getline(foi, tmpC);				//获取选项C
		getline(foi, tmpD);				//获取选项D
		getline(foi, tmpAnswer);		//获取答案
		tmpProblem.setNum(tmpNum);		//临时存储题目编号
		tmpProblem.setTitle(tmpTitle);	//临时存储题目标题
		tmpProblem.setA(tmpA);			//临时存储选项A
		tmpProblem.setB(tmpB);			//临时存储选项B
		tmpProblem.setC(tmpC);			//临时存储选项C
		tmpProblem.setD(tmpD);			//临时存储选项D
		tmpProblem.setAnswer(tmpAnswer);//临时存储标准答案
		vccp.push_back(tmpProblem);		//题目内容存入vetor容器
	}
	foi.close();
	tmpProblem = vccp.back();			//获取题库最后一个题目
	if (num > tmpProblem.getNum() || stoi(num) < 0) //题目编号合法判断
		cout << "题目编号越界，删除失败\n";
	else
	{	
		//擦除相关编题目，vector下标是从0开始的，题目编号是从1开始的所以需要-1
		vccp.erase(vccp.begin() + stoi(num) - 1);	
		foi.open(pathProblem, ios::out);
		if (!foi)				//文件异常处理
		{
			cout << "用户文件打开失败！请联系系统管理员。\n" << endl;
			system("pause");						//暂停
			exitErrorTheSystem();				//系统异常终止
			return false;
		}
		for (int i = 0; i < vccp.size(); i++)
		{
			//题目数据写入文件
			//i从0开始的，题目下标是从1开始的所以+1
			if (i != 0)
				foi << endl;
			foi << i + 1 << endl;
			foi << vccp[i].getTitle() << endl;
			foi << vccp[i].getA() << endl;
			foi << vccp[i].getB() << endl;
			foi << vccp[i].getC() << endl;
			foi << vccp[i].getD() << endl;
			foi << vccp[i].getAnswer();

		}
		foi.close();
		cout << "清除完毕\n";
	}

	return true;
}

void CAdmin::userManagement(string userName, CAdmin admin, string adminName)
{
	system("cls");
	//用户管理菜单
	cout << "================================================\n";
	cout << endl;
	cout << "=                 1.重置密码                   =\n";
	cout << "=                 2.删除账户                   =\n";
	cout << "=                 3.返回上级                   =\n";
	cout << "=                 4.退出系统                   =\n";
	cout << endl;
	cout << "================================================\n";
	
	string ans = "no";							//记录用户输入和相关命令
	bool flag2 = false;						//标记选项2合法性
	string inNewPassword;					//新密码
	bool flag_userManagement = false;				//标记用户管理菜单选项的选择合法性
	int sel = -1;									//菜单选项
	do
	{
		flag_userManagement = false;							//用户菜单管理选项标记初始化
		cin >> sel;								//用户键盘输入选项
		switch (sel)
		{
		case 1:
			cout << "请输入新密码：";
			cin >> inNewPassword;			//键盘输入旧密码
			//调用更改密码函数
			system("cls");
			admin.resettingUserPassword(userName,inNewPassword, pathUser);
			cout << "三秒后自动返回上一级菜单。\n";
			for (int i = 3; i > 0; i--)
			{
				cout << endl << i << endl;
				systemSleep(1000);
			}
			admin.userManagement(userName, admin, userName);		//自动返回上一级菜单
			break;
			
		case 2:
			do
			{
				ans = "no";						//确保安全性默认指令为no
				flag2 = false;					//选项二内部标记初始化
				cout << "是否确认注销，请输入yes/no\n";
				cin >> ans;						//用户键盘输入命令
				if (!(ans == "yes" || ans == "no"))
				{
					cout << "无效输入，请重新输入。\n";
					flag2 = true;
				}
			} while (flag2);					//非法输入要求重新输入
			system("cls");
			admin.cancelAccount(ans, pathUser, userName);	//调用账号注销函数
			cout << "三秒后自动返回上一级菜单。\n";
			for (int i = 3; i > 0; i--)
			{
				cout << endl << i << endl;
				systemSleep(1000);
			}
			admin.userManagement(userName, admin, userName);		//自动返回上一级菜单
			break;
		case 3:	openMenu(adminName, admin.identity);		//返回上一级菜单
			break;
		case 4:	exitSystem();					//退出系统
			break;
		default: flag_userManagement = true;						//非法输入会改变合法输入标记
		}
		if (flag_userManagement)				//非法输入
		{
			cout << "无效输入，请重新输入.\n";
			cin.clear();			//更改cin状态标识符准备接受下一次的输入
			systemSleep(1000);		//系统休眠
			refreshBuffer();		//刷新缓冲区
		}
	} while (flag_userManagement);			//非法输入要求重新输入
}

bool CAdmin::resettingUserPassword(string Name, string newPassword, string path)
{
	string userName;			//用户名存储
	pair<string, string>userMessage;		//用户密码与身份信息存储
	map<string, pair<string, string>>mp;	//key:用户名 value:用户密码与身份信息
	fstream foi(path, ios::in);			//打开注册信息文件
	fstream fwoi;
	if (!foi)				//文件异常处理
	{
		cout << "系统文件打开失败！请联系系统管理员。\n" << endl;
		system("pause");						//暂停
		exit(EXIT_FAILURE);				//系统异常终止
	}
	if (foi.peek() == EOF)			//文件空时特殊处理
	{
		cout << "系统文件空, 请联系系统管理员\n";
		return false;
	}
	while (!foi.eof())								//把文件遍历到文件尾
	{
		foi >> userName >> userMessage.first >> userMessage.second; //写入临时变量
		mp[userName] = userMessage;					//文件数据存入map
	}
	auto tmpit = mp.find(Name);				//查找在此用户信息

	if (tmpit == mp.end())					//未找到相关用户
		cout << "未找到相关用户\n";
	else    //重置密码不需要新旧密码比对
	{
		tmpit->second.first = newPassword;		//替换旧密码
		fwoi.open(path, ios::out);			//打开注册信息文件
		for (auto it = mp.begin(); it != mp.end(); it++)	//写入更新后的数据
			fwoi << it->first << " " << it->second.first << " " << it->second.second << endl;
		fwoi.close();						//关闭文件
		cout << "密码重置成功\n";
	}
	foi.clear();						//更改cin状态标识符
	foi.close();						//关闭文件

	return false;
}

bool CAdmin::clearQuestions(string instruct, string path)
{
	if (instruct == "no")		//撤销操作
	{
		cout << "操作已撤销\n";
		return false;
	}
	fstream foi(path, ios::out || ios :: in);			//打开注册信息文件
	if (!foi)				//文件异常处理
	{
		cout << "系统文件打开失败！请联系系统管理员。\n" << endl;
		system("pause");						//暂停
		exit(EXIT_FAILURE);				//系统异常终止
	}
	if (foi.peek() == EOF)			//文件空时特殊处理
	{
		cout << "系统文件空, 不需要清空\n";
		return false;
	}
	foi.close();
	foi.open(path, ios::out);			//打开注册信息文件
	if (!foi)				//文件异常处理
	{
		cout << "系统文件打开失败！请联系系统管理员。\n" << endl;
		system("pause");						//暂停
		exit(EXIT_FAILURE);				//系统异常终止
	}
	foi << "";
	cout << "题库已清空\n";
	system("pause");
	foi.close();
	return false;
}

void CUser::menu()
{
	system("cls");
	//用户菜单
	cout << "================================================\n";
	cout << endl;
	cout << "=                 1.开始测试                   =\n";
	cout << "=                 2.注销账户                   =\n";
	cout << "=                 3.修改密码                   =\n";
	cout << "=                 4.退出系统                   =\n";
	cout << endl;
	cout << "================================================\n";
}

CUser::CUser()
{
	identity = usertype;			//初始化用户标签
}

//测试函数
/////////////////////////////////////////////////////////////
void Print(int* a, int n)
{
	for (int i = 0; i < n; i++)
		cout << a[i] << " ";
	cout << endl;
}
/////////////////////////////////////////////////////////

bool CUser::testQuestions(string num)
{
	CProblem tmpProblem;				//临时存储题目数据
	//临时存储题目编号，标题，选项A,选项B,选项C,选项D,答案
	string tmpNum, tmpTitle, tmpA, tmpB, tmpC, tmpD, tmpAnswer;
	vector<CProblem>vccp;				//临时存储题库文件内容
	fstream foi(pathProblem, ios::in | ios::out);		//打开题库文件
	if (!foi)				//文件异常处理
	{
		cout << "用户文件打开失败！请联系系统管理员。\n" << endl;
		system("pause");						//暂停
		exitErrorTheSystem();				//系统异常终止
		return false;
	}
	if (foi.peek() == EOF)					//文件空时特殊处理
	{
		foi.clear();						//更改cin状态标识符
		cout << "题库文件空！请联系系统管理员添加题库。\n" << endl;
		foi.close(); //关闭文件
		return true;
	}
	while (!foi.eof())					//遍历文件
	{
		getline(foi, tmpNum);			//获取题目编号
		getline(foi, tmpTitle);			//获取题目标题
		getline(foi, tmpA);				//获取选项A
		getline(foi, tmpB);				//获取选项B
		getline(foi, tmpC);				//获取选项C
		getline(foi, tmpD);				//获取选项D
		getline(foi, tmpAnswer);		//获取答案
		tmpProblem.setNum(tmpNum);		//临时存储题目编号
		tmpProblem.setTitle(tmpTitle);	//临时存储题目标题
		tmpProblem.setA(tmpA);			//临时存储选项A
		tmpProblem.setB(tmpB);			//临时存储选项B
		tmpProblem.setC(tmpC);			//临时存储选项C
		tmpProblem.setD(tmpD);			//临时存储选项D
		tmpProblem.setAnswer(tmpAnswer);//临时存储标准答案
		vccp.push_back(tmpProblem);		//题目内容存入vetor容器
	}
	foi.close(); //关闭文件

	tmpProblem = vccp.back();			//获取题库最后一个题目
	int maxNum = stoi((tmpProblem.getNum()));	//最大题目编号
	int n = stoi(num);			//数组元素的个数，即生成随机数的个数
	int* numArr = new int[n];	//保存随机抽取的题目编号
	Random(numArr, n, 1, maxNum);	//生成随机数的通常范围为0~32767，这里通过取模控制取值为0~maxNum 
	qsort(numArr, n, sizeof(*numArr), cmpfunc);		//库函数排序
	Print(numArr, n);
	int i = 0;
	for (auto it = vccp.begin(); it != vccp.end(); it++)
	{
		if (numArr[i] == stoi(it->getNum()))
		{
			cout << it->getNum() << " ";
			cout << it->getTitle() << endl;
			cout << it->getA() << endl;
			cout << it->getB() << endl;
			cout << it->getC() << endl;
			cout << it->getD() << endl;
			cout << it->getAnswer() << endl;
			i++;
			cout << endl;
		}
	}

	return false;
}

bool CProblem::setNum(string _Num)
{
	num = _Num;
	return true;
}

bool CProblem::setTitle(string _title)
{
	title = _title;
	return true;
}

bool CProblem::setA(string _A)
{
	A = _A;
	return true;
}

bool CProblem::setB(string _B)
{
	B = _B;
	return true;
}

bool CProblem::setC(string _C)
{
	C = _C;
	return true;
}

bool CProblem::setD(string _D)
{
	D = _D;
	return true;
}

bool CProblem::setAnswer(string _isAnswer)
{
	isAnswer = _isAnswer;
	return true;
}

string CProblem::getNum()
{
	return num;
}

string CProblem::getTitle()
{
	return title;
}

string CProblem::getA()
{
	return A;
}

string CProblem::getB()
{
	return B;
}

string CProblem::getC()
{
	return C;
}

string CProblem::getD()
{
	return D;
}

string CProblem::getAnswer()
{
	return isAnswer;
}
