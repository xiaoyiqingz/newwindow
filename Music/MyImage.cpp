#include "StdAfx.h"
#include "MyImage.h"


CMyImage::CMyImage(void)
{
	m_pImage=NULL;
	ZeroMemory(m_strImageName, sizeof(m_strImageName) );
}


CMyImage::~CMyImage(void)
{
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
	m_pImage=Image::FromFile((LPCWSTR)strFileName);

	//�����ж�
	if ((m_pImage==NULL)||(m_pImage->GetLastStatus()!=Ok))
	{
		DestroyImage();
		return false;
	}

	return true;
}

//����ͼƬ
bool CMyImage::LoadImage(HINSTANCE hInstance, LPCTSTR pszResourceName)
{
	//�����ж�
	ASSERT(m_pImage==NULL);
	if (m_pImage!=NULL) return false;

	//������Դ
	HRSRC hResource=FindResource(hInstance,pszResourceName,TEXT("IMAGE"));
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
	m_pImage=Image::FromStream(pIStream);

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

bool CMyImage::LoadImage(HINSTANCE hInstance, UINT nIDResource)
{
	//�����ж�
	ASSERT(m_pImage==NULL);
	if (m_pImage!=NULL) return false;

	//������Դ
	HRSRC hResource=FindResource(hInstance, MAKEINTRESOURCE(nIDResource), RT_BITMAP);
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
	m_pImage=Image::FromStream(pIStream);

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

	//�滭ͼ��
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
