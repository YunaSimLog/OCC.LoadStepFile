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
#include <BRepBuilderAPI_Transform.hxx>
#include <ShapeFix_Wire.hxx>

// 면의 normal 방향 찾기
#include <GeomAPI_ProjectPointOnSurf.hxx>
#include <GeomLProp_SLProps.hxx>

// 사각형 와이어 만들기
#include <BRepBuilderAPI_MakePolygon.hxx>

// 인접한 면 찾기
#include <queue>
#include <TopTools_IndexedDataMapOfShapeListOfShape.hxx>
#include <TopExp.hxx>
#include <unordered_set>

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

			// * 모델 쉐이딩 및 테두리 표시
			hAISContext->SetDisplayMode(aisShape, AIS_Shaded, Standard_True);
			aisShape->Attributes()->SetFaceBoundaryDraw(true); // 테두리 표시
			hAISContext->Redisplay(aisShape, Standard_True);

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
bool ModelShape::SetSensorShape(Handle(AIS_InteractiveContext)& hAISContext, const int sensorId, const gp_Pnt& point, const Standard_Real width, const Standard_Real height)
{
	// #. 좌표와 가까운 면 찾기
	TopoDS_Face nearestFace = FindNearestFace(point);

	// #. 좌표와 가까운 면을 기준으로 사각형 영역에 해당하는 면 찾기
	std::vector<TopoDS_Face> connectedFaces = FineConnectedFacesWithinArea(point, nearestFace, width, height, hAISContext);

	BRepBuilderAPI_MakeWire  sensorMakeWire;

	for (int i = 0; i < connectedFaces.size(); ++i)
	{
		TopoDS_Face targetFace = connectedFaces[i];

		// #. Face의 normal 방향 가져오기
		gp_Dir projDir = GetFaceNormal(targetFace, point);

		// #. normal을 가진 사각형 점 가져오기
		auto rectPoints = MakeRectanlgePoints(point, projDir, width, height);

		// #. 사각형 와이어 만들기
		TopoDS_Shape rectWire = MakeRectangleWire(rectPoints);

		// #. Face 위로 투영
		BRepProj_Projection proj(rectWire, targetFace, projDir);

		// * 투영이 유효하지 않은 경우
		if (!proj.IsDone())
		{
			return false;
		}

		// #. 면에 투영된 형상
		TopoDS_Shape projectedShape = proj.Shape();

		// 점 단위로 Wire 재생성
		TopoDS_Wire fixedWire = RecreateWireFromPointsOnFace(projectedShape, targetFace);

		// Face 생성
		TopoDS_Face stickerFace = BRepBuilderAPI_MakeFace(fixedWire);

		// * 생성할 평면을 0.1mm 정도 위로 띄우기
		//  - 모델과 면이 겹쳐서 생성되면 번쩍거리고 잘 안보임
		gp_Vec offset(projDir);
		offset.Normalize();
		offset *= 0.1;

		// * 이동 변환 적용
		gp_Trsf trsf;
		trsf.SetTranslation(offset);

		TopoDS_Shape visualSticker = BRepBuilderAPI_Transform(stickerFace, trsf);

		// * AIS_Shape로 표시
		Handle(AIS_Shape) stickerShape = new AIS_Shape(visualSticker);
		hAISContext->Display(stickerShape, Standard_False);
		hAISContext->SetColor(stickerShape, Quantity_NOC_SEAGREEN, Standard_False);
	}

	return true;
}

/// <summary>
/// 점 단위로 와이어 재작성
/// </summary>
/// <param name="projectedShape"></param>
/// <param name="face"></param>
/// <returns></returns>
TopoDS_Wire  ModelShape::RecreateWireFromPointsOnFace(const TopoDS_Shape& projectedShape, const TopoDS_Face& face)
{
	std::vector<gp_Pnt> points;

	// 1. 기존 Edge 끝점 추출
	for (TopExp_Explorer exp(projectedShape, TopAbs_EDGE); exp.More(); exp.Next())
	{
		TopoDS_Edge edge = TopoDS::Edge(exp.Current());
		TopoDS_Vertex v1 = TopExp::FirstVertex(edge);
		TopoDS_Vertex v2 = TopExp::LastVertex(edge);

		gp_Pnt p1 = BRep_Tool::Pnt(v1);
		gp_Pnt p2 = BRep_Tool::Pnt(v2);

		points.push_back(p1);
		points.push_back(p2);
	}

	// 2. 중복점 제거 (같은 좌표)
	std::vector<gp_Pnt> uniquePoints;
	for (auto& p : points)
	{
		bool duplicate = false;
		for (auto& up : uniquePoints)
		{
			if (p.IsEqual(up, 1e-7)) { duplicate = true; break; }
		}
		if (!duplicate) uniquePoints.push_back(p);
	}

	// 3. Edge 재생성
	BRepBuilderAPI_MakeWire mkWire;
	for (size_t i = 0; i < uniquePoints.size(); ++i)
	{
		const gp_Pnt& p1 = uniquePoints[i];
		const gp_Pnt& p2 = uniquePoints[(i + 1) % uniquePoints.size()]; // 마지막 점은 첫 점과 연결
		mkWire.Add(BRepBuilderAPI_MakeEdge(p1, p2));
	}

	TopoDS_Wire wire = mkWire.Wire();

	// 4. ShapeFix_Wire로 끝점 연결 및 닫힘 보장
	ShapeFix_Wire fixWire;
	fixWire.Load(wire);
	fixWire.FixConnected();
	fixWire.FixClosed();
	fixWire.Perform();

	return fixWire.Wire();
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
/// 기준 면을 기준으로 특정 영역 내의 인접한 면들 찾기 사용자 정의 해시
/// </summary>
struct FaceHasher {
	std::size_t operator()(const TopoDS_Face& f) const {
		return (std::size_t)f.TShape().get();
	}
};

/// <summary>
/// 기준 면을 기준으로 특정 영역 내의 인접한 면들 찾기의 비교 함수
/// </summary>
struct FaceEqual {
	bool operator()(const TopoDS_Face& a, const TopoDS_Face& b) const {
		return a.IsSame(b);
	}
};

/// <summary>
/// 기준 점과 기준 면을 기준으로 특정 영역 내의 인접한 면들 찾기 
/// </summary>
std::vector<TopoDS_Face> ModelShape::FineConnectedFacesWithinArea(const gp_Pnt& basePoint, const TopoDS_Face& baseFace, Standard_Real width, Standard_Real height, Handle(AIS_InteractiveContext)& hAISContext)
{
	// * 찾은 면 결과
	std::vector<TopoDS_Face> result;

	// #. 영역 범위 값 구하기
	double areaValue = sqrt(pow(width * 0.5, 2) + pow(height * 0.5, 2));

	// #. 형상 내에서 특정 타입(Edge)와 그것을 포함하는 상위(Face)간의 관계를 매핑
	//  - 1번째 인자: 전체 모델
	//  - 2번째 인자: 엣지 단위로
	//  - 3번째 인자: 엣지가 속한 페이스
	//  - 4번째 인자: 결과
	TopTools_IndexedDataMapOfShapeListOfShape edgeToFaceMap;
	TopExp::MapShapesAndAncestors(_modelShape, TopAbs_EDGE, TopAbs_FACE, edgeToFaceMap);

	// * 평면 탐색을 위한 평면 담기
	std::queue < TopoDS_Face> q;
	q.push(baseFace);

	// * 검색 대상으로 사용한 면인지 구분을 위한 해시 컨테이너
	//  - TopoDS_Face는 기본적으로 std::hash 및 operator==가 정의되어 있지않으므로, FaceHasher, FaceEqual 정의
	std::unordered_set<TopoDS_Face, FaceHasher, FaceEqual> visited;
	visited.insert(baseFace);

	while (!q.empty())
	{
		TopoDS_Face current = q.front();
		q.pop();

		// 기준 Face도 결과에 포함됨
		result.push_back(current);

		// #. 면에 존재하는 모서리선들 순회
		for (TopExp_Explorer exp(current, TopAbs_EDGE); exp.More(); exp.Next())
		{
			// * 대상 모서리선
			TopoDS_Edge edge = TopoDS::Edge(exp.Current());

			// * 모서리선에 연결된 면들 가져오기
			const TopTools_ListOfShape adjacentFaces = edgeToFaceMap.FindFromKey(edge);

			// #. 가져온 면들 순회
			for (TopTools_ListIteratorOfListOfShape it(adjacentFaces); it.More(); it.Next())
			{
				// * 이미 탐색한 면이지 여부 체크
				TopoDS_Face adjFace = TopoDS::Face(it.Value());
				if (visited.find(adjFace) != visited.end())
				{
					continue;;
				}

				// * 기준점과 대상 면의 거리를 구하기
				TopoDS_Vertex vertex = BRepBuilderAPI_MakeVertex(basePoint);
				BRepExtrema_ExtPF dist(vertex, adjFace);

				Handle(AIS_Shape) aisFace = new AIS_Shape(adjFace);

				bool re = dist.IsDone();
				int n = dist.NbExt();

				// * 거리 계산이 유효한지 여부 확인
				if (dist.IsDone() && dist.NbExt() > 0)
				{
					// * 최소 거리 계산
					Standard_Real minDistance = sqrt(dist.SquareDistance(1));

					std::cout << "거리: " << minDistance << std::endl;

					// * 영역 범위 내 거리 값인지 여부 확인
					if (minDistance <= areaValue)
					{
						// * 검색한 면 대상 추가
						visited.insert(adjFace);
						q.push(adjFace);

						// * 찾은 면은 오렌지색
						aisFace->SetColor(Quantity_NOC_ORANGE);
						//hAISContext->Display(aisFace, Standard_True);
					}
				}
				else
				{
					aisFace->SetColor(Quantity_NOC_GREENYELLOW);
					//hAISContext->Display(aisFace, Standard_True);
				}
			}
		}
	}

	std::cout << result.size() << std::endl;

	return  result;
}

/// <summary>
/// 면을 쉘로 합치기
/// </summary>
TopoDS_Shell MakeShellFromFaces(const std::vector<TopoDS_Face>& faces)
{
	BRep_Builder builder;
	TopoDS_Shell shell;
	builder.MakeShell(shell);

	for (const auto& f : faces)
	{
		builder.Add(shell, f);
	}

	return shell;
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
	for (int i = 0; i < recPoints.max_size(); ++i)
	{
		polygon.Add(recPoints[i]);
	}

	// #02. 폴리곤 닫히도록 수행
	polygon.Close();

	// #03. 폴리곤의 와이어 반환
	return polygon.Wire();
}

void ModelShape::SetShadingMode(Handle(AIS_InteractiveContext)& hAISContext)
{
	// * STEP 모델 존재하지 않는 경우
	if (_hStepModelShape.IsNull())
	{
		return;
	}

	// * 모델 쉐이딩 및 테두리 표시
	hAISContext->SetDisplayMode(_hStepModelShape, AIS_Shaded, Standard_True);
	hAISContext->Redisplay(_hStepModelShape, Standard_True);
}

void ModelShape::SetWireMode(Handle(AIS_InteractiveContext)& hAISContext)
{
	// * STEP 모델 존재하지 않는 경우
	if (_hStepModelShape.IsNull())
	{
		return;
	}

	// * 모델 쉐이딩 및 테두리 표시
	hAISContext->SetDisplayMode(_hStepModelShape, AIS_WireFrame, Standard_True);
	hAISContext->Redisplay(_hStepModelShape, Standard_True);
}