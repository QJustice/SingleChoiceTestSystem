#include "testHead.h"
#include <iostream>
#include <fstream>
#include "systemHead.h"
#include <vector>
#include <string>
#include "errorExceptionHead.h"
#include <algorithm>

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
	identity = "administrators";		//初始化管理员标签
}

bool CAdmin::viewQuestions()
{
	CProblem tmpProblem;				//临时存储题目数据
	//临时存储题目编号，标题，选项A,选项B,选项C,选项D,
	string tmpNum, tmpTitle, tmpA, tmpB, tmpC, tmpD;
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
		tmpProblem.setNum(tmpNum);		//临时存储题目编号
		tmpProblem.setTitle(tmpTitle);	//临时存储题目标题
		tmpProblem.setA(tmpA);			//临时存储选项A
		tmpProblem.setB(tmpB);			//临时存储选项B
		tmpProblem.setC(tmpC);			//临时存储选项C
		tmpProblem.setD(tmpD);			//临时存储选项D
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
		cout << it->getD() << endl << endl;
	}
	foi.close();		//关闭文件

	return true;
}

bool CAdmin::addQuestions(CProblem problemData)
{
	CProblem tmpProblem;				//临时存储题目数据
	//临时存储题目编号，标题，选项A,选项B,选项C,选项D,
	string tmpNum, tmpTitle, tmpA, tmpB, tmpC, tmpD;
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
		foi << problemData.getD();
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
		tmpProblem.setNum(tmpNum);		//临时存储题目编号
		tmpProblem.setTitle(tmpTitle);	//临时存储题目标题
		tmpProblem.setA(tmpA);			//临时存储选项A
		tmpProblem.setB(tmpB);			//临时存储选项B
		tmpProblem.setC(tmpC);			//临时存储选项C
		tmpProblem.setD(tmpD);			//临时存储选项D
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
	foi << problemData.getD();
	foi.close(); //关闭文件

	return true;
}

bool CAdmin::deleteQuestions(string num)
{
	CProblem tmpProblem;				//临时存储题目数据
	//临时存储题目编号，标题，选项A,选项B,选项C,选项D,
	string tmpNum, tmpTitle, tmpA, tmpB, tmpC, tmpD;
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
		tmpProblem.setNum(tmpNum);		//临时存储题目编号
		tmpProblem.setTitle(tmpTitle);	//临时存储题目标题
		tmpProblem.setA(tmpA);			//临时存储选项A
		tmpProblem.setB(tmpB);			//临时存储选项B
		tmpProblem.setC(tmpC);			//临时存储选项C
		tmpProblem.setD(tmpD);			//临时存储选项D
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
			foi << vccp[i].getD();
		}
		foi.close();
		cout << "清除完毕\n";
	}

	return true;
}

void CAdmin::userManagement()
{

}

bool CAdmin::clearQuestions(string instruct, string path)
{
	if (instruct == "no")		//撤销操作
	{
		cout << "操作已撤销\n";
		return false;
	}
	fstream foi(path, ios::out);			//打开注册信息文件
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
	foi << "";
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
	identity = "user";			//初始化用户标签
}

bool CUser::testQuestions(string num)
{
	
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
