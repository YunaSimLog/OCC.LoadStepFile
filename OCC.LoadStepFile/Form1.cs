using DevExpress.XtraEditors;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace OCC.LoadStepFile
{
    public partial class Form1 : DevExpress.XtraBars.Ribbon.RibbonForm
    {
        #region attributes
        // --------------------------------------------------------------------------------------------------------------
        /// <summary>
        /// * OpenCASCADE Proxy 객체
        /// - 초기화는 Form 생성자에서 수행
        /// </summary>
        OCCTProxy _occtProxy;

        // --------------------------------------------------------------------------------------------------------------
        #endregion

        #region private

        /// <summary>
        /// Form1 불러오기 이벤트
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Form1_Load(object sender, EventArgs e)
        {
            // #01. OpenCASCADE 초기화 및 패널에 뷰 연결
            InitilizeOCCTProxy();

            // * STEP 파일 경로
            string stepFilePath = "../../../Sample/linkrods.step";

            // #01. STEP 파일 불러오기 수행
            LoadSTEPFile(stepFilePath);

            // * 쉐이딩 모드로 설정
            _occtProxy.SetShadingMode();

            // * 선택 색상 적용
            _occtProxy.SetSelectedStyle(220, 10, 10);

            // * 하이라이트 색상 적용
            _occtProxy.SetHighlightStyle(23, 44, 120);

            // * 뷰 큐브 그리기
            _occtProxy.SetViweCube();
        }

        /// <summary>
        /// Panel1 다시 그리기 이벤트
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void panel1_Paint(object sender, PaintEventArgs e)
        {
            // #01. 뷰 다시 그리기
            _occtProxy.RedrawView();

            // #02. 뷰 업데이트 하기
            _occtProxy.UpdateView();
        }

        /// <summary>
        /// STEP 파일 불러오기 클릭 이벤트
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnLoadSTEPFile_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Filter = "STEP 파일 (*.step, *.stp) | *.step; .stp; | 모든 파일 (.) | .";
            openFileDialog.Multiselect = false;

            DialogResult dialogResult = openFileDialog.ShowDialog();

            if (dialogResult == DialogResult.OK)
            {
                // * STEP 파일 경로
                string stepFilePath = openFileDialog.FileName;

                // #01. STEP 파일 불러오기 수행
                LoadSTEPFile(stepFilePath);
            }
        }

        /// <summary>
        /// 패널 사이즈 변경 이벤트
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void panel1_SizeChanged(object sender, EventArgs e)
        {
            // #01. 뷰 업데이트 하기
            _occtProxy.UpdateView();
        }

        private void btnShowShadingMode_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e)
        {
            // #01. 쉐이딩 모드로 설정
            _occtProxy.SetShadingMode();
        }

        private void btnShowWireMode_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e)
        {
            // #01. 와이어 모드로 설정
            _occtProxy.SetWireMode();
        }

        private void btnAmbientOcclusion_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e)
        {
            // #01. 엠비언트 오클루젼 설정 (작업중)
            _occtProxy.EnableAmbientOcclusion();
        }

        private void barEditColor_EditValueChanged(object sender, EventArgs e)
        {
            Color color = (Color)barEditColor.EditValue;
            int r = color.R;
            int g = color.G;
            int b = color.B;
            _occtProxy.SetColor(r, g, b);
        }

        private void panel1_MouseUp(object sender, MouseEventArgs e)
        {
            _occtProxy.Select();
        }

        private void panel1_MouseMove(object sender, MouseEventArgs e)
        {
            _occtProxy.MoveTo(e.X, e.Y);
        }

        private void panel1_MouseWheel(object sender, MouseEventArgs e)
        {
            // * 마우스 확대 축소 방법 1 (마우스 커서를 따라 줌아웃) *******************************
            _occtProxy.Zoom(e.X, e.Y, e.Delta);

            // * 마우스 확대 축소 방법 2 (화면 가운데를 줌아웃) ***********************************
            //int firstPosX = e.X;
            //int secondPosX = e.X + e.Delta / 120 * 10; // 마우스 휠 스크롤에 따라 확대/축소 비율 조정
            //int firstPosY = e.Y;
            //int secondPosY = e.Y + e.Delta / 120 * 10; // 마우스 휠 스크롤에 따라 확대/축소 비율 조정

            //_occtProxy.Zoom(firstPosX, firstPosY, secondPosX, secondPosY);
        }

        private void btnAllSelect_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e)
        {
            // * 모든 객체 선택
            _occtProxy.SelectAllObject();
        }

        private void barButtonItem2_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e)
        {
            bool selectd = _occtProxy.IsObjectSelected();

            if (selectd)
            {
                MessageBox.Show("선택된 것이 있는 상태", "", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            else
            {
                MessageBox.Show("선택된 것이 없는 상태", "", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        /// <summary>
        /// OCCTProxy 뷰어 초기화
        /// </summary>
        /// <returns></returns>
        private bool InitilizeOCCTProxy()
        {
            bool ret = true;

            // #01. OCCTProxy 뷰어 초기화
            //  - 패널 영역을 OpenCASCADE로 사용할 것 이다.
            ret &= _occtProxy.InitViewer(panel1.Handle);

            if (!ret)
            {
                XtraMessageBox.Show("OpenCASCADE 뷰어 초기화에 실패하였습니다.", "오류", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }

            return ret;
        }

        private bool LoadSTEPFile(string filePath)
        {
            bool ret = true;

            // #01. 파일 존재 여부 확인
            ret &= File.Exists(filePath);

            if (ret)
            {
                // #02. OCCTProxy의 TranslateModel을 이용하여 STEP 파일 부르기 수행
                _occtProxy.ImportStep(filePath);

                // #03. 전체 보기 뷰
                _occtProxy.ZoomAllView();
            }

            return ret;
        }

        #endregion

        #region public
        /// <summary>
        /// Form1 생성자
        /// </summary>
        public Form1()
        {
            // #01. Form 컨트롤 객체 초기화
            InitializeComponent();

            // #02. 마우스 휠 이벤트 핸들러 등록 
            panel1.MouseWheel += new MouseEventHandler(panel1_MouseWheel);

            // #03. OpenCASCADE 를 사용하기 위한 OCCTProxy 객체 초기화
            _occtProxy = new OCCTProxy();


        }
        #endregion

    }
}
