#pragma once
#include <string>
#include "basicHead.h"

class CAdmin;
class CUser;
class Cproblem;

using std::string;

#ifndef _TESTHEAD_
#define _TESTHEAD_

class CProblem
{
private:
	string num;				//��Ŀ���
	string title;			//��Ŀ
	string A, B, C, D;		//��ѡ���

public:
	char answer = ' ';			//�û��ش�Ĵ�
	bool setNum(string _Num);
	bool setTitle(string _title);
	bool setA(string _A);
	bool setB(string _B);
	bool setC(string _C);
	bool setD(string _D);

	string getNum();
	string getTitle();
	string getA();
	string getB();
	string getC();
	string getD();
};

class CAdmin:public CBasic
{

public:

	void menu();
	CAdmin();
	bool viewQuestions();				//�鿴��� 
	bool addQuestions(CProblem problemData);				//������Ŀ
	bool deleteQuestions(string num);				//ɾ����Ŀ
	void userManagement(string userName, CAdmin admin, string adminName);				//�û�����˵�	
	bool resettingUserPassword(string Name, string newPassword, string path);	//�����û�����
	bool clearQuestions(string instruct, string path);				//������
};

class CUser:public CBasic
{

public:

	void menu();
	CUser();
	bool testQuestions(string num);				//��ʼ����
};

#endif //_TESTHEAD_