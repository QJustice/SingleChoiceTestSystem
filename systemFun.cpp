#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <vector>
#include <map>
#include <utility>
#include <Windows.h>
#include "systemHead.h"
#include "errorExceptionHead.h"
#include "testHead.h"
#include <conio.h>
#include <algorithm>
#include <cctype>


using std::cout;
using std::cin;
using std::endl;
using std::pair;
using std::map;
using std::fstream;
using std::vector;
using std::ios;
using std::flush;
using std::fill;

bool logOn(string& Name, string& Password)			//��¼
{
	
	string userName;					//�û���
	pair<string, string>userMessage;		//�û������������Ϣ�洢
	map<string, pair<string, string>>mp;		//key:�û��� value:�û������������Ϣ
	fstream foi(pathUser, ios::in);			//��ע����Ϣ�ļ�

	if (!foi)				//�ļ��쳣����
	{
		cout << "�û��ļ���ʧ�ܣ�����ϵϵͳ����Ա��\n" << endl;
		system("pause");						//��ͣ
		exitErrorTheSystem();				//ϵͳ�쳣��ֹ
	}
	if (foi.peek() == EOF)			//�ļ���ʱ���⴦��
	{
		cout << "ϵͳ�ļ���, ����ϵϵͳ����Ա\n";
		return false;
	}
	while (!foi.eof())								//���ļ��������ļ�β
	{
		foi >> userName >> userMessage.first >> userMessage.second;
		mp[userName] = userMessage;					//�ļ����ݴ���map
	}
	int errortime = 0;						//��������������
	bool flag = false;						//����û��Ƿ���Լ�������
	do
	{
		auto tmpit = mp.find(Name);				//�����ڴ��û���Ϣ

		if (tmpit == mp.end())					//δ�ҵ�����û�
		{
			flag = true;
			cout << "δע���û�,����ע��\n\n";
			systemSleep(2000);					//ϵͳ����
			cout << "���������Ժ�.....\n";
			unregisteredUserMenu(Name, Password);		//����δע���û��˵�
		}
		else if (tmpit->second.first != Password)		//�û�����ȷ�����������
		{
			if (errortime > 2)						//�������������
			{
				cout << "�������������࣡����\n������˳�ϵͳ��";
				for (int i = 5; i > 0; i--)
				{
					cout << endl << i << endl;
					systemSleep(1000);
				}
				exitSystem();
			}
			errortime++;					//��¼����������
			cout << "�������\n��������������\n";
			cout << "������" << 4 - errortime << "�λ��ᣡ";
			cout << "����������\n";
			systemSleep(2000);			//ϵͳ����
			cin >> Password;			//���̶�ȡ�û����������
			flag = true;				//�����û�����
		}
		else							//�û��������붼��ȷ
			openMenu(Name, tmpit->second.second);		//�򿪲˵�
	} while (flag);					//�ﵽ��¼��������ѭ��

	return !flag;
}

bool registerNum(string& tempName)		//ע��
{
	string tempPassword;				//�洢�û�����
	fstream foi(pathUser, ios::in | ios::app);			//��ע����Ϣ�ļ�
	string userName, userPassword, usertype;	//��ʱ�洢�û��������룬�û�����
	vector<string>user;					//�洢�û���Ϣ
	if (!foi)				//�ļ��쳣����
	{
		cout << "�û��ļ���ʧ�ܣ�����ϵϵͳ����Ա��\n" << endl;
		system("pause");						//��ͣ
		exitErrorTheSystem();				//ϵͳ�쳣��ֹ
	}
	if (foi.peek() == EOF)			//�ļ���ʱ���⴦��
	{
		cout << "ϵͳ�ļ���, ����ϵϵͳ����Ա\n";
		return false;
	}
	while (!foi.eof())								//���ļ��������ļ�β
	{
		foi >> userName >> userPassword >> usertype;	//��ʱ�洢���û��������룬�û�����
		user.push_back(userName);					//�ļ����ݴ���vector
	}
	int flag = false;								//�쳣���
	do
	{
		flag = false;								//��ʼ���쳣���
		//find���е�ǰ�û����Ƿ�ע�ᣬfind���ص�������β��ô˵��û���ҵ�
		//find���صĲ�������β��ô˵�����û����Ѵ���
		if (user.end() != find(user.begin(), user.end(), tempName))
		{
			flag = true;							//�û����ѱ�ռ�ñ���쳣
			cout << "���û����Ѵ��ڣ�����������\n";
			systemSleep(2000);						//ϵͳ����
			cout << "�������û���\n";
			cin >> tempName;						//Ҫ�����������û���
		}

	} while (flag);									//�쳣����Ҫ����������
	cout << "����������\n";
	tempPassword = getpassword();		//���̶�ȡ�û�����,��������
	foi.clear();									//����cin״̬��ʶ��
	foi << tempName << " " << tempPassword << " " << usertype << endl;		//���ļ�׷�����ݣ�����ע����Ϣ
	foi.close();									//�ر��ļ�
	return !flag;
}

void systemMenu()		//���˵�
{
	system("cls");
	cout << "================================================\n";
	cout << endl;
	cout << "=                 1.ע���˺�                   =\n";
	cout << "=                 2.��¼ϵͳ                   =\n";
	cout << "=                 3.�˳�ϵͳ                   =\n";
	cout << endl;
	cout << "================================================\n";
}

void unregisteredUserMenu(string& name, string& password)
{
	bool flag = false;							//�쳣���
	int sel = -1;    							//�˵�ѡ��
	do
	{
		system("cls");
		cout << "================================================\n";
		cout << endl;
		cout << "=                 1.��������                   =\n";
		cout << "=                 2.ע���˺�                   =\n";
		cout << "=                 3.�˳�ϵͳ                   =\n";
		cout << endl;
		cout << "================================================\n";
		flag = 0;							//δע���û��˵�ѡ���ǳ�ʼ��
		cin >> sel;							//�û���������ѡ��
		switch (sel)
		{
		case 1:
			cout << "�������û���\n";
			cin >> name;					//�û����´Ӽ��������û���
			cout << "����������\n";
			password = getpassword();		//���̶�ȡ�û�����,��������
			break;
		case 2:
			cout << "�������û���\n";
			cin >> name;					//�û���������ѡ���û���
			registerNum(name);				//����ע�ắ��
			break;
		case 3: exitSystem();				//�˳�ϵͳ
			break;
		default: flag = true;					//��ǷǷ�����
		}
		if (flag)						//�Ƿ�����
		{
			cout << "��Ч���룬����������.\n";
			cin.clear();			//����cin״̬��ʶ��׼��������һ�ε�����
			systemSleep(1000);				//ϵͳ����
			refreshBuffer();				//ˢ�»�����
		}
	} while (flag);					//�Ƿ�����Ҫ����������
}

void exitSystem()
{
	//���������˳�
	exit(EXIT_SUCCESS);
}

void systemSleep(int stime)	//�ӳٵȴ�
{
	//ϵͳ����
	Sleep(stime);
}

bool judgmentString(string& str)
{
	//�����ַ���
	for (int i = 0; i < str.size(); i++)
		if (!isalpha(str[i]))				//����ַ��ж��Ƿ�Ϊ��ĸ
			return false;					//���ַ���ĸ����false
	return true;
}

bool judgmentNumber(string& str)
{
	//�����ַ���
	for (int i = 0; i < str.size(); i++)
		if (!isdigit(str[i]))				//����ַ��ж��Ƿ�Ϊ����
			return false;					//���ַ����ַ���false
	return true;
}

bool openMenu(string& userName, string& userType)
{
	cout << "ƴ��������......��\n";
	systemSleep(1500);						//ϵͳ����
	CAdmin admin;
	CUser user;							
	string tmpUserName;					//��ʱ�洢�û���
	string inOldPassword, inNewPassword;	//��ʱ�洢�¾�����
	string problemNum;				//��Ŀ���
	CProblem tmpProblem;		//��ʱ�洢��Ŀ����
	string tmpNum, tmpTitle, tmpA, tmpB, tmpC, tmpD, tmpAnswer; //��ʱ�洢��Ŀ��Ϣ
	string ans = "no";							//��¼�û�������������
	bool flag1 = false;						//���ѡ��1�Ϸ���
	bool flag2 = false;						//���ѡ��2�Ϸ���
	bool flag3 = false;						//���ѡ��3�Ϸ���
	bool flag4 = false;						//���ѡ��4�Ϸ���
	bool flag5 = false;						//���ѡ��5�Ϸ���
	bool flag7 = false;						//���ѡ��7�Ϸ���
	if (userType == admin.getIdentity())		//�ж��Ƿ�Ϊ����Ա
	{
		admin.menu();					//����Ա�˵�
		bool flag_admin = false;				//��ǹ���Ա�˵�ѡ���ѡ��Ϸ���		
		int sel = -1;						//�˵�ѡ��
		//��Ŀ��ţ����⣬ѡ��A,ѡ��B,ѡ��C,ѡ��D

		do
		{
			flag_admin = false;				//����Ա�˵�ѡ���ǳ�ʼ��
			cin >> sel;					//�û���������ѡ��
			switch (sel)
			{
			case 1:	
				admin.viewQuestions();	//���ò鿴��⺯��
				returnMenu(userName, userType);		//������һ���˵�
				break;
			case 2:
				tmpProblem.setNum("0");		//Ĭ����Ŀ���Ϊ0
				cout << "��������Ŀ���⣺\n";
				cin >> tmpTitle;			//���̶�ȡ��Ŀ����
				tmpProblem.setTitle(tmpTitle);
				cout << "������ѡ��A���ݣ�\n";
				cin >> tmpA;				//���̶�ȡѡ��A����
				tmpProblem.setA("A :" + tmpA);	//��ѡ�����Aǰ׺
				cout << "������ѡ��B���ݣ�\n";
				cin >> tmpB;				//���̶�ȡѡ��B����
				tmpProblem.setB("B :" + tmpB);	//��ѡ�����Bǰ׺
				cout << "������ѡ��C���ݣ�\n";
				cin >> tmpC;				//���̶�ȡѡ��C����
				tmpProblem.setC("C :" + tmpC);	//��ѡ�����Cǰ׺
				cout << "������ѡ��D���ݣ�\n";
				cin >> tmpD;				//���̶�ȡѡ��D����
				tmpProblem.setD("D :" + tmpD);	//��ѡ�����Dǰ׺
				cout << "�������׼��(A(a)/B(b)/C(c)/D(d))��\n";
				tmpAnswer = getUserAnswer();	//���̶�ȡ��׼��,char���Ը�ֵ��string
				tmpProblem.setAnswer("��׼�� :" + tmpAnswer); //����׼�𰸼���ǰ׺
				admin.addQuestions(tmpProblem);	//����������Ŀ�ĺ���
				returnMenu(userName, userType);		//������һ���˵�
				break;
			case 3:
				do
				{
					flag3 = false;			//ѡ�����ڲ���ǳ�ʼ��
					cout << "��������Ҫɾ������Ŀ��ţ�\n";
					cin >> problemNum;		//�û�����������Ŀ���
					if (!judgmentNumber(problemNum))	//�ж������Ƿ�Ϊ�Ϸ�����
					{
						cout << "��Ч���룬���������롣\n";
						flag3 = true;		//��ǷǷ�
					}
				} while (flag3);			//�Ƿ�Ҫ����������
				admin.deleteQuestions(problemNum);	//����ɾ����Ŀ����
				returnMenu(userName, userType);		//������һ���˵�
				break;
			case 4:	
				cout << "�����뱻�������û�����\n";
				cin >> tmpUserName;
				admin.userManagement(tmpUserName, admin, userName);
				returnMenu(userName, userType);		//������һ���˵�
				break;
			case 5:
				do
				{
					ans = "no";						//ȷ����ȫ��Ĭ��ָ��Ϊno
					flag5 = false;					//ѡ����ڲ���ǳ�ʼ��
					cout << "�Ƿ�ȷ����գ�������yes/no\n";
					cin >> ans;						//�û�������������
					ans = strToLower(ans);			//ͳһת��ΪСд
					if (!(ans == "yes" || ans == "no"))
					{
						cout << "��Ч���룬���������롣\n";
						flag5 = true;
					}
				} while (flag5);					//�Ƿ�����Ҫ����������
				admin.clearQuestions(ans, pathProblem);
				returnMenu(userName, userType);		//������һ���˵�
				break;
			case 6:
				cout << "����������룺";
				cin >> inOldPassword;			//��������������
				cout << "�����������룺";
				cin >> inNewPassword;			//�������������
				//���ø������뺯��
				admin.changPassword(userName, inOldPassword, inNewPassword, pathUser);
				returnMenu(userName, userType);		//������һ���˵�
				break;
			case 7:
				do
				{
					ans = "no";						//ȷ����ȫ��Ĭ��ָ��Ϊno
					flag7 = false;					//ѡ����ڲ���ǳ�ʼ��
					cout << "�Ƿ�ȷ��ע����������yes/no\n";
					cin >> ans;						//�û�������������
					ans = strToLower(ans);			//ͳһת��ΪСд
					if (!(ans == "yes" || ans == "no"))
					{
						cout << "��Ч���룬���������롣\n";
						flag7 = true;
					}
				} while (flag7);					//�Ƿ�����Ҫ����������
				admin.cancelAccount(ans, pathUser, userName);	//�����˺�ע������
				returnMenu(userName, userType);		//������һ���˵�
				break;
			case 8: exitSystem();			//�˳�ϵͳ
				break;
			default: flag_admin = true;		//�Ƿ������ı�Ϸ�������
			}
			if (flag_admin)		//�Ƿ�����
			{
				cout << "��Ч���룬����������.\n";
				cin.clear();			//����cin״̬��ʶ��׼��������һ�ε�����
				systemSleep(1000);		//ϵͳ����
				refreshBuffer();		//ˢ�»�����
			}
		} while (flag_admin);			//�Ƿ�����Ҫ����������
	}
	else if (userType == user.getIdentity())	//�ж��Ƿ�Ϊ�û�
	{
		user.menu();								//�û��˵� 
		bool flag_user = false;							//����û��˵�ѡ���ѡ��Ϸ���
		string testNum;								//�û��������Ŀ��ȡ����
		int sel = -1;									//�˵�ѡ��
		do
		{
			flag_user = false;							//�û��˵�ѡ���ǳ�ʼ��
			cin >> sel;								//�û���������ѡ��
			switch (sel)
			{
			case 1:
				do
				{
					flag1 = false;					//ѡ��һ�ڲ���ǳ�ʼ��
					cout << "���������������\n";
					cin >> testNum;					//�û����������������	
					if (!judgmentNumber(testNum))	//�ж��Ƿ�Ϸ�����
					{
						cout << "��Ч���룬���������롣\n";
						flag1 = true;
					}
				} while (flag1);					//�Ƿ�����Ҫ����������				
				user.testQuestions(testNum);
				returnMenu(userName, userType);		//������һ���˵�
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
				user.cancelAccount(ans, pathUser, userName);	//�����˺�ע������
				returnMenu(userName, userType);		//������һ���˵�
				break;
			case 3:
				cout << "����������룺";
				cin >> inOldPassword;			//��������������
				cout << "�����������룺";
				cin >> inNewPassword;			//�������������
				//���ø������뺯��
				user.changPassword(userName, inOldPassword, inNewPassword, pathUser);
				returnMenu(userName, userType);		//������һ���˵�
				break;
			case 4:	exitSystem();					//�˳�ϵͳ
				break;
			default: flag_user = true;						//�Ƿ������ı�Ϸ�������
			}
			if (flag_user)				//�Ƿ�����
			{
				cout << "��Ч���룬����������.\n";
				cin.clear();			//����cin״̬��ʶ��׼��������һ�ε�����
				systemSleep(1000);		//ϵͳ����
				refreshBuffer();		//ˢ�»�����
			}
		} while (flag_user);			//�Ƿ�����Ҫ����������
	}
	else	//δ֪���	
	{
		void unknownIdentity();
	}

	return true;
}

bool returnMenu(string& userName, string& userType)
{
	bool reMenuFlag = false;		//���ڱ�ǷǷ�����
	system("pause");				//����ǰ��ͣ���û��Ķ���Ļ�Ļ���
	do
	{
		system("cls");				//����
		cout << "================================================\n";
		cout << endl;
		cout << "=                 1.�����ϼ�                   =\n";
		cout << "=                 2.�˳�ϵͳ                   =\n";
		cout << endl;
		cout << "================================================\n";
		int sel = -1;				//�˵�ѡ��
		cin >> sel;					//�û���������ѡ��
		switch (sel)
		{
		case 1:
			openMenu(userName, userType);	//��������ﵽ�ؿ��˵���Ŀ��
			break;
		case 2:
			exitSystem();			//�����˳�ϵͳ����
			break;
		default:
			reMenuFlag = true;		//��ǷǷ�����
		}
		if (reMenuFlag)				//�Ƿ�����
		{
			cout << "��Ч���룬����������.\n";
			cin.clear();			//����cin״̬��ʶ��׼��������һ�ε�����
			systemSleep(1000);		//ϵͳ����
			refreshBuffer();		//ˢ�»�����
		}
	} while (reMenuFlag);	//�Ƿ�����Ҫ����������

	return !reMenuFlag;
}

string getpassword()
{
	string str = "";		//���ַ���
	char init = '\0';		//Ĭ���ַ�Ϊ��
	for (;;)
	{
		init = _getch();		//��ȡ���뵫����ʾ
		if (init == VK_RETURN)   //����������Enter ����ô���в���������
		{
			cout << endl;
			break;
		}
		else if (init == VK_BACK) //����������BACKSPACE ����ô�����˻�
		{
			cout << "\b \b" << flush;
			str.erase(str.length() - 1);
		}
		else					//��������ʱ��ӡ*��
		{
			cout << "*" << flush;
			str += init;		//���ַ������ַ���
		}
	}

	return str;
}

void Random(int* arr, int num, int minNum, int maxNum)//���ɷ�Χ��minNum~maxNum������� 
{
	if (num == maxNum)	//��ȡ��������Ŀ�������ʱ����Ҫ�����ȡֱ��ȫ�����
	{
		for (int i = 0; i < num; i++)
			arr[i] = i + 1;
		return;
	}
	srand(time(NULL));  //����ʱ������
	bool* flagArr = new bool[maxNum + 1];		//���ڱ���Ѿ����ֵ������
	fill(flagArr, flagArr + maxNum + 1, false);		//��������ʼ��ΪFALSE
	int temp = 0;				//��ʱ���������
	for (int i = 0; i < num;) 
	{
		temp = rand() % (maxNum - minNum + 1) + minNum;//��������maxNum~l������� 
		if (!flagArr[temp])		//��֤����Ψһ��
		{
			flagArr[temp] = true;		//�±�Ϊ���֣�Ԫ��ֵΪ��ǣ�ÿ�η�����������
			arr[i] = temp;		//��������
			i++;		//���������ֲ����������������±����
		}
		else			//���������־�����
			continue;
	}
}

int cmpfunc(const void* a, const void* b)
{
	//��С��������
	return (*(int*)a - *(int*)b);
}

char getUserAnswer()
{
	string tmpStr = "";
	char ans = '\0';
	bool flag = false;		//���ڱ�ǷǷ�����
	
	do
	{
		flag = false;				//ÿ������ǰ����Ҫ���ñ��
		cin >> tmpStr;				//������������
		if (tmpStr.size() > 1)		//���ַ����ڷǷ�
			flag = true;			//��ǷǷ�
		else
			ans = toupper(tmpStr[0]);		//ͳһת��Ϊ��д��������Ƿ��ж�
		//�Ƿ��ж�
		if (!(ans == 'A' || ans == 'B' || ans == 'C' || ans == 'D') || flag)
		{
			cout << "�Ƿ����룡���������룺\n";
			cin.clear();					//����cin״̬��׼����һ������
			flag = true;			//��ǷǷ�
		}

	} while (flag);		//�Ƿ�Ҫ����������

	return ans;				//�����û�����Ĵ�
}

bool getProblemData(vector<CProblem>* data, int* maxNum)
{
	CProblem tmpProblem;				//��ʱ�洢��Ŀ����
	//��ʱ�洢��Ŀ��ţ����⣬ѡ��A,ѡ��B,ѡ��C,ѡ��D,��
	string tmpNum, tmpTitle, tmpA, tmpB, tmpC, tmpD, tmpAnswer;
	//vector<CProblem>vccp;				//��ʱ�洢����ļ�����
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
		cout << "����ļ��գ�����ϵϵͳ����Ա�����⡣\n" << endl;
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
		getline(foi, tmpAnswer);		//��ȡ��
		tmpProblem.setNum(tmpNum);		//��ʱ�洢��Ŀ���
		tmpProblem.setTitle(tmpTitle);	//��ʱ�洢��Ŀ����
		tmpProblem.setA(tmpA);			//��ʱ�洢ѡ��A
		tmpProblem.setB(tmpB);			//��ʱ�洢ѡ��B
		tmpProblem.setC(tmpC);			//��ʱ�洢ѡ��C
		tmpProblem.setD(tmpD);			//��ʱ�洢ѡ��D
		tmpProblem.setAnswer(tmpAnswer);//��ʱ�洢��׼��
		data->push_back(tmpProblem);		//��Ŀ���ݴ���vetor����
	}
	foi.close(); //�ر��ļ�
	tmpProblem = data->back();			//��ȡ������һ����Ŀ
	*maxNum = stoi((tmpProblem.getNum()));	//�����Ŀ���

	return true;
}

string strToLower(string& str)
{
	for (string::iterator it = str.begin(); it != str.end(); it++)
		*it = tolower(*it);
	return str;
}
