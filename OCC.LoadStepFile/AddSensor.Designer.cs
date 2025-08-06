namespace OCC.LoadStepFile
{
    partial class AddSensor
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
            this.teX = new DevExpress.XtraEditors.TextEdit();
            this.labelControl1 = new DevExpress.XtraEditors.LabelControl();
            this.teY = new DevExpress.XtraEditors.TextEdit();
            this.labelControl2 = new DevExpress.XtraEditors.LabelControl();
            this.teZ = new DevExpress.XtraEditors.TextEdit();
            this.labelControl3 = new DevExpress.XtraEditors.LabelControl();
            this.btnOK = new DevExpress.XtraEditors.SimpleButton();
            this.btnCancel = new DevExpress.XtraEditors.SimpleButton();
            this.teSize = new DevExpress.XtraEditors.TextEdit();
            this.labelControl4 = new DevExpress.XtraEditors.LabelControl();
            ((System.ComponentModel.ISupportInitialize)(this.teX.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.teY.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.teZ.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.teSize.Properties)).BeginInit();
            this.SuspendLayout();
            // 
            // teX
            // 
            this.teX.EditValue = "0";
            this.teX.Location = new System.Drawing.Point(30, 15);
            this.teX.Name = "teX";
            this.teX.Size = new System.Drawing.Size(50, 20);
            this.teX.TabIndex = 0;
            // 
            // labelControl1
            // 
            this.labelControl1.Location = new System.Drawing.Point(12, 18);
            this.labelControl1.Name = "labelControl1";
            this.labelControl1.Size = new System.Drawing.Size(7, 14);
            this.labelControl1.TabIndex = 1;
            this.labelControl1.Text = "X";
            // 
            // teY
            // 
            this.teY.EditValue = "0";
            this.teY.Location = new System.Drawing.Point(30, 41);
            this.teY.Name = "teY";
            this.teY.Size = new System.Drawing.Size(50, 20);
            this.teY.TabIndex = 2;
            // 
            // labelControl2
            // 
            this.labelControl2.Location = new System.Drawing.Point(12, 44);
            this.labelControl2.Name = "labelControl2";
            this.labelControl2.Size = new System.Drawing.Size(8, 14);
            this.labelControl2.TabIndex = 3;
            this.labelControl2.Text = "Y";
            // 
            // teZ
            // 
            this.teZ.EditValue = "0";
            this.teZ.Location = new System.Drawing.Point(30, 67);
            this.teZ.Name = "teZ";
            this.teZ.Size = new System.Drawing.Size(50, 20);
            this.teZ.TabIndex = 4;
            // 
            // labelControl3
            // 
            this.labelControl3.Location = new System.Drawing.Point(12, 70);
            this.labelControl3.Name = "labelControl3";
            this.labelControl3.Size = new System.Drawing.Size(7, 14);
            this.labelControl3.TabIndex = 5;
            this.labelControl3.Text = "Z";
            // 
            // btnOK
            // 
            this.btnOK.Location = new System.Drawing.Point(12, 115);
            this.btnOK.Name = "btnOK";
            this.btnOK.Size = new System.Drawing.Size(116, 35);
            this.btnOK.TabIndex = 6;
            this.btnOK.Text = "확인";
            this.btnOK.Click += new System.EventHandler(this.btnOK_Click);
            // 
            // btnCancel
            // 
            this.btnCancel.Location = new System.Drawing.Point(134, 115);
            this.btnCancel.Name = "btnCancel";
            this.btnCancel.Size = new System.Drawing.Size(86, 35);
            this.btnCancel.TabIndex = 7;
            this.btnCancel.Text = "취소";
            this.btnCancel.Click += new System.EventHandler(this.btnCancel_Click);
            // 
            // teSize
            // 
            this.teSize.EditValue = "10";
            this.teSize.Location = new System.Drawing.Point(153, 15);
            this.teSize.Name = "teSize";
            this.teSize.Size = new System.Drawing.Size(67, 20);
            this.teSize.TabIndex = 8;
            // 
            // labelControl4
            // 
            this.labelControl4.Location = new System.Drawing.Point(121, 18);
            this.labelControl4.Name = "labelControl4";
            this.labelControl4.Size = new System.Drawing.Size(21, 14);
            this.labelControl4.TabIndex = 9;
            this.labelControl4.Text = "Size";
            // 
            // AddSensor
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 14F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(232, 162);
            this.Controls.Add(this.labelControl4);
            this.Controls.Add(this.teSize);
            this.Controls.Add(this.btnCancel);
            this.Controls.Add(this.btnOK);
            this.Controls.Add(this.labelControl3);
            this.Controls.Add(this.teZ);
            this.Controls.Add(this.labelControl2);
            this.Controls.Add(this.teY);
            this.Controls.Add(this.labelControl1);
            this.Controls.Add(this.teX);
            this.Name = "AddSensor";
            this.Text = "센서 삽입";
            ((System.ComponentModel.ISupportInitialize)(this.teX.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.teY.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.teZ.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.teSize.Properties)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private DevExpress.XtraEditors.TextEdit teX;
        private DevExpress.XtraEditors.LabelControl labelControl1;
        private DevExpress.XtraEditors.TextEdit teY;
        private DevExpress.XtraEditors.LabelControl labelControl2;
        private DevExpress.XtraEditors.TextEdit teZ;
        private DevExpress.XtraEditors.LabelControl labelControl3;
        private DevExpress.XtraEditors.SimpleButton btnOK;
        private DevExpress.XtraEditors.SimpleButton btnCancel;
        private DevExpress.XtraEditors.TextEdit teSize;
        private DevExpress.XtraEditors.LabelControl labelControl4;
    }
}