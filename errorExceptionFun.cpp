#include <cstdlib>
#include "errorExceptionHead.h"
#include <iostream>

using std::cout;
//�쳣�˳�ϵͳ
void exitErrorTheSystem()
{
	//�����쳣�˳�
	exit(EXIT_FAILURE);
}

//�����֤�쳣
void unknownIdentity()
{
	cout << "δ֪��ݣ���¼ʧ�ܣ�����ϵͳ����Ա\n";
}

//ˢ�»�����
void refreshBuffer()
{
	//���ļ�ָ������ָ���ļ���ͷ,�ﵽˢ�»�����Ч��
	rewind(stdin);
}