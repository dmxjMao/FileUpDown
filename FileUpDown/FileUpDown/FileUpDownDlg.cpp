
// FileUpDownDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "FileUpDown.h"
#include "FileUpDownDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFileUpDownDlg 对话框



CFileUpDownDlg::CFileUpDownDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_FILEUPDOWN_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFileUpDownDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STS_MSG, m_ctlMsg);
}

BEGIN_MESSAGE_MAP(CFileUpDownDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CFileUpDownDlg 消息处理程序

BOOL CFileUpDownDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	// init db
	m_adoConn.ADOConnect();
	if (!GetDBInfo())
		TRACE("GetDBInfo Failed !");

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CFileUpDownDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CFileUpDownDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// 获取数据库信息;
BOOL CFileUpDownDlg::GetDBInfo()
{
	CString strSQL = _T("select * from t_register_user");
	_RecordsetPtr& rs = m_adoConn.GetRecordSet((_bstr_t)strSQL);

	_variant_t userID, userType, userPwd; 
	while (!rs->adoEOF)
	{
		userID = rs->GetCollect("userID");
		userType = rs->GetCollect("userType");
		userPwd = rs->GetCollect("userPwd");
	
		auto pUserInfo = m_mapUserInfo[userID.iVal] = std::make_shared<CUserInfo>();
		pUserInfo->id = userID.iVal;
		pUserInfo->type = userType.iVal;
		pUserInfo->pwd = (_bstr_t)userPwd;

		rs->MoveNext();
	}

	return TRUE;
}