
// MFCAlienHVACDlg.h : header file
//

#pragma once
#include "afxwin.h"


// CMFCAlienHVACDlg dialog
class CMFCAlienHVACDlg : public CDialogEx
{
// Construction
public:
	CMFCAlienHVACDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MFCALIENHVAC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	// Manually added message map functions
	void OnMouseMove(UINT nFlags, CPoint point);
	void OnLButtonUp(UINT nFlags, CPoint point);
	void OnLButtonDown(UINT nFlags, CPoint point);

private:
	void SetActiveAlien(int alien);

    int m_tempature_data[5][3]; // The prefered temperature of each alien used to calute cost
	int m_room_occupant[5];     // The occupant of each room
    int m_active_alien;         // The alien currently being accessed or moved

public:
	afx_msg void OnBnClickedButtonCalculate();
	CString m_cost; // The display for the calcualted cost

	afx_msg void OnStnClickedAlien1();
	afx_msg void OnStnClickedAlien2();
	afx_msg void OnStnClickedAlien3();
	afx_msg void OnStnClickedAlien4();
	afx_msg void OnStnClickedAlien5();
private:
	CString m_temp1; // Statistics for m_active_alien
	CString m_temp2;
	CString m_temp3;
public:
	//afx_msg void OnStnClickedTemp3();
private:
	CStatic m_alien1_cont; // Control variables for movin aliens
	CStatic m_alien2_cont;
	CStatic m_alien3_cont;
	CStatic m_alien4_cont;
	CStatic m_alien5_cont;
public:
//	afx_msg void OnBnClickedStaticRoom1();
};
