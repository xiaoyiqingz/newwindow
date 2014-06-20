#pragma once

class CMyImage
{
public:
	Bitmap *			m_pImage;                       //Í¼Æ¬¶ÔÏó
	TCHAR               m_strImageName[MAX_PATH];       //Í¼Æ¬Ãû³Æ
	RECT				m_rcNinePart;
	HBITMAP				m_hBitmap;

public:
	CMyImage();
	~CMyImage();

	//ÊÇ·ñ¼ÓÔØ
	bool IsNull();
	//»ñÈ¡¿í¶È
	INT GetWidth();
	//»ñÈ¡¸ß¶È
	INT GetHeight();

	void SetNinePart(CONST LPRECT lprcNinePart);
	HBITMAP ImageToBitmap(/*HDC hDC*/);

	//¹ÜÀíº¯Êý
public:
	//Ïú»ÙÍ¼Æ¬
	bool DestroyImage();
	//¼ÓÔØÍ¼Æ¬
	bool LoadImage(LPCTSTR pszFileName);
	//¼ÓÔØÍ¼Æ¬
	bool LoadImage(HINSTANCE hInstance, LPCTSTR pszResourceName, LPCTSTR pszType);
	bool LoadImage(HINSTANCE hInstance, UINT nIDResource);

	//»æ»­º¯Êý
public:
	//»æ»­Í¼Ïñ
	bool DrawImage(CDC * pDC, INT nXPos, INT nYPos);
	//»æ»­Í¼Ïñ
	bool DrawImage(CDC * pDC, INT nXPos, INT nYPos, INT nDestWidth, INT nDestHeight);
	//»æ»­Í¼Ïñ
	bool DrawImage(CDC * pDC, RECT &rc);
	//»æ»­Í¼Ïñ
	bool DrawImage(CDC * pDC, INT nXDest, INT nYDest, INT nDestWidth, INT nDestHeight, INT nXScr, INT nYSrc);
	//»æ»­Í¼Ïñ
	bool DrawImage(CDC * pDC, INT nXDest, INT nYDest, INT nDestWidth, INT nDestHeight, INT nXScr, INT nYSrc, INT nSrcWidth, INT nSrcHeight);

	//Í¸Ã÷»æ»­
public:
	//»ìºÏ»æ»­
	bool AlphaDrawImage(CDC * pDestDC, INT xDest, INT yDest, BYTE cbAlphaDepth);
	//»ìºÏ»æ»­
	bool AlphaDrawImage(CDC * pDestDC, INT xDest, INT yDest, INT cxDest, INT cyDest, INT xSrc, INT ySrc, BYTE cbAlphaDepth);
	//»ìºÏ»æ»­
	bool AlphaDrawImage(CDC * pDestDC, INT xDest, INT yDest, INT cxDest, INT cyDest, INT xSrc, INT ySrc, INT cxSrc, INT cySrc, BYTE cbAlphaDepth);

public:
	//»æ»­Í¼Ïñ
	bool Draw( CDC * pDC, INT x, INT y, INT cx, INT cy,INT nLeft,INT nTop,INT nRight,INT nBottom );
	//»æ»­Í¼Ïñ
	bool Draw( CDC * pDC, const RECT& rectDest, const RECT& rectSrc );
	//»æ»­Í¼Ïñ
	bool Draw( CDC * pDC, const RECT& rectDest );
};

