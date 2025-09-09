#include <Windows.h>
#include <iostream>
#include "ModelShape.h"

// topology
#include <TopoDS.hxx>
#include <TopoDS_Shape.hxx>

// STEP 파일 불러오기
#include <STEPControl_Reader.hxx>
#include <vcclr.h>
#include <AIS_InteractiveContext.hxx>

// 가장 가까운 면 찾기
#include <TopoDS_Face.hxx>
#include <TopExp_Explorer.hxx>
#include <BRepExtrema_ExtPF.hxx>
#include <gp_Pnt.hxx>
#include <BRepExtrema_DistShapeShape.hxx>
#include <BRepBuilderAPI_MakeVertex.hxx>

// 형상 생성 도구
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepPrimAPI_MakeSphere.hxx>
#include <BRepProj_Projection.hxx>
#include <BRepPrimAPI_MakePrism.hxx>
#include <BRepTools.hxx>

// 면의 normal 방향 찾기
#include <GeomAPI_ProjectPointOnSurf.hxx>
#include <GeomLProp_SLProps.hxx>

// 사각형 와이어 만들기
#include <BRepBuilderAPI_MakePolygon.hxx>

/// <summary>
/// 모델 형상 생성자
/// </summary>
ModelShape::ModelShape()
{

}

/// <summary>
/// 모델 형상 싱글턴 인스턴스 반환
/// </summary>
ModelShape& ModelShape::Instance()
{
	static ModelShape instance;
	return  instance;
}

/// <summary>
/// 모델 형상 소멸자
/// </summary>
ModelShape::~ModelShape()
{

}

/// <summary>
/// STEP 파일 불러오기
/// </summary>
bool ModelShape::SetSTEPModelShape(Handle(AIS_InteractiveContext)& hAISContext, const TCollection_AsciiString& aFilename)
{
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

			// * 마지막 TopoDS_Shape만 보관한다. (여러개 TopoDS_Shape 고려하지 않는다.)
			_modelShape = aShape;

			// * OpenCasCade에서 표시 가능한 객체인 AIS_Shape으로 변환
			Handle(AIS_Shape) aisShape = new AIS_Shape(aShape);

			// * Viewer 에 표시
			hAISContext->Display(aisShape, Standard_False);

			// * Step 모델 색상 (회색)
			hAISContext->SetColor(aisShape, Quantity_NOC_SLATEGRAY2, Standard_False);

			// * 선택 모드 활성화 (Face 선택 가능)
			hAISContext->Activate(aisShape, AIS_Shape::SelectionMode(TopAbs_FACE));

			// * 마지막 AIS_Shape만 보관한다. (여러개 AIS_Shape 고려하지 않는다.)
			_hStepModelShape = aisShape;
		}

		if (_hStepModelShape.IsNull())
		{
			std::cout << "STEP 파일 Handle_AIS_ShapeH 값이 Null" << std::endl;
		}
	}

	// * 모든 Shape이 표시된 후 뷰어 갱신
	hAISContext->UpdateCurrentViewer();
	return true;
}

/// <summary>
/// 센서 형상 추가
/// </summary>
/// <param name="sensorId">센서 아이디</param>
/// <param name="point">센서 중심 위치 포인트</param>
/// <param name="width">센서 가로 사이즈</param>
/// <param name="height">센서 세로 사이즈</param>
bool ModelShape::SetSensorShape(Handle(AIS_InteractiveContext)& hAISContext, const int sensorId, const gp_Pnt& point, const double width, const double height)
{
	// #. 좌표와 가까운 면 찾기
	TopoDS_Face nearestFace = FindNearestFace(point);

	// #. Face의 normal 방향 가져오기
	gp_Dir projDir = GetFaceNormal(nearestFace, point);

	// #. normal을 가진 사각형 점 가져오기
	auto rectPoints = MakeRectanlgePoints(point, projDir, width, height);

	// #. 사각형 와이어 만들기
	TopoDS_Shape rectWire = MakeRectangleWire(rectPoints);

	// #. Face 위로 투영
	BRepProj_Projection proj(rectWire, nearestFace, projDir);

	// * 투영이 유효하지 않은 경우
	if (!proj.IsDone())
	{
		return false;
	}

	// #. 면에 투영된 형상
	TopoDS_Shape projectedShape = proj.Shape();

	// #. 면에 투영된 형상에서 와이어 가져오기
	TopoDS_Wire projectedWire;
	for (TopExp_Explorer exp(projectedShape, TopAbs_WIRE); exp.More(); exp.Next())
	{
		projectedWire = TopoDS::Wire(exp.Current());
		break; // 첫 번째 Wire만 사용
	}

	// * 투영된 형상의 와이어가 유호하지 않은 경우
	if (projectedWire.IsNull())
	{
		return false;
	}

	// #. 투영 와이어로 면 생성
	TopoDS_Face stickerFace = BRepBuilderAPI_MakeFace(projectedWire);

	// #. 두께로 사용할 벡터 생성
	gp_Vec offset(projDir);
	offset.Scale(0.1);

	// #. 0.1mm 두께로 얇게 돌출
	TopoDS_Shape thinSticker = BRepPrimAPI_MakePrism(stickerFace, offset);

	// #. AIS_Shape로 생성
	Handle(AIS_Shape) thinStickerShape = new AIS_Shape(thinSticker);

	// * Viewer 에 표시
	hAISContext->Display(thinStickerShape, Standard_False);

	// #. 색상 정보 설정
	hAISContext->SetColor(thinStickerShape, Quantity_NOC_SEAGREEN, Standard_False);

	return true;
}

/// <summary>
/// 좌표와 가까운 면 찾기
/// </summary>
TopoDS_Face ModelShape::FindNearestFace(const gp_Pnt& point)
{
	double minDist = DBL_MAX;
	TopoDS_Face nearestFace;

	// * modelShape에서 모든 Face 순회
	for (TopExp_Explorer exp(_modelShape, TopAbs_FACE); exp.More(); exp.Next())
	{
		TopoDS_Face face = TopoDS::Face(exp.Current());
		BRepExtrema_DistShapeShape dist(BRepBuilderAPI_MakeVertex(point), face);

		if (dist.IsDone() && dist.Value() < minDist)
		{
			minDist = dist.Value();
			nearestFace = face;
		}
	}
	return nearestFace;
}

/// <summary>
/// 면의 Normal 방향 찾기
/// </summary>
gp_Dir ModelShape::GetFaceNormal(const TopoDS_Face& face, const gp_Pnt& refPoint)
{
	// * 기본 방향은 z방향으로 설정
	gp_Dir normalDir(0, 0, 1);

	// #01. Face의 기하(Surface) 핸들
	Handle(Geom_Surface) surf = BRep_Tool::Surface(face);

	// * 곡면이 유효하지 않을 경우 z방향으로 반환
	if (surf.IsNull())
	{
		return normalDir;
	}

	// #02. 기준점을 곡면에 투영 -> (u,v)
	GeomAPI_ProjectPointOnSurf projector(refPoint, surf);

	// * 투명 결과가 유효하지 않을 경우, z방향으로 반환
	if (!projector.IsDone() || projector.NbPoints() == 0)
	{
		return normalDir;
	}

	// #03. 점에 가장 가까운 곡면의 UV 가져오기
	Standard_Real u, v;
	projector.LowerDistanceParameters(u, v);

	// #04. (u,v) 에서 Normal 방향 계산
	GeomLProp_SLProps props(surf, u, v, 1, Precision::Confusion());
	if (!props.IsNormalDefined())
	{
		return normalDir;
	}

	// * 계산된 Normal 방향 가져오기
	normalDir = props.Normal();

	// #05. Face 방향 보정 (뒤집힌 Face 라면 반전)
	if (face.Orientation() == TopAbs_REVERSED)
	{
		normalDir.Reverse();
	}

	return normalDir;
}

/// <summary>
/// 사각형의 4점 만들기
/// </summary>
/// <param name="centerPoint">중심 점</param>
/// <param name="normal">normal 방향</param>
/// <param name="width">가로</param>
/// <param name="height">세로</param>
/// <returns></returns>
std::array<gp_Pnt, 4> ModelShape::MakeRectanlgePoints(const gp_Pnt& centerPoint, gp_Dir& normal, Standard_Real width, Standard_Real height)
{
	// gp_Dir -> gp_Vec으로 변환
	gp_Vec n(normal);

	// 기준 벡터 선택
	gp_Vec a(0, 0, 1);
	if (Abs(n.Dot(a) > 0.999))
	{
		a = gp_Vec(0, 1, 0);
	}

	// u = n x a
	gp_Vec u = n ^ a;
	if (u.Magnitude() < 1e-12)
	{
		a = gp_Vec(1, 0, 0);
		u = n ^ a;
	}
	u.Normalize();

	gp_Vec v = n ^ u;
	v.Normalize();

	double hw = width * 0.5;
	double hh = height * 0.5;

	gp_Pnt p0 = centerPoint.Translated(u * hw + v * hh);
	gp_Pnt p1 = centerPoint.Translated(u * (-hw) + v * hh);
	gp_Pnt p2 = centerPoint.Translated(u * (-hw) + v * (-hh));
	gp_Pnt p3 = centerPoint.Translated(u * hw + v * (-hh));

	std::cout << "p0 : " << p0.X() << ", " << p0.Y() << ", " << p0.Z() << std::endl;
	std::cout << "p1 : " << p1.X() << ", " << p1.Y() << ", " << p1.Z() << std::endl;
	std::cout << "p2 : " << p2.X() << ", " << p2.Y() << ", " << p2.Z() << std::endl;
	std::cout << "p3 : " << p3.X() << ", " << p3.Y() << ", " << p3.Z() << std::endl;

	return { p0,p1,p2,p3 };
}

/// <summary>
/// 사각형 와이어 만들기
/// </summary>
/// <param name="recPoints">사각형 꼭지점 배열</param>
/// <returns></returns>
TopoDS_Shape ModelShape::MakeRectangleWire(const std::array<gp_Pnt, 4>& recPoints)
{
	// * 사각형 점을 이을 폴리곤
	BRepBuilderAPI_MakePolygon polygon;

	// #01. 점 순회하며, 폴리곤에 점 추가
	for (int i=0;i<recPoints.max_size();++i)
	{
		polygon.Add(recPoints[i]);
	}

	// #02. 폴리곤 닫히도록 수행
	polygon.Close();

	// #03. 폴리곤의 와이어 반환
	return polygon.Wire();
}
