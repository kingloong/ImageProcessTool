// DlgEdgeSobel.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ImageProcessTool.h"
#include "DlgSobel.h"
#include "afxdialogex.h"

extern Mat srcImg;
// CDlgSobel �Ի���

IMPLEMENT_DYNAMIC(CDlgSobel, CDialogEx)

CDlgSobel::CDlgSobel(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgSobel::IDD, pParent)
	, m_scale(1)
	, m_delta(0)
	, m_depth(CV_8U)
	, m_kSize(3)
	, m_dX(1)
	, m_dY(1)
{

}

CDlgSobel::~CDlgSobel()
{
}

void CDlgSobel::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO4, m_ddepth);
	DDX_Control(pDX, IDC_COMBO3, m_apertureSize);
	DDX_Control(pDX, IDC_COMBO2, m_dx);
	DDX_Control(pDX, IDC_COMBO1, m_dy);
	DDX_Text(pDX, IDC_EDIT1, m_scale);
	DDV_MinMaxDouble(pDX, m_scale, 0, 10);
	DDX_Text(pDX, IDC_EDIT2, m_delta);
	DDV_MinMaxDouble(pDX, m_delta, -10, 10);
}


BEGIN_MESSAGE_MAP(CDlgSobel, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO4, &CDlgSobel::OnCbnSelchangeCombo4)
	ON_CBN_SELCHANGE(IDC_COMBO3, &CDlgSobel::OnCbnSelchangeCombo3)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CDlgSobel::OnCbnSelchangeCombo2)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CDlgSobel::OnCbnSelchangeCombo1)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN2, &CDlgSobel::OnDeltaposSpin2)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, &CDlgSobel::OnDeltaposSpin1)
	ON_EN_CHANGE(IDC_EDIT1, &CDlgSobel::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &CDlgSobel::OnEnChangeEdit2)
END_MESSAGE_MAP()


// CDlgSobel ��Ϣ��������


void CDlgSobel::OnCbnSelchangeCombo4()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	int sel = m_ddepth.GetCurSel();
	CString string;
	m_ddepth.GetLBText(sel,string);
	if(string == _T("CV_8U"))	m_depth = CV_8U;
	else if(string == _T("CV_16U"))	m_depth = CV_16U;
	else if(string == _T("CV_16S"))	m_depth = CV_16S;
	else if(string == _T("CV_32F"))	m_depth = CV_32F;
	else if(string == _T("CV_64F"))	m_depth = CV_64F;
}


void CDlgSobel::OnCbnSelchangeCombo3()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	int sel = m_apertureSize.GetCurSel();
	CString string;
	m_apertureSize.GetLBText(sel,string);
	if(string == _T("1"))	m_kSize = 1;
	else if(string == _T("3"))	m_kSize = 3;
	else if(string == _T("5"))	m_kSize = 5;
	else if(string == _T("7"))	m_kSize = 7;
}


void CDlgSobel::OnCbnSelchangeCombo2()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	int sel = m_dx.GetCurSel();
	CString string;
	m_dx.GetLBText(sel,string);
	if(string == _T("���"))	m_dX = 0;
	else if(string == _T("һ��"))	m_dX = 1;
	else if(string == _T("����"))	m_dX = 2;
	if((m_dX == 0)&&(m_dY == 0))
	{
		MessageBox(_T("X��Y�����ֽ�������ͬʱΪ�㣡"),_T("����"),MB_ICONWARNING);
		m_dY = 1;
		m_dy.SetCurSel(1);
	}
}


void CDlgSobel::OnCbnSelchangeCombo1()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	int sel = m_dy.GetCurSel();
	CString string;
	m_dy.GetLBText(sel,string);
	if(string == _T("���"))	m_dY = 0;
	else if(string == _T("һ��"))	m_dY = 1;
	else if(string == _T("����"))	m_dY = 2;
	if((m_dX == 0)&&(m_dY == 0))
	{
		MessageBox(_T("X��Y�����ֽ�������ͬʱΪ�㣡"),_T("����"),MB_ICONWARNING);
		m_dX = 1;
		m_dx.SetCurSel(1);
	}
}


void CDlgSobel::OnDeltaposSpin1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	UpdateData(true);
	if(pNMUpDown->iDelta == 1)
	{
		if(m_scale>0)	m_scale -= 0.1;
	}
	else if(pNMUpDown->iDelta == -1)
	{
		if(m_scale<10)	m_scale += 0.1;
	}
	UpdateData(false);
	*pResult = 0;
}


void CDlgSobel::OnDeltaposSpin2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	UpdateData(true);
	if(pNMUpDown->iDelta == 1)
	{
		if(m_delta>-10)	m_delta -= 0.1;
	}
	else if(pNMUpDown->iDelta == -1)
	{
		if(m_delta<10)	m_delta += 0.1;
	}
	UpdateData(false);
	*pResult = 0;
}


BOOL CDlgSobel::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ����Ӷ���ĳ�ʼ��
	if(srcImg.depth() == CV_8U)
	{
		m_ddepth.AddString(_T("CV_8U"));
		m_ddepth.AddString(_T("CV_16S"));
		m_ddepth.AddString(_T("CV_32F"));
		m_ddepth.AddString(_T("CV_64F"));
	}
	else if((srcImg.depth() == CV_16U)||(srcImg.depth() == CV_16S))
	{
		m_ddepth.AddString(_T("CV_16U"));
		m_ddepth.AddString(_T("CV_16S"));
		m_ddepth.AddString(_T("CV_32F"));
		m_ddepth.AddString(_T("CV_64F"));
	}
	else if(srcImg.depth() == CV_32F)
	{
		m_ddepth.AddString(_T("CV_32F"));
		m_ddepth.AddString(_T("CV_64F"));
	}
	else if(srcImg.depth() == CV_64F)
	{
		m_ddepth.AddString(_T("CV_64F"));
	}
	m_ddepth.SetCurSel(0);

	m_apertureSize.AddString(_T("1"));
	m_apertureSize.AddString(_T("3"));
	m_apertureSize.AddString(_T("5"));
	m_apertureSize.AddString(_T("7"));
	m_apertureSize.SetCurSel(1);

	m_dx.AddString(_T("���"));
	m_dx.AddString(_T("һ��"));
	m_dx.AddString(_T("����"));
	m_dx.SetCurSel(1);

	
	m_dy.AddString(_T("���"));
	m_dy.AddString(_T("һ��"));
	m_dy.AddString(_T("����"));
	m_dy.SetCurSel(1);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CDlgSobel::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ����ӿؼ�֪ͨ�����������
	UpdateData(true);
	if(m_scale < 0)	m_scale = 0;
	else if(m_scale > 10)	m_scale = 10;
	UpdateData(false);
}


void CDlgSobel::OnEnChangeEdit2()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ����ӿؼ�֪ͨ�����������
	UpdateData(true);
	if(m_delta < -10)	m_delta = -10;
	else if(m_delta > 10)	m_delta = 10;
	UpdateData(false);
}