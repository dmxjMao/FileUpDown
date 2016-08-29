
// FileUpDownDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "UserInfo.h"

#include "ADOConn.h" //���ݿ�

// CFileUpDownDlg �Ի���
class CFileUpDownDlg : public CDialogEx
{
// ����
public:
	CFileUpDownDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FILEUPDOWN_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// ������״̬���������Ϣ
	CStatic		m_ctlMsg;
	// ���ݿ�
	CADOConn	m_adoConn;

private:
	//read db ��ע����û���Ϣ;
	UserInfoMap m_mapUserInfo;

private:
	// ��ȡ���ݿ���Ϣ;
	BOOL GetDBInfo();
};
