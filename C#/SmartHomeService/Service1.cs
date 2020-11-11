using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Linq;
using System.ServiceProcess;
using System.Text;
using System.Threading.Tasks;
using System.Threading;
namespace WindowsService1
{
    public partial class Service1 : ServiceBase
    {
        BackgroundWorker worker;
        ArduinoCommunication communication;
        Logger log;
        SqlHelper sql;
        public Service1()
        {
            log = new Logger();
            sql = new SqlHelper(log);
            communication = new ArduinoCommunication(sql, log);
            worker = new BackgroundWorker();
            worker.DoWork += Worker_DoWork;
            worker.RunWorkerCompleted += Worker_RunWorkerCompleted;
            InitializeComponent();
        }

        private void Worker_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            this.Stop();
        }

        private void Worker_DoWork(object sender, DoWorkEventArgs e)
        {
            DoWork();
        }

        protected override void OnStart(string[] args)
        {
            log.WriteToFile("Service started!");
            worker.RunWorkerAsync();
            base.OnStart(args);
        }
        private void DoWork()
        {
            communication.ListenPort();
        }
        protected override void OnStop()
        {
            log.WriteToFile("Service stopped!");
            base.OnStop();
        }
    }
}
