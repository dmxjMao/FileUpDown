#pragma once
#include <map>
#include <string>
#include <memory> //shared_ptr;

/*
	t_register_user表结构
*/

typedef int USERID;

class CUserInfo
{
public:
	int id;				//用户ID;
	int type;			//用户类型;
	std::string pwd;	//密码;
};


typedef std::map<USERID, std::shared_ptr<CUserInfo>> UserInfoMap;

