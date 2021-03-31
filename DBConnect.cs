using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using MySql.Data.MySqlClient;
using System.Windows.Forms;
using System.Threading.Tasks;

/// <summary>
/// Zeshan-----mySQL Database details, username is "seconduser" and password is "shsu"
/// Zeshan-----go to the link for database connection methods "https://www.codeproject.com/articles/43438/connect-c-to-mysql"
/// </summary>

namespace Financial_Portfolio_Manager
{
    class DBConnect
    {
        private MySqlConnection connection;
        private string server;
        private string database;
        private string uid;
        private string password;

        //Constructor
        public DBConnect()
        {
            Initialize();
        }

        //Initialize values
        private void Initialize()
        {
            server = "localhost";
            database = "FPM";
            uid = "seconduser";
            password = "shsu";
            string connectionString;
            connectionString = "SERVER=" + server + ";" + "DATABASE=" +
            database + ";" + "UID=" + uid + ";" + "PASSWORD=" + password + ";";

            connection = new MySqlConnection(connectionString);
        }

        //open connection to database
        private bool OpenConnection()
        {
            try
            {
                connection.Open();
                return true;
            }
            catch (MySqlException ex)
            {
                //When handling errors, you can your application's response based 
                //on the error number.
                //The two most common error numbers when connecting are as follows:
                //0: Cannot connect to server.
                //1045: Invalid user name and/or password.
                switch (ex.Number)
                {
                    case 0:
                        MessageBox.Show("Cannot connect to server.  Contact administrator");
                        break;

                    case 1045:
                        MessageBox.Show("Invalid username/password, please try again");
                        break;
                }
                return false;
            }
        }

        //Close connection
        private bool CloseConnection()
        {
            try
            {
                connection.Close();
                return true;
            }
            catch (MySqlException ex)
            {
                MessageBox.Show(ex.Message);
                return false;
            }
        }

        //Insert statement
        public void Insert(string firstname, string lastname, string username, string password, int riskprofile)
        {
            string RiskProfile = riskprofile.ToString();
            string values ="\""+firstname+  "\",\""+lastname+"\",\""+username+"\",\""+password+"\",\""+ RiskProfile + "\"";
            string query = "INSERT INTO users (firstname, lastname, username, password, riskProfile) VALUES("+values+")";
            string query1 = "CREATE TABLE " + username + " (StockTicker VARCHAR(30), Quantity VARCHAR(30), DateOfPurchase DATE, PurchasePrice INT, Value INT)";

            //open connection
            if (this.OpenConnection() == true)
            {
                //create command and assign the query and connection from the constructor
                MySqlCommand cmd = new MySqlCommand(query, connection);
                MySqlCommand cmd1 = new MySqlCommand(query1, connection);
                //Execute command
                cmd.ExecuteNonQuery();
                cmd1.ExecuteNonQuery();
                //close connection
                this.CloseConnection();
            }
        }

        /*
        Zeshan-----may have to create all these methods depending on what operations we want

        //Update statement
        public void Update()
        {
        }

        //Delete statement
        public void Delete()
        {
        }

        //Select statement
        public List<string>[] Select()
        {
        }

        //Count statement
        public int Count()
        {
        }

        //Backup
        public void Backup()
        {
        }

        //Restore
        public void Restore()
        {
        }
        
         */
    }
}
