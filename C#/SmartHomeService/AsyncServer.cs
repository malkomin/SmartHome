using System;
using System.Collections.Generic;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
namespace SmartHomeService
{
    public class AsyncServer
    {
        private TcpListener client;
        Logger log;
        SensorService service;
        public AsyncServer(Logger log, SensorService service)
        {
            this.service = service;
            this.log = log;
            client = new TcpListener(IPAddress.Any, 13000);

        }
        public void Start()
        {
            client.Start();
            log.WriteToFile("Waiting for clients...");
            while (true)
            {
                while (client.Pending())
                {
                    ConnectionThread newconnection = new ConnectionThread(this.client, this.log, this.service);
                    Thread newthread = new Thread(new ThreadStart(newconnection.HandleConnection));
                    newthread.Start();
                }
            }
        }
        class ConnectionThread
        {
            public TcpListener threadListner;
            Logger log;
            private static int connections = 0;
            SensorService service;
            public ConnectionThread(TcpListener threadListner, Logger log, SensorService service)
            {
                this.service = service;
                this.threadListner = threadListner;
                this.log = log;
            }
            public void HandleConnection()
            {
                int recv;
                byte[] data = new byte[1024];
                string dataStr = "";
                TcpClient client = threadListner.AcceptTcpClient();
                NetworkStream ns = client.GetStream();
                string output;
                connections++;
                log.WriteToFile("New client accepted: " + connections + " active connections");
                string welcome = "Welcome to server";
                data = Encoding.ASCII.GetBytes(welcome);
                ns.Write(data, 0, data.Length);
                while (true)
                {
                    data = new byte[1024];
                    recv = ns.Read(data, 0, data.Length);
                    if (recv == 0) break;
                    dataStr= Encoding.ASCII.GetString(data);
                    output = service.processData(dataStr);
                    data = Encoding.ASCII.GetBytes(output);
                    ns.Write(data, 0, data.Length);
                }
                ns.Close();
                client.Close();
                connections--;
                log.WriteToFile("Client disconnected: " + connections + " active connections");
            }
        }
    }
}
