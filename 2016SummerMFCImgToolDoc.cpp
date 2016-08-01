
// 2016SummerMFCImgToolDoc.cpp : CMy2016SummerMFCImgToolDoc 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "2016SummerMFCImgTool.h"
#endif

#include "2016SummerMFCImgToolDoc.h"
#include "FileNewDlg.h"

#include <propkey.h>

#include "IppImage/IppConvert.h"
#include "IppImage/IppImage.h"
#include "IppImage/IppEnhance.h"
#include "BrightnessContrastDlg.h"
#include "GammaCorrectionDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMy2016SummerMFCImgToolDoc

IMPLEMENT_DYNCREATE(CMy2016SummerMFCImgToolDoc, CDocument)

BEGIN_MESSAGE_MAP(CMy2016SummerMFCImgToolDoc, CDocument)
	ON_COMMAND(ID_WINDOW_DUPLICATE, &CMy2016SummerMFCImgToolDoc::OnWindowDuplicate)
	ON_COMMAND(ID_EDIT_COPY, &CMy2016SummerMFCImgToolDoc::OnEditCopy)
	ON_COMMAND(ID_IMAGE_INVERSE, &CMy2016SummerMFCImgToolDoc::OnImageInverse)
	ON_COMMAND(ID_BRIGHRNESS_CONTRAST, &CMy2016SummerMFCImgToolDoc::OnBrighrnessContrast)
	ON_COMMAND(ID_GAMMA_CORRECTION, &CMy2016SummerMFCImgToolDoc::OnGammaCorrection)
END_MESSAGE_MAP()


// CMy2016SummerMFCImgToolDoc 생성/소멸
#define CONVERT_DIB_TO_BYTEIMAGE(m_Dib, img)\
	IppByteImage img; \
	IppDibToImage(m_Dib, img);

#define CONVERT_IMAGE_TO_DIB \
	IppDib dib; \
	IppImageToDib(img, dib);

CMy2016SummerMFCImgToolDoc::CMy2016SummerMFCImgToolDoc()
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CMy2016SummerMFCImgToolDoc::~CMy2016SummerMFCImgToolDoc()
{
}

BOOL CMy2016SummerMFCImgToolDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	BOOL ret = TRUE;

	if (theApp.m_pNewDib == nullptr){
	CFileNewDlg dlg;

	if (dlg.DoModal() == IDOK)	 {
		if (dlg.m_nType == 0)
			ret = m_Dib.CreateGrayBitmap(dlg.m_nWidth, dlg.m_nHeight);
		else
			ret = m_Dib.CreateRgbBitmap(dlg.m_nWidth, dlg.m_nHeight);
	}
	else
		ret = FALSE;
	}
	else{
		m_Dib = *(theApp.m_pNewDib);
		theApp.m_pNewDib = NULL;
	}

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return ret;
}




// CMy2016SummerMFCImgToolDoc serialization

void CMy2016SummerMFCImgToolDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CMy2016SummerMFCImgToolDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CMy2016SummerMFCImgToolDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMy2016SummerMFCImgToolDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMy2016SummerMFCImgToolDoc 진단

#ifdef _DEBUG
void CMy2016SummerMFCImgToolDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMy2016SummerMFCImgToolDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMy2016SummerMFCImgToolDoc 명령


BOOL CMy2016SummerMFCImgToolDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return m_Dib.Save(CT2A(lpszPathName));
}


BOOL CMy2016SummerMFCImgToolDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	BOOL res = m_Dib.Load(CT2A(lpszPathName));

	if (res)
		AfxPrintInfo(_T("[파일 열기] 파일 경로: %s, 가로크기: %d 픽셀, 세로크게: %d픽셀, 색상수 : %d"), lpszPathName, m_Dib.GetWidth(), m_Dib.GetHeight(), 0x01 << m_Dib.GetBitCount());

	return res;
}


void CMy2016SummerMFCImgToolDoc::OnWindowDuplicate()
{
	AfxNewBitmap(m_Dib);
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CMy2016SummerMFCImgToolDoc::OnEditCopy()
{
	if (m_Dib.IsValid())
		m_Dib.CopyToClipboard();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CMy2016SummerMFCImgToolDoc::OnImageInverse()
{
	CONVERT_DIB_TO_BYTEIMAGE(m_Dib, img);
	IppInverse(img);
	CONVERT_IMAGE_TO_DIB(img, dib);

	AfxPrintInfo(_T("[반전] 입력 영상 : %s"), GetTitle());
	AfxNewBitmap(dib);
}


void CMy2016SummerMFCImgToolDoc::OnBrighrnessContrast()
{
	CBrightnessContrastDlg dlg;

	if (dlg.DoModal() == IDOK)
	{
		CONVERT_DIB_TO_BYTEIMAGE(m_Dib, img);
		IppBrightness(img, dlg.m_nBrightness);
		IppContrast(img, dlg.m_nContrast);
		CONVERT_IMAGE_TO_DIB(img, dib);

		AfxPrintInfo(_T("[밝기/명암비 조절] 입력 영상 : %s, 밝기 : %d, 명암비 : %d%%"), GetTitle(), dlg.m_nBrightness, dlg.m_nContrast);
		AfxNewBitmap(dib);

	}
}


void CMy2016SummerMFCImgToolDoc::OnGammaCorrection()
{
	CGammaCorrectionDlg dlg;

	if (dlg.DoModal() == IDOK){
		CONVERT_DIB_TO_BYTEIMAGE(m_Dib, img);
		IppGammaCorrection(img, dlg.m_fGamma);
		CONVERT_IMAGE_TO_DIB(img, dib);

		AfxPrintInfo(_T("[감마 보정] 입력 영상: %s, 감마 : %4.2f"), GetTitle(), dlg.m_fGamma);
		AfxNewBitmap(dib);
	}
}
