using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

/// <summary>
/// Zeshan-----event handler for Button 2 ie button2_Click method creates an instance of DBConnect class to use its insert method.
/// Zeshan-----Insert method takes the input from Form1's sign up section as parameters and use them to populate the users table.
/// Zeshan-----Insert method also creates a new table by the name of username to store their portfolio.
/// </summary>

namespace Financial_Portfolio_Manager
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        string Fname, Lname, Uname, Pword;
        int Rprof;

        private void button1_Click(object sender, EventArgs e)
        {
            var form = new Form2();
            form.Show();
        }

        private void label3_Click(object sender, EventArgs e)
        {

        }

        private void label5_Click(object sender, EventArgs e)
        {

        }

        private void label6_Click(object sender, EventArgs e)
        {

        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            Rprof = comboBox1.SelectedIndex;
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            
        }

        private void textBox6_TextChanged(object sender, EventArgs e)
        {
            Lname = textBox6.Text;
        }

        private void textBox4_TextChanged(object sender, EventArgs e)
        {
            Uname = textBox4.Text;
        }

        private void textBox5_TextChanged(object sender, EventArgs e)
        {
            Pword = textBox5.Text;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            var form = new Form2();
            form.Show();

            DBConnect dbEvent = new DBConnect();
            dbEvent.Insert(Fname,Lname,Uname,Pword,Rprof);
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void textBox3_TextChanged(object sender, EventArgs e)
        {
            Fname = textBox3.Text;

        }
    }
}
