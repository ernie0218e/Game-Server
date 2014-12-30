#pragma once
using namespace System;
using namespace System::Text;
using namespace System::Net::Sockets;
using namespace System::Threading;
using namespace System::Net;
using namespace System::Collections::Generic;
using namespace std;

ref class TCPServer
{
private:
	String^ IP;
	array <IPAddress^> ^myip;
	TcpListener^ tcpListener;
	Thread^ listenThread;
	Thread^ gameThread;
	/*List<String^>^ recieveData;
	List<String^>^ sendData;*/
	List<Socket^>^ socketList;
	int connection_count;
	void gameStart(void);
	void ListenForClients(void);
	void HandleClientComm(Object^);
	void MarshalString(String ^, string&);
public:
	TCPServer();
	~TCPServer();
	void Start();
	void setIP(String ^);
	String^ serverIP();
	String^ serverCount();
	String^ getIParray();
};

