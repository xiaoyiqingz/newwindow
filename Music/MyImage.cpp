#include "StdAfx.h"
#include "MyImage.h"


CMyImage::CMyImage()
{
	m_pImage=NULL;
	ZeroMemory(m_strImageName, sizeof(m_strImageName));
	::SetRect(&m_rcNinePart,0,0,0,0);
}


CMyImage::~CMyImage()
{
	 DestroyImage();
}

//是否加载
bool CMyImage::IsNull()
{
	//加载判断
	if (m_pImage==NULL) return true;
	if (m_pImage->GetLastStatus()!=Ok) return true;

	return false;
}

//获取宽度
INT CMyImage::GetWidth()
{
	//加载判断
	ASSERT(IsNull()==false);
	if (IsNull()==true) return 0;

	//获取宽度
	return m_pImage->GetWidth();
}

//获取高度
INT CMyImage::GetHeight()
{
	//加载判断
	ASSERT(IsNull()==false);
	if (IsNull()==true) return 0;

	//获取高度
	return m_pImage->GetHeight();
}

//销毁图片
bool CMyImage::DestroyImage()
{
	//删除对象
	if (m_pImage!=NULL) SafeDelete(m_pImage);

	return true;
}

//加载图片
bool CMyImage::LoadImage(LPCTSTR pszFileName)
{
	//加载判断
	ASSERT(m_pImage==NULL);
	if (m_pImage!=NULL) return false;

	//加载文件
	CT2CW strFileName(pszFileName);
	m_pImage=Bitmap::FromFile((LPCWSTR)strFileName);

	//错误判断
	if ((m_pImage==NULL)||(m_pImage->GetLastStatus()!=Ok))
	{
		DestroyImage();
		return false;
	}

	return true;
}

//加载图片
bool CMyImage::LoadImage(HINSTANCE hInstance, LPCTSTR pszResourceName, LPCTSTR pszType)
{
	//加载判断
	ASSERT(m_pImage==NULL);
	if (m_pImage!=NULL) return false;

	//查找资源
	HRSRC hResource=FindResource(hInstance,pszResourceName,pszType);
	if (hResource==NULL) return false;

	//读取资源
	DWORD dwImageSize=SizeofResource(hInstance,hResource);
	LPVOID pImageBuffer=LoadResource(hInstance,hResource);

	//创建数据
	IStream * pIStream=NULL;
	if (CreateStreamOnHGlobal(NULL,TRUE,&pIStream)!=S_OK)
	{
		ASSERT(FALSE);
		return false;
	}

	//写入数据
	pIStream->Write(pImageBuffer,dwImageSize,NULL);

	//创建位图
	m_pImage=Bitmap::FromStream(pIStream);

	//释放资源
	SafeRelease(pIStream);

	//错误判断
	if ((m_pImage==NULL)||(m_pImage->GetLastStatus()!=Ok))
	{
		ASSERT(FALSE);
		return false;
	}

	return true;
}

bool CMyImage::LoadImage(HINSTANCE hInstance, UINT nIDResource)
{
	//加载判断
	ASSERT(m_pImage==NULL);
	if (m_pImage!=NULL) return false;

	//查找资源
	HRSRC hResource=FindResource(hInstance, MAKEINTRESOURCE(nIDResource), RT_BITMAP);
	if (hResource==NULL) return false;

	//读取资源
	DWORD dwImageSize=SizeofResource(hInstance,hResource);
	LPVOID pImageBuffer=LoadResource(hInstance,hResource);

	//创建数据
	IStream * pIStream=NULL;
	if (CreateStreamOnHGlobal(NULL,TRUE,&pIStream)!=S_OK)
	{
		ASSERT(FALSE);
		return false;
	}

	//写入数据
	pIStream->Write(pImageBuffer,dwImageSize,NULL);

	//创建位图
	m_pImage=Bitmap::FromStream(pIStream);

	//释放资源
	SafeRelease(pIStream);

	//错误判断
	if ((m_pImage==NULL)||(m_pImage->GetLastStatus()!=Ok))
	{
		ASSERT(FALSE);
		return false;
	}

	return true;
}

//绘画图像
bool CMyImage::DrawImage(CDC * pDC, INT nXPos, INT nYPos)
{
	//加载判断
	ASSERT(m_pImage!=NULL);
	if (m_pImage==NULL) return false;

	//创建屏幕
	ASSERT(pDC!=NULL);
	Graphics graphics(pDC->GetSafeHdc());

	//获取属性
	INT nImageWidth=m_pImage->GetWidth();
	INT nImageHeight=m_pImage->GetHeight();

	//构造位置
	RectF rcDrawRect;
	rcDrawRect.X=(REAL)nXPos;
	rcDrawRect.Y=(REAL)nYPos;
	rcDrawRect.Width=(REAL)nImageWidth;
	rcDrawRect.Height=(REAL)nImageHeight;

	//绘画图像
	graphics.DrawImage(m_pImage,rcDrawRect,0,0,(REAL)nImageWidth,(REAL)nImageHeight,UnitPixel);

	return true;
}

//绘画图像
bool CMyImage::DrawImage( CDC * pDC, INT nXPos, INT nYPos, INT nDestWidth, INT nDestHeight )
{
	//加载判断
	ASSERT(m_pImage!=NULL);
	if (m_pImage==NULL) return false;

	//创建屏幕
	ASSERT(pDC!=NULL);
	Graphics graphics(pDC->GetSafeHdc());

	//构造位置
	RectF rcDrawRect;
	rcDrawRect.X=(REAL)nXPos;
	rcDrawRect.Y=(REAL)nYPos;
	rcDrawRect.Width=(REAL)nDestWidth;
	rcDrawRect.Height=(REAL)nDestHeight;

	//绘画图像
	graphics.DrawImage(m_pImage,rcDrawRect,0,0,(REAL)GetWidth(),(REAL)GetHeight(),UnitPixel);

	return true;
}

bool CMyImage::DrawImage(CDC * pDC, RECT &rc)
{
	ASSERT(m_pImage != NULL);
	if (m_pImage == NULL)  return false;

	ASSERT(pDC != NULL);
	Graphics graphics(pDC->GetSafeHdc());

	RectF rcDrawRect;
	rcDrawRect.X = (REAL)rc.left;
	rcDrawRect.Y = (REAL)rc.top;
	rcDrawRect.Width = (REAL)(rc.right - rc.left);
	rcDrawRect.Height = (REAL)(rc.bottom- rc.top);

	graphics.DrawImage(m_pImage, rcDrawRect,0, 0, (REAL)GetWidth(), (REAL)GetHeight(), UnitPixel);
}

//绘画图像
bool CMyImage::DrawImage(CDC * pDC, INT nXDest, INT nYDest, INT nDestWidth, INT nDestHeight, INT nXScr, INT nYSrc, INT nSrcWidth, INT nSrcHeight)
{
	//加载判断
	ASSERT(m_pImage!=NULL);
	if (m_pImage==NULL) return false;

	//创建屏幕
	ASSERT(pDC!=NULL);
	Graphics graphics(pDC->GetSafeHdc());

	//构造位置
	RectF rcDrawRect;
	rcDrawRect.X=(REAL)nXDest;
	rcDrawRect.Y=(REAL)nYDest;
	rcDrawRect.Width=(REAL)nDestWidth;
	rcDrawRect.Height=(REAL)nDestHeight;

	//绘画图像
	graphics.DrawImage(m_pImage,rcDrawRect,(REAL)nXScr,(REAL)nYSrc,(REAL)nSrcWidth,(REAL)nSrcHeight,UnitPixel);

	return true;
}

//绘画图像
bool CMyImage::DrawImage(CDC * pDC, INT nXDest, INT nYDest, INT nDestWidth, INT nDestHeight, INT nXScr, INT nYSrc)
{
	//加载判断
	ASSERT(m_pImage!=NULL);
	if (m_pImage==NULL) return false;

	//创建屏幕
	ASSERT(pDC!=NULL);
	Graphics graphics(pDC->GetSafeHdc());

	//构造位置
	RectF rcDrawRect;
	rcDrawRect.X=(REAL)nXDest;
	rcDrawRect.Y=(REAL)nYDest;
	rcDrawRect.Width=(REAL)nDestWidth;
	rcDrawRect.Height=(REAL)nDestHeight;

	//绘画图像
	graphics.DrawImage(m_pImage,rcDrawRect,(REAL)nXScr,(REAL)nYSrc,(REAL)nDestWidth,(REAL)nDestHeight,UnitPixel);

	return true;
}

//混合绘画
bool CMyImage::AlphaDrawImage(CDC * pDestDC, INT xDest, INT yDest, BYTE cbAlphaDepth)
{
	//透明绘画
	AlphaDrawImage(pDestDC,xDest,yDest,GetWidth(),GetHeight(),0,0,cbAlphaDepth);

	return true;
}

//混合绘画
bool CMyImage::AlphaDrawImage(CDC * pDestDC, INT xDest, INT yDest, INT cxDest, INT cyDest, INT xSrc, INT ySrc, BYTE cbAlphaDepth)
{
	//加载判断
	ASSERT(m_pImage!=NULL);
	if (m_pImage==NULL) return false;

	//创建屏幕
	ASSERT(pDestDC!=NULL);
	Graphics graphics(pDestDC->GetSafeHdc());

	//构造位置
	RectF rcDrawRect;
	rcDrawRect.X=(REAL)xDest;
	rcDrawRect.Y=(REAL)yDest;
	rcDrawRect.Width=(REAL)cxDest;
	rcDrawRect.Height=(REAL)cyDest;

	//透明矩阵
	ColorMatrix Matrix=
	{
		1.0f,0.0f,0.0f,0.0f,0.0f,
		0.0f,1.0f,0.0f,0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,0.0f,
		0.0f,0.0f,0.0f,cbAlphaDepth/255.0f,0.0f,
		0.0f,0.0f,0.0f,0.0f,1.0f
	};

	//设置属性
	ImageAttributes Attributes;
	Attributes.SetColorMatrix(&Matrix,ColorMatrixFlagsDefault,ColorAdjustTypeBitmap);

	//绘画图像
	graphics.DrawImage(m_pImage,rcDrawRect,(REAL)xSrc,(REAL)ySrc,(REAL)cxDest,(REAL)cyDest,UnitPixel,&Attributes);

	return true;
}

//混合绘画
bool CMyImage::AlphaDrawImage(CDC * pDestDC, INT xDest, INT yDest, INT cxDest, INT cyDest, INT xSrc, INT ySrc, INT cxSrc, INT cySrc, BYTE cbAlphaDepth)
{
	//创建缓冲
	if ((cxDest!=cxSrc)||(cyDest!=cySrc))
	{
		//加载判断
		ASSERT(m_pImage!=NULL);
		if (m_pImage==NULL) return false;

		//创建屏幕
		ASSERT(pDestDC!=NULL);
		Graphics graphics(pDestDC->GetSafeHdc());

		//构造位置
		RectF rcDrawRect;
		rcDrawRect.X=(REAL)xDest;
		rcDrawRect.Y=(REAL)yDest;
		rcDrawRect.Width=(REAL)cxDest;
		rcDrawRect.Height=(REAL)cyDest;

		//透明矩阵
		ColorMatrix Matrix=
		{
			1.0f,0.0f,0.0f,0.0f,0.0f,
			0.0f,1.0f,0.0f,0.0f,0.0f,
			0.0f,0.0f,1.0f,0.0f,0.0f,
			0.0f,0.0f,0.0f,cbAlphaDepth/255.0f,0.0f,
			0.0f,0.0f,0.0f,0.0f,1.0f
		};

		//设置属性
		ImageAttributes Attributes;
		Attributes.SetColorMatrix(&Matrix,ColorMatrixFlagsDefault,ColorAdjustTypeBitmap);

		//绘画图像
		graphics.DrawImage(m_pImage,rcDrawRect,(REAL)xSrc,(REAL)ySrc,(REAL)cxSrc,(REAL)cySrc,UnitPixel,&Attributes);   
	}
	else
	{
		//普通调用
		AlphaDrawImage(pDestDC,xDest,yDest,cxDest,cyDest,xSrc,ySrc,cbAlphaDepth);
	}

	return true;
}

bool CMyImage::Draw( CDC * pDC, INT x, INT y, INT cx, INT cy,INT nLeft,INT nTop,INT nRight,INT nBottom )
{
	int cxImage = GetWidth();
	int cyImage = GetHeight();

	// 左上
	{
		RECT rcDest = {x, y, x+nLeft, y+nTop};
		RECT rcSrc = {0, 0, nLeft, nTop};
		if (!::IsRectEmpty(&rcDest) && !::IsRectEmpty(&rcSrc))
			DrawImage(pDC,rcDest.left, rcDest.top, rcDest.right-rcDest.left, rcDest.bottom-rcDest.top, 
			rcSrc.left, rcSrc.top,rcSrc.right-rcSrc.left, rcSrc.bottom-rcSrc.top);
	}

	// 左边
	{
		RECT rcDest = {x, y+nTop, x+nLeft, (y+nTop)+(cy-nTop-nBottom)};
		RECT rcSrc = {0, nTop, nLeft, nTop+(cyImage-nTop-nBottom)};
		if (!::IsRectEmpty(&rcDest) && !::IsRectEmpty(&rcSrc))
			DrawImage(pDC,rcDest.left, rcDest.top, rcDest.right-rcDest.left, rcDest.bottom-rcDest.top, 
			rcSrc.left, rcSrc.top,rcSrc.right-rcSrc.left, rcSrc.bottom-rcSrc.top);
	}

	// 上边
	{
		RECT rcDest = {x+nLeft, y,x+(cx-nRight), y+nTop};
		RECT rcSrc = {nLeft, 0, (cxImage-nLeft-nRight), nTop};
		if (!::IsRectEmpty(&rcDest) && !::IsRectEmpty(&rcSrc))
			DrawImage(pDC,rcDest.left, rcDest.top, rcDest.right-rcDest.left, rcDest.bottom-rcDest.top, 
			rcSrc.left, rcSrc.top,rcSrc.right-rcSrc.left, rcSrc.bottom-rcSrc.top);
	}

	// 右上
	{
		RECT rcDest = {x+(cx-nRight), y, (x+(cx-nRight))+nRight, y+nTop};
		RECT rcSrc = {cxImage-nRight, 0, (cxImage-nRight)+nRight, nTop};
		if (!::IsRectEmpty(&rcDest) && !::IsRectEmpty(&rcSrc))
			DrawImage(pDC,rcDest.left, rcDest.top, rcDest.right-rcDest.left, rcDest.bottom-rcDest.top, 
			rcSrc.left, rcSrc.top,rcSrc.right-rcSrc.left, rcSrc.bottom-rcSrc.top);
	}

	// 右边
	{
		RECT rcDest = {x+(cx-nRight), y+nTop, (x+(cx-nRight))+nRight, (y+nTop)+(cy-nTop-nBottom)};
		RECT rcSrc = {cxImage-nRight, nTop, (cxImage-nRight)+nRight, nTop+(cyImage-nTop-nBottom)};
		if (!::IsRectEmpty(&rcDest) && !::IsRectEmpty(&rcSrc))
			DrawImage(pDC,rcDest.left, rcDest.top, rcDest.right-rcDest.left, rcDest.bottom-rcDest.top, 
			rcSrc.left, rcSrc.top,rcSrc.right-rcSrc.left, rcSrc.bottom-rcSrc.top);
	}

	// 下边
	{
		RECT rcDest = {x+nLeft, y+(cy-nBottom), (x+nLeft)+(cx-nLeft-nRight), (y+(cy-nBottom))+nBottom};
		RECT rcSrc = {nLeft, cyImage-nBottom, nLeft+(cxImage-nLeft-nRight), (cyImage-nBottom)+nBottom};
		if (!::IsRectEmpty(&rcDest) && !::IsRectEmpty(&rcSrc))
			DrawImage(pDC,rcDest.left, rcDest.top, rcDest.right-rcDest.left, rcDest.bottom-rcDest.top, 
			rcSrc.left, rcSrc.top,rcSrc.right-rcSrc.left, rcSrc.bottom-rcSrc.top);
	}

	// 右下
	{
		RECT rcDest = {x+(cx-nRight), y+(cy-nBottom), (x+(cx-nRight))+nRight, (y+(cy-nBottom))+nBottom};
		RECT rcSrc = {cxImage-nRight, cyImage-nBottom, (cxImage-nRight)+nRight, (cyImage-nBottom)+nBottom};
		if (!::IsRectEmpty(&rcDest) && !::IsRectEmpty(&rcSrc))
			DrawImage(pDC,rcDest.left, rcDest.top, rcDest.right-rcDest.left, rcDest.bottom-rcDest.top, 
			rcSrc.left, rcSrc.top,rcSrc.right-rcSrc.left, rcSrc.bottom-rcSrc.top);
	}

	// 左下
	{
		RECT rcDest = {x, y+(cy-nBottom), x+nLeft, (y+(cy-nBottom))+nBottom};
		RECT rcSrc = {0, cyImage-nBottom, nLeft, (cyImage-nBottom)+nBottom};
		if (!::IsRectEmpty(&rcDest) && !::IsRectEmpty(&rcSrc))
			DrawImage(pDC,rcDest.left, rcDest.top, rcDest.right-rcDest.left, rcDest.bottom-rcDest.top, 
			rcSrc.left, rcSrc.top,rcSrc.right-rcSrc.left, rcSrc.bottom-rcSrc.top);
	}

	// 中间
	{
		RECT rcDest = {x+nLeft, y+nTop, x+(cx-nRight), y+(cy-nBottom)};
		RECT rcSrc = {nLeft, nTop, cxImage-nRight, cyImage-nBottom};

		if (!::IsRectEmpty(&rcDest) && !::IsRectEmpty(&rcSrc))
			DrawImage(pDC,rcDest.left, rcDest.top, rcDest.right-rcDest.left, rcDest.bottom-rcDest.top, 
			rcSrc.left, rcSrc.top,rcSrc.right-rcSrc.left, rcSrc.bottom-rcSrc.top);
	}

	return TRUE;
}

bool CMyImage::Draw( CDC * pDC, const RECT& rectDest, const RECT& rectSrc )
{
	return Draw(pDC,rectDest.left, rectDest.top, rectDest.right-rectDest.left, rectDest.bottom-rectDest.top, 
		rectSrc.left, rectSrc.top,rectSrc.right, rectSrc.bottom);
}

bool CMyImage::Draw( CDC * pDC, const RECT& rectDest )
{
	return Draw(pDC,rectDest,m_rcNinePart);
}

void CMyImage::SetNinePart( CONST LPRECT lprcNinePart )
{
	if( lprcNinePart == NULL ) return;

	::CopyRect(&m_rcNinePart,lprcNinePart);
}

HBITMAP CMyImage::ImageToBitmap(/*HDC hDC*/) 
{ 
	ASSERT(m_pImage != NULL);
	if(m_pImage == NULL) return NULL;
	m_pImage->GetHBITMAP(Color(0,0,0),&m_hBitmap);

	return m_hBitmap;
}