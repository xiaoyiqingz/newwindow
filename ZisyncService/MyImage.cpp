#include "StdAfx.h"
#include "MyImage.h"

CMyImage::CMyImage()
{
	m_pImage=NULL;
	ZeroMemory(m_strImageName, sizeof(m_strImageName));
	::SetRect(&m_rcNinePart,0,0,0,0);
	
	m_bIsInit = FALSE;
	m_bIsPause = FALSE;
	m_hTimer = INVALID_HANDLE_VALUE;
	m_pPropertyItem = NULL;
}


CMyImage::~CMyImage()
{	 	
	if (m_hTimer != INVALID_HANDLE_VALUE) {
		 if (!DeleteTimerQueueTimer(NULL, m_hTimer, INVALID_HANDLE_VALUE)) {
		 } else {
			 m_hTimer = INVALID_HANDLE_VALUE;
		 }
	 }

	if (m_pPropertyItem != NULL) {
		free(m_pPropertyItem);
		m_pPropertyItem = NULL;
	}

	m_bIsPause = FALSE;
	m_bIsInit = FALSE;

	 DestroyImage();
}

//�Ƿ����
bool CMyImage::IsNull()
{
	//�����ж�
	if (m_pImage==NULL) return true;
	if (m_pImage->GetLastStatus()!=Ok) return true;

	return false;
}

//��ȡ���
INT CMyImage::GetWidth()
{
	//�����ж�
	ASSERT(IsNull()==false);
	if (IsNull()==true) return 0;

	//��ȡ���
	return m_pImage->GetWidth();
}

//��ȡ�߶�
INT CMyImage::GetHeight()
{
	//�����ж�
	ASSERT(IsNull()==false);
	if (IsNull()==true) return 0;

	//��ȡ�߶�
	return m_pImage->GetHeight();
}

//����ͼƬ
bool CMyImage::DestroyImage()
{
	if (m_hTimer != INVALID_HANDLE_VALUE) {
		if (!DeleteTimerQueueTimer(NULL, m_hTimer, INVALID_HANDLE_VALUE)) {
		} else {
			m_hTimer = INVALID_HANDLE_VALUE;
		}
	}

	//ɾ������
	if (m_pImage!=NULL) SafeDelete(m_pImage);

	return true;
}

//����ͼƬ
bool CMyImage::LoadImage(LPCTSTR pszFileName)
{
	//�����ж�
	ASSERT(m_pImage==NULL);
	if (m_pImage!=NULL) return false;

	//�����ļ�
	CT2CW strFileName(pszFileName);
	m_pImage=Bitmap::FromFile((LPCWSTR)strFileName);

	//�����ж�
	if ((m_pImage==NULL)||(m_pImage->GetLastStatus()!=Ok))
	{
		DestroyImage();
		return false;
	}

	return true;
}

//����ͼƬ
bool CMyImage::LoadImage(HINSTANCE hInstance, LPCTSTR pszResourceName, LPCTSTR pszType)
{
	//�����ж�
	ASSERT(m_pImage==NULL);
	if (m_pImage!=NULL) return false;

	//������Դ
	HRSRC hResource=FindResource(hInstance,pszResourceName,pszType);
	if (hResource==NULL) return false;

	//��ȡ��Դ
	DWORD dwImageSize=SizeofResource(hInstance,hResource);
	LPVOID pImageBuffer=LoadResource(hInstance,hResource);  //�ú���װ��ָ����Դ��ȫ�ִ洢��

	//��������
	IStream * pIStream=NULL;
	if (CreateStreamOnHGlobal(NULL,TRUE,&pIStream)!=S_OK)   //������ָ���ڴ洴��������
	{
		ASSERT(FALSE);
		return false;
	}

	//д������
	pIStream->Write(pImageBuffer,dwImageSize,NULL);

	//����λͼ
	m_pImage=Bitmap::FromStream(pIStream);

	//�ͷ���Դ
	SafeRelease(pIStream);

	//�����ж�
	if ((m_pImage==NULL)||(m_pImage->GetLastStatus()!=Ok))
	{
		ASSERT(FALSE);
		return false;
	}

	return true;
}

bool CMyImage::LoadImage(HINSTANCE hInstance, UINT nIDResource, LPCTSTR lpszResType)
{
	//�����ж�
	ASSERT(m_pImage==NULL);
	if (m_pImage!=NULL) return false;

	//������Դ
	HRSRC hResource;
	if (lpszResType == NULL) {
		hResource =FindResource(hInstance, MAKEINTRESOURCE(nIDResource), RT_BITMAP);
	} else {
		hResource=FindResource(hInstance, MAKEINTRESOURCE(nIDResource), lpszResType);
	}

	if (hResource==NULL) return false;

	//��ȡ��Դ
	DWORD dwImageSize=SizeofResource(hInstance,hResource);
	LPVOID pImageBuffer=LoadResource(hInstance,hResource);

	//��������
	IStream * pIStream=NULL;
	if (CreateStreamOnHGlobal(NULL,TRUE,&pIStream)!=S_OK)
	{
		ASSERT(FALSE);
		return false;
	}

	//д������
	pIStream->Write(pImageBuffer,dwImageSize,NULL);

	//����λͼ
	m_pImage=Bitmap::FromStream(pIStream);

	//�ͷ���Դ
	SafeRelease(pIStream);

	//�����ж�
	Status lastState = m_pImage->GetLastStatus(); // bmp return InvalidParameter
	if ((m_pImage==NULL)||(lastState!=Ok))
	{
		ASSERT(FALSE);
		return false;
	}

	return true;
}

//�滭ͼ��
bool CMyImage::DrawImage(CDC * pDC, INT nXPos, INT nYPos)
{
	//�����ж�
	ASSERT(m_pImage!=NULL);
	if (m_pImage==NULL) return false;

	//������Ļ
	ASSERT(pDC!=NULL);
	Graphics graphics(pDC->GetSafeHdc());

	//��ȡ����
	INT nImageWidth=m_pImage->GetWidth();
	INT nImageHeight=m_pImage->GetHeight();

	//����λ��
	RectF rcDrawRect;
	rcDrawRect.X=(REAL)nXPos;
	rcDrawRect.Y=(REAL)nYPos;
	rcDrawRect.Width=(REAL)nImageWidth;
	rcDrawRect.Height=(REAL)nImageHeight;

	//�滭ͼ��  ��ָ��λ�ò��Ұ�ָ����С����ָ���� Image ��ָ������ ��rcDrawRect�л�Image�ӣ�0,0������width��heigh��
	graphics.DrawImage(m_pImage,rcDrawRect,0,0,(REAL)nImageWidth,(REAL)nImageHeight,UnitPixel);

	return true;
}

//�滭ͼ��
bool CMyImage::DrawImage( CDC * pDC, INT nXPos, INT nYPos, INT nDestWidth, INT nDestHeight )
{
	//�����ж�
	ASSERT(m_pImage!=NULL);
	if (m_pImage==NULL) return false;

	//������Ļ
	ASSERT(pDC!=NULL);
	Graphics graphics(pDC->GetSafeHdc());

	//����λ��
	RectF rcDrawRect;
	rcDrawRect.X=(REAL)nXPos;
	rcDrawRect.Y=(REAL)nYPos;
	rcDrawRect.Width=(REAL)nDestWidth;
	rcDrawRect.Height=(REAL)nDestHeight;

	//�滭ͼ��
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
	return true;
}

//�滭ͼ��
bool CMyImage::DrawImage(CDC * pDC, INT nXDest, INT nYDest, INT nDestWidth, INT nDestHeight, INT nXScr, INT nYSrc, INT nSrcWidth, INT nSrcHeight)
{
	//�����ж�
	ASSERT(m_pImage!=NULL);
	if (m_pImage==NULL) return false;

	//������Ļ
	ASSERT(pDC!=NULL);
	Graphics graphics(pDC->GetSafeHdc());

	//����λ��
	RectF rcDrawRect;
	rcDrawRect.X=(REAL)nXDest;
	rcDrawRect.Y=(REAL)nYDest;
	rcDrawRect.Width=(REAL)nDestWidth;
	rcDrawRect.Height=(REAL)nDestHeight;

	//�滭ͼ��
	graphics.DrawImage(m_pImage,rcDrawRect,(REAL)nXScr,(REAL)nYSrc,(REAL)nSrcWidth,(REAL)nSrcHeight,UnitPixel);

	return true;
}

//�滭ͼ��
bool CMyImage::DrawImage(CDC * pDC, INT nXDest, INT nYDest, INT nDestWidth, INT nDestHeight, INT nXScr, INT nYSrc)
{
	//�����ж�
	ASSERT(m_pImage!=NULL);
	if (m_pImage==NULL) return false;

	//������Ļ
	ASSERT(pDC!=NULL);
	Graphics graphics(pDC->GetSafeHdc());

	//����λ��
	RectF rcDrawRect;
	rcDrawRect.X=(REAL)nXDest;
	rcDrawRect.Y=(REAL)nYDest;
	rcDrawRect.Width=(REAL)nDestWidth;
	rcDrawRect.Height=(REAL)nDestHeight;

	//�滭ͼ��
	graphics.DrawImage(m_pImage,rcDrawRect,(REAL)nXScr,(REAL)nYSrc,(REAL)nDestWidth,(REAL)nDestHeight,UnitPixel);

	return true;
}

//��ϻ滭
bool CMyImage::AlphaDrawImage(CDC * pDestDC, INT xDest, INT yDest, BYTE cbAlphaDepth)
{
	//͸���滭
	AlphaDrawImage(pDestDC,xDest,yDest,GetWidth(),GetHeight(),0,0,cbAlphaDepth);

	return true;
}

//��ϻ滭
bool CMyImage::AlphaDrawImage(CDC * pDestDC, INT xDest, INT yDest, INT cxDest, INT cyDest, INT xSrc, INT ySrc, BYTE cbAlphaDepth)
{
	//�����ж�
	ASSERT(m_pImage!=NULL);
	if (m_pImage==NULL) return false;

	//������Ļ
	ASSERT(pDestDC!=NULL);
	Graphics graphics(pDestDC->GetSafeHdc());

	//����λ��
	RectF rcDrawRect;
	rcDrawRect.X=(REAL)xDest;
	rcDrawRect.Y=(REAL)yDest;
	rcDrawRect.Width=(REAL)cxDest;
	rcDrawRect.Height=(REAL)cyDest;

	//͸������
	ColorMatrix Matrix=
	{
		1.0f,0.0f,0.0f,0.0f,0.0f,
		0.0f,1.0f,0.0f,0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,0.0f,
		0.0f,0.0f,0.0f,cbAlphaDepth/255.0f,0.0f,
		0.0f,0.0f,0.0f,0.0f,1.0f
	};

	//��������
	ImageAttributes Attributes;
	Attributes.SetColorMatrix(&Matrix,ColorMatrixFlagsDefault,ColorAdjustTypeBitmap);

	//�滭ͼ��
	graphics.DrawImage(m_pImage,rcDrawRect,(REAL)xSrc,(REAL)ySrc,(REAL)cxDest,(REAL)cyDest,UnitPixel,&Attributes);

	return true;
}

//��ϻ滭
bool CMyImage::AlphaDrawImage(CDC * pDestDC, INT xDest, INT yDest, INT cxDest, INT cyDest, INT xSrc, INT ySrc, INT cxSrc, INT cySrc, BYTE cbAlphaDepth)
{
	//��������
	if ((cxDest!=cxSrc)||(cyDest!=cySrc))
	{
		//�����ж�
		ASSERT(m_pImage!=NULL);
		if (m_pImage==NULL) return false;

		//������Ļ
		ASSERT(pDestDC!=NULL);
		Graphics graphics(pDestDC->GetSafeHdc());

		//����λ��
		RectF rcDrawRect;
		rcDrawRect.X=(REAL)xDest;
		rcDrawRect.Y=(REAL)yDest;
		rcDrawRect.Width=(REAL)cxDest;
		rcDrawRect.Height=(REAL)cyDest;

		//͸������
		ColorMatrix Matrix=
		{
			1.0f,0.0f,0.0f,0.0f,0.0f,
			0.0f,1.0f,0.0f,0.0f,0.0f,
			0.0f,0.0f,1.0f,0.0f,0.0f,
			0.0f,0.0f,0.0f,cbAlphaDepth/255.0f,0.0f,
			0.0f,0.0f,0.0f,0.0f,1.0f
		};

		//��������
		ImageAttributes Attributes;
		Attributes.SetColorMatrix(&Matrix,ColorMatrixFlagsDefault,ColorAdjustTypeBitmap);

		//�滭ͼ��
		graphics.DrawImage(m_pImage,rcDrawRect,(REAL)xSrc,(REAL)ySrc,(REAL)cxSrc,(REAL)cySrc,UnitPixel,&Attributes);   
	}
	else
	{
		//��ͨ����
		AlphaDrawImage(pDestDC,xDest,yDest,cxDest,cyDest,xSrc,ySrc,cbAlphaDepth);
	}

	return true;
}

bool CMyImage::Draw( CDC * pDC, INT x, INT y, INT cx, INT cy,INT nLeft,INT nTop,INT nRight,INT nBottom )
{
	int cxImage = GetWidth();
	int cyImage = GetHeight();

	// ����
	{
		RECT rcDest = {x, y, x+nLeft, y+nTop};
		RECT rcSrc = {0, 0, nLeft, nTop};
		if (!::IsRectEmpty(&rcDest) && !::IsRectEmpty(&rcSrc))
			DrawImage(pDC,rcDest.left, rcDest.top, rcDest.right-rcDest.left, rcDest.bottom-rcDest.top, 
			rcSrc.left, rcSrc.top,rcSrc.right-rcSrc.left, rcSrc.bottom-rcSrc.top);
	}

	// ���
	{
		RECT rcDest = {x, y+nTop, x+nLeft, (y+nTop)+(cy-nTop-nBottom)};
		RECT rcSrc = {0, nTop, nLeft, nTop+(cyImage-nTop-nBottom)};
		if (!::IsRectEmpty(&rcDest) && !::IsRectEmpty(&rcSrc))
			DrawImage(pDC,rcDest.left, rcDest.top, rcDest.right-rcDest.left, rcDest.bottom-rcDest.top, 
			rcSrc.left, rcSrc.top,rcSrc.right-rcSrc.left, rcSrc.bottom-rcSrc.top);
	}

	// �ϱ�
	{
		RECT rcDest = {x+nLeft, y,x+(cx-nRight), y+nTop};
		RECT rcSrc = {nLeft, 0, (cxImage-nLeft-nRight), nTop};
		if (!::IsRectEmpty(&rcDest) && !::IsRectEmpty(&rcSrc))
			DrawImage(pDC,rcDest.left, rcDest.top, rcDest.right-rcDest.left, rcDest.bottom-rcDest.top, 
			rcSrc.left, rcSrc.top,rcSrc.right-rcSrc.left, rcSrc.bottom-rcSrc.top);
	}

	// ����
	{
		RECT rcDest = {x+(cx-nRight), y, (x+(cx-nRight))+nRight, y+nTop};
		RECT rcSrc = {cxImage-nRight, 0, (cxImage-nRight)+nRight, nTop};
		if (!::IsRectEmpty(&rcDest) && !::IsRectEmpty(&rcSrc))
			DrawImage(pDC,rcDest.left, rcDest.top, rcDest.right-rcDest.left, rcDest.bottom-rcDest.top, 
			rcSrc.left, rcSrc.top,rcSrc.right-rcSrc.left, rcSrc.bottom-rcSrc.top);
	}

	// �ұ�
	{
		RECT rcDest = {x+(cx-nRight), y+nTop, (x+(cx-nRight))+nRight, (y+nTop)+(cy-nTop-nBottom)};
		RECT rcSrc = {cxImage-nRight, nTop, (cxImage-nRight)+nRight, nTop+(cyImage-nTop-nBottom)};
		if (!::IsRectEmpty(&rcDest) && !::IsRectEmpty(&rcSrc))
			DrawImage(pDC,rcDest.left, rcDest.top, rcDest.right-rcDest.left, rcDest.bottom-rcDest.top, 
			rcSrc.left, rcSrc.top,rcSrc.right-rcSrc.left, rcSrc.bottom-rcSrc.top);
	}

	// �±�
	{
		RECT rcDest = {x+nLeft, y+(cy-nBottom), (x+nLeft)+(cx-nLeft-nRight), (y+(cy-nBottom))+nBottom};
		RECT rcSrc = {nLeft, cyImage-nBottom, nLeft+(cxImage-nLeft-nRight), (cyImage-nBottom)+nBottom};
		if (!::IsRectEmpty(&rcDest) && !::IsRectEmpty(&rcSrc))
			DrawImage(pDC,rcDest.left, rcDest.top, rcDest.right-rcDest.left, rcDest.bottom-rcDest.top, 
			rcSrc.left, rcSrc.top,rcSrc.right-rcSrc.left, rcSrc.bottom-rcSrc.top);
	}

	// ����
	{
		RECT rcDest = {x+(cx-nRight), y+(cy-nBottom), (x+(cx-nRight))+nRight, (y+(cy-nBottom))+nBottom};
		RECT rcSrc = {cxImage-nRight, cyImage-nBottom, (cxImage-nRight)+nRight, (cyImage-nBottom)+nBottom};
		if (!::IsRectEmpty(&rcDest) && !::IsRectEmpty(&rcSrc))
			DrawImage(pDC,rcDest.left, rcDest.top, rcDest.right-rcDest.left, rcDest.bottom-rcDest.top, 
			rcSrc.left, rcSrc.top,rcSrc.right-rcSrc.left, rcSrc.bottom-rcSrc.top);
	}

	// ����
	{
		RECT rcDest = {x, y+(cy-nBottom), x+nLeft, (y+(cy-nBottom))+nBottom};
		RECT rcSrc = {0, cyImage-nBottom, nLeft, (cyImage-nBottom)+nBottom};
		if (!::IsRectEmpty(&rcDest) && !::IsRectEmpty(&rcSrc))
			DrawImage(pDC,rcDest.left, rcDest.top, rcDest.right-rcDest.left, rcDest.bottom-rcDest.top, 
			rcSrc.left, rcSrc.top,rcSrc.right-rcSrc.left, rcSrc.bottom-rcSrc.top);
	}

	// �м�
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

//for GIF

bool CMyImage::TestGIF()
{
	UINT count = 0;
	count = m_pImage->GetFrameDimensionsCount();
	GUID* pDimensionIDs = new GUID[count];

	// �õ���֡�Ķ����б�
	m_pImage->GetFrameDimensionsList(pDimensionIDs, count);

	//��ȡ��֡��
	m_nFrameCount =  m_pImage->GetFrameCount(&pDimensionIDs[0]);

	// ����ͼ�����������Ŀ PropertyItemEquipMake.
	// ��ȡ����Ŀ�Ĵ�С.
	int nSize =  m_pImage->GetPropertyItemSize(PropertyTagFrameDelay);

	// Ϊ������Ŀ����ռ�.
	m_pPropertyItem = (PropertyItem*) malloc(nSize);
	m_pImage->GetPropertyItem(PropertyTagFrameDelay, nSize, m_pPropertyItem);
	delete pDimensionIDs;

	return m_nFrameCount > 1;
}

bool CMyImage::DrawFrameGIF(HWND hwnd, const RECT& rectDest)
{
	if (!TestGIF()) 
		return false;

	m_bIsInit = TRUE;
	m_hWnd = hwnd;
	m_rcGif = rectDest;
	m_nFramePosition = 0;

	long lPause = ((long*) m_pPropertyItem->value)[m_nFramePosition] * 10;

	CreateTimerQueueTimer(&m_hTimer, NULL, (WAITORTIMERCALLBACK)TimerRoute, this, 
		lPause, lPause, WT_EXECUTEINTIMERTHREAD);

	return true;
}

VOID CALLBACK CMyImage::TimerRoute(PVOID lpParam, BOOLEAN TimerOrWaitFired)
{
	ASSERT(lpParam);
	CMyImage *pImage = reinterpret_cast<CMyImage *> (lpParam);
	if (!pImage->m_bIsPause) {
		pImage->DrawGIF();
	} 
}

bool CMyImage::DrawGIF()
{	
	if (m_pImage != NULL) {
		GUID   pageGuid = FrameDimensionTime;

		RectF rcDrawRect;
		rcDrawRect.X = (REAL)m_rcGif.left;
		rcDrawRect.Y = (REAL)m_rcGif.top;
		rcDrawRect.Width = (REAL)m_rcGif.Width();
		rcDrawRect.Height = (REAL)m_rcGif.Height();

		HDC hdc= GetDC(m_hWnd);
		if (hdc)
		{
			Graphics graphics(hdc);
			graphics.DrawImage(m_pImage,rcDrawRect, 0,0,rcDrawRect.Width,rcDrawRect.Height,UnitPixel);
			::ReleaseDC(m_hWnd, hdc);
		}

		m_pImage->SelectActiveFrame(&pageGuid, m_nFramePosition++);		

		if (m_nFramePosition == m_nFrameCount)
			m_nFramePosition = 0;

		return true;
	}

	return false;
}
/*
void CMyImage::InitializeGIF()
{
	m_nFrameCount = 0;
	m_nFramePosition = 0;
	m_pPropertyItem = NULL;

	m_hThread = NULL;
	m_pDC = NULL;
	m_rcGif = CRect(0, 0, 0, 0);

	m_hExitEvent = CreateEvent(NULL,TRUE,FALSE,NULL);
	m_hPause = CreateEvent(NULL,TRUE,TRUE,NULL);
}



bool CMyImage::DrawGif(CDC * pDC, HWND hWnd, const RECT& rectDest)
{
	m_pDC = pDC;
	m_rcGif = rectDest;
	m_hWnd = hWnd;

	Graphics graphics(m_pDC->GetSafeHdc());
	Pen pen(Color(255, 0, 0));
	graphics.DrawLine(&pen, 20, 20, 200, 200);

	if (TRUE)
	{
		if (m_hThread == NULL)
		{

			unsigned int nTID = 0;

			m_hThread = (HANDLE) _beginthreadex( NULL, 0, _ThreadAnimationProc, this, CREATE_SUSPENDED,&nTID);

			if (!m_hThread)
			{
				TRACE(_T("Couldn't start a GIF animation thread\n"));
				return true;
			} 
			else 
				ResumeThread(m_hThread);
		}
	} 

	return false;

}

UINT CALLBACK CMyImage::_ThreadAnimationProc(LPVOID pParam)
{
	ASSERT(pParam);
	CMyImage *pImage = reinterpret_cast<CMyImage *> (pParam);
	pImage->ThreadAnimation();

	return 0;
}

void CMyImage::ThreadAnimation()
{
	m_nFramePosition = 0;

	bool bExit = false;
	while (bExit == false)
	{
		bExit = DrawFrameGif();
	}
}

bool CMyImage::DrawFrameGif()
{
	::WaitForSingleObject(m_hPause, INFINITE);

//	GUID   pageGuid = FrameDimensionTime;

	RectF rcDrawRect;
	rcDrawRect.X = (REAL)10;
	rcDrawRect.Y = (REAL)10;
	rcDrawRect.Width = (REAL)m_pImage->GetWidth();
	rcDrawRect.Height = (REAL)m_pImage->GetHeight();
	int nWidth = m_pImage->GetWidth();
	int nHeight = m_pImage->GetHeight();
	if (m_pDC)
	{
		Graphics graphics(m_pDC->GetSafeHdc());
		graphics.DrawImage(m_pImage, rcDrawRect, 0, 0, (REAL)nWidth, (REAL)nHeight,UnitPixel);
		Pen pen(Color(0, 255, 0));
		graphics.DrawLine(&pen, 10, 10, 100, 100);
	}

	m_pImage->SelectActiveFrame(&pageGuid, m_nFramePosition++);		

	if (m_nFramePosition == m_nFrameCount)
		m_nFramePosition = 0;

	long lPause = ((long*) m_pPropertyItem->value)[m_nFramePosition] * 10;
	
	DWORD dwErr = WaitForSingleObject(m_hExitEvent, lPause);

	return dwErr == WAIT_OBJECT_0;
}

void CMyImage::DestroyGIF()
{
	if (m_hThread)
	{
		SetEvent(m_hExitEvent);
		WaitForSingleObject(m_hThread, INFINITE);
	}

	CloseHandle(m_hThread);
	CloseHandle(m_hExitEvent);
	CloseHandle(m_hPause);

	free(m_pPropertyItem);

	m_pPropertyItem = NULL;
	m_hThread = NULL;
	m_hExitEvent = NULL;
	m_hPause = NULL;
}*/