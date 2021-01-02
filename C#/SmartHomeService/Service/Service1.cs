using System.ComponentModel;
using System.Net;
using System.ServiceProcess;
using System.Text;
using System.Threading.Tasks;
using System.Threading;
namespace SmartHomeService
{
    public partial class Service1 : ServiceBase
    {
        BackgroundWorker worker;
        Logger log;
        AsyncServer server;
        SensorService service;
        public Service1()
        {
            InitializeComponent();
            log = new Logger();
            service = new SensorService(log);
            server = new AsyncServer(log, service);
            worker = new BackgroundWorker();
            worker.DoWork += Worker_DoWork;
            worker.RunWorkerCompleted += Worker_RunWorkerCompleted;
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
            server.Start();
        }
        protected override void OnStop()
        {

            log.WriteToFile("Service stopped!");
            base.OnStop();
        }
    }
}
