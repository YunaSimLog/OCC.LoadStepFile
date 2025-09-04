#include <Windows.h>
#include <iostream>
#include "ModelShape.h"

#include <STEPControl_Reader.hxx>
#include <vcclr.h>
#include <AIS_InteractiveContext.hxx>

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

			// * OpenCasCade에서 표시 가능한 객체인 AIS_Shape으로 변환
			Handle(AIS_Shape) aisShape = new AIS_Shape(aShape);

			// * Viewer 에 표시
			hAISContext->Display(aisShape, Standard_False);

			// * 선택 모드 활성화 (Face 선택 가능)
			hAISContext->Activate(aisShape, AIS_Shape::SelectionMode(TopAbs_FACE));

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

