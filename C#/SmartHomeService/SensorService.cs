using System;
using System.Collections.Generic;
using System.Data;

namespace SmartHomeService
{
    public class SensorService
    {
        Logger log;
        SqlHelper sql;
        public SensorService(Logger log)
        {
            sql = new SqlHelper(log);
            this.log = log;
        }
        public string processData(String msg)
        {
            String output = "";
            String[] split = msg.Split('.');
            String request = split[0];
            if (request.Equals("GET"))
            {
                String tableName = split[1];
                output = ProcessSQL(tableName);
            }
            else if (request.Equals("SET"))
            {
                String tableName = split[1].ToUpper();
                String type = split[2].ToUpper();
                String value = split[3].Trim();
                output = ProcessSQL(tableName,type, value);
            }
            return output;
        }
        private string ProcessSQL(string tableName, string type = "" , string value = "")
        {
            string output ="";
            DataTable tbl = new DataTable();
            if (value == "")
            {
                string query = "SELECT TYPE, VALUE FROM " + tableName.ToUpper();
                tbl = sql.Select(query,false);
                tbl.TableName = tableName.ToUpper();
                foreach (DataRow row in tbl.Rows)
                {
                    type = Convert.ToString(row["TYPE"]);
                    value = Convert.ToString(row["VALUE"]);
                    if (output == "")
                    {
                        output = type + "=" + value;
                    }
                    else
                    {
                        output = output + ";" + type + "=" + value;
                    }
                }
            }
            else
            {
                try
                {
                    DataRow row = tbl.NewRow();
                    DataColumn typeCol = new DataColumn("TYPE");
                    DataColumn valueCol = new DataColumn("VALUE");
                    tbl.Columns.Add(typeCol);
                    tbl.Columns.Add(valueCol);
                    row["TYPE"] = type;
                    row["VALUE"] = value;
                    tbl.Rows.Add(row);
                    tbl.TableName = tableName.ToUpper();
                    sql.Update(tbl, "TYPE", false);
                    output = "OK";
                }
                catch(Exception e)
                {
                    log.WriteToFile("ERROR : " + e.Message);
                }
            }
            return output;
        }

    }
}
