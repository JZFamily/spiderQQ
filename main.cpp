//-----------------------------------------
//author:	jdz
//data:		2018-01-11
//description:	
//			打算写一个smartQQ，改写github上的 smartqq
//简单的框架就是 登陆接收

//获取二维码，其中cookies里有一个字段进行hash33加密后得到令牌，
//查询该二维码的状态

#include <Windows.h>
#include "main.h"
#include "Login.h"

bool LoginIn(int mode =0);

int main()
{
	//登录
	if (!LoginIn()) { return 0; }

	while (true)
	{

	}
	
	return 0;
}


bool LoginIn(int mode)
{
	if(!LoginByQRcode()) { return false; }
	if (!LoginByCookies()) { return false; }
	return true;
}
