#pragma once
//comment by jidzh@2018-01-25,ͨ����ά���¼
//1�����Ȼ�ȡ��ά�룬�Լ�cookies�в���qrsig
//2��ͨ��1��cookies������qrsig��������Ʋ�������ȡ��ά��״̬�����3��url
//3, ͨ��2��cookies������URL�����ptwebqq����
//4, ͨ��3��cookies�����vfwebqq
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


