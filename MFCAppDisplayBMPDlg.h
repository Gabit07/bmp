
// MFCAppDisplayBMPDlg.h : header file
//
#include "Cdib.h"
#include "../MFCAppDisplayBMP/usercontrol/dib.h"
#include "../MFCAppDisplayBMP/usercontrol/dibpal.h"

#pragma once


// CMFCAppDisplayBMPDlg dialog
class CMFCAppDisplayBMPDlg : public CDialogEx
{
// Construction
public:
	CMFCAppDisplayBMPDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPDISPLAYBMP_DIALOG };
#endif

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
public:
	afx_msg void OnBnClickedButtonOpen();

	
	int LoadBMP(CString filename);
	void _GetGUIDisplayImage(CDC* memDC);
	void _DrawPixelInfo(CDC* pDC);
	void Local2Global(int x, int y, int* x_, int* y_);
	void Global2Local(int x, int y, int* x_, int* y_);

	int m_nIMGX = 0;
	int m_nIMGY = 0;

	LPBYTE m_pImage = nullptr;
	LPBYTE m_pProcessImage = nullptr;

	int _OriX = 0; // 원점 x
	int _OriY = 0; // 원점 y
	double _dSfx = 0.0;
	double _dSfy = 0.0;

	CRect m_rect;
	CRectTracker m_rectTracker[4];

	CString m_strPath;
	CDIBPalette* m_palDIB = nullptr;;
	CDIBitmap* m_hDIB = nullptr;;
	CDib* m_pDIB = nullptr;;

	int m_nDisplayWidth = 0;
	int m_nDisplayHeight = 0;
	int m_nDisplayPitch = 0;

	CPoint m_NewPoint;
	void GetLocalPoint(CPoint point) { m_NewPoint = point; }
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};
