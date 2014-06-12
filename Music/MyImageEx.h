#pragma once
#include "atlimage.h"

//äÖÈ¾ÐÅÏ¢
struct tagImageRender
{
	INT                             nXImage;                            //Í¼Æ¬Î»ÖÃ
	INT                             nYImage;                            //Í¼Æ¬Î»ÖÃ
	INT                             nXScreen;                           //äÖÈ¾Î»ÖÃ
	INT                             nYScreen;                           //äÖÈ¾Î»ÖÃ
	INT                             cxRender;                           //äÖÈ¾³ß´ç
	INT                             cyRender;                           //äÖÈ¾³ß´ç
};

class CMyImageEx :
	public CImage
{
protected:
	TCHAR     m_strImageName[MAX_PATH];           //Í¼Æ¬Ãû³Æ

public:
	CMyImageEx(void);
	~CMyImageEx(void);
	//´´½¨º¯Êý

public:
	//¼ÓÔØÍ¼Æ¬
	bool LoadImage(HINSTANCE hInstance, LPCTSTR pszResourceName, LPCTSTR pszType);
	//¼ÓÔØÍ¼Æ¬
	bool LoadImage(void * pDate ,DWORD dwSize);

	//ÇøÓòº¯Êý
public:
	//´´½¨ÇøÓò
	bool CreateImageRegion(CRgn & ImageRgn, COLORREF crTransColor);
	//´´½¨ÇøÓò
	bool CreateImageRegion(CRgn & ImageRgn, INT nXSrcPos, INT nYSrcPos, INT nSrcWidth, INT nSrcHeight, COLORREF crTransColor);

	//Ò»°ã»æ»­
public:
	//Ò»°ã»æ»­
	BOOL BitBlt( HDC hDestDC, int xDest, int yDest, DWORD dwROP = SRCCOPY );
	//Ò»°ã»æ»­
	BOOL BitBlt( HDC hDestDC, const POINT& pointDest, DWORD dwROP = SRCCOPY );
	//Ò»°ã»æ»­
	BOOL BitBlt( HDC hDestDC, int xDest, int yDest, int nDestWidth, int nDestHeight, int xSrc, int ySrc, DWORD dwROP = SRCCOPY );
	//Ò»°ã»æ»­
	BOOL BitBlt( HDC hDestDC, const RECT& rectDest, const POINT& pointSrc, DWORD dwROP = SRCCOPY );

	//»æ»­Í¼Æ¬
public:
	//Æ½ÆÌ»æ»­
	bool DrawImageTile(CDC * pDC, CRect & rcDestRect);
	//Æ½ÆÌ»æ»­
	bool DrawImageTile(CDC * pDC, INT nXPos, INT nYPos, INT nWidth, INT nHeight);

	//Í¸Ã÷»æ»­
public:
	//Í¸Ã÷»æ»­
	bool TransDrawImage(CDC * pDestDC, INT xDest, INT yDest, COLORREF crTransColor);
	//Í¸Ã÷»æ»­
	bool TransDrawImage(CDC * pDestDC, INT xDest, INT yDest, INT cxDest, INT cyDest, INT xSrc, INT ySrc, COLORREF crTransColor);
	//Í¸Ã÷»æ»­
	bool TransDrawImage(CDC * pDestDC, INT xDest, INT yDest, INT cxDest, INT cyDest, INT xSrc, INT ySrc, INT cxSrc, INT cySrc, COLORREF crTransColor);

	//Í¸Ã÷»æ»­
public:
	//»ìºÏ»æ»­
	bool AlphaDrawImage(CDC * pDestDC, INT xDest, INT yDest, BYTE cbAlphaDepth);
	//»ìºÏ»æ»­
	bool AlphaDrawImage(CDC * pDestDC, INT xDest, INT yDest, INT cxDest, INT cyDest, INT xSrc, INT ySrc, BYTE cbAlphaDepth);
	//»ìºÏ»æ»­
	bool AlphaDrawImage(CDC * pDestDC, INT xDest, INT yDest, INT cxDest, INT cyDest, INT xSrc, INT ySrc, INT cxSrc, INT cySrc, BYTE cbAlphaDepth);

	//»ìºÏ»æ»­
public:
	//»ìºÏ»æ»­
	bool BlendDrawImage(CDC * pDestDC, INT xDest, INT yDest, COLORREF crTransColor, BYTE cbAlphaDepth);
	//»ìºÏ»æ»­
	bool BlendDrawImage(CDC * pDestDC, INT xDest, INT yDest, INT cxDest, INT cyDest, INT xSrc, INT ySrc, COLORREF crTransColor, BYTE cbAlphaDepth);
	//»ìºÏ»æ»­
	bool BlendDrawImage(CDC * pDestDC, INT xDest, INT yDest, INT cxDest, INT cyDest, INT xSrc, INT ySrc, INT cxSrc, INT cySrc, COLORREF crTransColor, BYTE cbAlphaDepth);

	//¸¨Öúº¯Êý
public:
	//¾ØÐÎ¼ì²é
	bool IsRectIntersect(const CRect & rcRect, INT nXPos, INT nYPos, INT nWidth, INT nHeight);
	//ÇøÓò¼ÆËã
	bool GetDrawImageArea(INT xDest, INT yDest, INT cxDest, INT cyDest, INT xSrc, INT ySrc, CRect & rcDirty, tagImageRender & ImageRender);protected:
};

