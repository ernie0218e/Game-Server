#include "StdAfx.h"
#include "TCPServer.h"

TCPServer::TCPServer(void){
	IP = gcnew String("127.0.0.1");
	game = NULL;
	//this->socketList = gcnew List<Socket^>();
	gameThread = nullptr;
	listenThread = nullptr;
	tcpListener = nullptr;
	connection_count = 0;
}

TCPServer::~TCPServer()
{
	if(tcpListener != nullptr)
		tcpListener->Stop();
	if(listenThread != nullptr)
		listenThread->Abort();
	if(gameThread != nullptr)
		gameThread->Abort();
	//socketList->Clear();
}

int TCPServer::Start()
{
	//******Game Initial************
	try{
		game = new MainGame();	
		game->Init();
		//******End Game Initial********
		//******new	a game thread*******
		this->gameThread = gcnew Thread(gcnew ThreadStart(this, &TCPServer::gameStart));
		this->gameThread->Start();
		//******End*********************
	}catch(Exception ^game_err){
		err_msg += game_err->Message + "\n";
		return 1;
	}
	System::Diagnostics::Debug::WriteLine(IP);
	
	this->tcpListener = gcnew TcpListener(IPAddress::Parse(IP), 9011);
	this->listenThread = gcnew Thread(gcnew ThreadStart(this, &TCPServer::ListenForClients));
	this->listenThread->Start();
	return 0;
}


void TCPServer::Stop()
{
	if(tcpListener != nullptr)
		tcpListener->Stop();
	if(listenThread != nullptr)
		listenThread->Abort();
	if(gameThread != nullptr)
		gameThread->Abort();
	//socketList->Clear();
}


void TCPServer::gameStart(void){
	for(;;){
		game->Update();
	}
}

void TCPServer::ListenForClients(void){
	//start the tcpListener
	int thread_id = 0, i;
	this->tcpListener->Start();

	while(true){
		//blocks until a client has connected to the server
		Socket ^client = this->tcpListener->AcceptSocket();

		//create a thread to handle communication
		//with connected client
		Thread ^clientThread = gcnew Thread(gcnew ParameterizedThreadStart(this, &TCPServer::HandleClientComm));
		clientThread->Start(client);
		clientThread->Name = Convert::ToString(++thread_id);
		msg += "Client:" + clientThread->Name + " connect." + "\n";
		connection_count++;
		//socketList->Add(client);
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
	tcpClient->ReceiveTimeout = 500;
	array <unsigned char> ^myBytes;
	array <unsigned char> ^myBufferBytes;
	String ^receivedata = nullptr;
	MainCharacter *mainchr;
	int dataLength;
	int ID;
	int flag = 0;
	//****************get map*****************
	char ***temp_map;
	String ^send_map;
	temp_map = game->mainMap->getBlockMap();
	
	if(tcpClient->Connected == true){
		
		myBufferBytes = gcnew array <unsigned char>(1024);
		//************send map******************
		myBytes = gcnew array <unsigned char>((game->mainMap->getBlockY())*(game->mainMap->getBlockX()));
		dataLength  = tcpClient->Receive(myBufferBytes);
		receivedata += Encoding::ASCII->GetString(myBufferBytes, 0, dataLength);
		
		if(receivedata=="iwanttoplay"){
			for(int i = 0;i < game->mainMap->getBlockY();i++)
				for(int j = 0;j < game->mainMap->getBlockX();j++){
					myBytes[i*game->mainMap->getBlockX()+j] = (*temp_map)[i][j];
				}
			tcpClient->Send(myBytes);
			
		}
		receivedata = nullptr;
		//**************end of send map**********
		//**************receive buffer***********
		try{
			myBufferBytes = gcnew array <unsigned char>(1024);
			dataLength  = tcpClient->Receive(myBufferBytes);
			
			if (dataLength > 0){
				receivedata += Encoding::ASCII->GetString(myBufferBytes, 0, dataLength);
			}
			//System::Diagnostics::Debug::WriteLine(receivedata);
		}catch(Exception ^rec){
			err_msg += rec->Message + "\n";
		}
		if(receivedata != nullptr){
		//**************new character************
			ID = game->generateID();
			try{
				mainchr = game->MakeNewChar(1000, 500, ID);
			}catch(Exception ^chr_err){
				err_msg += chr_err->Message + "\n";
			}
			
			System::Diagnostics::Debug::WriteLine(ID);

			myBytes = Encoding::ASCII->GetBytes(gcnew String(game->getCommand(mainchr).c_str())+"\0");
			try{
				tcpClient->Send(myBytes);
			}catch(Exception ^send_err){
				err_msg += send_err->Message + "\n";
			}
		//**************end of new character******
		
		receivedata = nullptr;
		while(true){
			try{
				/*try{
					do{
						myBufferBytes = gcnew array <unsigned char>(1024);
						dataLength  = tcpClient->Receive(myBufferBytes);
						if (dataLength > 0){
							receivedata += Encoding::ASCII->GetString(myBufferBytes, 0, dataLength);
						}
					}while(tcpClient->Available);
				}catch(Exception ^recv_err){
					System::Diagnostics::Debug::WriteLine("here");
					err_msg = recv_err->Message;
					break;
				}*/
				try{
					myBufferBytes = gcnew array <unsigned char>(tcpClient->SendBufferSize);
					dataLength = tcpClient->Receive(myBufferBytes);
					if(dataLength > 0){
						receivedata += Encoding::ASCII->GetString(myBufferBytes, 0, dataLength);
					}
				}catch(Exception ^recv_err){
					System::Diagnostics::Debug::WriteLine("here");
					err_msg += recv_err->Message + "\n";
					break;
				}
				
				//do some work
				if (receivedata != nullptr){
					//System::Diagnostics::Debug::WriteLine(receivedata);
					mainchr->setStatus(Convert::ToInt32(receivedata));
					//myBytes = Encoding::ASCII->GetBytes(gcnew String(game->newGame_info.c_str()) + gcnew String(game->sGame_info.c_str())+"\0");
					myBytes = Encoding::ASCII->GetBytes(gcnew String(game->getCommand(mainchr).c_str())+"\0");
					try{
						tcpClient->Send(myBytes);
					}catch(Exception ^send_err){
						err_msg += send_err->Message + "\n";
						break;
					}
				}
				receivedata = nullptr;
			}
			catch(Exception ^ee){
				err_msg += ee->Message + "\n";
				break;
			}
		}
		}
	}
	game->deleteChar(mainchr->getId());
	tcpClient->Close();
	//socketList->Remove(tcpClient);
	connection_count--;
}

void TCPServer::MarshalString ( String ^ s, string& os ) {
	using namespace Runtime::InteropServices;
	const char* chars = 
		(const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
	os = chars;
	Marshal::FreeHGlobal(IntPtr((void*)chars));
}

String^ TCPServer::getError()
{
	String^ temp = gcnew String(err_msg);
	err_msg = nullptr;
	return temp;
}

String^ TCPServer::getMessage()
{
	String ^temp = gcnew String(msg);
	msg = nullptr;
	return temp;
}
