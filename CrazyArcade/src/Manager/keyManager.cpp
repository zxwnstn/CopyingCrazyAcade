﻿#include "Etc/stdafx.h"
#include "Manager/keyManager.h"

keyManager::keyManager()
{
}


keyManager::~keyManager()
{
}

HRESULT keyManager::init()
{
	//키가 전부 눌려있지 않은 상태로 초기화하자
	for (int i = 0; i < KEYMAX; i++)
	{
		_keyUp.set(i, false);
		_keyDown.set(i, false);
	}

	playerKey[P1_UP] = VK_UP;
	playerKey[P1_DOWN] = VK_DOWN;
	playerKey[P1_LEFT] = VK_LEFT;
	playerKey[P1_RIGHT] = VK_RIGHT;
	playerKey[P1_EVENT] = VK_SPACE;
	playerKey[P1_USEITEM] = VK_DELETE;
	
	playerKey[P2_UP] = 'R';
	playerKey[P2_DOWN] = 'F';
	playerKey[P2_LEFT] = 'D';
	playerKey[P2_RIGHT] = 'G';
	playerKey[P2_EVENT] = 'S';
	playerKey[P2_USEITEM] = 'A';

	playerKey[GAME_RECTMODE] = VK_F2;
	playerKey[GAME_DEBUGMODE] = VK_F3;
	playerKey[GAME_LMOUSE] = VK_LBUTTON;
	playerKey[GAME_RMOUSE] = VK_RBUTTON;

	return S_OK;
}

void keyManager::release()
{
}

bool keyManager::isOnceKeyDown(int key)
{

	//GetAsyncKeyState현재 키의 상태를 알아오는 녀석
	//키가 눌려졌을때나 떨어졌을때 호출
	//0x8000 이전에는 누른적이 없고 호출시점에서 눌린상태
	if (GetFocus())
	{
		if (GetAsyncKeyState(playerKey[key]) & 0x8000)
		{
			if (!_keyDown[playerKey[key]])
			{
				_keyDown.set(playerKey[key], true);
				return true;
			}
		}
		else
		{
			_keyDown.set(playerKey[key], false);
		}
	}
	return false;
}

bool keyManager::isOnceKeyUp(int key)
{
	if (GetFocus())
	{
		if (GetAsyncKeyState(key) & 0x8000)
		{
			_keyUp.set(playerKey[key], true);
		}
		else
		{
			if (_keyUp[playerKey[key]])
			{
				_keyUp.set(playerKey[key], false);
				return true;
			}
		}
	}
	return false;
}

bool keyManager::isStayKeyDown(int key)
{
	if (GetFocus())
	{
		if (GetAsyncKeyState(playerKey[key]) & 0x8000)return true;
	}
	return false;
}

bool keyManager::isToggleKey(int key)
{

	//GetKeyState :현재 키의 토글상태
	//0x0001이전에 누른적이 있고 호출시점에서 안눌린 상태
	if (GetFocus())
	{
		if (GetKeyState(playerKey[key]) & 0x0001)return true;
	}
	return false;
}

void keyManager::setCustomKey(int dest, int userKey)
{
	playerKey[dest] = userKey;
}
