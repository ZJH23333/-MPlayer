
// MPlayer_BasicVersionView.h: CMPlayerBasicVersionView 类的接口
//

#pragma once
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

class CMPlayerBasicVersionView : public CView
{
protected: // 仅从序列化创建
	CMPlayerBasicVersionView() noexcept;
	DECLARE_DYNCREATE(CMPlayerBasicVersionView)

// 特性
public:
	CMPlayerBasicVersionDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMPlayerBasicVersionView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnClickButtonplay();
	afx_msg void OnClickButtonpause();
	afx_msg void OnClickButtonstop();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileNew();
	MCIDEVICEID m_DeviceID;
//	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
//	afx_msg void OnClickPlayMusic();
private:
	CButton *P_ButtonPlay;			//播放按钮的指针
	CButton *P_ButtonPause;         //暂停按钮的指针
	CButton *P_ButtonStop;          //停止按钮的指针
	CString *m_PathOfMusicDoc;		//添加歌曲文件时的路径
//	CString* m_NameOfMusicDoc;		//歌曲文件名
	CString NameOfFileFolder;
public:
	afx_msg void OnAddFileFolder();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg int nbutton(int nID, CRect rect, int nStyle);
	

};

#ifndef _DEBUG  // MPlayer_BasicVersionView.cpp 中的调试版本
inline CMPlayerBasicVersionDoc* CMPlayerBasicVersionView::GetDocument() const
   { return reinterpret_cast<CMPlayerBasicVersionDoc*>(m_pDocument); }
#endif

