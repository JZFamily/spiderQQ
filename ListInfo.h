
#pragma once

#include<string>

//add by jidzh@2018-02-09
struct friends
{
	unsigned long			flag;
	unsigned long			uin;
	unsigned short			categories;
};

struct marknames
{
	unsigned long			uin;
	std::string				markname;
	unsigned short			type;
};

struct categories
{
	unsigned short			index;
	unsigned short			sort;
	std::string				name;
};

struct vipinfo
{
	unsigned short			vip_level;
	unsigned long			u;
	bool					is_vip;
};

struct info
{
	unsigned short			face;
	unsigned short			flag;
	std::string				nick;
	unsigned long			uin;
};

struct gnamelist
{
	unsigned long			flag;
	std::string				name;
	unsigned long			gid;
	unsigned long			code;
};

