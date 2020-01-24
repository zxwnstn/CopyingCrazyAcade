#pragma once
#include "packet.h"
#include <map>
#include <vector>

class CrazyPacket;
//class Position2D 
//{
//	PacketTpye m_type;
//	int m_x;
//	int m_y;
//
//	void Write(OutputMemoryStream& out)
//	{
//		out.Write(&m_type,sizeof(m_type));
//		out.Write(&m_x, sizeof(m_x));
//		out.Write(&m_y, sizeof(m_y));
//	}
//	void Read(InputMemoryStream& in)
//	{
//		in.Read(&m_type, sizeof(m_type));
//		in.Read(&m_x, sizeof(m_x));
//		in.Read(&m_y, sizeof(m_y));
//	}
//};

class WorldState
{


public:
	// Ŭ���̾�Ʈ�� WorldPacket�� �����°��̾ƴ϶� Packet�� ������. 
	void Write(OutputMemoryStream& out); //WorlData RW��.
	void Read(InputMemoryStream& in);
	void PacketClassify(CrazyPacket* packet);

private:
	size_t Header;
	std::map<int, std::vector<float>> WorldData; 
	// ���⿡ �÷��̾���� ������ ��ǳ�������� ����
	// �÷��̾��� Ű���� 1����(NetID)�� �Ҵ�
	// ��ǳ���� 1000������� ����(�ִ� 21�ﰳ ��������)
	// value�� �� Ű���� x y��ǥ�� ��. 
	// �̰Ÿ� Write�ؼ� ��Ŷ���κ������.
	// �÷��̾��� ��� value�� NetID, x, y �� ��. (�����ؾ��ҵ�)
};