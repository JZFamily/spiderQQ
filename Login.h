#pragma once
//comment by jidzh@2018-01-25,通过二维码登录
//1，首先获取二维码，以及cookies中参数qrsig
//2，通过1的cookies，根据qrsig计算出令牌参数，获取二维码状态，获得3的url
//3, 通过2的cookies，根据URL，获得ptwebqq参数
//4, 通过3的cookies，获得vfwebqq
#include <string>
extern struct  webQQClient;
extern webQQClient client;


bool LoginByQRcode();
bool getQRcode();
bool CheckQRcodeState();
bool GetPtWebQQ();
bool GetVfWebQQ();

bool LoginByCookies();


void OpenQRCode();
std::string hash33(const std::string& s);
std::string UTF8ToGBK(std::string UTF8String);
int _utf8_to_gb(const char* src, char* dst, int len);


