#pragma once
#ifndef _SYSTEMHEAD_
#define _SYSTEMHEAD_

#include <string>
#include <vector>
#include "testHead.h"

using std::string;
using std::vector;

//�û��ļ�·��
const string pathUser = "D:/WorkSpace/VSFILE/SingleChoiceTestSystem/data/User.txt";
//����ļ�·��
const string pathProblem = "D:/WorkSpace/VSFILE/SingleChoiceTestSystem/data/Problem.txt";


const string usertype = "user";					//�û���ݱ�ʶ
const string admintype = "administrators";		//����Ա��ݱ�ʶ

bool registerNum(string& tempName);			//ע��
bool logOn(string& Name, string& Password);				//��¼
void systemMenu();			//���˵�
void unregisteredUserMenu(string& name, string& password); //δע���û��˵�
void exitSystem();			//�˳�ϵͳ
void systemSleep(int stime);			//�ӳٵȴ�
bool judgmentString(string& str);		//�ж��Ƿ�Ϊ�ַ���
bool judgmentNumber(string& str);			//�ж��Ƿ�Ϊ����
bool openMenu(string& userName, string& userType);		//�����˵�
bool returnMenu(string& userName, string& userType);	//������һ��
string getpassword();					//��������
void Random(int* arr, int num, int minNum, int maxNum);//���ɷ�Χ��minNum~maxNum������� 
int cmpfunc(const void* a, const void* b); //��Ŀ�������ʽ
char getUserAnswer();					//��ȡ�û�����Ĵ�
bool getProblemData(vector<CProblem>* data, int* maxNum); //��ȡ�������
string strToLower(string& str);				//�ַ���ת����Сд
#endif	//_SYSTEMHEAD_