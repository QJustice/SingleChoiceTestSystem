#include "basicHead.h"
#include <iostream>
#include <fstream>
#include <map>
#include <utility>
#include <cstdlib>

using std::cout;
using std::fstream;
using std::ios;
using std::map;
using std::pair;
using std::endl;


bool CBasic::changPassword(string& Name, string& oldPassword, string& newPassword, string path)
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
	else if (tmpit->second.first == oldPassword) //�¾�����ȶ�
	{
		tmpit->second.first = newPassword;		//�滻������
		fwoi.open(path, ios::out);			//��ע����Ϣ�ļ�
		for (auto it = mp.begin(); it != mp.end(); it++)	//д����º������
			fwoi << it->first << " " << it->second.first << " " << it->second.second << endl;
		fwoi.close();						//�ر��ļ�
		cout << "�����޸ĳɹ�\n";
	}
	else
		cout << "��������޸�ʧ��\n";
	foi.clear();						//����cin״̬��ʶ��
	foi.close();						//�ر��ļ�
	

	return false;
}

string CBasic::getUserName()
{
	return userName;
}

string CBasic::getpassword()
{
	return password;
}

string CBasic::getIdentity()
{
	return identity;
}

bool CBasic::cancelAccount(string instruct, string path, string Name)
{
	if (instruct == "no")		//��������
	{
		cout << "�����ѳ���\n";
		return false;
	}
	string userName;			//�û����洢
	pair<string, string>userMessage;		//�û������������Ϣ�洢
	map<string, pair<string, string>>mp;	//key:�û��� value:�û������������Ϣ
	fstream foi(path, ios::in);			//��ע����Ϣ�ļ�
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
		cout << "δ�ҵ��û��ļ���ע��ʧ��\n";
	else
		mp.erase(Name);					//ɾ���û���Ϣ
	foi.clear();						//����cin״̬��ʶ��
	foi.close();						//�ر��ļ�
	foi.open(path, ios::out);			//��ע����Ϣ�ļ�
	for (auto it = mp.begin(); it != mp.end(); it++)	//д����º������
		foi << it->first << " " << it->second.first << " " << it->second.second << endl;
	foi.close();						//�ر��ļ�

	return true;
}
