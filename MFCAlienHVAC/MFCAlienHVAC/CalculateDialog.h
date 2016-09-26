#pragma once


// CalculateDialog dialog

class CalculateDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CalculateDialog)

public:
	CalculateDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CalculateDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG_CALCULATE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_wall12;
	CString m_wall23;
	CString m_wall34;
	CString m_wall45;
	CString m_wall_total;
};
