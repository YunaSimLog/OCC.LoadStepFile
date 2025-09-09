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
    /// 모델에서 사용되는 OpenCasCade 매니저 클래스 (싱글턴)
    /// </summary>
    internal class OpenCasCadeModelManager : OpenCasCadeManager
    {
        #region attributes
        // -------------------------------------------------------------------------------------------------------
        // * OpenCasCadeModelManager 내부 인스턴스
        private static OpenCasCadeModelManager _inst;

        // * OpenCasCadeManager 외부에서 호출 가능한 인스턴스
        public static OpenCasCadeModelManager Instance
        {
            get
            {
                if (_inst == null)
                {
                    _inst = new OpenCasCadeModelManager();
                }

                return _inst;
            }
        }
        // -------------------------------------------------------------------------------------------------------
        #endregion

        #region private

        /// <summary>
        /// 패널 이벤트 초기화
        /// </summary>
        private void InitializePanelEvent()
        {
            // * 패널 다시 그리기
            _displayPanel.Paint += panel_Paint;
            // * 패널 사이즈 변경된 상태
            _displayPanel.SizeChanged += panel_SizeChanged;
            // * 마우스 업
            _displayPanel.MouseUp += panel_MouseUp;
            // * 마우스 이동
            _displayPanel.MouseMove += panel_MouseMove;
            // * 마우스 다운
            _displayPanel.MouseDown += panel_MouseDown;
            // * 마우스 휠 
            _displayPanel.MouseWheel += panel_MouseWheel;
            // * 마우스 더블 클릭
            _displayPanel.MouseDoubleClick += panel_MouseDoubleClick;
        }

        #endregion

        #region protected

        protected override bool MouseUpSpecialFunction(MouseEventArgs e)
        {
            bool ret = true;

            ret &= (_displayPanel != null);
            ret &= (_occtProxy != null);

            // * 센서 클릭 삽입 모드 선택 시 수행
            if (e.Button == MouseButtons.Left)
            {
                double x = 0.0, y = 0.0, z = 0.0;

                // * 클릭한 위치의 좌표 가져오기
                if (_occtProxy.GetPickPoint(ref x, ref y, ref z))
                {
                    Debug.Print($"{x}, {y}, {z}");

                    _occtProxy.SetSensorShape(0, x, y, z, 10, 10);

                    //// * 점 삽입
                    //_occtProxy.InsertPointAsSphere(x, y, z, 2);

                    //// * 사각 센서 삽입
                    //_occtProxy.CreateRectangleSensor(x, y, z);
                }
            }

            return ret;
        }

        #endregion

        #region public

        /// <summary>
        /// OpenCasCade 모델 초기화
        /// </summary>
        /// <returns></returns>
        public bool Initialize(Panel panel)
        {
            bool ret = true;

            // #01. 유효성 검사
            ret &= (panel != null);

            if (ret)
            {
                // #01. panel 컨트롤 설정   
                _displayPanel = panel;

                // #02. OpenCasCade 초기화
                _occtProxy = new OCCTProxy();

                // #03. OpenCasCadeManager 초기화
                base.Initialize();

                // #04. 패널 이벤트 초기화
                InitializePanelEvent();
            }

            return ret;
        }

        /// <summary>
        /// STEP 파일 불러오기
        /// </summary>
        /// <param name="filePath">파일 경로</param>
        /// <returns></returns>
        public bool LoadSTEPFile(string filePath)
        {
            bool ret = true;

            // #01. STEP 파일 불러오기
            ret &= _occtProxy.LoadSTEPFile(filePath);

            // #02. 화면 줌 핏
            _occtProxy.ZoomAllView();

            return ret;
        }

        #endregion

    }
}
