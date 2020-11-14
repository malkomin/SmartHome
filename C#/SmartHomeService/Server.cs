using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace WindowsService1
{
    public class Server
    {
        Logger log;
        IPAddress ip;
        int port;
        TcpListener listener;
        public Server(IPAddress ip, int port,Logger log)
        {
            this.log = log;
            this.ip = ip;
            this.port = port;
            listener = new TcpListener(ip, port);

        }
        public void RunServer()
        {
            TcpListener server = null;
            try
            {
                // Set the TcpListener on port 13000.

                // TcpListener server = new TcpListener(port);


                // Start listening for client requests.
                listener.Start();

                // Buffer for reading data
                Byte[] bytes = new Byte[256];
                String data = null;
                int i;
                // Enter the listening loop.
                while (true)
                {
                    log.WriteToFile("Waiting for Arduino Connection...");

                    // Perform a blocking call to accept requests.
                    // You could also use server.AcceptSocket() here.
                    TcpClient client = server.AcceptTcpClient();
                    log.WriteToFile("Arduino Connected!");
                    data = null;
                    // Get a stream object for reading and writing
                    NetworkStream stream = client.GetStream();
                    // Loop to receive all the data sent by the client.
                    while ((i = stream.Read(bytes, 0, bytes.Length)) != 0)
                    {
                        // Translate data bytes to a ASCII string.
                        data = System.Text.Encoding.ASCII.GetString(bytes, 0, i);
                        log.WriteToFile("Received: " + data);

                        // Process the data sent by the client.
                        data = data.ToUpper();

                        byte[] msg = System.Text.Encoding.ASCII.GetBytes(data);

                        // Send back a response.
                        stream.Write(msg, 0, msg.Length);
                        log.WriteToFile("Sent: "+ data);
                    }

                    // Shutdown and end connection
                    client.Close();
                }
            }
            catch (SocketException e)
            {
                log.WriteToFile("SocketException:"+ e);
            }
            finally
            {
                // Stop listening for new clients.
                server.Stop();
                log.WriteToFile("Server Stopped.");
            }
            


        }
    }
}
