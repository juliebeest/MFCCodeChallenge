// CalculateDialog.cpp : implementation file
// Warning: For entertainment purposes only. This program does not come iwht any warrantee,
// not even the implicit warrantee that it actually works.
// Copy write Julie Beeston 2016
//
// Dialog for displaying how the cost is calculated for a given configuration

#include "stdafx.h"
#include "MFCAlienHVAC.h"
#include "CalculateDialog.h"
#include "afxdialogex.h"


// CalculateDialog dialog

IMPLEMENT_DYNAMIC(CalculateDialog, CDialogEx)

//Constructor
CalculateDialog::CalculateDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CalculateDialog::IDD, pParent)
	, m_wall12(_T(""))
	, m_wall23(_T(""))
	, m_wall34(_T(""))
	, m_wall45(_T(""))
	, m_wall_total(_T(""))
{

}

//Destructor
CalculateDialog::~CalculateDialog()
{
}

//Data Exchange
void CalculateDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_WALL12, m_wall12);
	DDX_Text(pDX, IDC_WALL13, m_wall23);
	DDX_Text(pDX, IDC_WALL14, m_wall34);
	DDX_Text(pDX, IDC_WALL15, m_wall45);
	DDX_Text(pDX, IDC_WALL16, m_wall_total);
}


BEGIN_MESSAGE_MAP(CalculateDialog, CDialogEx)
END_MESSAGE_MAP()


// CalculateDialog message handlers
