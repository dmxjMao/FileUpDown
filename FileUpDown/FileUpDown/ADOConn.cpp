// ADOConn.cpp: implementation of the ADOConn class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ADOConn.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CADOConn::CADOConn()
{

}

CADOConn::~CADOConn()
{

}

void CADOConn::ADOConnect()//连接数据库
{
	try
	{
		m_pCon.CreateInstance("ADODB.Connection");
		m_pCon->ConnectionTimeout=3;//连接尝试时间
		//连接Access数据库
		/*
		原型: Open (_bstr_t ConnectionString, _bstr_t UserID, _bstr_t Password, long Options );
		*/
		m_pCon->Open("Provider=Microsoft.ACE.OLEDB.12.0;Data Source=FileUpDown.accdb;"	\
			"Jet OLEDB:DataBase Password=huyu@123",
			"", "", adModeUnknown);
	}
	catch(_com_error e)//捕捉异常
	{
		AfxMessageBox(e.Description());
	}
}

void CADOConn::ExitConn()//断开连接
{
	if(m_pRs!=NULL)
		m_pRs->Close();
	m_pCon->Close();
	
}

_RecordsetPtr& CADOConn::GetRecordSet(_bstr_t bstrSQL)//执行SQL查询语句
{
	try
	{
		if(m_pCon==NULL)
			ADOConnect();
		m_pRs.CreateInstance("ADODB.Recordset");//创建记录集
		/*
		原型:Open ( const _variant_t & Source, const _variant_t & ActiveConnection, 
			enum CursorTypeEnum CursorType, enum LockTypeEnum LockType, long Options );
			Source : 查询语句
			ActiveConnection : 建立好的连接
			CursorType : 游标类型
			LockType : 锁定类型， 只读、悲观、乐观adLockOptimistic（只有Update时锁定）
			Options : Source类型, adCmdText, adCmdTable, adCmdProc
		*/
		m_pRs->Open(bstrSQL,m_pCon.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	}
	catch(_com_error e)//捕捉异常
	{
		AfxMessageBox(e.Description());
	}
	return m_pRs;//返回结果集
}

BOOL CADOConn::ExecuteSQL(_bstr_t bstrSQL)//执行SQL操作语句
{
	try
	{
		if(m_pCon==NULL)
			ADOConnect();//连接数据库
		m_pCon->Execute(bstrSQL,NULL,adCmdText);//执行SQL
		return true;
	}
	catch(_com_error e)//捕捉异常
	{
		AfxMessageBox(e.Description());
		return false;
	}
}


/*
记录集的遍历、更新
_variant_t vID, vUsername ;
_RecordsetPtr  m_pRecordset;

while(! m_pRecordset->adoEOF)
{
	vID = m_pRecordset->GetCollect(_variant_t((long)0)); //取得第一列的值
	vUsername = m_pRecordset->GetCollect("姓名");		 //取得姓名列的值

	if(vID.vt != VT_NULL)
		TRACE("id:%d,姓名:%s\n", vID.lVal, (LPCTSTR)(_bstr_t)vUsername);

	CString strTmp = (LPCTSTR)(_bstr_t)vUsername;
	m_pRecordset->MoveNext();
}

m_pRecordset->MoveFirst();
m_pRecordset->Delete(adAffectCurrent); //删除当前记录

m_pRecordset->AddNew();  //添加新记录
m_pRecordset->PutCollect("学号", _variant_t((long)10));
m_pRecordset->PutCollect("姓名", _variant_t("王斌年"));

m_pRecordset->Move(1,_variant_t((long)adBookmarkFirst));  //从第一条记录往下移动一条记录
m_pRecordset->Update(); //保存

*/
