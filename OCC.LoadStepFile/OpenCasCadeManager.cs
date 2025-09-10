using DevExpress.XtraEditors;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace OCC.LoadStepFile
{
    /// <summary>
    /// OpenCasCade 매니저 추상클래스
    /// </summary>
    public abstract class OpenCasCadeManager
    {
        #region attributes
        // -------------------------------------------------------------------------------------------------------
        /// <summary>
        /// 드래깅 모드 상태 여부
        /// </summary>
        bool _isDraggingMode = false;

        /// <summary>
        /// 마우스 위치 X
        /// </summary>
        int _mousePosX;

        /// <summary>
        /// 마우스 위치 Y
        /// </summary>
        int _mousePosY;

        // * OpenCasCade를 연결할 패널
        protected Panel _displayPanel;

        // * OpenCasCade 프록시
        protected OCCTProxy _occtProxy;
        // -------------------------------------------------------------------------------------------------------
        #endregion

        #region private
        #endregion

        #region protected
        /// <summary>
        /// 패널 다시 그리기 이벤트
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        protected void panel_Paint(object sender, PaintEventArgs e)
        {
            // #01. 뷰 다시 그리기
            _occtProxy.RedrawView();

            // #02. 뷰 업데이트 하기
            _occtProxy.UpdateView();
        }

        /// <summary>
        /// 패널 사이즈 변경 이벤트
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        protected void panel_SizeChanged(object sender, EventArgs e)
        {
            // #01. 뷰 업데이트 하기
            _occtProxy.UpdateView();
        }

        /// <summary>
        /// 패널 마우스 업 이벤트
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        protected void panel_MouseUp(object sender, MouseEventArgs e)
        {
            // #01. 모델 선택
            _occtProxy.Select();

            // #02. 마우스 특수 함수
            MouseUpSpecialFunction(e);

            // * 드래깅 모드 종료
            _isDraggingMode = false;
        }

        /// <summary>
        /// 패널 마우스 이동 이벤트
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        protected void panel_MouseMove(object sender, MouseEventArgs e)
        {
            // * 마우스 호버되면 하이라이트 되도록
            _occtProxy.MoveTo(e.X, e.Y);

            // * 드래깅 모드일 때 수행
            if (_isDraggingMode)
            {
                // * 마우스 가운데 버튼 누른 상태로 이동할 때
                if (e.Button == System.Windows.Forms.MouseButtons.Right)
                {
                    // * 회전 수행
                    _occtProxy.Rotation(e.X, e.Y);
                }
                else if (e.Button == System.Windows.Forms.MouseButtons.Middle)
                {
                    // * 현재 마우스 위치 기준으로 마지막 저장된 위치 간 크기 구하기
                    var deltaX = e.X - _mousePosX;
                    var deltaY = _mousePosY - e.Y;

                    // * 팬 이동 수행
                    _occtProxy.Pan(deltaX, deltaY);
                }
            }

            // * 현재 마우스 위치 값 업데이트
            _mousePosX = e.X;
            _mousePosY = e.Y;
        }

        /// <summary>
        /// 패널 마우스 다운 이벤트
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        protected void panel_MouseDown(object sender, MouseEventArgs e)
        {
            // #01. 드래깅 모드 활성
            _isDraggingMode = true;

            // #02. 마우스 위치 정보 저장 
            _mousePosX = e.X;
            _mousePosY = e.Y;

            // #03. 마우스 우클릭 버튼 눌렀을 때 회전될 수 있도록
            if (e.Button == System.Windows.Forms.MouseButtons.Right)
            {
                // * 회전 시작 위치 현재 마우스 위치 값으로 설정
                _occtProxy.StartRotation(e.X, e.Y);
            }
        }

        /// <summary>
        /// 패널 마우스 휠 이벤트
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        protected void panel_MouseWheel(object sender, MouseEventArgs e)
        {
            // * 마우스 확대 축소 방법 1 (마우스 커서를 따라 줌아웃) 
            _occtProxy.Zoom(e.X, e.Y, e.Delta);
        }

        /// <summary>
        /// 패널 마우스 더블 클릭 이벤트
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        protected void panel_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            // * 전체 보기
            _occtProxy.ZoomAllView();
        }

        /// <summary>
        /// OpenCasCade 뷰어 영역 초기화
        /// </summary>
        /// <returns></returns>
        protected bool Initialize()
        {
            bool ret = true;

            // #01. 유효성 검사
            ret &= (_occtProxy != null);
            ret &= (_displayPanel != null);

            if (ret)
            {
                // #02. OCCTProxy 뷰어 초기화
                //  - 패널 영역을 OpenCASCADE로 사용할 것 이다.
                ret &= _occtProxy.InitViewer(_displayPanel.Handle);

                if (ret)
                {
                    // * 뷰 큐브 그리기
                    _occtProxy.SetViweCube();

                    // * 쉐이딩 모드로 설정
                    _occtProxy.SetShadingMode();

                    // * 선택 색상 적용
                    _occtProxy.SetSelectedStyle(220, 10, 10);

                    // * 하이라이트 색상 적용
                    _occtProxy.SetHighlightStyle(23, 44, 120);
                }
                else
                {
                    XtraMessageBox.Show("OpenCASCADE 뷰어 초기화에 실패하였습니다.", "오류", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }

            return ret;
        }

        /// <summary>
        /// 마우스 업에 사용될 특수 함수
        /// </summary>
        /// <returns></returns>
        protected abstract bool MouseUpSpecialFunction(MouseEventArgs e);

        #endregion

        #region public

        /// <summary>
        /// 쉐이딩 모드로 설정
        /// </summary>
        public void SetShadingMode()
        {
            // #01. 쉐이딩 모드로 설정
            _occtProxy.SetShadingMode();
        }

        /// <summary>
        /// 와이어 모드로 설정
        /// </summary>
        public void SetWireMode()
        {
            // #01. 와이어 모드로 설정
            _occtProxy.SetWireMode();
        }

        #endregion
    }
}
