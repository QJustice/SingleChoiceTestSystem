#include <iostream>
#include "systemHead.h"
#include "errorExceptionHead.h"

using std::cin;
using std::cout;

int main()
{
	bool flag = false;			//用于标记非法输入
	int sel;				//记录选项
	string tmpName, tmpPassword;  //临时存储用户名和密码
	do
	{		
		systemMenu();				//系统菜单
		flag = false;					//初始化非法输入标记
		cin >> sel;					//键盘读取用户输入选项
		switch (sel)				//菜单选择
		{
		case 1:						//选项一
			cout << "请输入用户名\n";
			cin >> tmpName;			//键盘读取用户输入
			registerNum(tmpName);	//调用注册函
			break;
		case 2:						//选项二
			cout << "请输入用户名\n";
			cin >> tmpName;			//键盘读取用户输入
			cout << "请输入密码\n";
			tmpPassword = getpassword();		//键盘读取用户输入,加密输入
			logOn(tmpName, tmpPassword);	//调用登录函数
			break;
		case 3:					//选项三
			exitSystem();			//调用退出系统函数
			break;
		default: flag = true;		//其他非法输入
		}
		if (flag)
		{
			cout << "无效输入，请重新输入.\n";
			cin.clear();			//更改cin状态标识符准备接受下一次的输入
			systemSleep(1000);		//系统休眠
			refreshBuffer();		//刷新缓冲区
		}
	} while (flag);		//非法输入下要求重新输入
	return 0;
}