﻿#include "Etc/stdafx.h"
#include "Boom.h"


Boom::Boom(BoomState _boomstate, float addedTime, BlockPosition _bPos)
	:state(_boomstate), bPos(_bPos)
{
	explosionDuring += addedTime;
	collisionRect.left = _bPos.x * BLOCK_WIDTH + MAPOFFSET_X;
	collisionRect.right = (_bPos.x + 1) * (BLOCK_WIDTH) + MAPOFFSET_X;
	collisionRect.top = _bPos.y * BLOCK_HEIGHT + MAPOFFSET_Y;
	collisionRect.bottom = (_bPos.y + 1) * (BLOCK_HEIGHT) + MAPOFFSET_Y;

	switch (state)
	{
	case BoomState::BoomCenter:
		curImage = IMAGEMANAGER->findImage("폭발센터");
		break;
	case BoomState::BoomHorizenRight:
		curImage = IMAGEMANAGER->findImage("폭발오른쪽");
		break;
	case BoomState::BoomHorizenRightEnd:
		curImage = IMAGEMANAGER->findImage("폭발오른쪽끝");
		break;
	case BoomState::BoomHorizenLeft:
		curImage = IMAGEMANAGER->findImage("폭발왼쪽");
		break;
	case BoomState::BoomHorizenLeftEnd:
		curImage = IMAGEMANAGER->findImage("폭발왼쪽끝");
		break;
	case BoomState::BoomVerticalUp:
		curImage = IMAGEMANAGER->findImage("폭발위쪽");
		break;
	case BoomState::BoomVerticalUpEnd:
		curImage = IMAGEMANAGER->findImage("폭발위쪽끝");
		break;
	case BoomState::BoomVerticalDown:
		curImage = IMAGEMANAGER->findImage("폭발아래쪽");
		break;
	case BoomState::BoomVerticalDownEnd:
		curImage = IMAGEMANAGER->findImage("폭발아래쪽끝");
		break;
	}
}
Boom::~Boom()
{
	curImage = nullptr;
}

void Boom::update(float _deltaTime)
{
	deltaTime = _deltaTime;
	pastTime += deltaTime;
	if (pastTime > explosionDuring)
		timeEnd = true;
}
void Boom::render(HDC hdc)
{
	frameCounter += deltaTime;
	if (frameCounter > frameChageTimer) {
		frameIndex++;
		frameCounter = 0.f;
	}
	curImage->frameRender(hdc, collisionRect.left, collisionRect.top, frameIndex, 0);
}
void Boom::debugRender(HDC hdc)
{
	DrawColorRect(hdc, collisionRect, RGB(22,237,237));
}

