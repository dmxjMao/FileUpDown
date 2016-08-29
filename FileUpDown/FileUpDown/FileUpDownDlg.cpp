
// FileUpDownDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FileUpDown.h"
#include "FileUpDownDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFileUpDownDlg �Ի���



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


// CFileUpDownDlg ��Ϣ�������

BOOL CFileUpDownDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	// init db
	m_adoConn.ADOConnect();
	if (!GetDBInfo())
		TRACE("GetDBInfo Failed !");

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CFileUpDownDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CFileUpDownDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// ��ȡ���ݿ���Ϣ;
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