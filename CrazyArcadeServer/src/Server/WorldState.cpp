#include "WorldState.h"

void WorldState::Write(OutputMemoryStream & out)
{
	//out.Write(PacketTpye::WorldState);
	// WorldDate�� ������� Write����(iterator�� ����ɵ�)
}

void WorldState::Read(InputMemoryStream & in)
{
	//in.Read(PacketTpye::WorldState);
	//Write�� ��������..
}

void WorldState::PacketClassify(CrazyPacket * packet) 
{
	if (packet->GetPacketTpye() == PacketTpye::PLAYER)
	{

	}

	if (packet->GetPacketTpye() == PacketTpye::BOMB)
	{

	}
	//Header���� Ȯ���Ѵ�.
	//if (Header == PacketTpye::PLAYER)
	//{
	//	//Player��� NetID�� üũ
	//	WorldData[NetID].x = 1.0f; //������;
	//	WorldData[NetId].y = 2.0f;
	//}
}
