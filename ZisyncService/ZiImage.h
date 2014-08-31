#pragma once

class CZiImage
{
public:
	Bitmap *			m_pImage;                       //ͼƬ����
	Image *				m_pImg;
	TCHAR               m_strImageName[MAX_PATH];       //ͼƬ����
	RECT				m_rcNinePart;
	HBITMAP				m_hBitmap;
/*
public:
	HANDLE				m_hThread;
	HANDLE				m_hPause;
	HANDLE				m_hExitEvent;
	HWND				m_hWnd;
	HINSTANCE			m_hInst;
*/
public:
	CZiImage();
	~CZiImage();

	//�Ƿ����
	bool IsNull();
	//��ȡ���
	INT GetWidth();
	//��ȡ�߶�
	INT GetHeight();

	void SetNinePart(CONST LPRECT lprcNinePart);
	HBITMAP ImageToBitmap(/*HDC hDC*/);

	//������
public:
	//����ͼƬ
	bool DestroyImage();
	//����ͼƬ
	bool LoadImage(LPCTSTR pszFileName);
	//����ͼƬ
	bool LoadImage(HINSTANCE hInstance, LPCTSTR pszResourceName, LPCTSTR pszType);
	bool LoadImage(HINSTANCE hInstance, UINT nIDResource, LPCTSTR lpszResType = NULL);

	//�滭����
public:
	//�滭ͼ��
	bool DrawImage(CDC * pDC, INT nXPos, INT nYPos);
	//�滭ͼ��
	bool DrawImage(CDC * pDC, INT nXPos, INT nYPos, INT nDestWidth, INT nDestHeight);
	//�滭ͼ��
	bool DrawImage(CDC * pDC, RECT &rc);
	//�滭ͼ��
	bool DrawImage(CDC * pDC, INT nXDest, INT nYDest, INT nDestWidth, INT nDestHeight, INT nXScr, INT nYSrc);
	//�滭ͼ��
	bool DrawImage(CDC * pDC, INT nXDest, INT nYDest, INT nDestWidth, INT nDestHeight, INT nXScr, INT nYSrc, INT nSrcWidth, INT nSrcHeight);

	//͸���滭
public:
	//��ϻ滭
	bool AlphaDrawImage(CDC * pDestDC, INT xDest, INT yDest, BYTE cbAlphaDepth);
	//��ϻ滭
	bool AlphaDrawImage(CDC * pDestDC, INT xDest, INT yDest, INT cxDest, INT cyDest, INT xSrc, INT ySrc, BYTE cbAlphaDepth);
	//��ϻ滭
	bool AlphaDrawImage(CDC * pDestDC, INT xDest, INT yDest, INT cxDest, INT cyDest, INT xSrc, INT ySrc, INT cxSrc, INT cySrc, BYTE cbAlphaDepth);

public:
	//�滭ͼ��
	bool Draw( CDC * pDC, INT x, INT y, INT cx, INT cy,INT nLeft,INT nTop,INT nRight,INT nBottom );
	//�滭ͼ��
	bool Draw( CDC * pDC, const RECT& rectDest, const RECT& rectSrc );
	//�滭ͼ��
	bool Draw( CDC * pDC, const RECT& rectDest );


public:
	UINT				m_nFrameCount;
	UINT				m_nFramePosition;
	PropertyItem*		m_pPropertyItem;
	HANDLE				m_hTimer;

	HWND				m_hWnd;
	CRect				m_rcGif;

	BOOL				m_bIsInit;
	BOOL				m_bIsPause;

	bool TestGIF();
	BOOL IsInitGIF(){return  m_bIsInit;}
	bool DrawFrameGIF(HWND hwnd, const RECT& rectDest);
	bool DrawGIF();
	static VOID CALLBACK  TimerRoute(PVOID lpParam, BOOLEAN TimerOrWaitFired);

/*	void InitializeGIF();
	void DestroyGIF();	
	bool DrawGif(CDC * pDC, HWND hWnd, const RECT& rectDest);
	bool DrawFrameGif();
	void ThreadAnimation();
	static UINT CALLBACK _ThreadAnimationProc(LPVOID pParam);*/
};
