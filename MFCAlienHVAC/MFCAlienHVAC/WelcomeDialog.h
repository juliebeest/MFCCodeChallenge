#pragma once


// WelcomeDialog dialog

class WelcomeDialog : public CDialogEx
{
	DECLARE_DYNAMIC(WelcomeDialog)

public:
	WelcomeDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~WelcomeDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG_WELCOME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
