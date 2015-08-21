Messaging in GenApp
==============================

* For implementation details visit [GenApp wiki - Messaging](http://gw105.iu.xsede.org/genapp/wiki/dn_messaging#no1) <br/>

Task
------------------------------
GenApp messaging provides a way for an executable to update the user interface, during execution, such as "progress" or any other valid JSON ouput. <br/>
The running module sends a message with the json output and a unique id to the server. <br/>
The websocket server is for clients and they can subscribe to a "topic" == unique_id and then get copies of the udp messages <br/>

Version
------------------------------
**0.1** <br/>
**Post Development, Ready to test** <br/>

Implementation
------------------------------
The messages are communicated via *User Datagram Protocol* (UDP) and send to the websocket running on ZeroMQ server <br/>

Installation
------------------------------
**For Mac Users** <br/>

* open a terminal and execute <br/>
```shell
    sudo chown -R $USER /usr/local/lib
    brew install zmq
```

Check Connection
------------------------------
* Go to test-zmq folder <br/>
* run **_./compile.sh_** <br/>
* Upon successfull compilation check the client-server connection by executing **_./test_** <br/>

Project Tree
------------------------------
## msg-udpserver <br/>
   |-- msg-udpserver.cpp
   |-- msg-udpserver.h
   
This includes the cpp and header files for the udp server. It contains APIs for initializing the socket connections, receiving JSON input from the genapp modules over the udp and redirecting them to the websocket server.


APIs
==============================
For APIs and documentation refer to the API-docs folder (currently under construction) <br/>


