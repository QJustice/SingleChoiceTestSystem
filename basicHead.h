#pragma once

#include <string>

class CBasic;

using std::string;

#ifndef _BASICHEAD_
#define _BASICHEAD_

class CBasic
{
protected:
	string identity;		//��ݱ�ǩ
	string userName;		//�û���
	string password;		//����
public:
	bool changPassword(string& Name, string& oldPassword, string& newPassword, string path);		//�޸�����
	string getUserName();		//��ȡ�û���
	string getpassword();		//��ȡ����
	string getIdentity();		//��ȡ��ݱ�ǩ
	bool cancelAccount(string instruct, string path, string Name);	//ע���˻�
};

#endif	//_BASICHEAD_