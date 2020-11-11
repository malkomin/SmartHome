using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;
using System.Data;

namespace WindowsService1
{
    class ArduinoCommunication
    {
        Logger log;
        SqlHelper sql;
        DataTable data;
        public ArduinoCommunication(SqlHelper sql,Logger log)
        {
            this.log = log;
            this.sql = sql;
            data = new DataTable();
        }
        public void ListenPort()
        {
            while(true)
            {
                log.WriteToFile("Service running...");
                data = sql.getTable("SELECT * FROM SENSOR_DATA");
                foreach(DataRow row in data.Rows)
                {
                    foreach(DataColumn col in data.Columns) 
                    {
                        log.WriteToFile("ROW : "+  row[col.ColumnName]);
                    }
                }
                Thread.Sleep(10000);
            }
        }
        public void 
    }
}
