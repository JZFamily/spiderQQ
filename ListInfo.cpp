#include "ListInfo.h"
#include	"json.hpp"
#include "NetworkWrapper.h"
#include"Common.h"
#include "Sqlite3Connector.h"
#include<vector>
#define USERAGENT "Mozilla/5.0 (Windows NT 6.3; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/61.0.3163.79 Safari/537.36"
#define IS_VERBOS true
// add by jidzh@2018-02-05,他的这个poll检测时间有些奇怪，之后看下机制
using namespace std;
using namespace nlohmann;

//好友列表
bool get_user_friends2()
{
	std::string PostData;
	HTTPConnection link;
	json PostDataByJson;
	//------拼接post数据包----
	PostDataByJson["vfwebqq"] = client.vfwebqq;
	PostDataByJson["hash"] = client.hash;
	PostData += PostDataByJson.dump();
	link.setVerbos(IS_VERBOS);
	link.setUserAgent(USERAGENT);
	link.setURL("http://s.web2.qq.com/api/get_user_friends2");
	link.setCookieInputFile("cookie4.txt");
	link.setReferer("http://s.web2.qq.com/proxy.html?v=20130916001&callback=1&id=1");
	link.setPostData(PostData);
	char buff[2048];
	link.setDataOutputBuffer(buff, 2048);
	link.perform();

	if (link.perform()) { link.HTTPConnectDebugPrint(); return false; }
	if (200 != link.getResponseCode()) { link.HTTPConnectDebugPrint(); return false; }
	//printf("Buff: %s\n", UTF8ToGBK(buff).c_str());
	json RecvDataByJson;

	RecvDataByJson.parse(buff);
	if (RecvDataByJson["retcode"] != 0)
	{
		printf("!Erro retcode =%d", RecvDataByJson["retcode"]);
		return false;
	}
	try
	{
		vector<friends> vfriends;
		friends friendsTmpBuff;
		json friends= json::array(RecvDataByJson["result"]["friends"]);
		for (size_t i = 0; i < friends.size(); i++)
		{
			friendsTmpBuff.flag = friends[i]["flag"];
			friendsTmpBuff.uin = friends[i]["uin"];
			friendsTmpBuff.categories = friends[i]["categories"];
			vfriends.push_back(friendsTmpBuff);
		}
		vector<marknames> vmarknames;
		marknames marknamesTmpBuff;
		json marknames = json::array(RecvDataByJson["result"]["marknames"]);
		for (size_t i = 0; i < marknames.size(); i++)
		{
			marknamesTmpBuff.markname = marknames[i]["markname"].dump();
			marknamesTmpBuff.type = marknames[i]["type"];
			marknamesTmpBuff.uin = marknames[i]["uin"];
			vmarknames.push_back(marknamesTmpBuff);
		}
		vector<categories> vcategories;
		categories categoriesTmpBuff;
		json categories = json::array(RecvDataByJson["result"]["categories"]);
		for (size_t i = 0; i < categories.size(); i++)
		{
			categoriesTmpBuff.index = categories[i]["index"];
			categoriesTmpBuff.name = categories[i]["name"].dump();
			categoriesTmpBuff.sort = categories[i]["sort"];
			vcategories.push_back(categoriesTmpBuff);
		}
		vector<info> vinfo;
		info infoTmpBuff;
		json info = json::array(RecvDataByJson["result"]["info"]);
		for (size_t i = 0; i < info.size(); i++)
		{
			infoTmpBuff.face= info[i]["face"];
			infoTmpBuff.flag = info[i]["flag"];
			infoTmpBuff.nick = info[i]["nick"].dump();
			infoTmpBuff.uin = info[i]["uin"];
			vinfo.push_back(infoTmpBuff);
		}
	}
	catch (...)
	{
		return false;
	}

	return true;
}
//群列表
bool get_group_name_list_mask2()
{
	std::string PostData;
	HTTPConnection link;
	json PostDataByJson;
	//------拼接post数据包----
	PostDataByJson["vfwebqq"] = client.vfwebqq;
	PostDataByJson["hash"] = client.hash;
	PostData += PostDataByJson.dump();
	link.setVerbos(IS_VERBOS);
	link.setUserAgent(USERAGENT);
	link.setURL("http://s.web2.qq.com/api/get_group_name_list_mask2");
	link.setCookieInputFile("cookie4.txt");
	link.setReferer("http://s.web2.qq.com/proxy.html?v=20130916001&callback=1&id=1");
	link.setPostData(PostData);
	char buff[2048];
	link.setDataOutputBuffer(buff, 2048);
	link.perform();

	if (link.perform()) { link.HTTPConnectDebugPrint(); return false; }
	if (200 != link.getResponseCode()) { link.HTTPConnectDebugPrint(); return false; }
	//printf("Buff: %s\n", UTF8ToGBK(buff).c_str());
	json RecvDataByJson;

	RecvDataByJson.parse(buff);
	if (RecvDataByJson["retcode"] != 0)
	{
		printf("!Erro retcode =%d", RecvDataByJson["retcode"]);
		return false;
	}
	try
	{
		vector<gnamelist> vgnamelist;
		gnamelist gnamelistTmpBuff;
		json gnamelist = json::array(RecvDataByJson["result"]["gnamelist"]);
		for (size_t i = 0; i < gnamelist.size(); i++)
		{
			gnamelistTmpBuff.code = gnamelist[i]["code"];
			gnamelistTmpBuff.flag = gnamelist[i]["flag"];
			gnamelistTmpBuff.gid = gnamelist[i]["gid"];
			gnamelistTmpBuff.name = gnamelist[i]["name"].dump;
			vgnamelist.push_back(gnamelistTmpBuff);
		}
	}
	catch (...)
	{
		return false;
	}

	return true;
	//{"retcode":0, "result" : {"gmasklist":[],
	//	"gnamelist" :
	//	[{"flag":152044561, "name" : "؏؏ᖗ古风动漫ᖘ؏؏", "gid" : 3186843681, "code" : 421517140};
	//	"gmarklist" : []}}
}

bool get_discus_list()
{
	{"retcode":0, "result" : {"dnamelist":[]}}
	HTTPConnection link;
	link.setVerbos(IS_VERBOS);
	link.setUserAgent(USERAGENT);
	std::string url = "http://s.web2.qq.com/api/get_discus_list?";
	url+= client.
	link.setURL();
	link.setCookieInputFile("cookie4.txt");
	link.setReferer("http://s.web2.qq.com/proxy.html?v=20130916001&callback=1&id=1");
	get
		http ://s.web2.qq.com/api/get_discus_list?clientid=53999199&psessionid=8368046764001d636f6e6e7365727665725f77656271714031302e3133332e34312e383400001ad00000066b026e040015808a206d0000000a406172314338344a69526d0000002859185d94e66218548d1ecb1a12513c86126b3afb97a3c2955b1070324790733ddb059ab166de6857&vfwebqq=1792cdf674d4a7c21fa5ef9083ac6513895e1614e3db906e8a4bb747a7e23ac9e547883138d1f5c4&t=1517843055273
}
bool  get_self_info2()
{
//	{"retcode":0, "result" : {"birthday":{"month":11, "year" : 1996, "day" : 25}, "face" : 0, "phone" : "", "occupation" : "", "allow" : 1, "college" : "北京交通大学燕郊职业", "uin" : 1798436275, "blood" : 5, "constel" : 11, "lnick" : "扎心了", "vfwebqq" : "58eaa9c78e7c84367444134d1d95067315b7885d8347a792a8ed951a1314dad6b95e68954e6116e8", "homepage" : "http://1798436275.qzone.qq.com", "vip_info" : 0, "city" : "威海", "country" : "中国", "personal" : "嘿嘿嘿嘿嘿嘿", "shengxiao" : 1, "nick" : "为美好的世界献上背锅侠", "email" : "", "province" : "山东", "account" : 1798436275, "gender" : "male", "mobile" : ""}}
//	get
//
//		http ://s.web2.qq.com/api/get_self_info2?t=1517843055275
}
bool get_online_buddies2()
{
	HTTPConnection t;
	t.setVerbos(true);
	t.setUserAgent(USERAGENT);
	//modify by jidzh@2018-01-25,for url拼接
	string url_raw = "http://d1.web2.qq.com/channel/get_online_buddies2?";
	url_raw += client.vfwebqq;
	url_raw += "&clientid=";
	url_raw += "53999199";// client.clientid;
	url_raw += "&psessionid";
	url_raw += client.psessionid;
	url_raw += "&t=1516844197976";
	t.setURL(url_raw);
	t.setReferer("http ://d1.web2.qq.com/proxy.html?v=20151105001&callback=1&id=2");
	t.setSSLVerifyHost(1);
	t.setSSLVerifyPeer(1);
	t.setCookieInputFile("cookie4.txt");
	char buff[4096];
	t.setDataOutputBuffer(buff, 4096);
	if (t.perform()) { t.HTTPConnectDebugPrint(); return false; }
	if (200 != t.getResponseCode()) { t.HTTPConnectDebugPrint(); return false; }

	printf("VfWebQQBuff: %s\n", buff);
	return true;
	{ "result":[{"client_type":7,"status" : "online","uin" : 2021160950},
	{ "client_type":7,"status" : "online","uin" : 4259172547 },,
	{ "client_type":2,"status" : "online","uin" : 3492184035 },
	{ "client_type":7,"status" : "online","uin" : 2153006193 },
	{ "client_type":2,"status" : "online","uin" : 533823102 }],"retcode" : 0 }
	//http://d1.web2.qq.com/channel/get_online_buddies2?vfwebqq=1792cdf674d4a7c21fa5ef9083a
	//c6513895e1614e3db906e8a4bb747a7e23ac9e547883138d1f5c4
	//&clientid=53999199&psessionid=8368046764001d636f6e6e7365727665725f776562717140
	//31302e3133332e34312e383400001ad00000066b026e040015808a206d0000000a40617231433
	//8344a69526d0000002859185d94e66218548d1ecb1a12513c86126b3afb97a3c2955b1070324
	//90733ddb059ab166de6857&t=1517843058710
}
bool get_recent_list2()
{

	post
		http ://d1.web2.qq.com/channel/get_recent_list2
}

def qHash(x, K) :
	N = [0] * 4
	for T in range(len(K)) :
		N[T % 4] ^= ord(K[T])

		U, V = 'ECOK', [0] * 4
		V[0] = ((x >> 24) & 255) ^ ord(U[0])
		V[1] = ((x >> 16) & 255) ^ ord(U[1])
		V[2] = ((x >> 8) & 255) ^ ord(U[2])
		V[3] = ((x >> 0) & 255) ^ ord(U[3])

		U1 = [0] * 8
		for T in range(8) :
			U1[T] = N[T >> 1] if T % 2 == 0 else V[T >> 1]

			N1, V1 = '0123456789ABCDEF', ''
			for aU1 in U1 :
V1 += N1[((aU1 >> 4) & 15)]
V1 += N1[((aU1 >> 0) & 15)]

return V1

def bknHash(skey, init_str = 5381) :
	
//add by jidzh@2018-08-08,
long bknHash(std::string skey,int init_str =5381)
{
	//hash_str = init_str
	//	for i in skey :
	//hash_str += (hash_str << 5) + ord(i)
	//	hash_str = int(hash_str & 2147483647)
	//	return hash_str
	long hash_str = init_str;
	for (auto &c : skey)
	{
		hash_str += (hash_str << 5) + c;
	}
	hash_str = int(hash_str & 2147483647);
	return hash_str;
}