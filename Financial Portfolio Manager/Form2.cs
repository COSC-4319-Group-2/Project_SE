using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Financial_Portfolio_Manager
{
    public partial class Form2 : Form
    {
        public Form2()
        {
            InitializeComponent();
        }

        
        

        private void Form2_Load(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            List<string>[] PF = Form1.Portfolio;

            dataGridView1.Columns.Add("StockTicker", "Stock_Ticker");
            foreach (string x in PF[0])
            {
                dataGridView1.Rows.Add(x);

            }

            dataGridView2.Columns.Add("DateOfPurchase", "Date");
            foreach (string x in PF[2])
            {
                dataGridView2.Rows.Add(x);

            }

            double net_val = 0;

            dataGridView3.Columns.Add("Value", "Value");
            foreach (string x in PF[4])
            {
                dataGridView3.Rows.Add(x);
                net_val += Double.Parse(x);
            }


            label1.Text = net_val.ToString();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            var form = new Form3();
            form.Show();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            var form = new Form3();
            form.Show();
        }

        private void tableLayoutPanel1_Paint(object sender, PaintEventArgs e)
        {

        }

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }

        private void dataGridView1_CellContentClick_1(object sender, DataGridViewCellEventArgs e)
        {

        }

        private void dataGridView2_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }

        private void dataGridView3_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void dataGridView4_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }

        private void label1_Click_1(object sender, EventArgs e)
        {
            
        }
    }
}
