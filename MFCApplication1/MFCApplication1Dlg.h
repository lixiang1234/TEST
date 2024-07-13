
// MFCApplication1Dlg.h: 头文件
//

#pragma once
class CColorComboBox : public CComboBox
{
	DECLARE_DYNAMIC(CColorComboBox)

public:
	CColorComboBox();
	virtual ~CColorComboBox();

protected:
	DECLARE_MESSAGE_MAP()

public:
	int AddItem(LPCTSTR lpszText, COLORREF clrValue);
	COLORREF GetCurColor();
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
};

// CMFCApplication1Dlg 对话框
class CMFCApplication1Dlg : public CDialogEx
{
// 构造
public:
	CMFCApplication1Dlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	CReBar rebar;
	CToolBar m_ToolBar;
	CColorComboBox m_colorComboBox;
	CMFCColorPickerCtrl PickerCtrl;
	COLORREF m_Color;
	CString m_strRGBColorDialog;
	CMFCColorPickerCtrl m_wndColorPalette;
	CString m_strRGBColorPalette;
	CMFCColorPickerCtrl m_wndLum;
	CMFCColorButton m_ColorPicker;
	CStatic m_wndColorBarFrame;
	CStatic m_wndColorBarFrame2;
	CMFCColorBar m_wndColorBar;
	CPalette m_palSys;
	CMFCColorBar m_wndColorBar2;
	CPalette m_palColorPicker;
	CString m_strRGB;
	CString m_strRGBColorBar;
	CString m_strRGBColorBar2;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg void OnColorPalette();
	afx_msg void OnLum();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnColorPicker();
	afx_msg void OnColorBar();
	afx_msg void OnColorBar2();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	
};
class MyFileDialg :public CFileDialog
{
	DECLARE_DYNAMIC(MyFileDialg)
public:
	MyFileDialg(BOOL bOpenFileDialog, LPCTSTR lpszDefExt = NULL, LPCTSTR lpszFileName = NULL, DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		LPCTSTR lpszFilter = NULL, CWnd* pParentWnd = NULL, DWORD dwSize = 0, BOOL bVistaStyle = TRUE);
protected:
	LPCTSTR m_lpszDefExt;
	LPCTSTR m_lpszFileName;
	DWORD m_dwFlags;
	LPCTSTR m_lpszFilter;
	CWnd* m_pParentWnd;
	DWORD m_dwSize;
	BOOL  m_bVistaStyle;
};

