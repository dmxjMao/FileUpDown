// ADOConn.h: interface for the ADOConn class.
//
//////////////////////////////////////////////////////////////////////

#pragma once


class CADOConn  
{
public:
	BOOL ExecuteSQL(_bstr_t bstrSQL);//执行SQL语句
	_RecordsetPtr& GetRecordSet(_bstr_t bstrSQL);//
	void ExitConn();		//断开连接
	void ADOConnect();	//连接数据库
	CADOConn();
	virtual ~CADOConn();
	_ConnectionPtr m_pCon;	//_ConnectionPtr对象
	_RecordsetPtr m_pRs;	//_RecordsetPtr对象

};
