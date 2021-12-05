
// MFCAppDisplayBMPDlg.cpp : implementation file
//


#include "pch.h"
#include "framework.h"
#include "MFCAppDisplayBMP.h"
#include "MFCAppDisplayBMPDlg.h"
#include "afxdialogex.h"


#include "common/CommonDefine.h"
#include <vector>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CMFCAppDisplayBMPDlg dialog



CMFCAppDisplayBMPDlg::CMFCAppDisplayBMPDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPDISPLAYBMP_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCAppDisplayBMPDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCAppDisplayBMPDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CMFCAppDisplayBMPDlg::OnBnClickedButtonOpen)
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CMFCAppDisplayBMPDlg message handlers

BOOL CMFCAppDisplayBMPDlg::OnInitDialog()
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

	// TODO: Add extra initialization here


	m_nIMGX = IMAGE_BUFFER_SIZE_X;
	m_nIMGY = IMAGE_BUFFER_SIZE_Y;

	if (!m_pDIB)
	{
		m_pDIB = new CDib();

	}
	if (!m_hDIB)
	{
		m_hDIB = new CDIBitmap;
		m_hDIB->MakeGrayImage(m_nIMGX, m_nIMGY);
	}

	if (!m_palDIB)
	{
		m_palDIB = new CDIBPalette;
		m_palDIB->CreatePal(m_hDIB);
	}

	if (!m_pImage)
	{
		m_pImage = new BYTE[IMAGE_BUFFER_SIZE_X * IMAGE_BUFFER_SIZE_Y];
		memset(m_pImage, 0, sizeof(BYTE) * IMAGE_BUFFER_SIZE_X * IMAGE_BUFFER_SIZE_Y);
	}
	if (!m_pProcessImage)
	{
		m_pProcessImage = new BYTE[IMAGE_BUFFER_SIZE_X * IMAGE_BUFFER_SIZE_Y];
		memset(m_pProcessImage, 0, sizeof(BYTE) * IMAGE_BUFFER_SIZE_X * IMAGE_BUFFER_SIZE_Y);
	}

	//_FitZoom();

	//reset();


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCAppDisplayBMPDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCAppDisplayBMPDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	if (IsIconic())
	{
		

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

		//CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.

		//dc.Rectangle(0, 0, 200, 100);
		CRect rect;

		this->GetClientRect(&rect);

		CDC memDC;

		CBitmap* pOldBmp;
		CBitmap bitmap;

		memDC.CreateCompatibleDC(&dc);
		bitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
		pOldBmp = memDC.SelectObject(&bitmap);

		_GetGUIDisplayImage(&memDC);
		//_DrowROI(&memDC, rect);
		_DrawPixelInfo(&memDC);


		dc.BitBlt(rect.left, rect.top, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);
		memDC.SelectObject(pOldBmp);
		memDC.DeleteDC();

		//dc.TextOut(50, 50, _T("fdffd"));

	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCAppDisplayBMPDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCAppDisplayBMPDlg::OnBnClickedButtonOpen()
{
	// TODO: Add your control notification handler code here
	CFileDialog dlg(TRUE, _T("bmp"), _T("*.bmp"));

	if (dlg.DoModal() != IDOK)
		return;

	LoadBMP(dlg.GetPathName());

	

	//Invalidate();

}

int CMFCAppDisplayBMPDlg::LoadBMP(CString filename)
{
	int i, j, ret = 1;
	int nByte, pitchBMP;
	CFile file;
	CDib* pdib = NULL;
	//LPBYTE fmS, fmD;
	CString str;

	if (!file.Open(filename, CFile::modeRead)) goto done;

	pdib = new CDib();

	if (pdib->Read(&file) == TRUE)
	{
		file.Close();

		ret = 0;

		if (pdib->m_lpBMIH->biHeight > m_nIMGY || pdib->m_lpBMIH->biWidth > m_nIMGX)
		{
			str.Format(_T("Image Size must be X<%d Y<%d (X=%d, Y=%d)"), m_nIMGX, m_nIMGY, pdib->m_lpBMIH->biWidth, pdib->m_lpBMIH->biHeight);
			AfxMessageBox(str);
			goto done;
		}

		if (pdib->m_lpBMIH->biHeight <= m_nIMGY && pdib->m_lpBMIH->biWidth <= m_nIMGX)
		{
			nByte = pdib->m_lpBMIH->biBitCount / 8;

			pitchBMP = ((DWORD)pdib->m_lpBMIH->biWidth * nByte * 8) / 32;
			if (((DWORD)pdib->m_lpBMIH->biWidth * nByte * 8) % 32) 	pitchBMP++;
			pitchBMP *= 4;

			memset(m_pImage, 0, m_nIMGX * m_nIMGY);

			for (i = 0; i < pdib->m_lpBMIH->biHeight; i++)
				for (j = 0; j < pdib->m_lpBMIH->biWidth; j++)
					*(m_pImage + m_nIMGX * i + j) = *(pdib->m_lpImage + pitchBMP * (pdib->m_lpBMIH->biHeight - 1 - i) + j);

			memcpy(m_pProcessImage, m_pImage, m_nIMGX * m_nIMGY);
		}
	}
	else
	{
		ret = 1;
		file.Close();
		goto done;
	}

done:
	if (pdib) delete pdib;

	Invalidate();

	return ret;
}

void CMFCAppDisplayBMPDlg::_GetGUIDisplayImage(CDC* memDC)
{
	int i, j;
	int left, top, right, bottom;
	int left_, top_, right_, bottom_;
	int nImageWidth, nImageHeight;
	int nGUIWidth, nGUIHeight;
	int width, height;          //화면에 Display하려고하는 폭 
	double dMultix, dMultiy;
	RECT rc;

	if (_dSfx == 0) { _dSfx = 1; _dSfy = 1; }

	CSize cz;
	LPBYTE fmT = NULL;

	nImageWidth = int(m_nIMGX * _dSfx);
	nImageHeight = int(m_nIMGY * _dSfy);
	GetClientRect(&rc);
	nGUIWidth = rc.right - rc.left;
	nGUIHeight = rc.bottom - rc.top;

	if (nGUIWidth >= nImageWidth && nGUIHeight >= nImageHeight)
	{
		left = 0; top = 0;
		right = nImageWidth;
		bottom = nImageHeight;

		width = right - left;
		height = bottom - top;
	}
	else
	{
		left = 0; top = 0;
		Local2Global(left, top, &left_, &top_);
		if (left_ < 0) left_ = 0;
		if (top_ < 0) top_ = 0;

		right = nGUIWidth - 1;
		bottom = nGUIHeight - 1;
		Local2Global(right, bottom, &right_, &bottom_);
		if (right_ >= m_nIMGX) right_ = m_nIMGX - 1;
		if (bottom_ >= m_nIMGY) bottom_ = m_nIMGY - 1;

		width = right - left;
		height = bottom - top;

		left = left_;
		top = top_;
		right = right_;
		bottom = bottom_;
	}

	if (left + width / _dSfx > m_nIMGX)	width = int((m_nIMGX - left) * _dSfx);
	if (top + height / _dSfy > m_nIMGY)  height = int((m_nIMGY - top) * _dSfy);

	if (m_pDIB == NULL || m_nDisplayWidth != width || m_nDisplayHeight != height)
	{
		if (width <= 0 || height <= 0) return;

		m_nDisplayWidth = width;
		if (width % 4)
			cz.cx = width + 4 - width % 4;
		else
			cz.cx = width;
		cz.cy = m_nDisplayHeight = height;

		m_nDisplayPitch = ((DWORD)cz.cx * 8) / 32;
		if (((DWORD)cz.cx * 8) % 32) 	m_nDisplayPitch++;
		m_nDisplayPitch *= 4;


		if (m_nDisplayPitch > width)
		{
			m_nDisplayPitch -= 4;
			m_nDisplayWidth = cz.cx = width = m_nDisplayPitch;
		}

		if (m_pDIB) delete m_pDIB;
		m_pDIB = new CDib(cz, 8);
	}

	dMultix = 1 / _dSfx;
	dMultiy = 1 / _dSfy;

	fmT = m_pDIB->m_lpImage;

	for (i = 0; i < height; i++)
		for (j = 0; j < width; j++)
			*(fmT + m_nDisplayPitch * static_cast<int>(m_nDisplayHeight - 1 - i) + j) = *(m_pProcessImage + m_nIMGX * static_cast<int>(top + i * dMultiy) + static_cast<int>(left + j * dMultix));

	if (m_pDIB)
	{
		m_pDIB->UsePalette(memDC);
		m_pDIB->Draw(memDC, CPoint(0, 0), CSize(m_nDisplayWidth, m_nDisplayHeight));
	}

}

//Dialog FOV 영역이 실제 이미지에서 어디인지 구하는 함수 
void CMFCAppDisplayBMPDlg::Local2Global(int x, int y, int* x_, int* y_)
{
	*x_ = int((x - _OriX) / _dSfx);
	*y_ = int((y - _OriY) / _dSfy);
}

//실제이미지의 위치를 Display되는 영역에서의 위치로 환산 
void CMFCAppDisplayBMPDlg::Global2Local(int x, int y, int* x_, int* y_)
{
	*x_ = int(x * _dSfx + _OriX);
	*y_ = int(y * _dSfy + _OriY);
}

void CMFCAppDisplayBMPDlg::_DrawPixelInfo(CDC* pDC)
{
	CRect rect;
	GetClientRect(rect);

	if (pDC == NULL) pDC = GetDC();

	int x = 0, y = 0;
	Local2Global(m_NewPoint.x, m_NewPoint.y, &x, &y);

	if (x < 0 || y < 0) return;
	if (x >= IMAGE_BUFFER_SIZE_X || y >= IMAGE_BUFFER_SIZE_Y) return;

	CPen* oldPen = NULL, newPen;

	pDC->SelectStockObject(NULL_BRUSH);
	pDC->SetBkMode(TRANSPARENT);

	int nVal = *(m_pImage + m_nIMGX * y + x);
	CString str;
	str.Format(_T("X:%d Y:%d Gray:%d"), x, y, nVal);


	pDC->SetTextColor(RGB(0, 255, 0));
	pDC->TextOutW(rect.left + 10, rect.top + 10, str);


	ReleaseDC(pDC);

}

void CMFCAppDisplayBMPDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	

	CDialogEx::OnMouseMove(nFlags, point);
}
