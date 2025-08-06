using DevExpress.XtraEditors;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace OCC.LoadStepFile
{
    public partial class AddSensor : DevExpress.XtraEditors.XtraForm
    {
        public double X { get; private set; }
        public double Y { get; private set; }
        public double Z { get; private set; }
        public double Size { get; private set; }

        public AddSensor()
        {
            InitializeComponent();
        }

        private void btnOK_Click(object sender, EventArgs e)
        {
            // #01. 입력 데이터 가져오기
            double x = 0.0, y = 0.0, z = 0.0, size = 10.0;
            double.TryParse(teX.Text, out x);
            double.TryParse(teY.Text, out y);
            double.TryParse(teZ.Text, out z);
            double.TryParse(teSize.Text, out size);

            X = x;
            Y = y;
            Z = z;
            Size = size;

            this.DialogResult = DialogResult.OK;
            Close();
        }

        private void btnCancel_Click(object sender, EventArgs e)
        {
            this.DialogResult = DialogResult.Cancel;
            Close();
        }
    }
}