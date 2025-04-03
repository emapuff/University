using System.Data;
using Microsoft.Data.SqlClient; 

namespace WinFormsApp2;

public partial class Form1 : Form
{
    private DataSet _ds = new DataSet();
    private SqlDataAdapter parentAdapter = new SqlDataAdapter();
    SqlDataAdapter childAdapter = new SqlDataAdapter();
    BindingSource bsParent = new BindingSource();
    BindingSource bsChild = new BindingSource();
    string connectionString = @"Server=EMA\SQLEXPRESS;Database=AgentieSpatiala;Integrated Security=true;
                            TrustServerCertificate=True;";
    public Form1()
    {
        InitializeComponent();
        this.Load += new System.EventHandler(this.Form1_Load!);
    }

    private void Form1_Load(object sender, EventArgs e)
    {
        try
        {
            using (SqlConnection conn = new SqlConnection(connectionString))
            {
                conn.Open();
                parentAdapter = new SqlDataAdapter("SELECT * FROM Cheltuieli;", conn);
                childAdapter = new SqlDataAdapter("SELECT * FROM NaveSpatiale;", conn);
                parentAdapter.Fill(_ds, "Cheltuieli");
                childAdapter.Fill(_ds, "NaveSpatiale");
                DataColumn pkColumn = _ds.Tables["Cheltuieli"].Columns["id_cheltuiala"];
                DataColumn fkColumn = _ds.Tables["NaveSpatiale"].Columns["id_cheltuiala"];
                DataRelation relation = new DataRelation("FK_Cheltuieli", pkColumn, fkColumn, true);
                _ds.Relations.Add(relation);
                bsParent.DataSource = _ds.Tables["Cheltuieli"];
                dataGridViewParent.DataSource = bsParent;

                bsChild.DataSource = bsParent;
                bsChild.DataMember = "FK_Cheltuieli";
                dataGridViewChild.DataSource = bsChild;
            }
        }
        catch (Exception ex)
        {
            MessageBox.Show(ex.Message);
        }
    }

    private void reloadButton_Click()
    {
        using (SqlConnection conn = new SqlConnection(connectionString))
        {
            conn.Open();
            childAdapter = new SqlDataAdapter("SELECT * FROM NaveSpatiale;", conn);
            _ds.Tables["NaveSpatiale"]?.Clear();
            childAdapter.Fill(_ds, "NaveSpatiale");
        }
    }

    private void insertButton_Click(object sender, EventArgs e)
    {
        if(textBoxTip.Text.Length >0 &&
           textBoxDisp.Text.Length> 0 &&
           textBoxNume.Text.Length> 0)
            try
            {
                
                var row = dataGridViewParent.CurrentCell.RowIndex;
                var lenght = dataGridViewChild.ColumnCount;
                var id_cheltuiala = (int) dataGridViewParent.Rows[row].Cells[0].Value;
                using (SqlConnection conn = new SqlConnection(connectionString))
                {
                    conn.Open();
                    var command = new SqlCommand("INSERT INTO NaveSpatiale (nume, tip, disponibilitate, id_cheltuiala) VALUES (@nume, @tip, @disponibilitate, @id_cheltuiala)", conn);
                    command.Parameters.AddWithValue("@nume", textBoxNume.Text);
                    command.Parameters.AddWithValue("@tip", textBoxTip.Text);
                    command.Parameters.AddWithValue("@disponibilitate", textBoxDisp.Text);
                    command.Parameters.AddWithValue("@id_cheltuiala", id_cheltuiala);
                    command.ExecuteNonQuery();
                    MessageBox.Show("Insert successful");
                    textBoxTip.Clear();
                    textBoxDisp.Clear();
                    textBoxNume.Clear();
                    reloadButton_Click();
                }
            }
            catch (Exception exception)
            {
                MessageBox.Show(exception.Message);
            }
        else 
            MessageBox.Show("Completati toate casutele");
    }

    private void deleteButton_Click(object sender, EventArgs e)
    {
        if (dataGridViewChild.CurrentRow != null)
        {
            var row = dataGridViewChild.CurrentRow.Index;
            var length = dataGridViewChild.ColumnCount;
            var id_nava = (int)dataGridViewChild.Rows[row].Cells[0].Value;
            try
            {
                using (var sqlConnection = new SqlConnection(connectionString))
                {
                    sqlConnection.Open();
                    var command = new SqlCommand("delete from NaveSpatiale where id_nava=@id", sqlConnection);
                    command.Parameters.AddWithValue("@id", id_nava);
                    command.ExecuteNonQuery();
                    reloadButton_Click();
                    MessageBox.Show("Delete successful");
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Nu putem sterge nava, echipajul o foloseste!");
            }
        }
        else
        {
            MessageBox.Show("Select row first");
        }
    }

    private void back_button_Click(object sender, EventArgs e)
    {
        try
        {
            using (var sqlConnection = new SqlConnection(connectionString))
            {
                sqlConnection.Open();
                childAdapter = new SqlDataAdapter("SELECT * FROM NaveSpatiale;", sqlConnection);
                _ds.Tables["NaveSpatiale"]?.Clear();
                childAdapter.Fill(_ds, "NaveSpatiale");
            }
        }
        catch (Exception exception)
        {
            MessageBox.Show(exception.Message);
        }
        
    }
    
}