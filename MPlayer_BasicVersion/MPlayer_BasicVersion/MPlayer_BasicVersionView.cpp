
// MPlayer_BasicVersionView.cpp: CMPlayerBasicVersionView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MPlayer_BasicVersion.h"
#endif

#include "MPlayer_BasicVersionDoc.h"
#include "MPlayer_BasicVersionView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//三个全局变量
HWND m_hWnd;
DWORD DeviceId;
tagMCI_OPEN_PARMSA mciOpenMusic;
// CMPlayerBasicVersionView
void Load(HWND hWnd, CString strFilepath)
{
	m_hWnd = hWnd;
	mciSendCommand(DeviceId, MCI_CLOSE, 0, 0);	//在加载文件前清空上次播放的音乐
	mciOpenMusic.lpstrElementName = strFilepath;//将音乐文件路径穿给设备
	DWORD dwReturn;
	if (dwReturn = mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_WAIT, (DWORD)(LPVOID)(&mciOpenMusic)))
	{
		char buffer[256];
		mciGetErrorString(dwReturn, buffer, 256);
	}
	DeviceId = mciOpenMusic.wDeviceID;
}
IMPLEMENT_DYNCREATE(CMPlayerBasicVersionView, CView)

BEGIN_MESSAGE_MAP(CMPlayerBasicVersionView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMPlayerBasicVersionView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_FILE_NEW, &CMPlayerBasicVersionView::OnFileNew)
	ON_WM_CREATE()
//	ON_BN_CLICKED(IDC_PLAY, OnClickPlayMusic)
ON_COMMAND(ID_32772, &CMPlayerBasicVersionView::OnAddFileFolder)
ON_WM_CREATE()
END_MESSAGE_MAP()

// CMPlayerBasicVersionView 构造/析构

CMPlayerBasicVersionView::CMPlayerBasicVersionView() noexcept
{
	// TODO: 在此处添加构造代码
	m_DeviceID = 0;
	m_PathOfMusicDoc =NULL;
//	m_NameOfMusicDoc = NULL;

}

CMPlayerBasicVersionView::~CMPlayerBasicVersionView()
{
}

BOOL CMPlayerBasicVersionView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMPlayerBasicVersionView 绘图

void CMPlayerBasicVersionView::OnDraw(CDC* /*pDC*/)
{
	CMPlayerBasicVersionDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CMPlayerBasicVersionView 打印


void CMPlayerBasicVersionView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMPlayerBasicVersionView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMPlayerBasicVersionView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMPlayerBasicVersionView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CMPlayerBasicVersionView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMPlayerBasicVersionView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMPlayerBasicVersionView 诊断

#ifdef _DEBUG
void CMPlayerBasicVersionView::AssertValid() const
{
	CView::AssertValid();
}

void CMPlayerBasicVersionView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMPlayerBasicVersionDoc* CMPlayerBasicVersionView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMPlayerBasicVersionDoc)));
	return (CMPlayerBasicVersionDoc*)m_pDocument;
}
#endif //_DEBUG


// CMPlayerBasicVersionView 消息处理程序


void CMPlayerBasicVersionView::OnFileNew()
{
	// TODO: 在此添加命令处理程序代码
	//打开文件管理器，选择歌曲
	//读取歌曲路径
	CFileDialog DocSelectDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT|OFN_ALLOWMULTISELECT, "MP3音频文件(*.mp3)|*.mp3", NULL);
	DocSelectDlg.m_ofn.nMaxFile = 100 * MAX_PATH;     // 100   Files   
	DocSelectDlg.m_ofn.lpstrFile = new   TCHAR[DocSelectDlg.m_ofn.nMaxFile];
	ZeroMemory(DocSelectDlg.m_ofn.lpstrFile, sizeof(TCHAR) * DocSelectDlg.m_ofn.nMaxFile);
	CString buf[1000];
	int num = 0;
	if (DocSelectDlg.DoModal() == IDCANCEL)return;
	else
	{
		POSITION pos = DocSelectDlg.GetStartPosition();
		while (pos != NULL)
		{
			buf[num] = DocSelectDlg.GetNextPathName(pos);
			num++;
		}
		int i = 0;
		m_PathOfMusicDoc = new CString[num];
		for (; i < num; i++)
		{
			m_PathOfMusicDoc[i] = buf[i];			//采集所有已添加歌曲的路径信息
		}
	}
	//	if (DocSelectDlg.DoModal() == IDOK)m_PathOfMusicDoc = DocSelectDlg.GetPathName();
	

	

}


void CMPlayerBasicVersionView::OnAddFileFolder()
{
	// TODO: 在此添加命令处理程序代码
	char szPath[MAX_PATH];     //存放选择的目录路径 

	ZeroMemory(szPath, sizeof(szPath));

	BROWSEINFO bi;
	bi.hwndOwner = m_hWnd;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = szPath;
	bi.lpszTitle = "请选择需要打包的目录：";
	bi.ulFlags = 0;
	bi.lpfn = NULL;
	bi.lParam = 0;
	bi.iImage = 0;
	//弹出选择目录对话框
	LPITEMIDLIST lp = SHBrowseForFolder(&bi);

	if (lp && SHGetPathFromIDList(lp, szPath))
	{
		NameOfFileFolder.Format("选择的目录为 %s", szPath);
//		AfxMessageBox(str);


	}
	else
		AfxMessageBox("无效的目录，请重新选择");
}


int CMPlayerBasicVersionView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	P_ButtonPause = new CButton();
	P_ButtonPlay = new CButton();
	P_ButtonStop = new CButton();
	P_ButtonPlay->Create("播放",                       //按钮标题
		WS_CHILD | WS_VISIBLE | WS_BORDER,//按钮风格
		CRect(10,20,50,35),            //按钮大小
		this,                          //按钮父指针
		ID_VIEW_APPLOOK_ONplay);                      //该按钮对应的ID号
	P_ButtonPlay->ShowWindow(SW_SHOWNORMAL);

	P_ButtonPause->Create("暂停",                       //按钮标题
		WS_CHILD | WS_VISIBLE | WS_BORDER,//按钮风格
		CRect(55,20,95,35),            //按钮大小
		this,                          //按钮父指针
		ID_VIEW_APPLOOK_ONpause);                      //该按钮对应的ID号
	P_ButtonPause->ShowWindow(SW_SHOWNORMAL);

	P_ButtonStop->Create("停止",                       //按钮标题
		WS_CHILD | WS_VISIBLE | WS_BORDER,//按钮风格
		CRect(100,20,140,35),            //按钮大小
		this,                          //按钮父指针
		ID_VIEW_APPLOOK_ONstop);                      //该按钮对应的ID号
	P_ButtonStop->ShowWindow(SW_SHOWNORMAL);
	
	// TODO:  在此添加您专用的创建代码

	return 0;
}

BEGIN_MESSAGE_MAP(...)


	ID_VIEW_APPLOOK_ONplay(IDB_BTN, OnClickButtonplay)   
	ID_VIEW_APPLOOK_ONpause(IDB_BTN, OnClickButtonpause)
	ID_VIEW_APPLOOK_ONstop(IDB_BTN, OnClickButtonstop) //按钮消息的处理函数

	END_MSG_MAP

/*int CMPlayerBasicVersionView::nbutton(int nID, CRect rect, int nStyle)
{
	 CString m_Caption;

	 m_Caption.LoadString(nID); //取按钮标题  

	 CButton * p_Button = new CButton();

	 ASSERT_VALID(p_Button);

	p_Button->Create(m_Caption, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | nStyle, rect, this, nID);  //创建按钮  

	return p_Button;

}*/


