
// MFCAlienHVACDlg.cpp : implementation file
// Warning: For entertainment purposes only. This program does not come iwht any warrantee,
// not even the implicit warrantee that it actually works.
// Copy write Julie Beeston 2016
//
// Primary dialog for this application.
// Contains 5 aliens and 5 rooms to drag and drop them into.
// As each alien is selected it statisitcs are displied on the screen.
// Once all 5 are in rooms then the calculate button can be used to determin the cost of the configuration,

#include "stdafx.h"
#include "MFCAlienHVAC.h"
#include "MFCAlienHVACDlg.h"
#include "afxdialogex.h"

#include "WelcomeDialog.h"
#include "CalculateDialog.h"
#include <cmath>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define MAX_ALIEN 5
#define ALIEN_SIZE 48
#define ROOM_BOTTOM 123
#define ROOM_WIDTH 147
#define ROOM_LEFT 38


// CAboutDlg dialog used for App About
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCAlienHVACDlg dialog



CMFCAlienHVACDlg::CMFCAlienHVACDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCAlienHVACDlg::IDD, pParent)
	, m_cost(_T(""))
	, m_temp1(_T(""))
	, m_temp2(_T(""))
	, m_temp3(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCAlienHVACDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_COST, m_cost);
	DDX_Text(pDX, IDC_TEMP1, m_temp1);
	DDX_Text(pDX, IDC_TEMP2, m_temp2);
	DDX_Text(pDX, IDC_TEMP3, m_temp3);
	DDX_Control(pDX, IDC_ALIEN1, m_alien1_cont);
	DDX_Control(pDX, IDC_ALIEN2, m_alien2_cont);
	DDX_Control(pDX, IDC_ALIEN3, m_alien3_cont);
	DDX_Control(pDX, IDC_ALIEN4, m_alien4_cont);
	DDX_Control(pDX, IDC_ALIEN5, m_alien5_cont);
}

BEGIN_MESSAGE_MAP(CMFCAlienHVACDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CALCULATE, &CMFCAlienHVACDlg::OnBnClickedButtonCalculate)
	ON_STN_CLICKED(IDC_ALIEN1, &CMFCAlienHVACDlg::OnStnClickedAlien1)
	ON_STN_CLICKED(IDC_ALIEN2, &CMFCAlienHVACDlg::OnStnClickedAlien2)
	ON_STN_CLICKED(IDC_ALIEN3, &CMFCAlienHVACDlg::OnStnClickedAlien3)
	ON_STN_CLICKED(IDC_ALIEN4, &CMFCAlienHVACDlg::OnStnClickedAlien4)
	ON_STN_CLICKED(IDC_ALIEN5, &CMFCAlienHVACDlg::OnStnClickedAlien5)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
    ON_WM_LBUTTONDOWN()
//	ON_BN_CLICKED(IDC_STATIC_ROOM1, &CMFCAlienHVACDlg::OnBnClickedStaticRoom1)
END_MESSAGE_MAP()


// CMFCAlienHVACDlg message handlers

BOOL CMFCAlienHVACDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// Display the welcome message and instruction to the user
	WelcomeDialog dlg;
	dlg.DoModal();

	// Set the prefered temperatures for all 3 time slots for each alien.
	// Implementation note: m_tempature_data is not defined as a const because 
	// it is intended to be randomly generated in future releases
	m_tempature_data[0][0] =200; // Alien 1 prefered temperatures
	m_tempature_data[0][1] =100;
	m_tempature_data[0][2] =200;

	m_tempature_data[1][0] =10; // Alien 2 prefered temperatures
	m_tempature_data[1][1] =50;
	m_tempature_data[1][2] =100;

	m_tempature_data[2][0] =150; // Alien 3 prefered temperatures
	m_tempature_data[2][1] =100;
	m_tempature_data[2][2] =250;

	m_tempature_data[3][0] =10; // Alien 4 prefered temperatures
	m_tempature_data[3][1] =10;
	m_tempature_data[3][2] =10;

	m_tempature_data[4][0] =200; // Alien 5 prefered temperatures
	m_tempature_data[4][1] =200;
	m_tempature_data[4][2] =200;

	// Set all rooms to unocupied
	m_room_occupant[0] = MAX_ALIEN;
	m_room_occupant[1] = MAX_ALIEN;
	m_room_occupant[2] = MAX_ALIEN;
	m_room_occupant[3] = MAX_ALIEN;
	m_room_occupant[4] = MAX_ALIEN;
	m_active_alien = MAX_ALIEN;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCAlienHVACDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCAlienHVACDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCAlienHVACDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// The user has moved the mouse. 
// If there is an active alien, move it with the mouse.
void CMFCAlienHVACDlg::OnMouseMove(UINT nFlags, CPoint point)
{
    // TODO: Add your message handler code here and/or call default
	switch (m_active_alien) {
       case 0:
           m_alien1_cont.MoveWindow(point.x,point.y,ALIEN_SIZE,ALIEN_SIZE,TRUE);
           break;
       case 1:
           m_alien2_cont.MoveWindow(point.x,point.y,ALIEN_SIZE,ALIEN_SIZE,TRUE);
           break;
       case 2:
           m_alien3_cont.MoveWindow(point.x,point.y,ALIEN_SIZE,ALIEN_SIZE,TRUE);
           break;
       case 3:
           m_alien4_cont.MoveWindow(point.x,point.y,ALIEN_SIZE,ALIEN_SIZE,TRUE);
           break;
       case 4:
           m_alien5_cont.MoveWindow(point.x,point.y,ALIEN_SIZE,ALIEN_SIZE,TRUE);
           break;
	   default: 
           break;
    }
    UpdateData(FALSE);
}

// The user has released the mouse. 
// If this is the end of a drag and drop of an alien, put the alien in the proper room
void CMFCAlienHVACDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	for(int i = 0 ; i < MAX_ALIEN ; i++) // Remove the active alien form any room he might have come from
	{ 
		if(m_room_occupant[i] == m_active_alien)
		{
			m_room_occupant[i] = MAX_ALIEN;
		}
	}

	if((point.y < ROOM_BOTTOM) && (m_active_alien != MAX_ALIEN)) // The user dropped the alien in a room
	{
	   int room = (point.x - ROOM_LEFT) / ROOM_WIDTH; // Determine which room
	   if(room > MAX_ALIEN -1)
	   {
		   room = MAX_ALIEN -1;
	   }
	   if(room < 0)
	   {
		   room = 0;
	   }

	   if(m_room_occupant[room] == MAX_ALIEN) // The room is empty
	   {
		   m_room_occupant[room] = m_active_alien;
		   OnMouseMove(nFlags, CPoint((room * ROOM_WIDTH) + (ROOM_LEFT*3) ,30));
	   }
	   else // The room is occupied
	   {
		   AfxMessageBox(_T("You can not put tow people in the same room."));
		   OnMouseMove(nFlags, CPoint(point.x ,ROOM_BOTTOM + 20));
	   }	
	}

	ReleaseCapture(); // Give mouse control back
	m_active_alien = MAX_ALIEN; 
	UpdateData(TRUE);
}

// The user has pressed the mose button.
// For future enhansments
void CMFCAlienHVACDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	//AfxMessageBox(_T("Got here."));
}

// The user has pressed the Calculate button.
// Calculate the cost of the current configuration and displays it 
// a pop-up dialog and store the total in m_cost
void CMFCAlienHVACDlg::OnBnClickedButtonCalculate()
{
	int wall[4];
	int total = 0;
	for(int i = 0 ; i < MAX_ALIEN ; i++)
	{
		if(m_room_occupant[i] == MAX_ALIEN)
		{
			AfxMessageBox(_T("There can not be any empty rooms"));
			return;
		}
	}
	for(int i = 0 ; i < MAX_ALIEN-1 ; i++)
	{
		int wall1 = 10 * (int)pow((m_tempature_data[m_room_occupant[i]][0] - m_tempature_data[m_room_occupant[i+1]][0]),2);
		int wall2 = 10 * (int)pow((m_tempature_data[m_room_occupant[i]][1] - m_tempature_data[m_room_occupant[i+1]][1]),2);
		int wall3 = 10 * (int)pow((m_tempature_data[m_room_occupant[i]][2] - m_tempature_data[m_room_occupant[i+1]][2]),2);
		wall[i] = max(wall1, max(wall2,wall3));
		total += wall[i];
	}
	// TODO: Add your control notification handler code here

	CalculateDialog dlg;
	dlg.m_wall12.Format(_T("%d"), wall[0]);
	dlg.m_wall23.Format(_T("%d"), wall[1]);
	dlg.m_wall34.Format(_T("%d"), wall[2]);
	dlg.m_wall45.Format(_T("%d"), wall[3]);
	dlg.m_wall_total.Format(_T("%d"), total);

	dlg.DoModal();
	m_cost.Format(_T("%d"), total);
	UpdateData(FALSE);
}

// The user has selected an alien. Update the screen with the stats for that alien.
// Also prepare to handle mose movements.
void CMFCAlienHVACDlg::SetActiveAlien(int alien)
{
	m_active_alien = alien;
	m_temp1.Format(_T("%d"), m_tempature_data[alien][0]);
	m_temp2.Format(_T("%d"), m_tempature_data[alien][1]);
	m_temp3.Format(_T("%d"), m_tempature_data[alien][2]);
	UpdateData(FALSE);
	SetCapture();
}

//The user selected alien 1
void CMFCAlienHVACDlg::OnStnClickedAlien1()
{
	SetActiveAlien(0);
}

//The user selected alien 2
void CMFCAlienHVACDlg::OnStnClickedAlien2()
{
	SetActiveAlien(1);
}

//The user selected alien 3
void CMFCAlienHVACDlg::OnStnClickedAlien3()
{
	SetActiveAlien(2);
}

//The user selected alien 4
void CMFCAlienHVACDlg::OnStnClickedAlien4()
{
	SetActiveAlien(3);
}

//The user selected alien 5
void CMFCAlienHVACDlg::OnStnClickedAlien5()
{
	SetActiveAlien(4);
}

