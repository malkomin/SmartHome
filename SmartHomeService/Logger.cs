using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace WindowsService1
{
    class Logger
    {
        string path = AppDomain.CurrentDomain.BaseDirectory + "\\Logs";
        string filepath = AppDomain.CurrentDomain.BaseDirectory + "\\Logs\\ServiceLog_" + DateTime.Now.Date.ToShortDateString().Replace('/', '_') + ".txt";
        string cursor_path = AppDomain.CurrentDomain.BaseDirectory + "\\Logs\\cursors.txt";
        public Dictionary<string, string> cursors = new Dictionary<string, string>();

        public void WriteToFile(string Message, string strfilepath = "")
        {
            if (strfilepath == "")
            {
                strfilepath = filepath;
            }
            else
            {
                strfilepath = AppDomain.CurrentDomain.BaseDirectory + "\\Logs\\" + strfilepath + "_" + DateTime.Now.Date.ToShortDateString().Replace('/', '_') + ".txt";
            }
            if (!Directory.Exists(path))
            {
                Directory.CreateDirectory(path);
            }
            if (!File.Exists(strfilepath))
            {
                // Create a file to write to.   
                using (StreamWriter sw = File.CreateText(strfilepath))
                {
                    sw.WriteLine(DateTime.Now + " : " + Message);
                }
            }
            else
            {
                using (StreamWriter sw = File.AppendText(strfilepath))
                {
                    sw.WriteLine(DateTime.Now + " : " + Message);
                }
            }
        }
        public void SaveCursor(string cursor_name, string cursor_value)
        {
            if (!Directory.Exists(path))
            {
                Directory.CreateDirectory(path);
            }
            if (!File.Exists(cursor_path))
            {
                // Create a file to write to.   
                using (StreamWriter sw = File.CreateText(cursor_path))
                {
                    try
                    {
                        cursors.Add(cursor_name, cursor_value);
                        sw.WriteLine(cursor_name + ";" + cursor_value);
                    }
                    catch (Exception e)
                    {
                        WriteToFile(e.Message);
                    }
                }
            }
            else
            {
                try
                {
                    using (FileStream fs = new FileStream(cursor_path, FileMode.OpenOrCreate))
                    {
                        if (cursors.ContainsKey(cursor_name))
                        {
                            cursors[cursor_name] = cursor_value;
                        }
                        else cursors.Add(cursor_name, cursor_value);
                        fs.SetLength(0);
                        using (StreamWriter sw = new StreamWriter(fs))
                        {
                            foreach (string cursor in cursors.Keys)
                            {
                                sw.WriteLine(cursor + ";" + Convert.ToString(cursors[cursor]));
                            }
                        }
                    }
                }
                catch (Exception e)
                {
                    WriteToFile(e.Message + " cursors icinde");
                }

            }
        }

    }
}
