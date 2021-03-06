#ifndef RENDER_HEAD_FILE
#define RENDER_HEAD_FILE

#pragma once

#include "Music.h"
#include "MyImage.h"

#define RESOURCE_ID TRUE
class CMyImage;

//资源结构
struct tagImageInfo
{
	CMyImage		*pImage;
	int				nRef;
};

//////////////////////////////////////////////////////////////////////////

class CRenderManager
{
protected:
	HFONT								m_hDefaultFont;			//默认字体
	HINSTANCE							m_hResInstance;			//资源句柄
	map<LPCTSTR,tagImageInfo*>			m_ArrayImage;			//图片数组
	map<int, tagImageInfo*>				m_ArrayImageId;
	vector<HFONT>						m_ArrayFont;			//字体管理

public:
	CRenderManager(void);
	~CRenderManager(void);

	//创建单例
public:
	static CRenderManager*GetInstance();

	//获取函数
public:
	HFONT GetDeaultFont(){return m_hDefaultFont;}

public:
	//进程目录
	bool GetWorkDirectory(TCHAR szWorkDirectory[], WORD wBufferCount);
	//默认字体
	void SetDefaultFont(LPCTSTR pStrFontName, int nSize, bool bBold, bool bUnderline, bool bItalic);
	//资源句柄
	void SetResInstance(HINSTANCE hInstance){m_hResInstance = hInstance;}

public:
	//
	void AddFont(LPCTSTR pStrFontName, int nSize, bool bBold=false, bool bUnderline=false, bool bItalic=false);
	//
	HFONT GetFont(int nIndex);
	//
	HFONT GetEndFont();

	//图片管理
public:
	//获取图片
	CMyImage *GetImage(LPCTSTR lpszFileName,LPCTSTR lpszResType=NULL);
	CMyImage *GetImage(UINT nID, LPCTSTR lpszResType=NULL);
	//删除图片
	void RemoveImage(CMyImage *&pImage, BOOL bResFromID = FALSE);
	//删除所有
	void ClearImage();

	//绘画函数
public:
	//区域色块
	void DrawColor(HDC hDC, const RECT& rc, COLORREF color);
	//渐变色块
	void DrawGradient(HDC hDC, const RECT& rc, DWORD dwFirst, DWORD dwSecond, bool bVertical, int nSteps);
	//绘制线条
	void DrawLine(HDC hDC, const RECT& rc, int nSize, COLORREF dwPenColor,int nStyle = PS_SOLID);
	//绘制矩形
	void DrawRect(HDC hDC, const RECT& rc, int nSize, COLORREF dwPenColor);
	//圆角矩形
	void DrawRoundRect(HDC hDC, const RECT& rc, int width, int height, int nSize, COLORREF dwPenColor);
	//文字尺寸
	SIZE GetTextSize(HDC hDC, LPCTSTR pstrText, HFONT hFont, UINT uStyle);
};

#define RenderEngine	CRenderManager::GetInstance()

#endif