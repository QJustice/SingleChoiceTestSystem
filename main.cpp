#include <iostream>
#include "systemHead.h"
#include "errorExceptionHead.h"

using std::cin;
using std::cout;

int main()
{
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