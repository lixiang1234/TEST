#pragma once
#include<afxwin.h>
#include<afxcmn.h>
#include<afxcview.h>
#include<afxext.h>
#include<afxshellmanager.h>
#include<afxshelllistCtrl.h>
#include<afxDockablePane.h>
#include "afxdialogex.h"
#include<afxribbonbar.h>
#include<afxext.h>
#include<afxcontextmenumanager.h>
#include <afxmenubar.h>
#include<afxDockablePaneAdapter.h>
#include <afxcolorpickerctrl.h>
#include <afxcolorbutton.h>
class CObjectToolBar : public CMFCToolBar
{
public:
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*)GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
	
	
};
class CObjectDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CObjectDlg)

public:
	CObjectDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CObjectDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
class CMyDockablePane :public CDockablePane
{
public:
	CMyDockablePane(void);
	~CMyDockablePane(void);
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void AdjustLayout();
	afx_msg void OnDestroy();
	// 定义三个控件
	CEdit m_edit;
	CStatic m_static;
	CObjectDlg m_objectDlg;
	CObjectToolBar m_wndToolBar;//工具条对象
};

class CMyListCtrl :public CListCtrl
{
	DECLARE_DYNAMIC(CMyListCtrl)
public:
	CMyListCtrl();
	afx_msg void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	~CMyListCtrl();
	DECLARE_MESSAGE_MAP()
	POSITION pos;
protected:
	CBrush m_myCustomBrush;	
	afx_msg void OnClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdraw(NMHDR* pNMHDR, LRESULT* pResult);
};
class CMyListBox1 :public CListBox
{	
	DECLARE_DYNAMIC(CMyListBox1)
public:
	CMyListBox1();
	afx_msg void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	~CMyListBox1();
protected:
	int        m_itemHeight;
	CRect            m_itemBound;
	int        m_leftOffset;
	int        m_topOffset;
	DECLARE_MESSAGE_MAP()
};
class CMyBar :public CStatusBar {
	
public:
	void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	
};
class CMyComboBox :public CComboBox
{
	DECLARE_DYNAMIC(CMyComboBox)
public:
	CMyComboBox();
	void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	 void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	CImageList* GetImageList() const;
	void* GetItemDataPtr(int nIndex) const;
	int AddString(LPCTSTR lpszString, int nImageIndex);
	void SetImageList(CImageList* pImageList);
	//int CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct);
public:
	CImageList* m_pImageList;
	CSize      m_imageSize;
	unsigned int  m_nEditHeight;
	int m_iIsDropList;
	struct CBDataXI
	{
		// 图像序号,如果为-1,则表示无图像
		int iImageIndex;
		
		// 关联数据的指针
		LPVOID pData;
		
		CBDataXI()
		{
			iImageIndex = -1;
			pData = NULL;
		}
	};

};
class MyFileDialg :public CFileDialog
{
	DECLARE_DYNAMIC(MyFileDialg)
public:
	MyFileDialg(BOOL bOpenFileDialog,LPCTSTR lpszDefExt = NULL,LPCTSTR lpszFileName = NULL,DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		LPCTSTR lpszFilter = NULL,CWnd* pParentWnd = NULL,DWORD dwSize = 0,BOOL bVistaStyle = TRUE);
	virtual void OnButtonClicked(DWORD dwIDCtl);
	virtual void OnCheckButtonToggled(DWORD dwIDCtl, BOOL bChecked);
	virtual void OnControlActivating (DWORD dwIDCtl);
	virtual void OnFileNameChange();
	virtual void OnFolderChange();
	virtual void OnInitDone();
	virtual void OnItemSelected(DWORD dwIDCtl,DWORD dwIDItem);
	virtual void OnTypeChange();
	virtual BOOL OnFileNameOK();

protected:
	LPCTSTR m_lpszDefExt;
	LPCTSTR m_lpszFileName;
	DWORD m_dwFlags;
	LPCTSTR m_lpszFilter;
	CWnd* m_pParentWnd; 
	DWORD m_dwSize;
	BOOL  m_bVistaStyle;
};
class CMyApp :public CWinApp {
public :
	BOOL  m_bHiColorIcons;
public:
	virtual BOOL InitInstance();
	
};
class CMainWindow :public CFrameWnd
{
public:
	CMainWindow();
protected:
	CMyListCtrl mylist;
	CButton mybuttom, Delbuttom, DrawItemButton, bkgroundButtom, BKGImageButtom,
		DelAllItemsButtom, ItemIndexRectButtom, AddItemBuytton,PUSHWINDOWS,ColorButton,colorButton2;
	CProgressCtrl progress;
	CImageList imagelist,imagelist2;
	CMyBar CStatusBar;
	//CMyList list;
	CSpinButtonCtrl CsplitButton;
	CSplitButton sbutton;
	CMyComboBox combobox;
	CMyListBox1 m_listBox;
	CMenu m_Menu,FileMenu,m_menu2, * pContextMenu;
	CMFCMenuBar  m_wndMenuBar;
	CMyDockablePane Pane;
	CToolBar m_ToolBar;
	CMFCShellListCtrl ShellListCtrl;
	CObjectToolBar CMyTOOL;
	CTreeCtrl m_TreeCrtl;
	CToolBarCtrl M_TOOLBarCtrl;
	CBitmap m_bmpToolBar;
	int nCOUNT, nCurrPos,NextPos;
	CDialogBar dialogBar;
	CMFCRibbonBar m_RibbonBar;
	CReBar rebar;
	BOOL state,state2,state3;
	POSITION pos1;
	CBrush m_myCustomBrush;

	COLORREF m_Color;
	CString m_strRGBColorDialog;
	CMFCColorPickerCtrl m_wndColorPalette;
	CString m_strRGBColorPalette;
	CMFCColorPickerCtrl m_wndLum;
	CStatic m_wndColorBarFrame;
	CStatic m_wndColorBarFrame2;
	CMFCColorBar m_wndColorBar;
	CPalette m_palSys;
	CMFCColorButton m_ColorPicker;
	
protected:
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCrestestruct);
	afx_msg void OnMybutton();
	afx_msg void OnDeleteColumn();
	afx_msg void OnDrawItem();
	afx_msg void OnGBKbutton();
	afx_msg void OnGKImage();
	afx_msg void OnDelallItem();
	afx_msg void OnGetItemIndexRect();
	afx_msg void OnNMDoubleClickList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMDBoubleClickList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnAddItem();
	afx_msg void OnPushWIndows();
	afx_msg void OnButton40010();
	afx_msg void OnToolbar();
	afx_msg void OnButton2();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint pos);
	afx_msg void Open();
	afx_msg void SavaAs();
	afx_msg void OnColorPalette();
	afx_msg void OnLum();
	void OpenFile();
	void GetColumnOrderArray();
	void GetEditControl();
	void DrawItem();
	void InsertItem();
	void MapIndexToID();
	void Arrange();
	void GetItemData();
	void GetInsertMark();
	
	UINT ThreadFunc(LPVOID Pparam);
	//virtual BOOL OnInitApp();
	DECLARE_MESSAGE_MAP()
	virtual void DoDataExchange(CDataExchange* pDX);	
public:
	afx_msg void OnButton40070();
	afx_msg void OnUpdateButton40070(CCmdUI* pCmdUI);
	afx_msg void OnUpdateButton40010(CCmdUI* pCmdUI);
	afx_msg void OnButton40011();
	afx_msg void OnUpdateButton40011(CCmdUI* pCmdUI);
};
typedef struct sData
{
	char PlayerName[50];
	char JerseyNumber[255];
}SDATA;