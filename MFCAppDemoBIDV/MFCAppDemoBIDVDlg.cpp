
// MFCAppDemoBIDVDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCAppDemoBIDV.h"
#include "MFCAppDemoBIDVDlg.h"
#include "afxdialogex.h"
#include <afx.h> // hoặc <windows.h> nếu chưa có
#include <atlstr.h> // để dùng CString

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern "C" {
	const wchar_t* Ecr_Init(const wchar_t* config);
	const wchar_t* Ecr_Connect(const wchar_t* posUrl, const wchar_t* config);
	bool Ecr_Connected();
	const wchar_t* Ecr_Execute(const wchar_t* cmd, const wchar_t* sessionId);
}


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCAppDemoBIDVDlg dialog



CMFCAppDemoBIDVDlg::CMFCAppDemoBIDVDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPDEMOBIDV_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCAppDemoBIDVDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCAppDemoBIDVDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CMFCAppDemoBIDVDlg message handlers

BOOL CMFCAppDemoBIDVDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	abc();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCAppDemoBIDVDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCAppDemoBIDVDlg::OnPaint()
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
HCURSOR CMFCAppDemoBIDVDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


/// <summary>
/// 2025-07-31 LeThanhYen Demo Connect POS BIDV
/// </summary>
/// <returns></returns>
bool CMFCAppDemoBIDVDlg::abc()
{
	typedef const wchar_t* (*ECR_INIT)(const wchar_t*);
	typedef const wchar_t* (*ECR_CONNECT)(const wchar_t*, const wchar_t*);
	typedef bool (*ECR_CONNECTED)();
	typedef const wchar_t* (*ECR_EXECUTE)(const wchar_t*, const wchar_t*);

	HINSTANCE hBridge = LoadLibrary(L"EcrBridge.dll");
	if (!hBridge) {
		OutputDebugString(L"Khong load duoc EcrBridge.dll\n");
		return FALSE;
	}

	ECR_INIT      pEcr_Init = (ECR_INIT)GetProcAddress(hBridge, "Ecr_Init");
	ECR_CONNECT   pEcr_Connect = (ECR_CONNECT)GetProcAddress(hBridge, "Ecr_Connect");
	ECR_CONNECTED pEcr_Connected = (ECR_CONNECTED)GetProcAddress(hBridge, "Ecr_Connected");
	ECR_EXECUTE   pEcr_Execute = (ECR_EXECUTE)GetProcAddress(hBridge, "Ecr_Execute");

	if (!pEcr_Init || !pEcr_Connect || !pEcr_Connected || !pEcr_Execute) {
		OutputDebugString(L"Lay dia chi ham trong DLL loi\n");
		FreeLibrary(hBridge);
		return FALSE;
	}

	CStringW config = L"{\"merchantName\":\"BIDV\",\"cashierId\":\"A123\",\"licenseForBIDV\":\"name=BIDV;bank=BIDV;copyright=Use for BIDV only;signature=88CAEA5A652C9D07A215115D2DE65242EA3F16A989C7415E26FF78909EDB4E10;expiryDate=2025-12-31;encryption=yes;encoding=base64;userConfirmation=yes;version=20;LCV=6B8D23\"}";
	CStringW posUrl = L"http://192.168.1.43:8080";

	OutputDebugString(L"Truoc Init\n");
	const wchar_t* resInit = pEcr_Init(config);
	OutputDebugString(L"Sau Init: ");
	OutputDebugString(resInit); OutputDebugString(L"\n");

	OutputDebugString(L"Truoc Connect\n");
	const wchar_t* resConnect = pEcr_Connect(posUrl, config);
	OutputDebugString(L"Sau Connect: ");
	OutputDebugString(resConnect); OutputDebugString(L"\n");

	OutputDebugString(L"Truoc Check Connected\n");
	bool isConnected = pEcr_Connected();
	CStringW connLog;
	connLog.Format(L"Check Connected: %d\n", isConnected ? 1 : 0);
	OutputDebugString(connLog);

	if (isConnected) {
		CStringW saleCmd = L"{\"command\":\"sale\",\"params\":{\"amount\":\"125000000\",\"currency\":\"704\"}}";
		OutputDebugString(L"Truoc Execute (sale)\n");
		const wchar_t* resSale = pEcr_Execute(saleCmd, NULL);
		OutputDebugString(L"Sau Execute (sale): ");
		OutputDebugString(resSale); OutputDebugString(L"\n");
	}
	else {
		OutputDebugString(L"Chua ket noi duoc toi may POS!\n");
	}

	FreeLibrary(hBridge);
	OutputDebugString(L"Ket thuc ham abc\n");
	return TRUE;
}


