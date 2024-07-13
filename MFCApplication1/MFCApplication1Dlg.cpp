
// MFCApplication1Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define IDC_TOOLBAR1 122
#define MAX_CFileDialog_FILE_COUNT 99
#define FILE_LIST_BUFFER_SIZE ((MAX_CFileDialog_FILE_COUNT * (MAX_PATH + 1)) + 1)
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CMFCApplication1Dlg 对话框



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_Color = RGB(255, 0, 255);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO2, m_colorComboBox);
	DDX_Control(pDX, IDC_LUM, m_wndLum);
	DDX_Control(pDX, IDC_COLOR_PALETTE, m_wndColorPalette);
	//DDX_Control(pDX, IDC_COLORBAR2, m_wndColorBarFrame2);
	//DDX_Control(pDX, IDC_COLORBAR, m_wndColorBarFrame);
	//DDX_Control(pDX, IDC_COLOR_PICKER, m_ColorPicker);
	//DDX_Text(pDX, IDC_RGB, m_strRGB);
	//DDX_Text(pDX, IDC_RGB_COLOR_BAR, m_strRGBColorBar);
	//DDX_Text(pDX, IDC_RGB_COLOR_BAR2, m_strRGBColorBar2);
	//DDX_Text(pDX, IDC_RGB_DLG, m_strRGBColorDialog);
	DDX_Text(pDX, IDC_RGB_COLOR_PALETTE, m_strRGBColorPalette);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//ON_BN_CLICKED(IDC_COLOR_DLG, OnColorDlg)
	ON_BN_CLICKED(IDC_COLOR_PICKER, OnColorPicker)
	ON_BN_CLICKED(IDC_COLOR_PALETTE, OnColorPalette)
	ON_BN_CLICKED(IDC_LUM, OnLum)
	ON_COMMAND(IDC_COLORBAR, OnColorBar)
	ON_COMMAND(IDC_COLORBAR2, OnColorBar2)
	ON_BN_CLICKED(IDOK, &CMFCApplication1Dlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CMFCApplication1Dlg 消息处理程序

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	if (!m_ToolBar.Create(this, WS_CHILD | WS_VISIBLE | CBRS_TOP, IDC_TOOLBAR1) || !m_ToolBar.LoadToolBar(IDR_TOOLBAR2))
	{
		TRACE0("创建失败");
		//return FALSE;

	}
	m_ToolBar.LoadToolBar(IDR_TOOLBAR2);
	//m_ToolBar.EnableDocking(CBRS_ALIGN_ANY);
	//RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);
	// TODO: 在此添加额外的初始化代码
	if (!rebar.Create(this, RBS_BANDBORDERS, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_TOP,ID_Raber))
		TRACE0("rebar Creation failed!!!");
	rebar.AddBar(&m_ToolBar);
	rebar.SetWindowPos(NULL, 0, 70, 500, 40, SWP_SHOWWINDOW);
	rebar.RedrawWindow();
	REBARBANDINFO info;
	info.cbSize = sizeof(info);
	info.fMask = RBBIM_BACKGROUND;
	m_ToolBar.ModifyStyle(0, TBSTYLE_TRANSPARENT);//设置工具栏背景色透明
	info.hbmBack = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP1));//加载位图
	rebar.GetReBarCtrl().SetBandInfo(0, &info);
	//CMFCColorPickerCtrl Picker = new CMFCColorPickerCtrl();
	m_colorComboBox.AddItem(_T("淡紫"), RGB(202, 111, 255));
	m_colorComboBox.AddItem(_T("淡蓝"), RGB(202, 224, 245));
	m_colorComboBox.AddItem(_T("天蓝"), RGB(68, 159, 245));
	m_colorComboBox.AddItem(_T("红色"), RGB(255, 0, 0));
	m_colorComboBox.AddItem(_T("蓝色"), RGB(0, 0, 255));
	m_colorComboBox.AddItem(_T("绿色"), RGB(0, 255, 0));
	m_colorComboBox.AddItem(_T("黄色"), RGB(255, 255, 0));
	m_colorComboBox.AddItem(_T("粉色"), RGB(255, 0, 255));
	m_colorComboBox.AddItem(_T("棕色"), RGB(255, 128, 64));
	m_colorComboBox.SetCurSel(0);
	m_ColorPicker.EnableAutomaticButton(_T("Automatic"), RGB(255, 0, 255));
	m_ColorPicker.EnableOtherButton(_T("Other"));
	m_ColorPicker.SetColor((COLORREF)-1);
	m_ColorPicker.SetColumnsNumber(10);

	// Create regular color bar:
	CRect rectColorBar;
	m_wndColorBarFrame.GetClientRect(&rectColorBar);
	m_wndColorBarFrame.MapWindowPoints(this, &rectColorBar);

	m_wndColorBar.SetHorzMargin(0);
	m_wndColorBar.SetVertMargin(0);
	m_wndColorBar.EnableOtherButton(_T("Other..."));

	m_wndColorBar.CreateControl(this, rectColorBar, IDC_COLORBAR, 5 /* columns */);
	m_wndColorBar.SetColor(RGB(0, 0, 0));

	// Create regular color bar with the custom palette:
	m_wndColorBarFrame2.GetClientRect(&rectColorBar);
	m_wndColorBarFrame2.MapWindowPoints(this, &rectColorBar);
#define NUM_COLOURS 64
	struct
	{
		LOGPALETTE    LogPalette;
		PALETTEENTRY  PalEntry[NUM_COLOURS];
	}pal;

	LOGPALETTE* pLogPalette = (LOGPALETTE*)&pal;
	pLogPalette->palVersion = 0x300;
	pLogPalette->palNumEntries = (WORD)NUM_COLOURS;

	COLORREF colorStart = RGB(0, 0, 255);
	COLORREF colorFinish = RGB(255, 255, 255);

	int nShift = 6;
	for (int i = 0; i < NUM_COLOURS; i++)
	{
		BYTE bR = (BYTE)((GetRValue(colorStart) * (NUM_COLOURS - i) + GetRValue(colorFinish) * i) >> nShift);
		BYTE bG = (BYTE)((GetGValue(colorStart) * (NUM_COLOURS - i) + GetGValue(colorFinish) * i) >> nShift);
		BYTE bB = (BYTE)((GetBValue(colorStart) * (NUM_COLOURS - i) + GetBValue(colorFinish) * i) >> nShift);

		pLogPalette->palPalEntry[i].peRed = bR;
		pLogPalette->palPalEntry[i].peGreen = bG;
		pLogPalette->palPalEntry[i].peBlue = bB;
		pLogPalette->palPalEntry[i].peFlags = 0;
	}

	m_palColorPicker.CreatePalette(pLogPalette);
	m_wndColorBar2.SetHorzMargin(0);
	m_wndColorBar2.SetVertMargin(0);

	m_wndColorBar2.CreateControl(this, rectColorBar, IDC_COLORBAR2, -1 /* columns */, &m_palColorPicker);
	m_wndColorBar2.SetColor(colorStart);

	// Create system palette:
	CClientDC dc(this);

	int nColors = 256; // Use 256 first entries
	UINT nSize = sizeof(LOGPALETTE) + (sizeof(PALETTEENTRY) * nColors);
	LOGPALETTE* pLP = (LOGPALETTE*) new BYTE[nSize];

	pLP->palVersion = 0x300;
	pLP->palNumEntries = (USHORT)nColors;

	::GetSystemPaletteEntries(dc.GetSafeHdc(), 0, nColors, pLP->palPalEntry);
	
	m_palSys.CreatePalette(pLP);

	delete[] pLP;

	m_wndColorPalette.SetType(CMFCColorPickerCtrl::PICKER);
	m_wndColorPalette.SetPalette(&m_palSys);
	m_wndColorPalette.SetColor(RGB(0, 255, 0));

	m_wndLum.SetType(CMFCColorPickerCtrl::LUMINANCE);
	m_wndLum.SetPalette(&m_palSys);
	m_wndLum.SetColor(RGB(0, 255, 0));

	UpdateData(FALSE);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

void CMFCApplication1Dlg::OnColorPalette()
{
	COLORREF color = m_wndColorPalette.GetColor();

	m_strRGBColorPalette.Format(_T("%d,%d,%d"), GetRValue(color), GetGValue(color), GetBValue(color));

	m_wndLum.SetColor(color);
	UpdateData(FALSE);
}

void CMFCApplication1Dlg::OnLum()
{
	COLORREF color = m_wndLum.GetColor();

	m_strRGBColorPalette.Format(_T("%d,%d,%d"), GetRValue(color), GetGValue(color), GetBValue(color));

	m_wndColorPalette.SetLuminance(m_wndLum.GetLuminance());
	UpdateData(FALSE);
}
void CMFCApplication1Dlg::OnColorPicker()
{
	COLORREF color = m_ColorPicker.GetColor();
	if (color == -1)
	{
		color = m_ColorPicker.GetAutomaticColor();
	}

	m_strRGB.Format(_T("%d,%d,%d"), GetRValue(color), GetGValue(color), GetBValue(color));

	UpdateData(FALSE);
}

void CMFCApplication1Dlg::OnColorBar()
{
	COLORREF color = m_wndColorBar.GetColor();

	m_strRGBColorBar.Format(_T("%d,%d,%d"), GetRValue(color), GetGValue(color), GetBValue(color));

	UpdateData(FALSE);
}

void CMFCApplication1Dlg::OnColorBar2()
{
	COLORREF color = m_wndColorBar2.GetColor();

	m_strRGBColorBar2.Format(_T("%d,%d,%d"), GetRValue(color), GetGValue(color), GetBValue(color));

	UpdateData(FALSE);
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
IMPLEMENT_DYNAMIC(MyFileDialg, CFileDialog)
MyFileDialg::MyFileDialg(BOOL bOpenFileDialog, LPCTSTR lpszDefExt, LPCTSTR lpszFileName, DWORD dwFlags, LPCTSTR lpszFilter, CWnd* pParentWnd, DWORD dwSize, BOOL bVistaStyle)
	:CFileDialog(bOpenFileDialog, lpszDefExt, lpszFileName, dwFlags, lpszFilter, pParentWnd, dwSize, bVistaStyle)
{
	this->m_bOpenFileDialog = bOpenFileDialog;
	this->m_lpszDefExt = lpszDefExt;
	this->m_lpszFileName = lpszFileName;
	this->m_dwFlags = dwFlags;
	this->m_lpszFilter = lpszFilter;
	this->m_pParentWnd = pParentWnd;
	this->m_dwSize = dwSize;
	this->m_bVistaStyle = m_bVistaStyle;
}

void CMFCApplication1Dlg::OnBnClickedOk()
{
	CMFCColorDialog dlg(m_Color, 0, this);
	if (dlg.DoModal() == IDOK)
	{
		m_Color = dlg.GetColor();

		m_strRGBColorDialog.Format(_T("%d,%d,%d"), GetRValue(m_Color), GetGValue(m_Color), GetBValue(m_Color));

		UpdateData(FALSE);
	}
	// TODO: 在此添加控件通知处理程序代码
	
}
IMPLEMENT_DYNAMIC(CColorComboBox, CComboBox)

CColorComboBox::CColorComboBox()
{

}

CColorComboBox::~CColorComboBox()
{
}


BEGIN_MESSAGE_MAP(CColorComboBox, CComboBox)
END_MESSAGE_MAP()
int CColorComboBox::AddItem(LPCTSTR lpszText, COLORREF clrValue)
{
	int nIndex = AddString(lpszText);
	SetItemData(nIndex, clrValue);
	return nIndex;
}


COLORREF CColorComboBox::GetCurColor()
{
	int nIndex = GetCurSel();
	if (nIndex != -1)
	{
		return GetItemData(nIndex);
	}
	else
	{
		return -1;
	}
}


void CColorComboBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO:  添加您的代码以绘制指定项
	//验证是否为组合框控件
	ASSERT(lpDrawItemStruct->CtlType == ODT_COMBOBOX);
	CDC dc;
	dc.Attach(lpDrawItemStruct->hDC);

	//获取项目区域
	CRect itemRC(lpDrawItemStruct->rcItem);
	//定义显示颜色的区域
	CRect clrRC = itemRC;
	//定义文本区域
	CRect textRC = itemRC;
	//获取系统文本颜色
	COLORREF clrText = GetSysColor(COLOR_WINDOWTEXT);
	//选中时的文本颜色
	COLORREF clrSelected = GetSysColor(COLOR_HIGHLIGHT);
	//获取窗口背景颜色
	COLORREF clrNormal = GetSysColor(COLOR_WINDOW);
	//获取当前项目索引
	int nIndex = lpDrawItemStruct->itemID;
	//判断项目状态
	int nState = lpDrawItemStruct->itemState;
	if (nState & ODS_SELECTED)	//处于选中状态
	{
		dc.SetTextColor((0x00FFFFFF & ~(clrText)));		//文本颜色取反
		dc.SetBkColor(clrSelected);						//设置文本背景颜色
		dc.FillSolidRect(&clrRC, clrSelected);			//填充项目区域为高亮效果
	}
	else
	{
		dc.SetTextColor(clrText);						//设置正常的文本颜色
		dc.SetBkColor(clrNormal);						//设置正常的文本背景颜色
		dc.FillSolidRect(&clrRC, clrNormal);
	}
	if (nState & ODS_FOCUS)								//如果项目获取焦点，绘制焦点区域
	{
		dc.DrawFocusRect(&itemRC);
	}

	//计算文本区域
	int nclrWidth = itemRC.Width() / 4;
	textRC.left = nclrWidth + 55;

	//计算颜色显示区域
	clrRC.DeflateRect(2, 2);
	clrRC.right = nclrWidth + 50;


	//绘制颜色文本并且填充颜色区域
	if (nIndex != -1)	//项目不为空
	{
		//获取项目颜色
		COLORREF clrItem = GetItemData(nIndex);
		dc.SetBkMode(TRANSPARENT);
		//获取文本
		CString szText;
		GetLBText(nIndex, szText);
		//输出文本
		dc.DrawText(szText, textRC, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
		dc.FillSolidRect(&clrRC, clrItem);
		//输出颜色
		dc.FrameRect(&clrRC, &CBrush(RGB(0, 0, 0)));
	}
	dc.Detach();
}
