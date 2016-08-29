#pragma once
#include <map>
#include <string>
#include <memory> //shared_ptr;

/*
	t_register_user��ṹ
*/

typedef int USERID;

class CUserInfo
{
public:
	int id;				//�û�ID;
	int type;			//�û�����;
	std::string pwd;	//����;
};


typedef std::map<USERID, std::shared_ptr<CUserInfo>> UserInfoMap;

