namespace WinFormsApp2;

partial class Form1
{
    /// <summary>
    ///  Required designer variable.
    /// </summary>
    private System.ComponentModel.IContainer components = null;

    /// <summary>
    ///  Clean up any resources being used.
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
        label1 = new System.Windows.Forms.Label();
        label2 = new System.Windows.Forms.Label();
        dataGridViewParent = new System.Windows.Forms.DataGridView();
        dataGridViewChild = new System.Windows.Forms.DataGridView();
        back = new System.Windows.Forms.Button();
        insert = new System.Windows.Forms.Button();
        delete = new System.Windows.Forms.Button();
        textBoxNume = new System.Windows.Forms.TextBox();
        textBoxTip = new System.Windows.Forms.TextBox();
        textBoxDisp = new System.Windows.Forms.TextBox();
        nume = new System.Windows.Forms.Label();
        tip = new System.Windows.Forms.Label();
        disponibilitate = new System.Windows.Forms.Label();
        button1 = new System.Windows.Forms.Button();
        ((System.ComponentModel.ISupportInitialize)dataGridViewParent).BeginInit();
        ((System.ComponentModel.ISupportInitialize)dataGridViewChild).BeginInit();
        SuspendLayout();
        // 
        // label1
        // 
        label1.Font = new System.Drawing.Font("Segoe UI", 14F);
        label1.Location = new System.Drawing.Point(170, 222);
        label1.Name = "label1";
        label1.Size = new System.Drawing.Size(194, 28);
        label1.TabIndex = 3;
        label1.Text = "Cheltuieli";
        label1.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
        // 
        // label2
        // 
        label2.Font = new System.Drawing.Font("Segoe UI", 14F);
        label2.Location = new System.Drawing.Point(737, 222);
        label2.Name = "label2";
        label2.Size = new System.Drawing.Size(207, 41);
        label2.TabIndex = 4;
        label2.Text = "Nave Spatiale";
        label2.TextAlign = System.Drawing.ContentAlignment.TopCenter;
        // 
        // dataGridViewParent
        // 
        dataGridViewParent.BackgroundColor = System.Drawing.Color.FromArgb(((int)((byte)192)), ((int)((byte)192)), ((int)((byte)255)));
        dataGridViewParent.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
        dataGridViewParent.Location = new System.Drawing.Point(33, 278);
        dataGridViewParent.Name = "dataGridViewParent";
        dataGridViewParent.RowHeadersWidth = 51;
        dataGridViewParent.Size = new System.Drawing.Size(479, 238);
        dataGridViewParent.TabIndex = 5;
        dataGridViewParent.Text = "dataGridView1";
        // 
        // dataGridViewChild
        // 
        dataGridViewChild.BackgroundColor = System.Drawing.Color.FromArgb(((int)((byte)192)), ((int)((byte)192)), ((int)((byte)255)));
        dataGridViewChild.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
        dataGridViewChild.Location = new System.Drawing.Point(592, 279);
        dataGridViewChild.Name = "dataGridViewChild";
        dataGridViewChild.RowHeadersWidth = 51;
        dataGridViewChild.Size = new System.Drawing.Size(492, 237);
        dataGridViewChild.TabIndex = 6;
        dataGridViewChild.Text = "dataGridView1";
        // 
        // back
        // 
        back.BackColor = System.Drawing.Color.FromArgb(((int)((byte)128)), ((int)((byte)128)), ((int)((byte)255)));
        back.Location = new System.Drawing.Point(70, 25);
        back.Name = "back";
        back.Size = new System.Drawing.Size(131, 37);
        back.TabIndex = 7;
        back.Text = "back";
        back.UseVisualStyleBackColor = false;
        back.Click += back_button_Click;
        // 
        // insert
        // 
        insert.BackColor = System.Drawing.Color.FromArgb(((int)((byte)128)), ((int)((byte)128)), ((int)((byte)255)));
        insert.Location = new System.Drawing.Point(70, 101);
        insert.Name = "insert";
        insert.Size = new System.Drawing.Size(131, 37);
        insert.TabIndex = 8;
        insert.Text = "insert";
        insert.UseCompatibleTextRendering = true;
        insert.UseVisualStyleBackColor = false;
        insert.Click += insertButton_Click;
        // 
        // delete
        // 
        delete.BackColor = System.Drawing.Color.FromArgb(((int)((byte)128)), ((int)((byte)128)), ((int)((byte)255)));
        delete.Location = new System.Drawing.Point(70, 172);
        delete.Name = "delete";
        delete.Size = new System.Drawing.Size(131, 37);
        delete.TabIndex = 9;
        delete.Text = "delete";
        delete.UseVisualStyleBackColor = false;
        delete.Click += deleteButton_Click;
        // 
        // textBoxNume
        // 
        textBoxNume.Location = new System.Drawing.Point(462, 25);
        textBoxNume.Name = "textBoxNume";
        textBoxNume.Size = new System.Drawing.Size(220, 27);
        textBoxNume.TabIndex = 10;
        // 
        // textBoxTip
        // 
        textBoxTip.Location = new System.Drawing.Point(465, 98);
        textBoxTip.Name = "textBoxTip";
        textBoxTip.Size = new System.Drawing.Size(215, 27);
        textBoxTip.TabIndex = 11;
        // 
        // textBoxDisp
        // 
        textBoxDisp.Location = new System.Drawing.Point(465, 172);
        textBoxDisp.Name = "textBoxDisp";
        textBoxDisp.Size = new System.Drawing.Size(217, 27);
        textBoxDisp.TabIndex = 12;
        // 
        // nume
        // 
        nume.Location = new System.Drawing.Point(405, 25);
        nume.Name = "nume";
        nume.Size = new System.Drawing.Size(51, 26);
        nume.TabIndex = 13;
        nume.Text = "Nume";
        // 
        // tip
        // 
        tip.Location = new System.Drawing.Point(420, 98);
        tip.Name = "tip";
        tip.Size = new System.Drawing.Size(39, 23);
        tip.TabIndex = 14;
        tip.Text = "Tip";
        // 
        // disponibilitate
        // 
        disponibilitate.Location = new System.Drawing.Point(354, 172);
        disponibilitate.Name = "disponibilitate";
        disponibilitate.Size = new System.Drawing.Size(105, 21);
        disponibilitate.TabIndex = 15;
        disponibilitate.Text = "disponibilitate";
        // 
        // button1
        // 
        button1.Location = new System.Drawing.Point(259, 99);
        button1.Name = "button1";
        button1.Size = new System.Drawing.Size(104, 38);
        button1.TabIndex = 16;
        button1.Text = "button1";
        button1.UseVisualStyleBackColor = true;
        // 
        // Form1
        // 
        AutoScaleDimensions = new System.Drawing.SizeF(8F, 20F);
        AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
        BackColor = System.Drawing.SystemColors.Info;
        ClientSize = new System.Drawing.Size(1095, 546);
        Controls.Add(button1);
        Controls.Add(disponibilitate);
        Controls.Add(tip);
        Controls.Add(nume);
        Controls.Add(textBoxDisp);
        Controls.Add(textBoxTip);
        Controls.Add(textBoxNume);
        Controls.Add(delete);
        Controls.Add(insert);
        Controls.Add(back);
        Controls.Add(dataGridViewChild);
        Controls.Add(dataGridViewParent);
        Controls.Add(label2);
        Controls.Add(label1);
        Text = "Cheltuieli Nave Spatiale";
        ((System.ComponentModel.ISupportInitialize)dataGridViewParent).EndInit();
        ((System.ComponentModel.ISupportInitialize)dataGridViewChild).EndInit();
        ResumeLayout(false);
        PerformLayout();
    }

    private System.Windows.Forms.Button button1;

    private System.Windows.Forms.TextBox textBoxTip;
    private System.Windows.Forms.TextBox textBoxDisp;
    private System.Windows.Forms.Label nume;
    private System.Windows.Forms.Label tip;
    private System.Windows.Forms.Label disponibilitate;

    private System.Windows.Forms.TextBox textBoxNume;

    private System.Windows.Forms.Button back;
    private System.Windows.Forms.Button insert;
    private System.Windows.Forms.Button delete;

    private System.Windows.Forms.DataGridView dataGridViewParent;
    private System.Windows.Forms.DataGridView dataGridViewChild;

    private System.Windows.Forms.Label label1;
    private System.Windows.Forms.Label label2;

    #endregion
}