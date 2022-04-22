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
	//����Ա�˵�
	cout << "================================================\n";
	cout << endl;
	cout << "=                 1.�鿴���                   =\n";
	cout << "=                 2.������Ŀ                   =\n";
	cout << "=                 3.ɾ����Ŀ                   =\n";
	cout << "=                 4.�û�����                   =\n";
	cout << "=                 5.������                   =\n";
	cout << "=                 6.�޸�����                   =\n";
	cout << "=                 7.ע���˺�                   =\n";
	cout << "=                 8.�˳�ϵͳ                   =\n";
	cout << endl;
	cout << "================================================\n";
}

CAdmin::CAdmin()
{
	identity = "administrators";		//��ʼ������Ա��ǩ
}

bool CAdmin::viewQuestions()
{
	CProblem tmpProblem;				//��ʱ�洢��Ŀ����
	//��ʱ�洢��Ŀ��ţ����⣬ѡ��A,ѡ��B,ѡ��C,ѡ��D,
	string tmpNum, tmpTitle, tmpA, tmpB, tmpC, tmpD;
	vector<CProblem>vccp;				//��ʱ�洢����ļ�����
	fstream foi(pathProblem, ios::in);		//������ļ�
	if (!foi)				//�ļ��쳣����
	{
		cout << "�û��ļ���ʧ�ܣ�����ϵϵͳ����Ա��\n" << endl;
		system("pause");						//��ͣ
		exitErrorTheSystem();				//ϵͳ�쳣��ֹ
		return false;
	}
	if (foi.peek() == EOF)			//�ļ���ʱ���⴦��
	{
		cout << "����ļ���\n";
		return false;
	}
	while (!foi.eof())					//�����ļ�
	{
		getline(foi, tmpNum);			//��ȡ��Ŀ���
		getline(foi, tmpTitle);			//��ȡ��Ŀ����
		getline(foi, tmpA);				//��ȡѡ��A
		getline(foi, tmpB);				//��ȡѡ��B
		getline(foi, tmpC);				//��ȡѡ��C
		getline(foi, tmpD);				//��ȡѡ��D
		tmpProblem.setNum(tmpNum);		//��ʱ�洢��Ŀ���
		tmpProblem.setTitle(tmpTitle);	//��ʱ�洢��Ŀ����
		tmpProblem.setA(tmpA);			//��ʱ�洢ѡ��A
		tmpProblem.setB(tmpB);			//��ʱ�洢ѡ��B
		tmpProblem.setC(tmpC);			//��ʱ�洢ѡ��C
		tmpProblem.setD(tmpD);			//��ʱ�洢ѡ��D
		vccp.push_back(tmpProblem);		//��Ŀ���ݴ���vetor����
	}
	cout << "----------------------------------------------\n\n";
	for (auto it = vccp.begin(); it != vccp.end(); it++)	//����vetor������ӡ���
	{
		cout << it->getNum() << " ";
		cout << it->getTitle() << endl;
		cout << it->getA() << endl;
		cout << it->getB() << endl;
		cout << it->getC() << endl;
		cout << it->getD() << endl << endl;
	}
	foi.close();		//�ر��ļ�

	return true;
}

bool CAdmin::addQuestions(CProblem problemData)
{
	CProblem tmpProblem;				//��ʱ�洢��Ŀ����
	//��ʱ�洢��Ŀ��ţ����⣬ѡ��A,ѡ��B,ѡ��C,ѡ��D,
	string tmpNum, tmpTitle, tmpA, tmpB, tmpC, tmpD;
	vector<CProblem>vccp;				//��ʱ�洢����ļ�����
	fstream foi(pathProblem, ios::in | ios::out);		//������ļ�
	if (!foi)				//�ļ��쳣����
	{
		cout << "�û��ļ���ʧ�ܣ�����ϵϵͳ����Ա��\n" << endl;
		system("pause");						//��ͣ
		exitErrorTheSystem();				//ϵͳ�쳣��ֹ
		return false;
	}
	if (foi.peek() == EOF)					//�ļ���ʱ���⴦��
	{
		foi.clear();						//����cin״̬��ʶ��
		problemData.setNum("1");
		foi << problemData.getNum() << endl;
		foi << problemData.getTitle() << endl;
		foi << problemData.getA() << endl;
		foi << problemData.getB() << endl;
		foi << problemData.getC() << endl;
		foi << problemData.getD();
		foi.close(); //�ر��ļ�

		return true;
	}
	while (!foi.eof())					//�����ļ�
	{
		getline(foi, tmpNum);			//��ȡ��Ŀ���
		getline(foi, tmpTitle);			//��ȡ��Ŀ����
		getline(foi, tmpA);				//��ȡѡ��A
		getline(foi, tmpB);				//��ȡѡ��B
		getline(foi, tmpC);				//��ȡѡ��C
		getline(foi, tmpD);				//��ȡѡ��D
		tmpProblem.setNum(tmpNum);		//��ʱ�洢��Ŀ���
		tmpProblem.setTitle(tmpTitle);	//��ʱ�洢��Ŀ����
		tmpProblem.setA(tmpA);			//��ʱ�洢ѡ��A
		tmpProblem.setB(tmpB);			//��ʱ�洢ѡ��B
		tmpProblem.setC(tmpC);			//��ʱ�洢ѡ��C
		tmpProblem.setD(tmpD);			//��ʱ�洢ѡ��D
		vccp.push_back(tmpProblem);		//��Ŀ���ݴ���vetor����
	}
	tmpProblem = vccp.back();			//��ȡ������һ����Ŀ
	//���������Ŀ��Ÿ��µ�ǰ��Ŀ���
	problemData.setNum(to_string(stoi((tmpProblem.getNum())) + 1));
	foi.clear();						//����cin״̬��ʶ��
	//��Ŀ����д���ļ�
	foi << endl << problemData.getNum() << endl;
	foi << problemData.getTitle() << endl;
	foi << problemData.getA() << endl;
	foi << problemData.getB() << endl;
	foi << problemData.getC() << endl;
	foi << problemData.getD();
	foi.close(); //�ر��ļ�

	return true;
}

bool CAdmin::deleteQuestions(string num)
{
	CProblem tmpProblem;				//��ʱ�洢��Ŀ����
	//��ʱ�洢��Ŀ��ţ����⣬ѡ��A,ѡ��B,ѡ��C,ѡ��D,
	string tmpNum, tmpTitle, tmpA, tmpB, tmpC, tmpD;
	vector<CProblem>vccp;				//��ʱ�洢����ļ�����
	fstream foi(pathProblem, ios::in);		//������ļ�
	if (!foi)				//�ļ��쳣����
	{
		cout << "�û��ļ���ʧ�ܣ�����ϵϵͳ����Ա��\n" << endl;
		system("pause");						//��ͣ
		exitErrorTheSystem();				//ϵͳ�쳣��ֹ
		return false;
	}
	if (foi.peek() == EOF)			//�ļ���ʱ���⴦��
	{
		cout << "����ļ���, ����Ҫɾ��\n";
		return false;
	}
	while (!foi.eof())					//�����ļ�
	{
		getline(foi, tmpNum);			//��ȡ��Ŀ���
		getline(foi, tmpTitle);			//��ȡ��Ŀ����
		getline(foi, tmpA);				//��ȡѡ��A
		getline(foi, tmpB);				//��ȡѡ��B
		getline(foi, tmpC);				//��ȡѡ��C
		getline(foi, tmpD);				//��ȡѡ��D
		tmpProblem.setNum(tmpNum);		//��ʱ�洢��Ŀ���
		tmpProblem.setTitle(tmpTitle);	//��ʱ�洢��Ŀ����
		tmpProblem.setA(tmpA);			//��ʱ�洢ѡ��A
		tmpProblem.setB(tmpB);			//��ʱ�洢ѡ��B
		tmpProblem.setC(tmpC);			//��ʱ�洢ѡ��C
		tmpProblem.setD(tmpD);			//��ʱ�洢ѡ��D
		vccp.push_back(tmpProblem);		//��Ŀ���ݴ���vetor����
	}
	foi.close();
	tmpProblem = vccp.back();			//��ȡ������һ����Ŀ
	if (num > tmpProblem.getNum() || stoi(num) < 0) //��Ŀ��źϷ��ж�
		cout << "��Ŀ���Խ�磬ɾ��ʧ��\n";
	else
	{	
		//������ر���Ŀ��vector�±��Ǵ�0��ʼ�ģ���Ŀ����Ǵ�1��ʼ��������Ҫ-1
		vccp.erase(vccp.begin() + stoi(num) - 1);	
		foi.open(pathProblem, ios::out);
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
			foi << vccp[i].getD();
		}
		foi.close();
		cout << "������\n";
	}

	return true;
}

void CAdmin::userManagement()
{

}

bool CAdmin::clearQuestions(string instruct, string path)
{
	if (instruct == "no")		//��������
	{
		cout << "�����ѳ���\n";
		return false;
	}
	fstream foi(path, ios::out);			//��ע����Ϣ�ļ�
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
	foi << "";
	foi.close();

	return false;
}

void CUser::menu()
{
	system("cls");
	//�û��˵�
	cout << "================================================\n";
	cout << endl;
	cout << "=                 1.��ʼ����                   =\n";
	cout << "=                 2.ע���˻�                   =\n";
	cout << "=                 3.�޸�����                   =\n";
	cout << "=                 4.�˳�ϵͳ                   =\n";
	cout << endl;
	cout << "================================================\n";
}

CUser::CUser()
{
	identity = "user";			//��ʼ���û���ǩ
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
