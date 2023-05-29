
// ImageProkimdahunView.cpp: CImageProkimdahunView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ImageProkimdahun.h"
#endif

#include "ImageProkimdahunDoc.h"
#include "ImageProkimdahunView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define TWO_IMAGES 1
#define THREE_IMAGES 2
#define TWO_IMAGES_SCALED 4


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
	ON_COMMAND(ID_PIXEL_HISTO_EQ, &CImageProkimdahunView::OnPixelHistoEq)
	ON_COMMAND(ID_PIXEL_TWO_IMAGE_ADD, &CImageProkimdahunView::OnPixelTwoImageAdd)
	ON_COMMAND(ID_REGION_SHARPENING, &CImageProkimdahunView::OnRegionSharpening)
	ON_COMMAND(ID_REGION_MEANING, &CImageProkimdahunView::OnRegionMeaning)
	ON_COMMAND(ID_REGION_SOBEL, &CImageProkimdahunView::OnRegionSobel)
	ON_COMMAND(ID_REGION_MEDIAN, &CImageProkimdahunView::OnRegionMedian)
	ON_COMMAND(ID_EROSION, &CImageProkimdahunView::OnErosion)
	ON_COMMAND(ID_DILATTION, &CImageProkimdahunView::OnDilattion)
	ON_COMMAND(ID_OPENING, &CImageProkimdahunView::OnOpening)
	ON_COMMAND(ID_CLOSING, &CImageProkimdahunView::OnClosing)
	ON_COMMAND(ID_GEOMETRY_ZOOMIN_PIXEL_COPY, &CImageProkimdahunView::OnGeometryZoominPixelCopy)
	ON_COMMAND(ID_GEOMETRY_XOOMIN_INTERPOLATION, &CImageProkimdahunView::OnGeometryXoominInterpolation)
	ON_COMMAND(ID_GEOMETRY_ZOOMOUT_SUBSAMPLING, &CImageProkimdahunView::OnGeometryZoomoutSubsampling)
	ON_COMMAND(ID_GEOMETRY_ZOOMOUT_AVG, &CImageProkimdahunView::OnGeometryZoomoutAvg)
	ON_COMMAND(ID_LABELING, &CImageProkimdahunView::OnLabeling)
	ON_COMMAND(ID_LABELING_STACK, &CImageProkimdahunView::OnLabelingStack)
	ON_COMMAND(ID_GEOMETRY_ROTATE, &CImageProkimdahunView::OnGeometryRotate)
	ON_COMMAND(ID_BorderFollow, &CImageProkimdahunView::OnBorderfollow)
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

void CImageProkimdahunView::OnDraw(CDC* pDC)
{
	CImageProkimdahunDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg == NULL)return;

	if (pDoc->depth == 1) {
		for (int y = 0; y < pDoc->imageHeight; y++) {
			for (int x = 0; x < pDoc->imageWidth; x++) {
				pDC->SetPixel(x, y, RGB(pDoc->inputImg[y][x], pDoc->inputImg[y][x], pDoc->inputImg[y][x]));
			}
		}
		if (viewMode == THREE_IMAGES) {
			for (int y = 0; y < pDoc->imageHeight; y++) {
				for (int x = 0; x < pDoc->imageWidth; x++) {
					pDC->SetPixel(x + pDoc->imageWidth + 30, y, RGB(pDoc->inputImg2[y][x], pDoc->inputImg2[y][x], pDoc->inputImg2[y][x]));
				}
			}
			for (int y = 0; y < pDoc->imageHeight; y++) {
				for (int x = 0; x < pDoc->imageWidth; x++) {
					pDC->SetPixel(x + pDoc->imageWidth*2 + 60, y, RGB(pDoc->resultImg[y][x], pDoc->resultImg[y][x], pDoc->resultImg[y][x]));
				}
			}
		}
		else if (viewMode == TWO_IMAGES_SCALED) {
			for (int y = 0; y < pDoc->gImageHeight; y++) {
				for (int x = 0; x < pDoc->gImageWidth; x++) {
					pDC->SetPixel(x + pDoc->imageWidth + 30, y, RGB(pDoc->gResultImg[y][x], pDoc->gResultImg[y][x], pDoc->gResultImg[y][x]));
				}
			}
		}
		else {
			for (int y = 0; y < pDoc->imageHeight; y++) {
				for (int x = 0; x < pDoc->imageWidth; x++) {
					pDC->SetPixel(x + pDoc->imageWidth + 30, y, RGB(pDoc->resultImg[y][x], pDoc->resultImg[y][x], pDoc->resultImg[y][x]));
				}
			}
		}
	}
	else if (pDoc->depth == 3) {
		for (int y = 0; y < pDoc->imageHeight; y++) {
			for (int x = 0; x < pDoc->imageWidth; x++) {
				pDC->SetPixel(x, y, RGB(pDoc->inputImg[y][3*x], pDoc->inputImg[y][3*x+1], pDoc->inputImg[y][3*x+2]));
			}
		}
		if (viewMode == THREE_IMAGES) {
			for (int y = 0; y < pDoc->imageHeight; y++) {
				for (int x = 0; x < pDoc->imageWidth; x++) {
					pDC->SetPixel(x+pDoc->imageWidth+30, y, RGB(pDoc->inputImg2[y][3 * x], pDoc->inputImg2[y][3 * x + 1], pDoc->inputImg2[y][3 * x + 2]));
				}
			}
			for (int y = 0; y < pDoc->imageHeight; y++) {
				for (int x = 0; x < pDoc->imageWidth; x++) {
					pDC->SetPixel(x+pDoc->imageWidth*2+60, y, RGB(pDoc->resultImg[y][3 * x], pDoc->resultImg[y][3 * x + 1], pDoc->resultImg[y][3 * x + 2]));
				}
			}
		}
		else if (viewMode == TWO_IMAGES_SCALED) {
			for (int y = 0; y < pDoc->gImageHeight; y++) {
				for (int x = 0; x < pDoc->gImageWidth; x++) {
					pDC->SetPixel(x + pDoc->imageWidth + 30, y, RGB(pDoc->gResultImg[y][3*x], pDoc->gResultImg[y][3*x+1], pDoc->gResultImg[y][3*x+2]));
				}
			}
		}
		else {
			for (int y = 0; y < pDoc->imageHeight; y++) {
				for (int x = 0; x < pDoc->imageWidth; x++) {
					pDC->SetPixel(x + pDoc->imageWidth + 30, y, RGB(pDoc->resultImg[y][3 * x], pDoc->resultImg[y][3 * x + 1], pDoc->resultImg[y][3 * x + 2]));
				}
			}
		}
	}

	

	if (!pDoc)
		return;

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

	if (pDoc->inputImg == NULL)return;
	pDoc->PixelAdd();
	viewMode = TWO_IMAGES;//OnDraw에서 else로 되어있기때문에 안해줘도 상관 없다.
	Invalidate(FALSE);
}


void CImageProkimdahunView::OnPixelHistoEq()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다
	CImageProkimdahunDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg == NULL)return;
	pDoc->PixelHistoEq();
	viewMode = TWO_IMAGES;
	Invalidate(FALSE);

}


void CImageProkimdahunView::OnPixelTwoImageAdd()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProkimdahunDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->PixelTwoImageAdd();
	viewMode = THREE_IMAGES;

	Invalidate(FALSE);

}


void CImageProkimdahunView::OnRegionSharpening()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProkimdahunDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg == NULL)return;
	pDoc->RegionSharpening();
	viewMode = TWO_IMAGES;
	Invalidate(FALSE);
}


void CImageProkimdahunView::OnRegionMeaning()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProkimdahunDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg == NULL)return;
	pDoc->RegionMeaning();

	viewMode = TWO_IMAGES;
	Invalidate(FALSE);
}


void CImageProkimdahunView::OnRegionSobel()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProkimdahunDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg == NULL)return;
	pDoc->RegionSobel();
	viewMode = TWO_IMAGES;
	Invalidate(FALSE);
}


void CImageProkimdahunView::OnRegionMedian()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProkimdahunDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg == NULL)return;
	pDoc->RegionMedian();
	viewMode = TWO_IMAGES;
	Invalidate(FALSE);
}


void CImageProkimdahunView::OnErosion()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProkimdahunDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg == NULL)return;
	pDoc->Erosion();
	viewMode = TWO_IMAGES;
	Invalidate(FALSE);
}


void CImageProkimdahunView::OnDilattion()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProkimdahunDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc->inputImg == NULL)return;
	pDoc->Dilation();
	viewMode = TWO_IMAGES;
	Invalidate(FALSE);
}


void CImageProkimdahunView::OnOpening()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProkimdahunDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg == NULL)return;
	pDoc->Opening();
	viewMode = TWO_IMAGES;
	Invalidate(FALSE);
}


void CImageProkimdahunView::OnClosing()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProkimdahunDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg == NULL)return;
	pDoc->Closing();
	viewMode = TWO_IMAGES;
	Invalidate(FALSE);
}


void CImageProkimdahunView::OnGeometryZoominPixelCopy()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProkimdahunDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg == NULL) return;
	pDoc->GeometryZoominPixelCopy();
	viewMode = TWO_IMAGES_SCALED;
	Invalidate(FALSE);
}


void CImageProkimdahunView::OnGeometryXoominInterpolation()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProkimdahunDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg == NULL) return;
	pDoc->GeometryZoominInterpolation();
	viewMode = TWO_IMAGES_SCALED;
	Invalidate(FALSE);
}


void CImageProkimdahunView::GeometryZoomminInterpolation()
{
	// TODO: 여기에 구현 코드 추가.
}


void CImageProkimdahunView::OnGeometryZoomoutSubsampling()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	CImageProkimdahunDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg == NULL) return;
	pDoc->GeometryZoomoutSubsampling();
	viewMode = TWO_IMAGES_SCALED;
	Invalidate(FALSE);
}


void CImageProkimdahunView::OnGeometryZoomoutAvg()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProkimdahunDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg == NULL) return;
	pDoc->GeometryZoomoutAvg();
	viewMode = TWO_IMAGES_SCALED;
	Invalidate(FALSE);
}


void CImageProkimdahunView::OnLabeling()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProkimdahunDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg == NULL) return;
	pDoc->grass_label(0,0);
	viewMode = TWO_IMAGES;
	Invalidate(FALSE);
}


void CImageProkimdahunView::OnLabelingStack()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProkimdahunDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg == NULL) return;
	pDoc->m_BlobColoring(0, 0);
	viewMode = TWO_IMAGES;
	Invalidate(FALSE);
}


void CImageProkimdahunView::OnGeometryRotate()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProkimdahunDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg == NULL) return;
	pDoc->GeometryRotate();
	viewMode = TWO_IMAGES_SCALED;
	Invalidate(FALSE);
}


void CImageProkimdahunView::OnBorderfollow()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	CImageProkimdahunDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->m_BorderFollow(pDoc->imageHeight, pDoc->imageWidth);
	Invalidate(FALSE);
}
