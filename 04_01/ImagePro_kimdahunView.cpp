﻿
// ImagePro_kimdahunView.cpp: CImageProkimdahunView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ImagePro_kimdahun.h"
#endif

#include "ImagePro_kimdahunDoc.h"
#include "ImagePro_kimdahunView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define TWO_IMAGES 1
#define THREE_IMAGES 2


// CImageProkimdahunView

IMPLEMENT_DYNCREATE(CImageProkimdahunView, CScrollView)

BEGIN_MESSAGE_MAP(CImageProkimdahunView, CScrollView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CImageProkimdahunView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_PIXEL_ADD, &CImageProkimdahunView::OnPixelAdd)
	ON_COMMAND(ID_APP_ABOUT, &CImageProkimdahunView::OnAppAbout)
	ON_COMMAND(ID_HISTO_EQ, &CImageProkimdahunView::OnHistoEq)
	ON_COMMAND(ID_PIXEL_TWO_IMAGE_ADD, &CImageProkimdahunView::OnPixelTwoImageAdd)
END_MESSAGE_MAP()

// CImageProkimdahunView 생성/소멸

CImageProkimdahunView::CImageProkimdahunView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CImageProkimdahunView::~CImageProkimdahunView()
{
}

BOOL CImageProkimdahunView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CScrollView::PreCreateWindow(cs);
}

// CImageProkimdahunView 그리기

void CImageProkimdahunView::OnDraw(CDC* pDC)//CDC는 화면에 출력하는 것을 관장하는 클래스
{
	CImageProkimdahunDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc->inputImg == NULL)return;
	if (pDoc->depth == 1) {
		for (int y = 0; y < pDoc->imageHeight; y++) {
			for (int x = 0; x < pDoc->imageWidth; x++) {
				pDC->SetPixel(x, y, RGB(pDoc->inputImg[y][x], pDoc->inputImg[y][x], pDoc->inputImg[y][x]));//
			}
		}
		if (viewMode == THREE_IMAGES) {
			for (int y = 0; y < pDoc->imageHeight; y++) {
				for (int x = 0; x < pDoc->imageWidth; x++) {
					pDC->SetPixel(x+pDoc->imageWidth+30, y, RGB(pDoc->inputimg2[y][x], pDoc->inputimg2[y][x], pDoc->inputimg2[y][x]));//
				}
			}
			for (int y = 0; y < pDoc->imageHeight; y++) {
				for (int x = 0; x < pDoc->imageWidth; x++) {
					pDC->SetPixel(x + pDoc->imageWidth*2 + 60, y, RGB(pDoc->resultImg[y][x], pDoc->resultImg[y][x], pDoc->resultImg[y][x]));//
				}
			}
		}
		else {
			for (int y = 0; y < pDoc->imageHeight; y++) {
				for (int x = 0; x < pDoc->imageWidth; x++) {
					pDC->SetPixel(x + pDoc->imageWidth + 30, y, RGB(pDoc->resultImg[y][x], pDoc->resultImg[y][x], pDoc->resultImg[y][x]));//
				}
			}
		}
	}

	else if (pDoc->depth == 3) {
		for (int y = 0; y < pDoc->imageHeight; y++) {
			for (int x = 0; x < pDoc->imageWidth; x++) {
				pDC->SetPixel(x, y, RGB(pDoc->inputImg[y][3*x], pDoc->inputImg[y][3*x+1], pDoc->inputImg[y][3*x+2]));//
			}
		}
		if (viewMode == THREE_IMAGES) {
			for (int y = 0; y < pDoc->imageHeight; y++) {
				for (int x = 0; x < pDoc->imageWidth; x++) {
					pDC->SetPixel(x + pDoc->imageWidth + 30, y, RGB(pDoc->inputimg2[y][3*x], pDoc->inputimg2[y][3 * x+1], pDoc->inputimg2[y][3 * x+2]));//
				}
			}
			for (int y = 0; y < pDoc->imageHeight; y++) {
				for (int x = 0; x < pDoc->imageWidth; x++) {
					pDC->SetPixel(x + pDoc->imageWidth * 2 + 60, y, RGB(pDoc->resultImg[y][3 * x], pDoc->resultImg[y][3 * x+1], pDoc->resultImg[y][3 * x]));//
				}
			}
		}
		else {
			for (int y = 0; y < pDoc->imageHeight; y++) {
				for (int x = 0; x < pDoc->imageWidth; x++) {
					pDC->SetPixel(x + pDoc->imageWidth + 30, y, RGB(pDoc->resultImg[y][3 * x], pDoc->resultImg[y][3 * x+1], pDoc->resultImg[y][3 * x+2]));//
				}
			}
		}
	}


	//for (int y = 0; y < 256; y++) {// original image 출력
	//	for (int x = 0; x < 256; x++) {
	//		pDC->SetPixel(x, y, RGB(pDoc->inputImg[y][x], pDoc->inputImg[y][x], pDoc->inputImg[y][x]));//
	//	}
	//}
	//if (viewMode == THREE_IMAGES) {

	//	for (int y = 0; y < 256; y++) {// result image 출력
	//		for (int x = 0; x < 256; x++) {
	//			pDC->SetPixel(x + 300, y, RGB(pDoc->inputimg2[y][x], pDoc->inputimg2[y][x], pDoc->inputimg2[y][x]));//
	//		}
	//	}
	//	for (int y = 0; y < 256; y++) {// result image 출력
	//		for (int x = 0; x < 256; x++) {
	//			pDC->SetPixel(x + 600, y, RGB(pDoc->resultImg[y][x], pDoc->resultImg[y][x], pDoc->resultImg[y][x]));//
	//		}
	//	}
	//}
	//else {
	//	for (int y = 0; y < 256; y++) {// result image 출력
	//		for (int x = 0; x < 256; x++) {
	//			pDC->SetPixel(x + 300, y, RGB(pDoc->resultImg[y][x], pDoc->resultImg[y][x], pDoc->resultImg[y][x]));//
	//		}
	//	}
	//}
	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}

void CImageProkimdahunView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 이 뷰의 전체 크기를 계산합니다.

	sizeTotal.cx = 2048;
	sizeTotal.cy = 1024;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CImageProkimdahunView 인쇄


void CImageProkimdahunView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CImageProkimdahunView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CImageProkimdahunView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CImageProkimdahunView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CImageProkimdahunView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CImageProkimdahunView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CImageProkimdahunView 진단

#ifdef _DEBUG
void CImageProkimdahunView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CImageProkimdahunView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CImageProkimdahunDoc* CImageProkimdahunView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageProkimdahunDoc)));
	return (CImageProkimdahunDoc*)m_pDocument;
}
#endif //_DEBUG


// CImageProkimdahunView 메시지 처리기


void CImageProkimdahunView::OnPixelAdd()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProkimdahunDoc* pDoc;
	pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->PixelAdd();
	viewMode = TWO_IMAGES;
	Invalidate(FALSE);
}


void CImageProkimdahunView::OnAppAbout()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	// TODO: 여기에 명령 처리기 코드를 추가합니다
	CImageProkimdahunDoc* pDoc;
	pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->Pixeltimes();

	Invalidate(FALSE);
}


void CImageProkimdahunView::OnHistoEq()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProkimdahunDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->PixelHistoEq();
	viewMode = TWO_IMAGES;
	Invalidate(FALSE);
}


void CImageProkimdahunView::OnPixelTwoImageAdd()
{
	
	CImageProkimdahunDoc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);

	pDoc->PixelTwoImageAdd();
	viewMode = THREE_IMAGES;
	Invalidate(FALSE);

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}
