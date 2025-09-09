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

        /// <summary>
        /// * OpenCasCade 모델 매니저
        ///  - 초기화는 생성자에서 수행
        /// </summary>
        OpenCasCadeModelManager _openCasCadeModelManager;

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
           
        }

        /// <summary>
        /// STEP 파일 불러오기 클릭 이벤트
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnLoadSTEPFile_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e)
        {
            // #01. 파일 다이얼로그를 통해 STEP 파일 경로 받아오기
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Filter = "STEP 파일 (*.step, *.stp) | *.step; .stp; | 모든 파일 (.) | .";
            openFileDialog.Multiselect = false;

            DialogResult dialogResult = openFileDialog.ShowDialog();

            if (dialogResult == DialogResult.OK)
            {
                // * STEP 파일 경로
                string stepFilePath = openFileDialog.FileName;

                // #02. STEP 파일 불러오기 수행
                LoadSTEPFile(stepFilePath);
            }
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

        private void barEditBackColor_EditValueChanged(object sender, EventArgs e)
        {
            Color color = (Color)barEditBackColor.EditValue;
            int r = color.R;
            int g = color.G;
            int b = color.B;

            // * 배경 색상 변경
            _occtProxy.SetBackgroundColor(r, g, b);
        }

        private void chkUseGradient_CheckedChanged(object sender, DevExpress.XtraBars.ItemClickEventArgs e)
        {
            if (chkUseGradient.Checked)
            {
                // * 상단 컬러
                Color topColor = barEditGradientBackColorTop.EditValue == null ? Color.White : (Color)barEditGradientBackColorTop.EditValue;
                // * 하단 컬러
                Color downColor = barEditGradientBackColorDown.EditValue == null ? Color.CornflowerBlue : (Color)barEditGradientBackColorDown.EditValue;

                // * 그라데이션 배경색 적용
                _occtProxy.SetBackgroundGradientColor(topColor.R, topColor.G, topColor.B, downColor.R, downColor.G, downColor.B);
            }
            else
            {
                Color color = (Color)barEditBackColor.EditValue;
                _occtProxy.SetBackgroundColor(color.R, color.G, color.B);
            }
        }
        private void barEditGradientBackColorTop_EditValueChanged(object sender, EventArgs e)
        {
            if (chkUseGradient.Checked)
            {
                // * 상단 컬러
                Color topColor = barEditGradientBackColorTop.EditValue == null ? Color.White : (Color)barEditGradientBackColorTop.EditValue;
                // * 하단 컬러
                Color downColor = barEditGradientBackColorDown.EditValue == null ? Color.CornflowerBlue : (Color)barEditGradientBackColorDown.EditValue;

                // * 그라데이션 배경색 적용
                _occtProxy.SetBackgroundGradientColor(topColor.R, topColor.G, topColor.B, downColor.R, downColor.G, downColor.B);
            }
        }

        private void barEditGradientBackColorDown_EditValueChanged(object sender, EventArgs e)
        {
            if (chkUseGradient.Checked)
            {
                // * 상단 컬러
                Color topColor = barEditGradientBackColorTop.EditValue == null ? Color.White : (Color)barEditGradientBackColorTop.EditValue;
                // * 하단 컬러
                Color downColor = barEditGradientBackColorDown.EditValue == null ? Color.CornflowerBlue : (Color)barEditGradientBackColorDown.EditValue;

                // * 그라데이션 배경색 적용
                _occtProxy.SetBackgroundGradientColor(topColor.R, topColor.G, topColor.B, downColor.R, downColor.G, downColor.B);
            }
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

        private void btnAllSelect_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e)
        {
            // * 모든 객체 선택
            _occtProxy.SelectAllObject();
        }


        private bool LoadSTEPFile(string filePath)
        {
            bool ret = true;

            // #01. 파일 존재 여부 확인
            ret &= File.Exists(filePath);

            if (ret)
            {
                // #02. STEP 파일 부르기 수행
                _openCasCadeModelManager.LoadSTEPFile(filePath);
            }

            return ret;
        }

        private void btnAddSensor_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e)
        {
            bool ret = true;

            // #01. 센서 추가 Form 띄우기
            var addSensor = new AddSensor();
            var dialogResult = addSensor.ShowDialog();

            ret &= (dialogResult == DialogResult.OK);

            if (ret)
            {
                // #02. 입력 파라미터 가져오기
                double x = addSensor.X;
                double y = addSensor.Y;
                double z = addSensor.Z;
                double size = addSensor.Size;

                // #03. 점 삽입
                _occtProxy.InsertPointAsSphere(x, y, z, size);
            }
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

            // #03. OpenCASCADE 를 사용하기 위한 OCCTProxy 객체 초기화
            _occtProxy = new OCCTProxy();

            // * OpenCasCade 모델 매니저 초기화
            _openCasCadeModelManager = OpenCasCadeModelManager.Instance;
            _openCasCadeModelManager.Initialize(panel2);
        }

        #endregion
    }
}
