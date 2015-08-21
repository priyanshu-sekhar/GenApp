using jsonscons::json;
using jsoncons::output_format;
using std::string;

void msg-udpserver::readConfigFile(){
    string currentDir = get_current_dir_name();
    string genappHome = currentDir + "/../..";
    
    this->appconfigFile = genappHome + "/appconfig.json";  
    json appconfig_json = json::parse_file(this->appconfigFile);
    json messaging = appconfig_json["messaging"];
    
    this->zmqhostip = messaging["zmqhostip"].as<std::string>();
    this->zmqhostport = messaging["zmqport"].as<std::string>();
    this->udphostip = messaging["udphostip"].as<std::string>();
    this->udphostport = messaging["udpport"].as<std::string>();
    
    this->zmqServerAdd = "tcp://" + this->udphostip + ":" + this->udpport;
    
    
    this->io_threads = 1;
}

void msg-udpserver::retransmit(){
    zmq::context_t context (this->io_threads);
    zmq::socket_t socket (context, ZMQ_PUSH);
    socket.connect(this->zmqServerAdd);
    
    udpSocket = new QUdpSocket(this);
    
    QString add = QString::fromStdString(this->udphostip);
    QHostAddress qAdd = new QHostAddress(add);
    
    udpSocket->bind( qAdd, QString::toUShort(this->udphostport) );
    while (udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        udpSocket->readDatagram(datagram.data(), datagram.size(),
                                &sender, &senderPort);
        
        string buf = QTextCodec::codecForMib(1015)->toUnicode(datagram).toStdString();
        
        zmq::message_t reply(datagram.size());
        memcpy ((void *) reply.data(), buf, datagram.size());
        socket.send (reply);
    }
}

//void msg-udpserver::connectToHost(){
//}
//
//void msg-udpserver::initSocket(){
//    zmq::context_t context (this->io_threads);
//    zmq::socket_t socket (context, ZMQ_REP);
//    socket.connect(this->zmqServerAdd);
//    
//    udpSocket = new QUdpSocket(this);
//    udpSocket->bind(this->udphostip, this->udphostport);
//    
//}