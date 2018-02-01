
#include <curl.h>
#include"NetworkWrapper.h"
#include "Login.h"
#include"json.hpp"
using namespace std;
using namespace nlohmann;
std::string USERAGENT = "Mozilla/5.0 (Windows NT 6.3; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/61.0.3163.79 Safari/537.36";

struct  webQQClient
{
	std::string qrsig;
	std::string step2url;
	std::string ptwebqq;
	std::string vfwebqq;
};

webQQClient client;

//comment by jidzh@2018-01-25,首次登录需要扫描二维码

bool LoginByQRcode()
{
	if (!getQRcode()) { return false; }
	if (!CheckQRcodeState()) { return false; }
	//令牌
	if (!GetPtWebQQ()) { return false; }
	//验证verify
	if (!GetVfWebQQ()) { return false; }
	return true;
}


//add by jidzh@2018-01-25,二维码成功后需要，再次确认。

bool LoginByCookies()
{
	std::string PostData;
	HTTPConnection link;
	json PostDataByJson;
//------拼接post数据包----
	PostDataByJson["ptwebqq"] = client.ptwebqq.c_str();
	PostDataByJson["clientid"] = 53999199;
	PostDataByJson["psessionid"] = "";
	PostDataByJson["status"] = "online";
	PostData = "r=";
	PostData+= PostDataByJson.dump();

//------
	link.setVerbos(1);
	link.setURL("http://d1.web2.qq.com/channel/login2");
	link.setReferer("http://s.web2.qq.com/proxy.html?v=20130916001&callback=1&id=1");
	link.setUserAgent(USERAGENT);
	link.setPostData(PostData);
	char buff[1024];
	link.setDataOutputBuffer(buff, 1024);

	link.perform();

	if (link.perform()) { link.HTTPConnectDebugPrint(); return false; }
	if (200 != link.getResponseCode()) { link.HTTPConnectDebugPrint(); return false; }
	printf("Buff: %s\n", UTF8ToGBK(buff).c_str());
	return true;
}
bool getQRcode()
{
	HTTPConnection link;
	link.setVerbos(1);
	link.setUserAgent(USERAGENT);
	//comment by jidzh@2018-01-24
	link.setURL("https://ssl.ptlogin2.qq.com/ptqrshow?appid=501004106&e=0&l=M&s=5&d=72&v=4&t=0.1");
	link.setDataOutputFile("qrcode.png");
	//这边cookies的生存周期是0，httponly标志是true。//jidzh@2018-01-25,可能我理解错误
	//不带这个cookies反而过不去
	link.setCookieOutputFile("cookie1.txt");
	//modify by jidzh@2018-01-23,如果执行错误
	if (link.perform()) { link.HTTPConnectDebugPrint(); return false; }
	if (200 != link.getResponseCode()) { link.HTTPConnectDebugPrint(); return false; }
	std::vector<Cookie> vec = link.getCookies();
	for (auto& c : vec)
	{
		if (c.name == "qrsig")
		{
			client.qrsig = c.value;
		}
	}

	OpenQRCode();
	printf("二维码已打开. 请使用手机扫描二维码进行登录.\n");
	return true;
}


bool CheckQRcodeState()
{
	std::string tmpurl;
	while (true)
	{
		HTTPConnection link;
		link.setVerbos(true);
		link.setUserAgent(USERAGENT);
		//printf("%s",hash332(qrsig).c_str());

		std::string url_raw = "https://ssl.ptlogin2.qq.com/ptqrlogin?ptqrtoken=";
		url_raw += hash33(client.qrsig);
		url_raw +="&webqq_type=10&remember_uin=1&login2qq=1&aid=501004106&"
			"u1=https%3A%2F%2Fw.qq.com%2Fproxy.html%3Flogin2qq%3D1%26webqq_type%3D10&"
			"ptredirect=0&ptlang=2052&daid=164&from_ui=1&pttype=1&dumy=&fp=loginerroralert&0-0-157510&"
			"mibao_css=m_webqq&t=undefined&g=1&js_type=0&js_ver=10184&login_sig=&pt_randsalt=3";
		//std::string url_ans = StrParse(url_raw, hash33(qrsig));

		link.setURL(url_raw);
		link.setReferer("https://ui.ptlogin2.qq.com/cgi-bin/login?daid=164&target=self&style=16&mibao_css=m_webqq&appid=501004106&enable_qlogin=0&no_verifyimg=1&s_url=http%3A%2F%2Fw.qq.com%2Fproxy.html&f_url=loginerroralert&strong_login=1&login_state=10&t=0.1");
		link.setCookieInputFile("cookie1.txt");
		link.setCookieOutputFile("cookie2.txt");
		

		char buff[1024];
		link.setDataOutputBuffer(buff, 1024);
		if (link.perform()) { link.HTTPConnectDebugPrint(); return false; }
		if (200 != link.getResponseCode()) { link.HTTPConnectDebugPrint(); return false; }
		//comment by jidzh@2018-01-23,此处需要改进
		//打印buff ，判断是否已登录
		//66未失效，继续循环
		//67认证中
		//0成功
		//失效，返回false
		//成功，返回true
		//ptuiCB('状态码'，'0','跳转网址','0','描述文本','qq号')
		printf("Buff: %s\n", UTF8ToGBK(buff).c_str());
		
		
		char* p = strstr(buff, "http");
		if (p)
		{
			char* q = strstr(p, "'");
			char xbuf[1024];
			memset(xbuf, 0, 1024);
			memcpy(xbuf, p, q - p);
			client.step2url = xbuf;
			printf("URL Got!\n");
			break;
		}
		Sleep(500);
	}

	//tmp(tmpurl);
	return true ;
}

bool tmp(const std::string url)
{
	HTTPConnection link;
	link.setVerbos(true);
	link.setUserAgent(USERAGENT);
	link.setURL(url);
	if (link.perform()) { link.HTTPConnectDebugPrint(); return false; }
	if (200 != link.getResponseCode()) { link.HTTPConnectDebugPrint(); return false; }
	return true;
}

bool GetPtWebQQ()
{
	HTTPConnection t;
	t.setVerbos(true);
	t.setUserAgent(USERAGENT);
	t.setURL(client.step2url);
	t.setSSLVerifyHost(0);
	t.setSSLVerifyPeer(0);
	t.setReferer("http://s.web2.qq.com/proxy.html?v=20130916001&callback=1&id=1");
	t.setCookieInputFile("cookie2.txt");
	t.setCookieOutputFile("cookie3.txt");

	//modify by jidzh@2018-01-23,如果执行错误
	if (t.perform()) { t.HTTPConnectDebugPrint(); return false; }
	//del by jidzh@2018-01-30,这个地方会有302
	//if (200 != t.getResponseCode()) { t.HTTPConnectDebugPrint(); return false; }

	std::vector<Cookie> vec = t.getCookies();
	for (auto& c : vec)
	{
		if (c.name == "ptwebqq")
		{
			client.ptwebqq = c.value;
			break;
		}
	}

	return true;
}


bool GetVfWebQQ()
{
	HTTPConnection t;
	t.setVerbos(true);
	t.setUserAgent(USERAGENT);
	//modify by jidzh@2018-01-25,for url拼接
	string url_raw = "https://s.web2.qq.com/api/getvfwebqq?ptwebqq=";
	url_raw+= client.ptwebqq;
	url_raw+= "&clientid=53999199&psessionid=&t=1516844197976";
	t.setURL(url_raw);
	t.setReferer("http://s.web2.qq.com/proxy.html?v=20130916001&callback=1&id=1");
	t.setSSLVerifyHost(1);
	t.setSSLVerifyPeer(1);
	t.setCookieInputFile("cookie3.txt");
	t.setCookieOutputFile("cookie4.txt");
	char buff[4096];
	t.setDataOutputBuffer(buff, 4096);

	if (t.perform()) { t.HTTPConnectDebugPrint(); return false; }
	if(200!=t.getResponseCode()) { t.HTTPConnectDebugPrint(); return false; }

	printf("VfWebQQBuff: %s\n", buff);

	return true;
	
}

void OpenQRCode()
{
	ShellExecute(NULL, "open", "qrcode.png", NULL, NULL, SW_SHOWMAXIMIZED);
}

std::string hash33(const std::string& s)
{
	int e = 0;
	int sz = s.size();
	for (int i = 0; i<sz; ++i)
	{
		e += (e << 5) + (int)s[i];
	}
	int result = 2147483647 & e;
	char buff[16];
	sprintf(buff, "%d", result);
	return std::string(buff);
}

//comment by jidzh@2018-01-24,之后要把那个根据转码原理的代码拿过来，拒绝win接口
std::string UTF8ToGBK(std::string UTF8String)
{
	int sz = UTF8String.size() * 2 / 3 + 256;
	auto gbkstr = new char[sz];
	memset(gbkstr, 0, sz);

	if (_utf8_to_gb(UTF8String.c_str(), gbkstr, sz) != 0)
	{
		return "[MiniEngine] UT8ToGBK Convert Failed";
	}

	std::string s((char*)gbkstr);

	delete[] gbkstr;
	return s;
}

int _utf8_to_gb(const char* src, char* dst, int len)
{
	int ret = 0;
	WCHAR* strA;
	int i = MultiByteToWideChar(CP_UTF8, 0, src, -1, NULL, 0);
	if (i <= 0) {
		return -1;
	}
	strA = (WCHAR*)malloc(i * 2);
	MultiByteToWideChar(CP_UTF8, 0, src, -1, strA, i);
	i = WideCharToMultiByte(CP_ACP, 0, strA, -1, NULL, 0, NULL, NULL);
	if (len >= i) {
		ret = WideCharToMultiByte(CP_ACP, 0, strA, -1, dst, i, NULL, NULL);
		dst[i] = 0;
	}
	if (ret <= 0) {
		free(strA);
		return -2;
	}
	free(strA);
	return 0;
}