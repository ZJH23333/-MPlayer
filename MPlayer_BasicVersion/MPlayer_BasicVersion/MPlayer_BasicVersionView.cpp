
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


// CMPlayerBasicVersionView

IMPLEMENT_DYNCREATE(CMPlayerBasicVersionView, CView)

BEGIN_MESSAGE_MAP(CMPlayerBasicVersionView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMPlayerBasicVersionView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_FILE_NEW, &CMPlayerBasicVersionView::OnFileNew)
END_MESSAGE_MAP()

// CMPlayerBasicVersionView 构造/析构

CMPlayerBasicVersionView::CMPlayerBasicVersionView() noexcept
{
	// TODO: 在此处添加构造代码
	m_DeviceID = 0;

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
	CString	m_PathOfMusicDoc;
	CFileDialog DocSelectDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"MP3音频文件(*.mp3)|*.mp3", NULL);
	if (DocSelectDlg.DoModal() == IDCANCEL)return;
	else m_PathOfMusicDoc = DocSelectDlg.GetPathName();
//	if (DocSelectDlg.DoModal() == IDOK)m_PathOfMusicDoc = DocSelectDlg.GetPathName();
	//关闭当前播放音乐

	mciSendCommand(m_DeviceID, MCI_CLOSE, 0, 0);

	//播放所选择的音乐
	MCI_OPEN_PARMS mciOpenMusic;
	UINT playDeviceID;
	mciOpenMusic.lpstrDeviceType = L"mp3";
	mciOpenMusic.lpstrElementName = m_PathOfMusicDoc;
	mciSendCommand(0, MCI_PLAY, MCI_OPEN_ELEMENT, (DWORD)&mciOpenMusic);
	playDeviceID = mciOpenMusic.wDeviceID;
	MCI_PLAY_PARMS mciPLay;
	mciSendCommand(playDeviceID, MCI_PLAY, MCI_WAIT, (DWORD)&mciPLay);
}
