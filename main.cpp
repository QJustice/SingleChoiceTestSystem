#include <iostream>
#include "systemHead.h"
#include "errorExceptionHead.h"

using std::cin;
using std::cout;

int main()
{
	int flag = 0;			//���ڱ�ǷǷ�����
	int sel;				//��¼ѡ��
	string tmpName, tmpPassword;  //��ʱ�洢�û���������
	do
	{		
		systemMenu();				//ϵͳ�˵�
		flag = 0;					//��ʼ���Ƿ�������
		cin >> sel;					//���̶�ȡ�û�����ѡ��
		switch (sel)				//�˵�ѡ��
		{
		case 1:						//ѡ��һ
			flag = 1;					//���Ϊ��ѡ��һ
			cout << "�������û���\n";
			cin >> tmpName;			//���̶�ȡ�û�����
			registerNum(tmpName);	//����ע�ắ
			break;
		case 2:						//ѡ���
			flag = 2;					//���Ϊ��ѡ���
			cout << "�������û���\n";
			cin >> tmpName;			//���̶�ȡ�û�����
			cout << "����������\n";
			cin >> tmpPassword;		//���̶�ȡ�û�����
			logOn(tmpName, tmpPassword);	//���õ�¼����
			break;
		case 3:					//ѡ����
			flag = 3;				//���Ϊ��ѡ����
			exitSystem();			//�����˳�ϵͳ����
			break;
		default: flag = 0;		//�����Ƿ�����
		}
		if (0 == flag)
		{
			cout << "��Ч���룬����������.\n";
			cin.clear();			//����cin״̬��ʶ��׼��������һ�ε�����
			systemSleep(1000);		//ϵͳ����
			refreshBuffer();		//ˢ�»�����
		}
	} while (flag == 0);		//�Ƿ�������Ҫ����������
	return 0;
}