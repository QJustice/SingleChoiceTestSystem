#include <iostream>
#include <cstdlib>;
#include "systemHead.h"
#include "errorExceptionHead.h"

using std::cin;
using std::cout;

int main()
{
	bool getLogonFlag = false;	//ע������е�¼ʱ����Ϸ����
	int logonSel;				//ע�����¼ʱѡ��ָ��
	bool flag = false;			//���ڱ�ǷǷ�����
	int sel;				//��¼ѡ��
	string tmpName, tmpPassword;  //��ʱ�洢�û���������
	do
	{		
		systemMenu();				//ϵͳ�˵�
		flag = false;					//��ʼ���Ƿ�������
		cin >> sel;					//���̶�ȡ�û�����ѡ��
		switch (sel)				//�˵�ѡ��
		{
		case 1:						//ѡ��һ
			cout << "�������û���\n";
			cin >> tmpName;			//���̶�ȡ�û�����
			registerNum(tmpName);	//����ע�ắ
			system("cls");
			cout << "|----------------------------------------------|\n";
			cout << "|                                              |\n";
			cout << "|                ***ע��ɹ�***                |\n";
			cout << "|                                              |\n";
			cout << "|----------------------------------------------|\n";
			cout << "|                                              |\n";
			cout << "|                 1.������¼                   |\n";
			cout << "|                 2.�˳�ϵͳ                   |\n";
			cout << "|                                              |\n";
			cout << "|----------------------------------------------|\n";
			do
			{				
				cin >> logonSel;
				switch (logonSel)
				{
				case 1: 
					cout << "�������û���\n";
					cin >> tmpName;			//���̶�ȡ�û�����
					cout << "����������\n";
					tmpPassword = getpassword();		//���̶�ȡ�û�����,��������
					logOn(tmpName, tmpPassword);	//���õ�¼����
					break;
				case 2:
					exitSystem();			//�����˳�ϵͳ����
					break;
				default:
					getLogonFlag = true;
				}
				if (getLogonFlag)
				{
					cout << "��Ч���룬����������.\n";
					cin.clear();			//����cin״̬��ʶ��׼��������һ�ε�����
					systemSleep(1000);		//ϵͳ����
					refreshBuffer();		//ˢ�»�����
				}
			} while (getLogonFlag);
			break;
		case 2:						//ѡ���
			cout << "�������û���\n";
			cin >> tmpName;			//���̶�ȡ�û�����
			cout << "����������\n";
			tmpPassword = getpassword();		//���̶�ȡ�û�����,��������
			logOn(tmpName, tmpPassword);	//���õ�¼����
			break;
		case 3:					//ѡ����
			exitSystem();			//�����˳�ϵͳ����
			break;
		default: flag = true;		//�����Ƿ�����
		}
		if (flag)
		{
			cout << "��Ч���룬����������.\n";
			cin.clear();			//����cin״̬��ʶ��׼��������һ�ε�����
			systemSleep(1000);		//ϵͳ����
			refreshBuffer();		//ˢ�»�����
		}
	} while (flag);		//�Ƿ�������Ҫ����������
	return 0;
}