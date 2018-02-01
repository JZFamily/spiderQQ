#pragma once
#include <string>
#include <vector>
#include <functional>

//modify by jidz@2018-01-24,and i think Ҫ��Ҫ��һЩmethod ��
struct Cookie
{
    std::string domain;//����
    bool httpOnly;		//�Ƿ���http�д���cookies1��ʶ
    std::string path;//����·��
    bool secure;	//�Ƿ�ʹ�ð�ȫЭ���־
    int expiration;//���ʱ��
    std::string name;//����
    std::string value;//ֵ
};

class HTTPConnection
{
public:
    HTTPConnection();
    ~HTTPConnection();

    bool isReady() const;

    /// Behavior Options
    int setVerbos(bool v);/// curllib disabled by default.
    int setHeaderInBody(bool enable);///curllib disabled by default.

    int setURL(const std::string& URL);

    int setHeaderWriter(const std::function<int(char*,int)>& fn);
    int setHeaderOutputBuffer(void* ptr,int maxsz);
    int setHeaderOutputFile(const std::string& filename);

    int setDataWriter(const std::function<int(char*,int)>& fn);
    int setDataOutputBuffer(void* ptr,int maxsz);
    int setDataOutputFile(const std::string& filename);

    int setDataReader(const std::function<int(char*,int)>& fn);
    int setDataInputFile(const std::string& filename);

    int enableCookieEngine();
    int setCookieInputFile(const std::string& filename);
    int setCookieOutputFile(const std::string& filename);
    int setCookieSession(bool new_session);

    int addCookie(const std::string& raw_cookie);
    int clearCookie();
    int clearSessionCookie();
    int flushCookie();
    int reloadCookie();

    int setTimeout(int second);

    /// HTTP Option
    int setAcceptEncoding(const std::string& encoding);
    int setAcceptEncodingAll();
    int setTransferEncoding(bool enable);/// disabled by default
    int setUserAgent(const std::string& user_agent);
    int setReferer(const std::string& referer);
    int setOrigin(const std::string& origin);
    int setPostData(const void* data,int sz);
    int setPostData(const std::string& data);
	//comment by jidzh@2018-01-25,�ض���
    int setFollowLocation(bool enable);/// disabled by default
	//add by jidzh@2018-01-24,for SSL֧�֣��ƺ�Ĭ�ϴ�
	int setSSLVerifyPeer(bool enable);
	int setSSLVerifyHost(bool enable);

    enum class Method
    {
        Get,Post
    };

    int setMethod(Method m);/// Method::Get by default.

    int perform();

    /// Response
    int getResponseCode();
    std::vector<Cookie> getCookies();

    /// Error handling
    int getLastErrCode();
    std::string getLastError();

	//add by jidzh@2018-01-23
	void HTTPConnectDebugPrint();
private:
    class _impl;
    _impl* _p;
};
