#pragma once
#include <AIS_Shape.hxx>
#include <map>
#include <TopoDS_Face.hxx>
#include <TopoDS_Shell.hxx>
#include <TopoDS_Wire.hxx>

/// <summary>
/// 모델 형상 클래스
/// 싱글턴 패턴으로 구현
/// </summary>
class ModelShape
{
private:
	/// <summary>
	/// 모델 형상 생성자 
	/// </summary>
	ModelShape();

	/// <summary>
	/// 모델 형상 싱글턴 인스턴스
	/// </summary>
	static ModelShape* _pInstance;

	/// <summary>
	/// 복사 생성자 금지
	/// </summary>
	/// <param name="대상 ModelShape 객체"></param>
	ModelShape(const ModelShape&) = delete;

	/// <summary>
	/// 대입 연산자 금지
	/// </summary>
	/// <param name="대상 ModelShape 객체"></param>
	/// <returns></returns>
	ModelShape& operator=(const ModelShape&) = delete;

public:
	/// <summary>
	/// 모델 형상 싱글턴 인스턴스 반환
	/// </summary>	
	static ModelShape& Instance();

	/// <summary>
	/// 모델	형상 소멸자
	/// </summary>
	~ModelShape();

private:
	/// <summary>
	/// STEP 모델 형상
	/// </summary>
	TopoDS_Shape _modelShape;

	/// <summary>
	/// 뷰어 표시용 STEP 모델 형상
	/// </summary>
	Handle_AIS_Shape _hStepModelShape;

	/// <summary>
	/// 뷰여 표시용 센서	형상 맵
	/// </summary>
	std::map<int, Handle_AIS_Shape> _hSensorShape;

	TCollection_AsciiString ToAsciiString(const System::String^ theString);

	/// <summary>
	/// 좌표와 가까운 면 찾기
	/// </summary>
	TopoDS_Face ModelShape::FindNearestFace(const gp_Pnt& point);

	/// <summary>
	/// 기준 점과 기준 면을 기준으로 특정 영역 내의 인접한 면들 찾기 
	/// </summary>
	std::vector<TopoDS_Face> FineConnectedFacesWithinArea(const gp_Pnt& basePoint, const TopoDS_Face& baseFace, Standard_Real width, Standard_Real height, Handle(AIS_InteractiveContext)& hAISContext);

	TopoDS_Wire RecreateWireFromPointsOnFace(const TopoDS_Shape& projectedShape, const TopoDS_Face& face);

	/// <summary>
	/// 면의 Normal 방향 찾기
	/// </summary>
	gp_Dir GetFaceNormal(const TopoDS_Face& face, const gp_Pnt& refPoint);

	/// <summary>
	/// 사각형의 4점 만들기
	/// </summary>
	std::array<gp_Pnt, 4> MakeRectanlgePoints(const gp_Pnt& centerPoint, gp_Dir& normal, Standard_Real width, Standard_Real height);

	/// <summary>
	/// 사각형 와이어 만들기
	/// </summary>
	TopoDS_Shape MakeRectangleWire(const std::array<gp_Pnt, 4>& recPoints);

public:
	/// <summary>
	/// STEP 모델 형상 설정
	/// </summary>
	bool ModelShape::SetSTEPModelShape(Handle(AIS_InteractiveContext)& hAISContext, const TCollection_AsciiString& aFilename);

	/// <summary>
	/// 센서 형상 반환
	/// </summary>
	Handle_AIS_Shape ModelShape::GetSensorShape(const int sensorId) const;

	/// <summary>
	/// 센서 형상 설정
	/// </summary>
	bool ModelShape::SetSensorShape(Handle(AIS_InteractiveContext)& hAISContext, const int sensorId, const gp_Pnt& point, const Standard_Real width, const Standard_Real height);

	void SetShadingMode(Handle(AIS_InteractiveContext)& hAISContext);

	void SetWireMode(Handle(AIS_InteractiveContext)& hAISContext);
};