// WelcomeDialog.cpp : implementation file
// Warning: For entertainment purposes only. This program does not come iwht any warrantee,
// not even the implicit warrantee that it actually works.
// Copy write Julie Beeston 2016
//
// Dialog shown at start up to explain to the user the purpos of the application

#include "stdafx.h"
#include "MFCAlienHVAC.h"
#include "WelcomeDialog.h"
#include "afxdialogex.h"


// WelcomeDialog dialog

IMPLEMENT_DYNAMIC(WelcomeDialog, CDialogEx)

//Constructor
WelcomeDialog::WelcomeDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(WelcomeDialog::IDD, pParent)
{

}

//Destructor
WelcomeDialog::~WelcomeDialog()
{
}

// Data Exchange
void WelcomeDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(WelcomeDialog, CDialogEx)
END_MESSAGE_MAP()


// WelcomeDialog message handlers
