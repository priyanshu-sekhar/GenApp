#include <glib.h>
#include <iostream>
#include <stdint.h>
#include <sys/time.h>
#include <fstream>
#include <stdlib.h>
#include <zmq.hpp>

using namespace std;

class msg-udpserver{
    public:
        void readConfigFile();
        void initSocket();
        void connectToHost();
        void retransmit();
    private:
        string appconfigFile;
        string zmqhostip;
        string zmqhostport;
        string udphostip;
        string udphostport;
        string zmqServerAdd;
        string udpServerAdd;
        int io_threads;
        QUdpSocket* udpSocket;
        
}