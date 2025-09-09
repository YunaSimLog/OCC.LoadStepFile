// include required OCCT headers
#include <Standard_Version.hxx>
#include <Message_ProgressIndicator.hxx>
#include <Message_ProgressScope.hxx>
// for OCC graphic
#include <Aspect_DisplayConnection.hxx>
#include <WNT_Window.hxx>
#include <OpenGl_GraphicDriver.hxx>
// for object display
#include <V3d_Viewer.hxx>
#include <V3d_View.hxx>
#include <AIS_InteractiveContext.hxx>
#include <AIS_Shape.hxx>
// topology
#include <TopoDS.hxx>
#include <TopoDS_Shape.hxx>
#include <TopoDS_Compound.hxx>
// brep tools
#include <BRep_Builder.hxx>
#include <BRepTools.hxx>
// step I/E
#include <STEPControl_Reader.hxx>
#include <STEPControl_Writer.hxx>
// wrapper of pure C++ classes to ref classes
#include <NCollection_Haft.h>

// View Cube
#include <AIS_ViewCube.hxx>
#include <Prs3d_DatumAspect.hxx>
#include <Graphic3d_AspectText3d.hxx>
#include <Quantity_Color.hxx>

// 포인트 생성
// 기본 형상
#include <gp_Pnt.hxx>
#include <AIS_Point.hxx>
#include <TopoDS_Vertex.hxx>
#include  <Geom_CartesianPoint.hxx>

// 형상 생성 도구
#include <BRepBuilderAPI_MakeVertex.hxx>
#include <BRepPrimAPI_MakeSphere.hxx>

// AIS 시각화 관련
#include <AIS_Shape.hxx>
#include <Prs3d_PointAspect.hxx>
#include <AIS_InteractiveContext.hxx>

// 색상 관련
#include <Quantity_Color.hxx>

// 기타 OpenCascade 핸들 타입
#include <Standard_Handle.hxx>

// 화면 클릭된 곡면에 수직된 점 정보 가져오기 위함
#include <GeomAPI_ProjectPointOnSurf.hxx>

// 사각형 와이어 생성을 위함.
#include  <Standard.hxx>
#include  <Standard_DefineAlloc.hxx>
#include  <Standard_Handle.hxx>
#include  <TopoDS_Shape.hxx>
#include  <TopoDS_Compound.hxx>
#include  <TopTools_HSequenceOfShape.hxx>
#include  <Standard_Integer.hxx>
#include  <TopoDS_Wire.hxx>
#include  <BRepBuilderAPI_MakeEdge.hxx>
#include  <BRepBuilderAPI_MakeWire.hxx>
#include  <BRepProj_Projection.hxx>
#include  <BRepBuilderAPI_MakeFace.hxx>

// 가장 가까운 면 찾기
#include <TopoDS_Shape.hxx>
#include <TopoDS_Face.hxx>
#include <TopExp_Explorer.hxx>
#include <BRepExtrema_ExtPF.hxx>
#include <gp_Pnt.hxx>
#include <BRepExtrema_DistShapeShape.hxx>

#include <vcclr.h>
#include <GeomLProp_SLProps.hxx>

#include "ModelShape.h"

// list of required OCCT libraries
#pragma comment(lib, "TKernel.lib"            )
#pragma comment(lib, "TKMath.lib"             )
#pragma comment(lib, "TKXSBase.lib"           )
#pragma comment(lib, "TKService.lib"          )
#pragma comment(lib, "TKV3d.lib"              )
#pragma comment(lib, "TKBool.lib"             )
#pragma comment(lib, "TKBRep.lib"             )
#pragma comment(lib, "TKDESTEP.lib"           )
#pragma comment(lib, "TKG2d.lib"              )
#pragma comment(lib, "TKG3d.lib"              )
#pragma comment(lib, "TKGeomAlgo.lib"         )
#pragma comment(lib, "TKGeomBase.lib"         )
#pragma comment(lib, "TKMesh.lib"             )
#pragma comment(lib, "TKPrim.lib"             )
#pragma comment(lib, "TKTObj.lib"             )
#pragma comment(lib, "TKTopAlgo.lib"          )
#pragma comment(lib, "TKView.lib"             )
#pragma comment(lib, "TKShHealing.lib"        )
#pragma comment(lib, "TKOpenGl.lib"           )

//#pragma comment(lib, "TKBin.lib"			    )
//#pragma comment(lib, "TKBinL.lib"             )
//#pragma comment(lib, "TKBinTObj.lib"          )
//#pragma comment(lib, "TKBinXCAF.lib"          )
//#pragma comment(lib, "TKBO.lib"               )
//#pragma comment(lib, "TKCAF.lib"              )
//#pragma comment(lib, "TKCDF.lib"              )
//#pragma comment(lib, "TKD3DHost.lib"          )
//#pragma comment(lib, "TKD3DHostTest.lib"      )
//#pragma comment(lib, "TKDCAF.lib"             )
//#pragma comment(lib, "TKDE.lib"               )
//#pragma comment(lib, "TKDECascade.lib"        )
//#pragma comment(lib, "TKDEGLTF.lib"           )
//#pragma comment(lib, "TKDEIGES.lib"           )
//#pragma comment(lib, "TKDEOBJ.lib"            )
//#pragma comment(lib, "TKDEPLY.lib"            )
//#pragma comment(lib, "TKDESTL.lib"            )
//#pragma comment(lib, "TKDEVRML.lib"           )
//#pragma comment(lib, "TKDFBrowser.lib"        )
//#pragma comment(lib, "TKDraw.lib"             )
//#pragma comment(lib, "TKExpress.lib"          )
//#pragma comment(lib, "TKFeat.lib"             )
//#pragma comment(lib, "TKFillet.lib"           )
//#pragma comment(lib, "TKHLR.lib"              )
//#pragma comment(lib, "TKIVtk.lib"             )
//#pragma comment(lib, "TKIVtkDraw.lib"         )
//#pragma comment(lib, "TKLCAF.lib"             )
//#pragma comment(lib, "TKMeshVS.lib"           )
//#pragma comment(lib, "TKMessageModel.lib"     )
//#pragma comment(lib, "TKMessageView.lib"      )
//#pragma comment(lib, "TKOffset.lib"           )
//#pragma comment(lib, "TKOpenGles.lib"         )
//#pragma comment(lib, "TKOpenGlesTest.lib"     )
//#pragma comment(lib, "TKOpenGlTest.lib"       )
//#pragma comment(lib, "TKQADraw.lib"           )
//#pragma comment(lib, "TKRWMesh.lib"           )
//#pragma comment(lib, "TKShapeView.lib"        )
//#pragma comment(lib, "TKStd.lib"              )
//#pragma comment(lib, "TKStdL.lib"             )
//#pragma comment(lib, "TKTInspector.lib"       )
//#pragma comment(lib, "TKTInspectorAPI.lib"    )
//#pragma comment(lib, "TKTObjDRAW.lib"         )
//#pragma comment(lib, "TKToolsDraw.lib"        )
//#pragma comment(lib, "TKTopTest.lib"          )
//#pragma comment(lib, "TKTreeModel.lib"        )
//#pragma comment(lib, "TKVCAF.lib"             )
//#pragma comment(lib, "TKViewerTest.lib"       )
//#pragma comment(lib, "TKVInspector.lib"       )
//#pragma comment(lib, "TKXCAF.lib"             )
//#pragma comment(lib, "TKXDEDRAW.lib"          )
//#pragma comment(lib, "TKXMesh.lib"            )
//#pragma comment(lib, "TKXml.lib"              )
//#pragma comment(lib, "TKXmlL.lib"             )
//#pragma comment(lib, "TKXmlTObj.lib"          )
//#pragma comment(lib, "TKXmlXCAF.lib"          )
//#pragma comment(lib, "TKXSDRAW.lib"           )
//#pragma comment(lib, "TKXSDRAWDE.lib"         )
//#pragma comment(lib, "TKXSDRAWGLTF.lib"       )
//#pragma comment(lib, "TKXSDRAWIGES.lib"       )
//#pragma comment(lib, "TKXSDRAWOBJ.lib"        )
//#pragma comment(lib, "TKXSDRAWPLY.lib"        )
//#pragma comment(lib, "TKXSDRAWSTEP.lib"       )
//#pragma comment(lib, "TKXSDRAWSTL.lib"        )
//#pragma comment(lib, "TKXSDRAWVRML.lib"       )

ref class StepModel;
//! Auxiliary tool for converting C# string into UTF-8 string.
static TCollection_AsciiString toAsciiString(String^ theString)
{
	if (theString == nullptr)
	{
		return TCollection_AsciiString();
	}

	pin_ptr<const wchar_t> aPinChars = PtrToStringChars(theString);
	const wchar_t* aWCharPtr = aPinChars;
	if (aWCharPtr == NULL || *aWCharPtr == L'\0')
	{
		return TCollection_AsciiString();
	}
	return TCollection_AsciiString(aWCharPtr);
}

/// <summary>
/// Proxy class encapsulating calls to OCCT C++ classes within
/// C++/CLI class visible from .Net (CSharp)
/// </summary>
public

ref class OCCTProxy
{
public:
	// ============================================
	// Viewer functionality
	// ============================================

	/// <summary>
	/// Initialize a viewer
	/// </summary>
	/// <param name="theWnd">System.IntPtr that contains the window handle (HWND) of the
	/// control</param>
	bool InitViewer(System::IntPtr theWnd)
	{
		try
		{
			Handle(Aspect_DisplayConnection) aDisplayConnection;
			myGraphicDriver() = new OpenGl_GraphicDriver(aDisplayConnection);
		}
		catch (Standard_Failure)
		{
			return false;
		}

		myViewer() = new V3d_Viewer(myGraphicDriver());
		myViewer()->SetDefaultLights();
		myViewer()->SetLightOn();
		myView() = myViewer()->CreateView();
		Handle(WNT_Window) aWNTWindow = new WNT_Window(reinterpret_cast<HWND>(theWnd.ToPointer()));
		myView()->SetWindow(aWNTWindow);
		if (!aWNTWindow->IsMapped())
		{
			aWNTWindow->Map();
		}
		myAISContext() = new AIS_InteractiveContext(myViewer());
		myAISContext()->UpdateCurrentViewer();
		myView()->Redraw();
		myView()->MustBeResized();
		return true;
	}

	/// <summary>
	/// Make dump of current view to file
	/// </summary>
	/// <param name="theFileName">Name of dump file</param>
	bool Dump(const TCollection_AsciiString& theFileName)
	{
		if (myView().IsNull())
		{
			return false;
		}
		myView()->Redraw();
		return myView()->Dump(theFileName.ToCString()) != Standard_False;
	}

	/// <summary>
	/// Redraw view
	/// </summary>
	void RedrawView(void)
	{
		if (!myView().IsNull())
		{
			myView()->Redraw();
		}
	}

	/// <summary>
	/// Update view
	/// </summary>
	void UpdateView(void)
	{
		if (!myView().IsNull())
		{
			myView()->MustBeResized();
		}
	}

	/// <summary>
	/// Set computed mode in false
	/// </summary>
	void SetDegenerateModeOn(void)
	{
		if (!myView().IsNull())
		{
			myView()->SetComputedMode(Standard_False);
			myView()->Redraw();
		}
	}

	/// <summary>
	/// Set computed mode in true
	/// </summary>
	void SetDegenerateModeOff(void)
	{
		if (!myView().IsNull())
		{
			myView()->SetComputedMode(Standard_True);
			myView()->Redraw();
		}
	}

	/// <summary>
	/// Fit all
	/// </summary>
	void WindowFitAll(int theXmin, int theYmin, int theXmax, int theYmax)
	{
		if (!myView().IsNull())
		{
			myView()->WindowFitAll(theXmin, theYmin, theXmax, theYmax);
		}
	}

	/// <summary>
	/// Current place of window
	/// </summary>
	/// <param name="theZoomFactor">Current zoom</param>
	void Place(int theX, int theY, float theZoomFactor)
	{
		Standard_Real aZoomFactor = theZoomFactor;
		if (!myView().IsNull())
		{
			myView()->Place(theX, theY, aZoomFactor);
		}
	}

	/// <summary>
	/// Set Zoom
	/// </summary>
	void Zoom(int theX1, int theY1, int theX2, int theY2)
	{
		if (!myView().IsNull())
		{
			myView()->Zoom(theX1, theY1, theX2, theY2);
		}
	}

	/// <summary>
	/// 화면 줌
	/// </summary>
	/// <param name="x">마우스 X 좌표</param>
	/// <param name="y">마우스 Y 좌표</param>
	/// <param name="delta">크기</param>
	void Zoom(int x, int y, double delta)
	{
		if (!myView().IsNull())
		{
			// #01. 화면 크기 가져오기
			int width, height;
			myView()->Window()->Size(width, height);

			// #02. 줌을 적용할 좌표 계산
			int x1 = x + width * delta / 10000.0;
			int y1 = y + height * delta / 10000.0;

			// #03. 줌 시작 점을 설정한다.
			myView()->StartZoomAtPoint(x, y);

			// #04. 줌 적용
			//  - StartZoomAtPoint() 메서드로 줌 시작점을 설정한 후, 줌을 적용한다.
			myView()->ZoomAtPoint(x, y, x1, y1);
		}
	}

	/// <summary>
	/// Set Pan
	/// </summary>
	void Pan(int theX, int theY)
	{
		if (!myView().IsNull())
		{
			myView()->Pan(theX, theY);
		}
	}

	/// <summary>
	/// Rotation
	/// </summary>
	void Rotation(int theX, int theY)
	{
		if (!myView().IsNull())
		{
			myView()->Rotation(theX, theY);
		}
	}

	/// <summary>
	/// Start rotation
	/// </summary>
	void StartRotation(int theX, int theY)
	{
		if (!myView().IsNull())
		{
			myView()->StartRotation(theX, theY);
		}
	}

	/// <summary>
	/// Select by rectangle
	/// </summary>
	void Select(int theX1, int theY1, int theX2, int theY2)
	{
		if (!myAISContext().IsNull())
		{
			myAISContext()->SelectRectangle(Graphic3d_Vec2i(theX1, theY1),
				Graphic3d_Vec2i(theX2, theY2),
				myView());
			myAISContext()->UpdateCurrentViewer();
		}
	}

	/// <summary>
	/// Select by click
	/// </summary>
	void Select(void)
	{
		if (!myAISContext().IsNull())
		{
			myAISContext()->SelectDetected();
			myAISContext()->UpdateCurrentViewer();
		}
	}

	/// <summary>
	/// 전체 객체 선택
	/// </summary>
	void SelectAllObject()
	{
		if (!myAISContext().IsNull())
		{
			// * 선택 결과를 저장할 리스트
			AIS_ListOfInteractive aList;
			// * 모든 타입을 선택한다.
			//  - Signature == -1 → Edge, Face, Vertex, Solid 등 모든 TopoDS_Shape 하위 항목 포함
			int Signature = -1;
			// #01. 화면에 표시되고 있는 객체들 중 타입에 맞는 객체를 aList에 추가한다.
			myAISContext()->DisplayedObjects(AIS_KOI_Shape, Signature, aList);

			// #02. 선택 초기화
			myAISContext()->ClearSelected(false);

			// #03. 현재 선택된 경우의 스타일을 가져온다.
			Handle(Prs3d_Drawer) selectedStyle = myAISContext()->HighlightStyle(Prs3d_TypeOfHighlight_Selected);

			// #04. 가져온 선택 리스트 순회
			for (AIS_ListIteratorOfListOfInteractive it(aList); it.More(); it.Next())
			{
				// #04-1. 선택된 항목을 AIS_InteractiveObject 형으로 변환
				Handle(AIS_InteractiveObject) obj = it.Value();

				// #04-2. 해당 객체 선택
				myAISContext()->AddSelect(obj);

				// * 선택 하이라이트를 현재 선택된 경우의 스타일로 적용한다.
				//  - 아래 코드를 수행하지 않으면, 선택 스타일이 적용 안된다.
				//  - AddSelect으로 선택한건, 선택 스타일이 안먹는 것 같다.
				myAISContext()->HilightWithColor(obj, selectedStyle, false);
			}

			// #05. 뷰 업데이트
			myAISContext()->UpdateCurrentViewer();
		}
	}

	/// <summary>
	/// 선택 색상 설정
	/// </summary>
	void SetSelectedStyle(int theR, int theG, int theB)
	{
		if (!myAISContext().IsNull())
		{
			// * 색상 생성
			Quantity_Color aCol = Quantity_Color(theR / 255., theG / 255., theB / 255., Quantity_TOC_RGB);

			// 선택 시 적용되는 강조 스타일 설정 (7.5 버전 이상 부터 지원)
			myAISContext()->HighlightStyle(Prs3d_TypeOfHighlight_Selected)->SetColor(aCol); // 색깔 반영은 됨
			myAISContext()->HighlightStyle(Prs3d_TypeOfHighlight_Selected)->SetDisplayMode(1); // 색깔 반영은 됨
			myAISContext()->HighlightStyle(Prs3d_TypeOfHighlight_Selected)->SetTransparency(0.0f);
		}
	}

	/// <summary>
	/// 하이라이트 색상 설정
	/// </summary>
	/// <param name="theR"></param>
	/// <param name="theG"></param>
	/// <param name="theB"></param>
	void SetHighlightStyle(int theR, int theG, int theB)
	{
		if (!myAISContext().IsNull())
		{
			// * 색상 생성
			Quantity_Color aCol = Quantity_Color(theR / 255., theG / 255., theB / 255., Quantity_TOC_RGB);

			Handle(Prs3d_Drawer) highlightStyle = new Prs3d_Drawer();
			highlightStyle->SetColor(aCol);								// 색상 부여
			highlightStyle->SetDisplayMode(1);							// Shading 모드
			highlightStyle->SetTransparency(0.0);           // 불투명

			// 하이라이트 스타일 설정
			myAISContext()->SetHighlightStyle(highlightStyle);
		}
	}

	/// <summary>
	/// 뷰 큐브 생성
	/// </summary>
	void SetViweCube()
	{
		// #01. 뷰 큐브 객체 생성
		Handle(AIS_ViewCube) theViewCube = new AIS_ViewCube();

		// #02. 뷰 큐브의 기본 속성 가져오기
		const Handle(Prs3d_Drawer)& aDrawer = theViewCube->Attributes();

		// #03. 기준축을 설정하기 위한 새 객체 생성
		aDrawer->SetDatumAspect(new Prs3d_DatumAspect());

		// #04. 기준축 설정하기 위한 새 객체를 핸들로 받아온다.
		const Handle(Prs3d_DatumAspect)& aDatumAsp = aDrawer->DatumAspect();

		// #05. 축 텍스트 색상 설정
		aDatumAsp->TextAspect(Prs3d_DatumParts_XAxis)->SetColor(Quantity_NOC_RED);
		aDatumAsp->TextAspect(Prs3d_DatumParts_YAxis)->SetColor(Quantity_NOC_GREEN);
		aDatumAsp->TextAspect(Prs3d_DatumParts_ZAxis)->SetColor(Quantity_NOC_BLUE);

		// #06. Transform Persistence를 통해 위치 설정
		Handle(Graphic3d_TransformPers) aTrsfPers =
			new Graphic3d_TransformPers(Graphic3d_TMF_TriedronPers,	// 화면상에 고정되어 움직이지 않도록 (카메라 회전, 확대/ 축소 영향을 받지 않도록)
				Aspect_TOTP_RIGHT_LOWER,						// 우측 하단
				Graphic3d_Vec2i(100, 100));	// 오프셋 되는 위치 

		// #07. 뷰 큐브 위치 설정
		//theViewCube->SetTransformPersistence(aTrsfPers);

		// * 뷰 큐브 내부 여백 
		theViewCube->SetBoxFacetExtension(5.0);

		// * 색상 넣기
		theViewCube->SetBoxColor(Quantity_NOC_MEDIUMPURPLE2);

		// #07. 뷰 큐브를 컨텍스트에 표시
		myAISContext()->Display(theViewCube, Standard_True);
	}

	/// <summary>
	/// Move view
	/// </summary>
	void MoveTo(int theX, int theY)
	{
		if ((!myAISContext().IsNull()) && (!myView().IsNull()))
		{
			myAISContext()->MoveTo(theX, theY, myView(), Standard_True);
		}
	}

	/// <summary>
	/// Select by rectangle with pressed "Shift" key
	/// </summary>
	void ShiftSelect(int theX1, int theY1, int theX2, int theY2)
	{
		if ((!myAISContext().IsNull()) && (!myView().IsNull()))
		{
			myAISContext()->SelectRectangle(Graphic3d_Vec2i(theX1, theY1),
				Graphic3d_Vec2i(theX2, theY2),
				myView(),
				AIS_SelectionScheme_XOR);
			myAISContext()->UpdateCurrentViewer();
		}
	}

	/// <summary>
	/// Select by "Shift" key
	/// </summary>
	void ShiftSelect(void)
	{
		if (!myAISContext().IsNull())
		{
			myAISContext()->SelectDetected(AIS_SelectionScheme_XOR);
			myAISContext()->UpdateCurrentViewer();
		}
	}

	/// <summary>
	/// Set background color
	/// </summary>
	void BackgroundColor(int& theRed, int& theGreen, int& theBlue)
	{
		Standard_Real R1;
		Standard_Real G1;
		Standard_Real B1;
		if (!myView().IsNull())
		{
			myView()->BackgroundColor(Quantity_TOC_RGB, R1, G1, B1);
		}
		theRed = (int)R1 * 255;
		theGreen = (int)G1 * 255;
		theBlue = (int)B1 * 255;
	}

	/// <summary>
	/// Get background color Red
	/// </summary>
	int GetBGColR(void)
	{
		int aRed, aGreen, aBlue;
		BackgroundColor(aRed, aGreen, aBlue);
		return aRed;
	}

	/// <summary>
	/// Get background color Green
	/// </summary>
	int GetBGColG(void)
	{
		int aRed, aGreen, aBlue;
		BackgroundColor(aRed, aGreen, aBlue);
		return aGreen;
	}

	/// <summary>
	/// Get background color Blue
	/// </summary>
	int GetBGColB(void)
	{
		int aRed, aGreen, aBlue;
		BackgroundColor(aRed, aGreen, aBlue);
		return aBlue;
	}

	/// <summary>
	/// Update current viewer
	/// </summary>
	void UpdateCurrentViewer(void)
	{
		if (!myAISContext().IsNull())
		{
			myAISContext()->UpdateCurrentViewer();
		}
	}

	/// <summary>
	/// Front side
	/// </summary>
	void FrontView(void)
	{
		if (!myView().IsNull())
		{
			myView()->SetProj(V3d_Yneg);
		}
	}

	/// <summary>
	/// Top side
	/// </summary>
	void TopView(void)
	{
		if (!myView().IsNull())
		{
			myView()->SetProj(V3d_Zpos);
		}
	}

	/// <summary>
	/// Left side
	/// </summary>
	void LeftView(void)
	{
		if (!myView().IsNull())
		{
			myView()->SetProj(V3d_Xneg);
		}
	}

	/// <summary>
	/// Back side
	/// </summary>
	void BackView(void)
	{
		if (!myView().IsNull())
		{
			myView()->SetProj(V3d_Ypos);
		}
	}

	/// <summary>
	/// Right side
	/// </summary>
	void RightView(void)
	{
		if (!myView().IsNull())
		{
			myView()->SetProj(V3d_Xpos);
		}
	}

	/// <summary>
	/// Bottom side
	/// </summary>
	void BottomView(void)
	{
		if (!myView().IsNull())
		{
			myView()->SetProj(V3d_Zneg);
		}
	}

	/// <summary>
	/// Axo side
	/// </summary>
	void AxoView(void)
	{
		if (!myView().IsNull())
		{
			myView()->SetProj(V3d_XposYnegZpos);
		}
	}

	/// <summary>
	/// Scale
	/// </summary>
	float Scale(void)
	{
		if (myView().IsNull())
		{
			return -1;
		}
		else
		{
			return (float)myView()->Scale();
		}
	}

	/// <summary>
	/// Zoom in all view
	/// </summary>
	void ZoomAllView(void)
	{
		if (!myView().IsNull())
		{
			myView()->FitAll();
			myView()->ZFitAll();
		}
	}

	/// <summary>
	/// Reset view
	/// </summary>
	void Reset(void)
	{
		if (!myView().IsNull())
		{
			myView()->Reset();
		}
	}

	/// <summary>
	/// Set display mode of objects
	/// </summary>
	/// <param name="theMode">Set current mode</param>
	void SetDisplayMode(int theMode)
	{
		if (myAISContext().IsNull())
		{
			return;
		}
		AIS_DisplayMode aCurrentMode;
		if (theMode == 0)
		{
			aCurrentMode = AIS_WireFrame;
		}
		else
		{
			aCurrentMode = AIS_Shaded;
		}

		// * 선택된 것이 없다면, 전체 디스플레이 모드 적용
		if (myAISContext()->NbSelected() == 0)
		{
			myAISContext()->SetDisplayMode(aCurrentMode, Standard_False);
		}
		else
		{
			// * 선택된 것이 있다면, 선택만 디스플레이 모드 적용
			for (myAISContext()->InitSelected(); myAISContext()->MoreSelected();
				myAISContext()->NextSelected())
			{
				myAISContext()->SetDisplayMode(myAISContext()->SelectedInteractive(),
					theMode,
					Standard_False);
			}

		}
		myAISContext()->UpdateCurrentViewer();
	}

	/// <summary>
	/// 쉐이딩 모드로 설정
	/// </summary>
	void SetShadingMode()
	{
		// #01. 컨텍스트가 있는지 여부 확인
		if (myAISContext().IsNull())
		{
			return;
		}

		// * 쉐이딩 모드
		AIS_DisplayMode aCurrentMode = AIS_Shaded;

		// #02. 디스플레이 모드를 쉐이딩 모드로 설정
		myAISContext()->SetDisplayMode(aCurrentMode, Standard_False);

		// #03. 뷰 업데이트
		myAISContext()->UpdateCurrentViewer();
	}

	void SetWireMode()
	{
		// #01. 컨텍스트가 있는지 여부 확인
		if (myAISContext().IsNull())
		{
			return;
		}

		// * 쉐이딩 모드
		AIS_DisplayMode aCurrentMode = AIS_WireFrame;

		// #02. 디스플레이 모드를 와이어 모드로 설정
		myAISContext()->SetDisplayMode(aCurrentMode, Standard_False);

		// #03. 뷰 업데이트
		myAISContext()->UpdateCurrentViewer();
	}

	/// <summary>
	/// 선택 객체에 색상 적용
	/// </summary>
	void SetColor(int theR, int theG, int theB)
	{
		// #01. 컨텍스트가 있는지 여부
		if (myAISContext().IsNull())
		{
			return;
		}

		// #02. 색상 정보 생성
		Quantity_Color aCol = Quantity_Color(theR / 255., theG / 255., theB / 255., Quantity_TOC_RGB);

		// #03. 선택 객체 순회하며 색상 적용
		for (myAISContext()->InitSelected(); myAISContext()->MoreSelected(); myAISContext()->NextSelected())
		{
			myAISContext()->SetColor(myAISContext()->SelectedInteractive(), aCol, Standard_False);
		}

		// #04. 뷰 업데이트
		myAISContext()->UpdateCurrentViewer();
	}

	/// <summary>
	/// Get object color red
	/// </summary>
	int GetObjColR(void)
	{
		int aRed, aGreen, aBlue;
		ObjectColor(aRed, aGreen, aBlue);
		return aRed;
	}

	/// <summary>
	/// Get object color green
	/// </summary>
	int GetObjColG(void)
	{
		int aRed, aGreen, aBlue;
		ObjectColor(aRed, aGreen, aBlue);
		return aGreen;
	}

	/// <summary>
	/// Get object color R/G/B
	/// </summary>
	void ObjectColor(int& theRed, int& theGreen, int& theBlue)
	{
		if (myAISContext().IsNull())
		{
			return;
		}
		theRed = 255;
		theGreen = 255;
		theBlue = 255;
		Handle(AIS_InteractiveObject) aCurrent;
		myAISContext()->InitSelected();
		if (!myAISContext()->MoreSelected())
		{
			return;
		}
		aCurrent = myAISContext()->SelectedInteractive();
		if (aCurrent->HasColor())
		{
			Quantity_Color anObjCol;
			myAISContext()->Color(aCurrent, anObjCol);
			Standard_Real r1, r2, r3;
			anObjCol.Values(r1, r2, r3, Quantity_TOC_RGB);
			theRed = (int)r1 * 255;
			theGreen = (int)r2 * 255;
			theBlue = (int)r3 * 255;
		}
	}

	/// <summary>
	/// Get object color blue
	/// </summary>
	int GetObjColB(void)
	{
		int aRed, aGreen, aBlue;
		ObjectColor(aRed, aGreen, aBlue);
		return aBlue;
	}

	/// <summary>
	/// Set background color R/G/B
	/// </summary>
	void SetBackgroundColor(int theRed, int theGreen, int theBlue)
	{
		if (!myView().IsNull())
		{
			myView()->SetBackgroundColor(Quantity_TOC_RGB,
				theRed / 255.,
				theGreen / 255.,
				theBlue / 255.);
		}
	}

	void SetBackgroundGradientColor(int topRed, int topGreen, int topBlue, int downRed, int downGreen, int downBlue)
	{
		if (!myView().IsNull())
		{
			// * 색상 만들기
			Quantity_Color topColor = Quantity_Color(topRed / 255., topGreen / 255., topBlue / 255., Quantity_TOC_RGB);
			Quantity_Color bottomColor = Quantity_Color(downRed / 255., downGreen / 255., downBlue / 255., Quantity_TOC_RGB);

			// * 그라데이션 색상 적용
			myView()->SetBgGradientColors(topColor, bottomColor, Aspect_GFM_VER); // 수직 그라데이션

			// * 뷰 업데이트
			myView()->Update();
		}
	}

	/// <summary>
	/// Erase objects
	/// </summary>
	void EraseObjects(void)
	{
		if (myAISContext().IsNull())
		{
			return;
		}

		myAISContext()->EraseSelected(Standard_False);
		myAISContext()->ClearSelected(Standard_True);
	}

	/// <summary>
	/// Get version
	/// </summary>
	float GetOCCVersion(void) { return (float)OCC_VERSION; }

	/// <summary>
	/// set material
	/// </summary>
	void SetMaterial(int theMaterial)
	{
		if (myAISContext().IsNull())
		{
			return;
		}
		for (myAISContext()->InitSelected(); myAISContext()->MoreSelected();
			myAISContext()->NextSelected())
		{
			myAISContext()->SetMaterial(myAISContext()->SelectedInteractive(),
				(Graphic3d_NameOfMaterial)theMaterial,
				Standard_False);
		}
		myAISContext()->UpdateCurrentViewer();
	}

	/// <summary>
	/// set transparency
	/// </summary>
	void SetTransparency(int theTrans)
	{
		if (myAISContext().IsNull())
		{
			return;
		}
		for (myAISContext()->InitSelected(); myAISContext()->MoreSelected();
			myAISContext()->NextSelected())
		{
			myAISContext()->SetTransparency(myAISContext()->SelectedInteractive(),
				((Standard_Real)theTrans) / 10.0,
				Standard_False);
		}
		myAISContext()->UpdateCurrentViewer();
	}

	/// <summary>
	/// Return true if object is selected
	/// </summary>
	bool IsObjectSelected(void)
	{
		if (myAISContext().IsNull())
		{
			return false;
		}
		myAISContext()->InitSelected();
		return myAISContext()->MoreSelected() != Standard_False;
	}

	/// <summary>
	/// Return display mode
	/// </summary>
	int DisplayMode(void)
	{
		if (myAISContext().IsNull())
		{
			return -1;
		}
		int  aMode = -1;
		bool OneOrMoreInShading = false;
		bool OneOrMoreInWireframe = false;
		for (myAISContext()->InitSelected(); myAISContext()->MoreSelected();
			myAISContext()->NextSelected())
		{
			if (myAISContext()->IsDisplayed(myAISContext()->SelectedInteractive(), 1))
			{
				OneOrMoreInShading = true;
			}
			if (myAISContext()->IsDisplayed(myAISContext()->SelectedInteractive(), 0))
			{
				OneOrMoreInWireframe = true;
			}
		}
		if (OneOrMoreInShading && OneOrMoreInWireframe)
		{
			aMode = 10;
		}
		else if (OneOrMoreInShading)
		{
			aMode = 1;
		}
		else if (OneOrMoreInWireframe)
		{
			aMode = 0;
		}

		return aMode;
	}

	/// <summary>
	/// Create new view
	/// </summary>
	/// <param name="theWnd">System.IntPtr that contains the window handle (HWND) of the
	/// control</param>
	void CreateNewView(System::IntPtr theWnd)
	{
		if (myAISContext().IsNull())
		{
			return;
		}
		myView() = myAISContext()->CurrentViewer()->CreateView();
		if (myGraphicDriver().IsNull())
		{
			myGraphicDriver() = new OpenGl_GraphicDriver(Handle(Aspect_DisplayConnection)());
		}
		Handle(WNT_Window) aWNTWindow = new WNT_Window(reinterpret_cast<HWND>(theWnd.ToPointer()));
		myView()->SetWindow(aWNTWindow);
		Standard_Integer w = 100, h = 100;
		aWNTWindow->Size(w, h);
		if (!aWNTWindow->IsMapped())
		{
			aWNTWindow->Map();
		}
	}

	/// <summary>
	/// Set AISContext
	/// </summary>
	bool SetAISContext(OCCTProxy^ theViewer)
	{
		this->myAISContext() = theViewer->GetContext();
		if (myAISContext().IsNull())
		{
			return false;
		}
		return true;
	}

	/// <summary>
	/// Get AISContext
	/// </summary>
	Handle(AIS_InteractiveContext) GetContext(void) { return myAISContext(); }

public:
	// ============================================
	// Import / export functionality
	// ============================================

	/*/// <summary>
   /// Import Step file
   /// </summary>
   /// <param name="theFileName">Name of import file</param>
	bool ImportStep(String^ theFileName)
	{
		const TCollection_AsciiString aFilename = toAsciiString(theFileName);

		STEPControl_Reader    aReader;
		IFSelect_ReturnStatus aStatus = aReader.ReadFile(aFilename.ToCString());
		if (aStatus == IFSelect_RetDone)
		{
			bool isFailsonly = false;
			aReader.PrintCheckLoad(isFailsonly, IFSelect_ItemsByEntity);

			int aNbRoot = aReader.NbRootsForTransfer();
			aReader.PrintCheckTransfer(isFailsonly, IFSelect_ItemsByEntity);
			for (Standard_Integer n = 1; n <= aNbRoot; n++)
			{
				Standard_Boolean ok = aReader.TransferRoot(n);
				int              aNbShap = aReader.NbShapes();
				if (aNbShap > 0)
				{
					for (int i = 1; i <= aNbShap; i++)
					{
						TopoDS_Shape aShape = aReader.Shape(i);
						myAISContext()->Display(new AIS_Shape(aShape), Standard_False);
					}
					myAISContext()->UpdateCurrentViewer();
				}
			}
		}
		else
		{
			return false;
		}

		return true;
	}*/

	/// <summary>
	///  STEP 파일 불러오기
	/// </summary>
	/// <param name="theFileName"></param>
	/// <returns></returns>
	bool ImportStep(String^ theFileName)
	{
		// * 파일 경로를 OCCT에서 인식 가능한 문자열로 생성
		const TCollection_AsciiString aFilename = toAsciiString(theFileName);

		// * STEP 파일 읽기 전용 객체 초기화
		STEPControl_Reader aReader;
		// * STEP 파일 읽기
		IFSelect_ReturnStatus aStatus = aReader.ReadFile(aFilename.ToCString());
		// * STEP 파일 읽기 성공 여부 판단
		if (aStatus != IFSelect_RetDone)
			return false;

		// * 파일 로딩 과정에서 발생한 오류/경고를 출력
		aReader.PrintCheckLoad(false, IFSelect_ItemsByEntity);

		// * STEP 파일에서는 여러개의 Root 엔티티가 존재할 수 있어, Root 수 가져오기
		int aNbRoot = aReader.NbRootsForTransfer();
		// * 변환 과정시 발생한 체크 메시지 출력
		aReader.PrintCheckTransfer(false, IFSelect_ItemsByEntity);
		// * Root 수 만큼 순회하며 변환
		for (Standard_Integer n = 1; n <= aNbRoot; n++)
		{
			// * 변환 실패할 경우 continue
			if (!aReader.TransferRoot(n))
			{
				continue;
			}

			// * 변환된 결과에서 Shape 개수 가져오기
			int aNbShap = aReader.NbShapes();

			// Shape 수 만큼 순회
			for (int i = 1; i <= aNbShap; i++)
			{
				// * Shape 가져오기
				TopoDS_Shape aShape = aReader.Shape(i);

				// * OpenCasCade에서 표시 가능한 객체인 AIS_Shape으로 변환
				Handle(AIS_Shape) aisShape = new AIS_Shape(aShape);

				// * Viewer 에 표시
				myAISContext()->Display(aisShape, Standard_False);

				// * 선택 모드 활성화 (Face 선택 가능)
				myAISContext()->Activate(aisShape, AIS_Shape::SelectionMode(TopAbs_FACE));
			}
		}

		// * 모든 Shape이 표시된 후 뷰어 갱신
		myAISContext()->UpdateCurrentViewer();
		return true;
	}

	/// <summary>
	/// Import Step file
	/// </summary>
	/// <param name="theFileName">Name of import file</param>
	bool ImportStep(const TCollection_AsciiString& theFileName)
	{
		STEPControl_Reader    aReader;
		IFSelect_ReturnStatus aStatus = aReader.ReadFile(theFileName.ToCString());
		if (aStatus == IFSelect_RetDone)
		{
			bool isFailsonly = false;
			aReader.PrintCheckLoad(isFailsonly, IFSelect_ItemsByEntity);

			int aNbRoot = aReader.NbRootsForTransfer();
			aReader.PrintCheckTransfer(isFailsonly, IFSelect_ItemsByEntity);
			for (Standard_Integer n = 1; n <= aNbRoot; n++)
			{
				Standard_Boolean ok = aReader.TransferRoot(n);
				int              aNbShap = aReader.NbShapes();
				if (aNbShap > 0)
				{
					for (int i = 1; i <= aNbShap; i++)
					{
						TopoDS_Shape aShape = aReader.Shape(i);
						myAISContext()->Display(new AIS_Shape(aShape), Standard_False);
					}
					myAISContext()->UpdateCurrentViewer();
				}
			}
		}
		else
		{
			return false;
		}

		return true;
	}

	/// <summary>
	/// Export Step file
	/// </summary>
	/// <param name="theFileName">Name of export file</param>
	bool ExportStep(const TCollection_AsciiString& theFileName)
	{
		STEPControl_StepModelType aType = STEPControl_AsIs;
		IFSelect_ReturnStatus     aStatus;
		STEPControl_Writer        aWriter;
		for (myAISContext()->InitSelected(); myAISContext()->MoreSelected();
			myAISContext()->NextSelected())
		{
			Handle(AIS_InteractiveObject) anIO = myAISContext()->SelectedInteractive();
			Handle(AIS_Shape)             anIS = Handle(AIS_Shape)::DownCast(anIO);
			TopoDS_Shape                  aShape = anIS->Shape();
			aStatus = aWriter.Transfer(aShape, aType);
			if (aStatus != IFSelect_RetDone)
			{
				return false;
			}
		}

		aStatus = aWriter.Write(theFileName.ToCString());
		if (aStatus != IFSelect_RetDone)
		{
			return false;
		}

		return true;
	}

	void EnableAmbientOcclusion()
	{
		if (myView().IsNull())
			return;

		Graphic3d_RenderingParams& params = myView()->ChangeRenderingParams();

		params.Method = Graphic3d_RM_RAYTRACING;
		params.IsShadowEnabled = true;  // 그림자
		params.IsReflectionEnabled = true;  // 반사
		params.IsTransparentShadowEnabled = true;   // 투명 그림자
		myAISContext()->UpdateCurrentViewer();

		// 렌더링 갱신
		myView()->Redraw();
	}

	/// <summary>
	/// 점 삽입 (확대/축소에 영향 받지 않음)
	/// </summary>
	/// <param name="x">좌표X</param>
	/// <param name="y">좌표Y</param>
	/// <param name="z">좌표Z</param>
	/// <param name="pixelSize">픽셀 사이즈 (최대 7까지 입력)</param>
	void InsertPoint(double x, double y, double z, double pixelSize)
	{
		if (myView().IsNull() || myAISContext().IsNull())
			return;

		// #01. 점 좌표 생성
		gp_Pnt point(x, y, z);
		Handle(AIS_Point) aPoint = new AIS_Point(new Geom_CartesianPoint(point));

		// #02. 색상 설정 
		Quantity_Color color(Quantity_NOC_RED);

		// #03. 점 정보 설정
		// * 픽셀 사이즈는 최대가 7로 고정되어 있다. 그 이상 값을 넣어도 사이즈는 동일하다.
		Handle(Prs3d_Drawer) drawer = new Prs3d_Drawer();
		drawer->SetPointAspect(new Prs3d_PointAspect(Aspect_TOM_O, color, pixelSize));

		// #04. drawer를 AIS_Point에 설정
		aPoint->SetAttributes(drawer);

		// #05. Context에 등록 및 표시
		myAISContext()->Display(aPoint, Standard_True);
	}

	/// <summary>
	/// 점(구) 삽입 (확대/축소 영향 받음)
	/// </summary>
	/// <param name="x">좌표X</param>
	/// <param name="y">좌표Y</param>
	/// <param name="z">좌표Z</param>
	/// <param name="radius">구 반지름</param>
	void InsertPointAsSphere(double x, double y, double z, double radius)
	{
		if (myView().IsNull() || myAISContext().IsNull())
			return;

		// #01. 점 위치
		gp_Pnt center(x, y, z);

		// #02. 구 형상 생성 (작은 반지름)
		TopoDS_Shape sphere = BRepPrimAPI_MakeSphere(center, radius);

		// #03. AIS_Shape로 생성
		Handle(AIS_Shape) aShape = new AIS_Shape(sphere);

		// #04. 색상 설정
		aShape->SetColor(Quantity_NOC_GREENYELLOW);
		aShape->SetDisplayMode(AIS_Shaded);

		// #05. Context에 표시
		myAISContext()->Display(aShape, Standard_True);
	}

	/// <summary>
	/// 선택 포인트 가져오기
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="z"></param>
	/// <returns></returns>
	bool GetPickPoint(double% x, double% y, double% z)
	{
		// * 클릭된 Shape이 있는지 확인
		if (myAISContext()->HasDetectedShape())
		{
			// * 첫 번째 선택된 점의 3D 좌표를 반환
			//  - MainSelector() = 선택 관리 객체.
			//  - PickedPoint(1) = 첫 번째 선택된 점의 3D 좌표를 반환. (gp_Pnt 타입)
			gp_Pnt pickedPoint = myAISContext()->MainSelector()->PickedPoint(1);

			x = pickedPoint.X();
			y = pickedPoint.Y();
			z = pickedPoint.Z();

			return  true;
		}

		return false;
	}

	bool CreateRectangleSensor(double x, double y, double z)
	{
		// * 점 위치
		gp_Pnt pickedPoint(x, y, z);

		// * 점에 근접한 페이스 찾기
		TopoDS_Face face = FindNearestFace(pickedPoint);

		if (face.IsNull())
			return false;

		// * 사각형 와이어 생성
		gp_Pnt p1(x - 5, y - 5, z);
		gp_Pnt p2(x + 5, y - 5, z);
		gp_Pnt p3(x + 5, y + 5, z);
		gp_Pnt p4(x - 5, y + 5, z);

		//TopoDS_Edge e1 = BRepBuilderAPI_MakeEdge(p1, p2);
		//TopoDS_Edge e2 = BRepBuilderAPI_MakeEdge(p2, p3);
		//TopoDS_Edge e3 = BRepBuilderAPI_MakeEdge(p3, p4);
		//TopoDS_Edge e4 = BRepBuilderAPI_MakeEdge(p4, p1);

		//TopoDS_Wire rectWire = BRepBuilderAPI_MakeWire(e1, e2, e3, e4);

		//// ----------------------------------------
		//// Face의 법선 방향을 투영 방향으로 사용
		//// ----------------------------------------
		//gp_Dir projDir(0, 0, 1); // 기본값
		//Handle(Geom_Surface) surf = BRep_Tool::Surface(face);
		//GeomLProp_SLProps props(surf, 0.5, 0.5, 1, gp::Resolution());
		//if (props.IsNormalDefined()) {
		//	projDir = props.Normal(); // 면의 법선 방향
		//}

		//BRepProj_Projection proj(rectWire, face, projDir);

		//// ----------------------------------------
		//// 투영 결과 수집
		//// ----------------------------------------
		//TopTools_ListOfShape projected;
		//for (proj.Init(); proj.More(); proj.Next()) {
		//	projected.Append(proj.Current());
		//}

		//if (projected.IsEmpty()) {
		//	std::cout << "Projection failed: no result." << std::endl;
		//	return false;
		//}

		//// ----------------------------------------
		//// Wire만 추출
		//// ----------------------------------------
		//TopoDS_Wire projectedWire;
		//for (TopTools_ListIteratorOfListOfShape it(projected); it.More(); it.Next()) {
		//	const TopoDS_Shape& s = it.Value();
		//	if (s.ShapeType() == TopAbs_WIRE) {
		//		projectedWire = TopoDS::Wire(s);
		//		break;
		//	}
		//}

		//if (projectedWire.IsNull()) {
		//	std::cout << "Projection did not produce a Wire." << std::endl;
		//	return false;
		//}

		//// ----------------------------------------
		//// 새로운 Face 생성
		//// ----------------------------------------
		//BRepBuilderAPI_MakeFace newFace(face, projectedWire);
		//if (!newFace.IsDone()) {
		//	std::cout << "Failed to build new Face with projected wire." << std::endl;
		//	return false;
		//}

		//TopoDS_Face resultFace = newFace.Face();

		//// 색상 적용
		//SetFaceColor(resultFace);

		return  true;
	}

	/// <summary>
	/// 점에 가장 가까운 Face 찾기
	/// </summary>
	/// <param name="queryPoint"></param>
	/// <returns></returns>
	TopoDS_Face  FindNearestFace(const gp_Pnt& queryPoint)
	{
		TopoDS_Shape aShape = GetOpenedShape();

		TopoDS_Face nearestFace;
		double minDist = 1e100; // 충분히 큰 값

		// gp_Pnt → TopoDS_Vertex 변환
		TopoDS_Vertex vtx = BRepBuilderAPI_MakeVertex(queryPoint);

		// 모든 Face 순회
		for (TopExp_Explorer exp(aShape, TopAbs_FACE); exp.More(); exp.Next())
		{
			TopoDS_Face face = TopoDS::Face(exp.Current());

			BRepExtrema_ExtPF distTool(vtx, face);
			if (distTool.IsDone() && distTool.NbExt() > 0)
			{
				double d = distTool.SquareDistance(1);

				if (d < minDist)
				{
					minDist = d;
					nearestFace = face;
				}
			}
		}

		return nearestFace;
	}

	/// <summary>
	/// 열린 Shape 가져오기
	/// </summary>
	/// <returns></returns>
	TopoDS_Shape GetOpenedShape()
	{
		AIS_ListOfInteractive list;

		// * 현재 AISContext에 표시된 객체 목록 가져오기
		myAISContext()->DisplayedObjects(list);

		Standard_Integer size = list.Size();

		// * 목록에서 AIS_Shape 타입 객체를 찾아 Shape 반환
		for (AIS_ListIteratorOfListOfInteractive it(list); it.More(); it.Next())
		{
			// * DownCast을 통해 AIS_Shape 타입으로 변환 시도
			Handle(AIS_Shape) aisShape = Handle(AIS_Shape)::DownCast(it.Value());

			// * AIS_Shape 타입이 맞다면 Shape 반환
			if (!aisShape.IsNull())
			{
				return aisShape->Shape(); // 현재 열린 Shape
			}
		}

		return TopoDS_Shape(); // 못 찾으면 빈 Shape
	}

	/// <summary>
	/// Face 색상 설정
	/// </summary>
	/// <param name="face"></param>
	void SetFaceColor(TopoDS_Face face)
	{
		// * TopExp_Explorer는 TopoDS_Shape 내부를 탐색하는 도구
		//  - face : TopoDS_Shape를 상속 받은 TopoDS_Face, TopoDS_Edge 등을 넣어 수행
		//  - TopAbs_Face : Face 타입만 추출
		TopExp_Explorer exp(face, TopAbs_FACE);

		// * 탐색된 Face에 대해 색상 설정 및 Context에 표시
		for (; exp.More(); exp.Next()) {
			// * 현재 탐색된 Face 가져오기
			TopoDS_Face face = TopoDS::Face(exp.Current());

			// * 시각화를 위해 AIS_Shape로 변환
			Handle(AIS_Shape) aisFace = new AIS_Shape(face);

			// * 색상 설정 
			aisFace->SetColor(Quantity_NOC_YELLOWGREEN);

			// * 디스플레이 모드 설정 (쉐이딩)
			myAISContext()->Display(aisFace, Standard_True);
		}
	}

	///<summary>
	/// STEP 파일 불러오기
	///</summary>
	bool LoadSTEPFile(String^ theFileName)
	{
		// * 파일 경로를 OCCT에서 인식 가능한 문자열로 생성
		const TCollection_AsciiString aFilename = toAsciiString(theFileName);

		// * STEP 파일 불러오기 수행
		return ModelShape::Instance().SetSTEPModelShape(myAISContext(), aFilename);
	}

	/// <summary>
	/// 센서 형상 추가
	/// </summary>
	/// <param name="sensorId">센서 아이디</param>
	/// <param name="x">센서 위치 X</param>
	/// <param name="y">센서 위치 Y</param>
	/// <param name="z">센서 위치 Z</param>
	/// <param name="width">센서 가로 사이즈</param>
	/// <param name="height">센서 세로 사이즈</param>
	/// <returns></returns>
	bool SetSensorShape(const int sensorId, const double x, const double y, const double z, const double width, const double height)
	{
		// * 좌표 점 생성
		const gp_Pnt point(x, y, z);

		// * 센서 형상 추가
		ModelShape::Instance().SetSensorShape(myAISContext(),sensorId, point, width, height);

		return true;
	}

	/// <summary>
	/// Initialize OCCTProxy
	/// </summary>
	void InitOCCTProxy(void)
	{
		myGraphicDriver() = NULL;
		myViewer() = NULL;
		myView() = NULL;
		myAISContext() = NULL;
	}

private:
	// fields
	NCollection_Haft<Handle(V3d_Viewer)>             myViewer;
	NCollection_Haft<Handle(V3d_View)>               myView;
	NCollection_Haft<Handle(AIS_InteractiveContext)> myAISContext;
	NCollection_Haft<Handle(OpenGl_GraphicDriver)>   myGraphicDriver;
};
