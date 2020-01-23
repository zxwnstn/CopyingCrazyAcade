#include "packet.h"

//critical section
int clientNumber;
bool wait = true;
std::mutex mtx;


void echo(TCPSocketPtr servsock, TCPSocketPtr clientSocket)
{
	//critical section
	mtx.lock();
	++clientNumber;
	mtx.unlock();

	int thisclientnumber = clientNumber;
	std::cout << thisclientnumber << "�� Ŭ���̾�Ʈ�� �����Ͽ����ϴ�!!" << std::endl;

	//Send IDpacket
	IDpacket idPacket;
	idPacket.packetType = (char)PacketTpye::PLAYER;
	idPacket.clientID = (char)thisclientnumber;

	OutputMemoryStream out;
	idPacket.Write(out);
	char* Buffer = static_cast<char*>(malloc(PACKET_MAX));
	memcpy(Buffer, out.GetBufferPtr(), out.GetLength());
	clientSocket->Send(Buffer, out.GetLength());
	std::cout << thisclientnumber << "�� Ŭ���̾�Ʈ�� ID��Ŷ�� ���½��ϴ�.\n";

	//Send initPacket
	InitiationPacket initPacket;
	for (int i = 0; i < 2; ++i) {
		initPacket.clientCharacter[i] = i;
		initPacket.clientCharacterPosX[i] = i;
		initPacket.clientCharacterPosY[i] = i;
		initPacket.clientID[i] = i;
	}
	initPacket.blocks = createVillageBlocksData();
	initPacket.show();

	OutputMemoryStream out2;
	initPacket.Write(out2);
	char* Buffer2 = static_cast<char*>(malloc(PACKET_MAX));
	memcpy(Buffer2, out2.GetBufferPtr(), out2.GetLength());
	clientSocket->Send(Buffer2, out2.GetLength());
	std::cout << thisclientnumber << "�� Ŭ���̾�Ʈ�� �̴���Ŷ�� ���½��ϴ�.\n";

	//Receive client Move data
	while (true) {
		MovePacket moveData;
		char* Buffer3 = static_cast<char*>(malloc(PACKET_MAX));
		int size = clientSocket->Receive(Buffer3, 1470);
		if (size < 0) {	// ����� ����
			break;
		}
		InputMemoryStream in(Buffer3, size);
		moveData.Read(in);
		moveData.show();
		//free(Buffer3);
	}
	//free(Buffer);
	//free(Buffer2);
	std::cout << thisclientnumber << "�� Ŭ���̾�Ʈ ���� ����" << '\n' << std::endl;
}

int main()
{
	WSADATA wsaData;
	auto err = WSAStartup(MAKEWORD(2, 2), &wsaData);

	SocketAddressFactory fac;
	SocketAddress servAddr(INADDR_ANY, 9190);
	SocketAddress clientAddr;

	TCPSocketPtr ServSock = SocketUtil::CreateTCPSocket(INET);

	ServSock->Bind(servAddr);
	std::cout << "������ �����մϴ�!" << std::endl;
	std::cout << "Ŭ���̾�Ʈ ���� �����..." << std::endl;

	srand(time(NULL));

	ServSock->Listen(5);

	while (true)
	{
		TCPSocketPtr ClientSocket;
		ClientSocket = ServSock->Accept(clientAddr);

		std::thread t1(echo, ServSock, ClientSocket);
		t1.detach();
	}

	WSACleanup();
}