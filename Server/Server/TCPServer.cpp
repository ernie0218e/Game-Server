#include "StdAfx.h"
#include "TCPServer.h"
MainGame *game;

TCPServer::TCPServer(void){
	IP = gcnew String("127.0.0.1");
}

TCPServer::~TCPServer()
{
	tcpListener->Stop();
	listenThread->Abort();
	gameThread->Abort();
	socketList->Clear();
}

void TCPServer::Start()
{
	//******Game Initial************
	game = new MainGame();
	game->Init();
	//******End Game Initial********
	//******new	a game thread*******
	this->gameThread = gcnew Thread(gcnew ThreadStart(this, &TCPServer::gameStart));
	//******End*********************
	
	System::Diagnostics::Debug::WriteLine(IP);
	this->serverIP();
	this->socketList = gcnew List<Socket^>();
	connection_count = 0;
	this->tcpListener = gcnew TcpListener(IPAddress::Parse(IP), 3000);
	this->listenThread = gcnew Thread(gcnew ThreadStart(this, &TCPServer::ListenForClients));
	this->listenThread->Start();
}

void TCPServer::gameStart(void){
	for(;;){
		game->Update();
	}
}

void TCPServer::ListenForClients(void){
	//start the tcpListener
	this->tcpListener->Start();

	while(true){
		//blocks until a client has connected to the server
		Socket ^client = this->tcpListener->AcceptSocket();

		//create a thread to handle communication
		//with connected client
		Thread ^clientThread = gcnew Thread(gcnew ParameterizedThreadStart(this, &TCPServer::HandleClientComm));
		clientThread->Start(client);
		connection_count++;
		socketList->Add(client);
	}
}


void TCPServer::setIP(String ^i)
{
	IP = i;
}

String^ TCPServer::serverIP(){
	return gcnew String(IP);
}


String^ TCPServer::getIParray()
{
	String ^p;
	myip = Dns::GetHostAddresses(Dns::GetHostName());
	for(int i = 0;i < myip->Length;i++)
		p += Convert::ToString(myip[i]) + "\n";
	return p;
}


String^ TCPServer::serverCount()
{
	return Convert::ToString(connection_count);
}

void TCPServer::HandleClientComm(Object ^client){
	Socket ^tcpClient = (Socket^ )client;
	tcpClient->ReceiveTimeout = 1000;
	array <unsigned char> ^myBytes;
	array <unsigned char> ^myBufferBytes;
	String ^receivedata = nullptr;
	int dataLength;
	
	//****************send map*****************
	char ***temp_map;
	String ^send_map;
	temp_map = game->mainMap->getBlockMap();
	
	if(tcpClient->Connected == true){
		//myBytes = Encoding::Unicode->GetBytes("Welcome to My Server !!!!!\n");
		//tcpClient->Send(myBytes);
		myBufferBytes = gcnew array <unsigned char>(1024);
		myBytes = gcnew array <unsigned char>((game->mainMap->getBlockY())*(game->mainMap->getBlockX()));
		dataLength  = tcpClient->Receive(myBufferBytes);
		receivedata += Encoding::ASCII->GetString(myBufferBytes, 0, dataLength);
		System::Diagnostics::Debug::WriteLine(receivedata);
		if(receivedata=="iwanttoplay"){
			for(int i = 0;i < game->mainMap->getBlockY();i++)
				for(int j = 0;j < game->mainMap->getBlockX();j++){
					myBytes[i*game->mainMap->getBlockX()+j] = (*temp_map)[i][j];
					System::Diagnostics::Debug::WriteLine(Convert::ToString(myBytes[i*game->mainMap->getBlockY()+j]));
				}
			//System::Diagnostics::Debug::WriteLine(Convert::ToString(myBytes->Length));
			tcpClient->Send(myBytes);
			System::Diagnostics::Debug::WriteLine("Test");
		}
		receivedata = nullptr;
	//**************end of send map**********
		
		while(true){
			try{
				try{
					do{
						myBufferBytes = gcnew array <unsigned char>(1024);
						dataLength  = tcpClient->Receive(myBufferBytes);
					
						if (dataLength > 0){
							receivedata += Encoding::Unicode->GetString(myBufferBytes, 0, dataLength);
						}
					}while(tcpClient->Available);
				}catch(Exception ^recv_err){
					break;
				}
				//do some work
				if (receivedata != nullptr){
					myBytes = Encoding::Unicode->GetBytes(receivedata);
					for(int i = 0;i < socketList->Count;i++){
						if(tcpClient != socketList[i]){
							try{
								socketList[i]->Send(myBytes);
							}
							catch(Exception ^send_err){

							}
						}
					}
				}
				receivedata = nullptr;
			}
			catch(Exception ^ee){
				break;
			}
		}
	}
	tcpClient->Close();
	socketList->Remove(tcpClient);
	connection_count--;
}


