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

            // #02. OpenCASCADE 를 사용하기 위한 OCCTProxy 객체 초기화
            _occtProxy = new OCCTProxy();
        }
        #endregion

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
            _occtProxy.SetSeletedStyle(220, 10, 10);
            
            // * 하이라이트 색상 적용
            _occtProxy.SetHighlightStyle(23, 44, 120);

            // * 현재 컬러 가져오기
            GetCurrentColor();
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

        private bool GetCurrentColor()
        {
            bool ret = true;

            int r, g, b;

            r = _occtProxy.GetObjColR();
            g = _occtProxy.GetObjColG();
            b = _occtProxy.GetObjColB();

            Color color = Color.FromArgb(r, g, b);
            barEditColor.EditValue = color;

            return ret;
        }

        private void barEditColor_EditValueChanged(object sender, EventArgs e)
        {

        }

        private void panel1_MouseUp(object sender, MouseEventArgs e)
        {
            _occtProxy.Select();
        }

        private void panel1_MouseMove(object sender, MouseEventArgs e)
        {
            _occtProxy.MoveTo(e.X, e.Y);
        }

        private void btnAllSelect_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e)
        {
            _occtProxy.SelectAllObject();
        }
    }
}
