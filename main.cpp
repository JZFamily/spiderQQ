//-----------------------------------------
//author:	jdz
//data:		2018-01-11
//description:	
//			����дһ��smartQQ����дgithub�ϵ� smartqq
//�򵥵Ŀ�ܾ��� ��½����

//��ȡ��ά�룬����cookies����һ���ֶν���hash33���ܺ�õ����ƣ�
//��ѯ�ö�ά���״̬

#include <Windows.h>
#include "main.h"
#include "Login.h"

bool LoginIn(int mode =0);

int main()
{
	//��¼
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
