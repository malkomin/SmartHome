using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Data.SqlClient;
using System.Data;

namespace WindowsService1
{
 
    class SqlHelper
    {
        SqlConnection connection;
        SqlDataAdapter adapter;
        bool isOpen = false;
        string conn_str = "Data Source=MALIKOODLE\\SQLSERVER;Initial Catalog=Smart_Home;Persist Security Info=True;User ID=sa;Password=1";
        Dictionary<string, object> columns;
        Logger log;
        string parameter;
        string columnnames = "";
        string parameters = "";
        public SqlHelper(Logger log)
        {
            this.log = log;
            connection = new SqlConnection(conn_str);
            columns = new Dictionary<string, object>();
        }

        public void Insert(DataTable data)
        {
            int i = 0;
            string insert_str;
            if (data != null)
            {
                foreach (DataRow row in data.Rows)
                {
                    foreach (DataColumn col in data.Columns)
                    {
                        columns.Add(col.ColumnName, row.ItemArray[i]);
                        i++;
                    }
                    foreach (KeyValuePair<string, object> col in columns)
                    {
                        parameter = "@" + col.Key;
                        if (parameters == "")
                        {
                            parameters = parameters + parameter;
                        }
                        else
                        {
                            parameters = parameters + "," + parameter;
                        }
                    }
                    columnnames = parameters.Replace("@", "");
                    insert_str = "INSERT INTO " + data.TableName + " (" + columnnames + ")" + " VALUES" + "(" + parameters + ")";
                    using (SqlCommand command = new SqlCommand(insert_str, connection))
                    {
                        if (isOpen == false)
                        {
                            try
                            {
                                connection.Open();
                            }
                            catch (Exception e)
                            {
                                log.WriteToFile(e.Message);
                            }
                            isOpen = true;
                        }
                        foreach (KeyValuePair<string, object> col in columns)
                        {
                            try
                            {
                                command.Parameters.AddWithValue("@" + col.Key, col.Value);
                            }
                            catch (Exception e)
                            {
                                log.WriteToFile(e.Message);
                            }
                        }
                        try
                        {
                            command.ExecuteNonQuery();
                        }
                        catch (SqlException ex)
                        {
                            if (ex.Number == 2627)
                            {

                            }
                            else
                            {
                                log.WriteToFile(ex.Message);
                            }
                        }
                    }
                    i = 0;
                    columns.Clear();
                    parameters = "";
                }
                log.WriteToFile("Insert işlemi tamamlandı.");
                connection.Close();
            }
        }
        public DataTable SelectFromTable(string tablename,string[] condition)
        {
            DataTable table = new DataTable();
            /*
             *TODO
             * - Create parametric select query
             */
            return table;

        }

        public DataTable getTable(string query)
        {

            DataTable data = new DataTable();
            log.WriteToFile("SQL bağlantısı açılıyor");
            log.WriteToFile("SQL Sorgu : " + query);
            using (SqlCommand cmd = new SqlCommand(query, connection))
            {
                if (!isOpen)
                {
                    connection.Open();
                    isOpen = true;
                }
                adapter = new SqlDataAdapter(query, connection);
                data.Clear();
                adapter.Fill(data);
                log.WriteToFile("SQL data dolduruldu.");
                connection.Close();
                log.WriteToFile("SQL bağlantısı kapandı");
                isOpen = false;
            }
            return data;
        }
        public void InsertToTable(DataTable data)
        {
            using (connection)
            {
                log.WriteToFile("SQL bağlantısı açılıyor.");
                if (!isOpen)
                {
                    connection.Open();
                    isOpen = true;
                }
                log.WriteToFile(data.TableName + " tablosu yazılıyor.");
                using (SqlBulkCopy bulk = new SqlBulkCopy(connection))
                {
                    bulk.DestinationTableName = data.TableName;
                    try
                    {
                        bulk.WriteToServer(data);
                        log.WriteToFile(data.TableName + " tablosu yazıldı.");
                    }
                    catch (Exception e)
                    {
                        Console.WriteLine(e.Message);
                    }
                }
                connection.Close();
                isOpen = false;
                log.WriteToFile("SQL bağlantısı kapatılıyor.");
            }

        }
        private void DeleteFromTable(DataTable data)
        {
            try
            {
                using (connection)
                {
                    log.WriteToFile("SQL bağlantısı açılıyor.");
                    connection.Open();
                    string delete = "DELETE FROM " + data.TableName;
                    using (SqlCommand com = new SqlCommand(delete, connection))
                    {
                        com.ExecuteNonQuery();
                    }
                    connection.Close();
                    log.WriteToFile("SQL bağlantısı kapatılıyor.");
                }
            }
            catch (Exception e)
            {
                log.WriteToFile(e.Message);
            }


        }

    }
}

