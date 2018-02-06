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
	//comment by jidzh@2018-02-05,
	//when msg is recv， is not the server push it actively
	// there is a that is poll
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

// add by jidzh@2018-02-05,他的这个poll检测时间有些奇怪，之后看下机制

//好友列表
bool get_user_friends2()
{
http://s.web2.qq.com/api/get_user_friends2
	POST
	{ "vfwebqq":"1792cdf674d4a7c21fa5ef9083ac6513895e1614e3db906e8a4bb747a7e23ac9e547883138d1f5c4","hash" : "5F2F53590C1C04BC" }
}
//群列表
bool get_group_name_list_mask2()
{
http://s.web2.qq.com/api/get_group_name_list_mask2
r: {"vfwebqq":"1792cdf674d4a7c21fa5ef9083ac6513895e1614e3db906e8a4bb747a7e23ac9e547883138d1f5c4", "hash" : "5F2F53590C1C04BC"}

}
bool get_discus_list()
{
	get
http://s.web2.qq.com/api/get_discus_list?clientid=53999199&psessionid=8368046764001d636f6e6e7365727665725f77656271714031302e3133332e34312e383400001ad00000066b026e040015808a206d0000000a406172314338344a69526d0000002859185d94e66218548d1ecb1a12513c86126b3afb97a3c2955b1070324790733ddb059ab166de6857&vfwebqq=1792cdf674d4a7c21fa5ef9083ac6513895e1614e3db906e8a4bb747a7e23ac9e547883138d1f5c4&t=1517843055273
}
bool  get_self_info2()
{
	get

http://s.web2.qq.com/api/get_self_info2?t=1517843055275
}
bool get_online_buddies2()
{
http://d1.web2.qq.com/channel/get_online_buddies2?vfwebqq=1792cdf674d4a7c21fa5ef9083ac6513895e1614e3db906e8a4bb747a7e23ac9e547883138d1f5c4&clientid=53999199&psessionid=8368046764001d636f6e6e7365727665725f77656271714031302e3133332e34312e383400001ad00000066b026e040015808a206d0000000a406172314338344a69526d0000002859185d94e66218548d1ecb1a12513c86126b3afb97a3c2955b1070324790733ddb059ab166de6857&t=1517843058710
}
bool get_recent_list2()
{
	post
http://d1.web2.qq.com/channel/get_recent_list2
}
void poll2()
{
	post

		http://d1.web2.qq.com/channel/poll2
r: {"ptwebqq":"558aff2c8b7f6c8beb0a0b9d074ae7d9bb7ccd7b0f46234cfcde424b0048c344", "clientid" : 53999199, "psessionid" : "8368046764001d636f6e6e7365727665725f77656271714031302e3133332e34312e383400001ad00000066b026e040015808a206d0000000a406172314338344a69526d0000002859185d94e66218548d1ecb1a12513c86126b3afb97a3c2955b1070324790733ddb059ab166de6857", "key" : ""}
}