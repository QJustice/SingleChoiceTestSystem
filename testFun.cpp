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
	//����Ա�˵�
	cout << "|------------------------------------------------|\n";
	cout << "|                                                |\n";
	cout << "|    ***��ӭ��¼����ѡ�������ϵͳ�����̨***    |\n";
	cout << "|                                                |\n";
	cout << "|================================================|\n";
	cout << "|                                                |\n";
	cout << "|=                 1.�鿴���                   =|\n";
	cout << "|=                 2.������Ŀ                   =|\n";
	cout << "|=                 3.ɾ����Ŀ                   =|\n";
	cout << "|=                 4.�û�����                   =|\n";
	cout << "|=                 5.������                   =|\n";
	cout << "|=                 6.�޸�����                   =|\n";
	cout << "|=                 7.ע���˺�                   =|\n";
	cout << "|=                 8.�˳�ϵͳ                   =|\n";
	cout << "|                                                |\n";
	cout << "|================================================|\n";
}

CAdmin::CAdmin()
{
	identity = admintype;		//��ʼ������Ա��ǩ
}

bool CAdmin::viewQuestions()
{
	vector<CProblem>vccp;				//��ʱ�洢����ļ�����

	int maxNum = 0;
	int* ptrmaxNum = &maxNum;
	vector<CProblem>* ptrvccp = &vccp;
	getProblemData(ptrvccp, ptrmaxNum);
	cout << "----------------------------------------------\n\n";
	for (auto it = vccp.begin(); it != vccp.end(); it++)	//����vetor������ӡ���
	{
		cout << it->getNum() << " ";
		cout << it->getTitle() << endl;
		cout << it->getA() << endl;
		cout << it->getB() << endl;
		cout << it->getC() << endl;
		cout << it->getD() << endl;
		cout << it->getAnswer() << endl << endl;
	}

	cout << "�ܹ���" << maxNum << "����Ŀ\n";
	return true;
}

bool CAdmin::addQuestions(CProblem problemData)
{
	fstream foi(pathProblem, ios::in);		//������ļ�
	if (!foi)				//�ļ��쳣����
	{
		cout << "�û��ļ���ʧ�ܣ�����ϵϵͳ����Ա��\n" << endl;
		system("pause");						//��ͣ
		exitErrorTheSystem();				//ϵͳ�쳣��ֹ
		return false;
	}
	if (foi.peek() == EOF)					//�ļ���ʱ���⴦��
	{
		foi.close();
		foi.open(pathProblem, ios::out);		//������ļ�
		if (!foi)				//�ļ��쳣����
		{
			cout << "�û��ļ���ʧ�ܣ�����ϵϵͳ����Ա��\n" << endl;
			system("pause");						//��ͣ
			exitErrorTheSystem();				//ϵͳ�쳣��ֹ
			return false;
		}
		problemData.setNum("1");
		foi << problemData.getNum() << endl;
		foi << problemData.getTitle() << endl;
		foi << problemData.getA() << endl;
		foi << problemData.getB() << endl;
		foi << problemData.getC() << endl;
		foi << problemData.getD() << endl;
		foi << problemData.getAnswer();
		foi.close(); //�ر��ļ�

		return true;
	}
	foi.close();

	//�ļ���Ϊ��ʱ
	foi.open(pathProblem, ios::app);		//������ļ�
	if (!foi)				//�ļ��쳣����
	{
		cout << "�û��ļ���ʧ�ܣ�����ϵϵͳ����Ա��\n" << endl;
		system("pause");						//��ͣ
		exitErrorTheSystem();				//ϵͳ�쳣��ֹ
		return false;
	}
	vector<CProblem>vccp;				//��ʱ�洢����ļ�����
	int maxNum = 0;
	int* ptrmaxNum = &maxNum;
	vector<CProblem>* ptrvccp = &vccp;
	getProblemData(ptrvccp, ptrmaxNum);
	//���������Ŀ��Ÿ��µ�ǰ��Ŀ���
	problemData.setNum(to_string(maxNum + 1));
	foi.clear();						//����cin״̬��ʶ��
	//��Ŀ����д���ļ�
	foi << endl << problemData.getNum() << endl;
	foi << problemData.getTitle() << endl;
	foi << problemData.getA() << endl;
	foi << problemData.getB() << endl;
	foi << problemData.getC() << endl;
	foi << problemData.getD() << endl;
	foi << problemData.getAnswer();
	foi.close(); //�ر��ļ�

	return true;
}

bool CAdmin::deleteQuestions(string num)
{
	vector<CProblem>vccp;				//��ʱ�洢����ļ�����
	int maxNum = 0;
	int* ptrmaxNum = &maxNum;
	vector<CProblem>* ptrvccp = &vccp;
	getProblemData(ptrvccp, ptrmaxNum);

	if (stoi(num) > maxNum || stoi(num) < 0) //��Ŀ��źϷ��ж�
		cout << "��Ŀ���Խ�磬ɾ��ʧ��\n";
	else
	{	
		//������ر���Ŀ��vector�±��Ǵ�0��ʼ�ģ���Ŀ����Ǵ�1��ʼ��������Ҫ-1
		vccp.erase(vccp.begin() + stoi(num) - 1);	
		fstream foi(pathProblem, ios::out);
		if (!foi)				//�ļ��쳣����
		{
			cout << "�û��ļ���ʧ�ܣ�����ϵϵͳ����Ա��\n" << endl;
			system("pause");						//��ͣ
			exitErrorTheSystem();				//ϵͳ�쳣��ֹ
			return false;
		}
		for (int i = 0; i < vccp.size(); i++)
		{
			//��Ŀ����д���ļ�
			//i��0��ʼ�ģ���Ŀ�±��Ǵ�1��ʼ������+1
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
		cout << "������\n";
	}

	return true;
}

void CAdmin::userManagement(string userName, CAdmin admin, string adminName)
{
	system("cls");
	//�û�����˵�
	cout << "================================================\n";
	cout << endl;
	cout << "=                 1.��������                   =\n";
	cout << "=                 2.ɾ���˻�                   =\n";
	cout << "=                 3.�����ϼ�                   =\n";
	cout << "=                 4.�˳�ϵͳ                   =\n";
	cout << endl;
	cout << "================================================\n";
	
	string ans = "no";							//��¼�û�������������
	bool flag2 = false;						//���ѡ��2�Ϸ���
	string inNewPassword;					//������
	bool flag_userManagement = false;				//����û�����˵�ѡ���ѡ��Ϸ���
	int sel = -1;									//�˵�ѡ��
	do
	{
		flag_userManagement = false;							//�û��˵�����ѡ���ǳ�ʼ��
		cin >> sel;								//�û���������ѡ��
		switch (sel)
		{
		case 1:
			cout << "�����������룺";
			cin >> inNewPassword;			//�������������
			//���ø������뺯��
			system("cls");
			admin.resettingUserPassword(userName,inNewPassword, pathUser);
			cout << "������Զ�������һ���˵���\n";
			for (int i = 3; i > 0; i--)
			{
				cout << endl << i << endl;
				systemSleep(1000);
			}
			admin.userManagement(userName, admin, userName);		//�Զ�������һ���˵�
			break;
			
		case 2:
			do
			{
				ans = "no";						//ȷ����ȫ��Ĭ��ָ��Ϊno
				flag2 = false;					//ѡ����ڲ���ǳ�ʼ��
				cout << "�Ƿ�ȷ��ע����������yes/no\n";
				cin >> ans;						//�û�������������
				ans = strToLower(ans);			//ͳһת��ΪСд
				if (!(ans == "yes" || ans == "no"))
				{
					cout << "��Ч���룬���������롣\n";
					flag2 = true;
				}
			} while (flag2);					//�Ƿ�����Ҫ����������
			system("cls");
			admin.cancelAccount(ans, pathUser, userName);	//�����˺�ע������
			cout << "������Զ�������һ���˵���\n";
			for (int i = 3; i > 0; i--)
			{
				cout << endl << i << endl;
				systemSleep(1000);
			}
			admin.userManagement(userName, admin, userName);		//�Զ�������һ���˵�
			break;
		case 3:	openMenu(adminName, admin.identity);		//������һ���˵�
			break;
		case 4:	exitSystem();					//�˳�ϵͳ
			break;
		default: flag_userManagement = true;						//�Ƿ������ı�Ϸ�������
		}
		if (flag_userManagement)				//�Ƿ�����
		{
			cout << "��Ч���룬����������.\n";
			cin.clear();			//����cin״̬��ʶ��׼��������һ�ε�����
			systemSleep(1000);		//ϵͳ����
			refreshBuffer();		//ˢ�»�����
		}
	} while (flag_userManagement);			//�Ƿ�����Ҫ����������
}

bool CAdmin::resettingUserPassword(string Name, string newPassword, string path)
{
	string userName;			//�û����洢
	pair<string, string>userMessage;		//�û������������Ϣ�洢
	map<string, pair<string, string>>mp;	//key:�û��� value:�û������������Ϣ
	fstream foi(path, ios::in);			//��ע����Ϣ�ļ�
	fstream fwoi;
	if (!foi)				//�ļ��쳣����
	{
		cout << "ϵͳ�ļ���ʧ�ܣ�����ϵϵͳ����Ա��\n" << endl;
		system("pause");						//��ͣ
		exit(EXIT_FAILURE);				//ϵͳ�쳣��ֹ
	}
	if (foi.peek() == EOF)			//�ļ���ʱ���⴦��
	{
		cout << "ϵͳ�ļ���, ����ϵϵͳ����Ա\n";
		return false;
	}
	while (!foi.eof())								//���ļ��������ļ�β
	{
		foi >> userName >> userMessage.first >> userMessage.second; //д����ʱ����
		mp[userName] = userMessage;					//�ļ����ݴ���map
	}
	auto tmpit = mp.find(Name);				//�����ڴ��û���Ϣ

	if (tmpit == mp.end())					//δ�ҵ�����û�
		cout << "δ�ҵ�����û�\n";
	else    //�������벻��Ҫ�¾�����ȶ�
	{
		tmpit->second.first = newPassword;		//�滻������
		fwoi.open(path, ios::out);			//��ע����Ϣ�ļ�
		for (auto it = mp.begin(); it != mp.end(); it++)	//д����º������
			fwoi << it->first << " " << it->second.first << " " << it->second.second << endl;
		fwoi.close();						//�ر��ļ�
		cout << "�������óɹ�\n";
	}
	foi.clear();						//����cin״̬��ʶ��
	foi.close();						//�ر��ļ�

	return false;
}

bool CAdmin::clearQuestions(string instruct, string path)
{
	if (instruct == "no")		//��������
	{
		cout << "�����ѳ���\n";
		return false;
	}
	fstream foi(path, ios::out || ios :: in);			//��ע����Ϣ�ļ�
	if (!foi)				//�ļ��쳣����
	{
		cout << "ϵͳ�ļ���ʧ�ܣ�����ϵϵͳ����Ա��\n" << endl;
		system("pause");						//��ͣ
		exit(EXIT_FAILURE);				//ϵͳ�쳣��ֹ
	}
	if (foi.peek() == EOF)			//�ļ���ʱ���⴦��
	{
		cout << "ϵͳ�ļ���, ����Ҫ���\n";
		return false;
	}
	foi.close();
	foi.open(path, ios::out);			//��ע����Ϣ�ļ�
	if (!foi)				//�ļ��쳣����
	{
		cout << "ϵͳ�ļ���ʧ�ܣ�����ϵϵͳ����Ա��\n" << endl;
		system("pause");						//��ͣ
		exit(EXIT_FAILURE);				//ϵͳ�쳣��ֹ
	}
	foi << "";
	cout << "��������\n";
	system("pause");
	foi.close();
	return false;
}

void CUser::menu()
{
	system("cls");
	//�û��˵�
	cout << "|------------------------------------------------|\n";
	cout << "|                                                |\n";
	cout << "|        ***��ӭ��¼����ѡ�������ϵͳ***        |\n";
	cout << "|                                                |\n";
	cout << "|================================================|\n";
	cout << "|                                                |\n";
	cout << "|=                 1.��ʼ����                   =|\n";
	cout << "|=                 2.ע���˻�                   =|\n";
	cout << "|=                 3.�޸�����                   =|\n";
	cout << "|=                 4.�˳�ϵͳ                   =|\n";
	cout << "|                                                |\n";
	cout << "|================================================|\n";
}

CUser::CUser()
{
	identity = usertype;			//��ʼ���û���ǩ
}

bool CUser::testQuestions(string num)
{
	vector<CProblem>vccp;				//��ʱ�洢����ļ�����
	int maxNum = 0;	   	               //�����Ŀ���
	int* ptrmaxNum = &maxNum;
	vector<CProblem>* ptrvccp = &vccp;
	getProblemData(ptrvccp, ptrmaxNum);
	int n = stoi(num);			//����Ԫ�صĸ�����������������ĸ���
	//��Ŀ��ȡ�����Ϸ��ж�
	if (n > maxNum || n < 0)	
	{
		cout << "��ȡ���������Ƿ�\n";
		return false;
	}
	if (0 == n)
	{
		cout << "��ȡ��������Ϊ0��ϵͳδ��ȡ��Ŀ\n";
		return false;
	}
	int* numArr = new int[n];	//���������ȡ����Ŀ���
	Random(numArr, n, 1, maxNum);	//�����������ͨ����ΧΪ0~32767������ͨ��ȡģ����ȡֵΪ0~maxNum 
	qsort(numArr, n, sizeof(*numArr), cmpfunc);		//�⺯������
	double socer = 0.0;
	double oneSocer = 100.0 / maxNum;

	int i = 0;
	for (auto it = vccp.begin(); it != vccp.end(); it++)
	{
		if (numArr[i] == stoi(it->getNum()))
		{
			i++;							//������ȷ�����Ŀ��������Ÿ���
			cout << it->getNum() << " ";
			cout << it->getTitle() << endl;
			cout << it->getA() << endl;
			cout << it->getB() << endl;
			cout << it->getC() << endl;
			cout << it->getD() << endl;
			cout << "��������Ĵ𰸣�\n";
			char ans = getUserAnswer();
			cout << it->getAnswer() << endl;
			cout << "��Ĵ�Ϊ��" << ans << endl;
			if (ans == it->getAnswer().back())
			{
				cout << "��Ļش�����ȷ��\n";
				cout << "�÷� + " << oneSocer << endl;
				socer += oneSocer;
				cout << "�ܵ÷� ��" << socer << endl;
			}
			else
				cout << "���ź����ش�����ٽ�������\n";
			cout << endl;
		}
	}
	cout << "���յ÷� ��" << socer << endl;

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
