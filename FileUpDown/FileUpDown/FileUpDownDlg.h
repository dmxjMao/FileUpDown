
// FileUpDownDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "UserInfo.h"

#include "ADOConn.h" //数据库

// CFileUpDownDlg 对话框
class CFileUpDownDlg : public CDialogEx
{
// 构造
public:
	CFileUpDownDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FILEUPDOWN_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// 服务器状态，错误等信息
	CStatic		m_ctlMsg;
	// 数据库
	CADOConn	m_adoConn;

private:
	//read db ：注册的用户信息;
	UserInfoMap m_mapUserInfo;

private:
	// 获取数据库信息;
	BOOL GetDBInfo();
};
