namespace OCC.LoadStepFile
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.panel1 = new System.Windows.Forms.Panel();
            this.ribbonPageCategory1 = new DevExpress.XtraBars.Ribbon.RibbonPageCategory();
            this.ribbonPage2 = new DevExpress.XtraBars.Ribbon.RibbonPage();
            this.ribbonPageGroup2 = new DevExpress.XtraBars.Ribbon.RibbonPageGroup();
            this.ribbonPage1 = new DevExpress.XtraBars.Ribbon.RibbonPage();
            this.ribbonPageGroup1 = new DevExpress.XtraBars.Ribbon.RibbonPageGroup();
            this.btnLoadSTEPFile = new DevExpress.XtraBars.BarButtonItem();
            this.ribbonPageGroup3 = new DevExpress.XtraBars.Ribbon.RibbonPageGroup();
            this.btnShowShadingMode = new DevExpress.XtraBars.BarButtonItem();
            this.btnShowWireMode = new DevExpress.XtraBars.BarButtonItem();
            this.btnAmbientOcclusion = new DevExpress.XtraBars.BarButtonItem();
            this.barEditColor = new DevExpress.XtraBars.BarEditItem();
            this.repositoryItemColorPickEdit1 = new DevExpress.XtraEditors.Repository.RepositoryItemColorPickEdit();
            this.ribbonPageGroup4 = new DevExpress.XtraBars.Ribbon.RibbonPageGroup();
            this.btnAllSelect = new DevExpress.XtraBars.BarButtonItem();
            this.barButtonItem2 = new DevExpress.XtraBars.BarButtonItem();
            this.ribbonControl1 = new DevExpress.XtraBars.Ribbon.RibbonControl();
            this.barButtonItem1 = new DevExpress.XtraBars.BarButtonItem();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemColorPickEdit1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.ribbonControl1)).BeginInit();
            this.SuspendLayout();
            // 
            // panel1
            // 
            this.panel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel1.Location = new System.Drawing.Point(0, 150);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(1073, 600);
            this.panel1.TabIndex = 1;
            this.panel1.SizeChanged += new System.EventHandler(this.panel1_SizeChanged);
            this.panel1.Paint += new System.Windows.Forms.PaintEventHandler(this.panel1_Paint);
            this.panel1.MouseDown += new System.Windows.Forms.MouseEventHandler(this.panel1_MouseDown);
            this.panel1.MouseMove += new System.Windows.Forms.MouseEventHandler(this.panel1_MouseMove);
            this.panel1.MouseUp += new System.Windows.Forms.MouseEventHandler(this.panel1_MouseUp);
            // 
            // ribbonPageCategory1
            // 
            this.ribbonPageCategory1.Name = "ribbonPageCategory1";
            this.ribbonPageCategory1.Text = "ribbonPageCategory1";
            // 
            // ribbonPage2
            // 
            this.ribbonPage2.Name = "ribbonPage2";
            this.ribbonPage2.Text = "ribbonPage2";
            // 
            // ribbonPageGroup2
            // 
            this.ribbonPageGroup2.Name = "ribbonPageGroup2";
            this.ribbonPageGroup2.Text = "ribbonPageGroup2";
            // 
            // ribbonPage1
            // 
            this.ribbonPage1.Groups.AddRange(new DevExpress.XtraBars.Ribbon.RibbonPageGroup[] {
            this.ribbonPageGroup1,
            this.ribbonPageGroup3,
            this.ribbonPageGroup4});
            this.ribbonPage1.Name = "ribbonPage1";
            this.ribbonPage1.Text = "ribbonPage1";
            // 
            // ribbonPageGroup1
            // 
            this.ribbonPageGroup1.ItemLinks.Add(this.btnLoadSTEPFile);
            this.ribbonPageGroup1.Name = "ribbonPageGroup1";
            this.ribbonPageGroup1.Text = "불러오기 도구";
            // 
            // btnLoadSTEPFile
            // 
            this.btnLoadSTEPFile.Caption = "STEP 파일 불러오기";
            this.btnLoadSTEPFile.Id = 1;
            this.btnLoadSTEPFile.ImageOptions.SvgImage = ((DevExpress.Utils.Svg.SvgImage)(resources.GetObject("btnLoadSTEPFile.ImageOptions.SvgImage")));
            this.btnLoadSTEPFile.Name = "btnLoadSTEPFile";
            this.btnLoadSTEPFile.ItemClick += new DevExpress.XtraBars.ItemClickEventHandler(this.btnLoadSTEPFile_ItemClick);
            // 
            // ribbonPageGroup3
            // 
            this.ribbonPageGroup3.ItemLinks.Add(this.btnShowShadingMode);
            this.ribbonPageGroup3.ItemLinks.Add(this.btnShowWireMode);
            this.ribbonPageGroup3.ItemLinks.Add(this.btnAmbientOcclusion);
            this.ribbonPageGroup3.ItemLinks.Add(this.barEditColor);
            this.ribbonPageGroup3.Name = "ribbonPageGroup3";
            this.ribbonPageGroup3.Text = "표현 도구";
            // 
            // btnShowShadingMode
            // 
            this.btnShowShadingMode.Caption = "쉐이딩 보기";
            this.btnShowShadingMode.Id = 3;
            this.btnShowShadingMode.ImageOptions.SvgImage = ((DevExpress.Utils.Svg.SvgImage)(resources.GetObject("btnShowShadingMode.ImageOptions.SvgImage")));
            this.btnShowShadingMode.Name = "btnShowShadingMode";
            this.btnShowShadingMode.ItemClick += new DevExpress.XtraBars.ItemClickEventHandler(this.btnShowShadingMode_ItemClick);
            // 
            // btnShowWireMode
            // 
            this.btnShowWireMode.Caption = "와이어 보기";
            this.btnShowWireMode.Id = 4;
            this.btnShowWireMode.ImageOptions.SvgImage = ((DevExpress.Utils.Svg.SvgImage)(resources.GetObject("btnShowWireMode.ImageOptions.SvgImage")));
            this.btnShowWireMode.Name = "btnShowWireMode";
            this.btnShowWireMode.ItemClick += new DevExpress.XtraBars.ItemClickEventHandler(this.btnShowWireMode_ItemClick);
            // 
            // btnAmbientOcclusion
            // 
            this.btnAmbientOcclusion.Caption = "엠비언트 오클루젼";
            this.btnAmbientOcclusion.Id = 5;
            this.btnAmbientOcclusion.ImageOptions.SvgImage = ((DevExpress.Utils.Svg.SvgImage)(resources.GetObject("btnAmbientOcclusion.ImageOptions.SvgImage")));
            this.btnAmbientOcclusion.Name = "btnAmbientOcclusion";
            this.btnAmbientOcclusion.ItemClick += new DevExpress.XtraBars.ItemClickEventHandler(this.btnAmbientOcclusion_ItemClick);
            // 
            // barEditColor
            // 
            this.barEditColor.Caption = "모델 색상 변경";
            this.barEditColor.Edit = this.repositoryItemColorPickEdit1;
            this.barEditColor.Id = 7;
            this.barEditColor.Name = "barEditColor";
            this.barEditColor.EditValueChanged += new System.EventHandler(this.barEditColor_EditValueChanged);
            // 
            // repositoryItemColorPickEdit1
            // 
            this.repositoryItemColorPickEdit1.AutoHeight = false;
            this.repositoryItemColorPickEdit1.AutomaticColor = System.Drawing.Color.Black;
            this.repositoryItemColorPickEdit1.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Combo)});
            this.repositoryItemColorPickEdit1.Name = "repositoryItemColorPickEdit1";
            // 
            // ribbonPageGroup4
            // 
            this.ribbonPageGroup4.ItemLinks.Add(this.btnAllSelect);
            this.ribbonPageGroup4.ItemLinks.Add(this.barButtonItem2);
            this.ribbonPageGroup4.Name = "ribbonPageGroup4";
            this.ribbonPageGroup4.Text = "선택";
            // 
            // btnAllSelect
            // 
            this.btnAllSelect.Caption = "전체 선택";
            this.btnAllSelect.Id = 8;
            this.btnAllSelect.ImageOptions.SvgImage = ((DevExpress.Utils.Svg.SvgImage)(resources.GetObject("btnAllSelect.ImageOptions.SvgImage")));
            this.btnAllSelect.Name = "btnAllSelect";
            this.btnAllSelect.ItemClick += new DevExpress.XtraBars.ItemClickEventHandler(this.btnAllSelect_ItemClick);
            // 
            // barButtonItem2
            // 
            this.barButtonItem2.Caption = "선택된 상태인지 확인";
            this.barButtonItem2.Id = 9;
            this.barButtonItem2.Name = "barButtonItem2";
            this.barButtonItem2.ItemClick += new DevExpress.XtraBars.ItemClickEventHandler(this.barButtonItem2_ItemClick);
            // 
            // ribbonControl1
            // 
            this.ribbonControl1.EmptyAreaImageOptions.ImagePadding = new System.Windows.Forms.Padding(35, 32, 35, 32);
            this.ribbonControl1.ExpandCollapseItem.Id = 0;
            this.ribbonControl1.Items.AddRange(new DevExpress.XtraBars.BarItem[] {
            this.ribbonControl1.ExpandCollapseItem,
            this.ribbonControl1.SearchEditItem,
            this.btnLoadSTEPFile,
            this.barButtonItem1,
            this.btnShowShadingMode,
            this.btnShowWireMode,
            this.btnAmbientOcclusion,
            this.barEditColor,
            this.btnAllSelect,
            this.barButtonItem2});
            this.ribbonControl1.Location = new System.Drawing.Point(0, 0);
            this.ribbonControl1.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.ribbonControl1.MaxItemId = 10;
            this.ribbonControl1.Name = "ribbonControl1";
            this.ribbonControl1.OptionsMenuMinWidth = 385;
            this.ribbonControl1.PageCategories.AddRange(new DevExpress.XtraBars.Ribbon.RibbonPageCategory[] {
            this.ribbonPageCategory1});
            this.ribbonControl1.Pages.AddRange(new DevExpress.XtraBars.Ribbon.RibbonPage[] {
            this.ribbonPage1});
            this.ribbonControl1.RepositoryItems.AddRange(new DevExpress.XtraEditors.Repository.RepositoryItem[] {
            this.repositoryItemColorPickEdit1});
            this.ribbonControl1.Size = new System.Drawing.Size(1073, 150);
            // 
            // barButtonItem1
            // 
            this.barButtonItem1.Caption = "음영 보기1";
            this.barButtonItem1.Id = 2;
            this.barButtonItem1.Name = "barButtonItem1";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 14F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1073, 750);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.ribbonControl1);
            this.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.Name = "Form1";
            this.Ribbon = this.ribbonControl1;
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemColorPickEdit1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.ribbonControl1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.Panel panel1;
        private DevExpress.XtraBars.Ribbon.RibbonPageCategory ribbonPageCategory1;
        private DevExpress.XtraBars.Ribbon.RibbonPage ribbonPage2;
        private DevExpress.XtraBars.Ribbon.RibbonPageGroup ribbonPageGroup2;
        private DevExpress.XtraBars.Ribbon.RibbonPage ribbonPage1;
        private DevExpress.XtraBars.Ribbon.RibbonPageGroup ribbonPageGroup1;
        private DevExpress.XtraBars.BarButtonItem btnLoadSTEPFile;
        private DevExpress.XtraBars.Ribbon.RibbonControl ribbonControl1;
        private DevExpress.XtraBars.Ribbon.RibbonPageGroup ribbonPageGroup3;
        private DevExpress.XtraBars.BarButtonItem barButtonItem1;
        private DevExpress.XtraBars.BarButtonItem btnShowShadingMode;
        private DevExpress.XtraBars.BarButtonItem btnShowWireMode;
        private DevExpress.XtraBars.BarButtonItem btnAmbientOcclusion;
        private DevExpress.XtraBars.Ribbon.RibbonPageGroup ribbonPageGroup4;
        private DevExpress.XtraBars.BarEditItem barEditColor;
        private DevExpress.XtraEditors.Repository.RepositoryItemColorPickEdit repositoryItemColorPickEdit1;
        private DevExpress.XtraBars.BarButtonItem btnAllSelect;
        private DevExpress.XtraBars.BarButtonItem barButtonItem2;
    }
}

