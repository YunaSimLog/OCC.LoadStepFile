#pragma once
#include <AIS_Shape.hxx>
#include <map>

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
	Handle_AIS_Shape _hStepModelShape;

	/// <summary>
	/// 센서	형상 맵
	/// </summary>
	std::map<int, Handle_AIS_Shape> _hSensorShape;

	TCollection_AsciiString toAsciiString(const System::String^ theString);

public:
	/// <summary>
	/// STEP 모델 형상 반환
	/// </summary>
	Handle_AIS_Shape GetStepModelShape() const;

	/// <summary>
	/// STEP 모델 형상 설정
	/// </summary>
	bool ModelShape::SetSTEPModelShape(Handle(AIS_InteractiveContext)& hAISContext, const TCollection_AsciiString& aFilename);

	/// <summary>
	/// 센서 형상 반환
	/// </summary>
	Handle_AIS_Shape GetSensorShape(int sensorId) const;

	/// <summary>
	/// 센서 형상 설정
	/// </summary>
	void SetSensorShape(int sensorId);
};