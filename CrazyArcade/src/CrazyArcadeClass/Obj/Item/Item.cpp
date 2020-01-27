﻿#include "Etc/stdafx.h"
#include "Item.h"


Item::Item(const IRECT & _rect, const BlockPosition _pos, ItemType _type)
	: collisionRect(_rect), pos(_pos)
{
	type = _type;

	collisionRect.left	 += xMargin;
	collisionRect.right	 -= xMargin;
	collisionRect.top	 += yMargin;
	collisionRect.bottom -= yMargin;
	
	//image match
	if (type != ItemType::ItemNone) 
	curImage = IMAGEMANAGER->findImage("아이템");
	
	switch (type)
	{
	case ItemType::ItemRangeUp:
		frameIndexY = 2;
		break;
	case ItemType::ItemSpeedUp:
		frameIndexY = 1;
		break;
	case ItemType::ItemBombLimitUp:
		frameIndexY = 0;
		break;
	//TODO : add another
	}
}
Item::~Item()
{
}

void Item::update(float _deltaTime)
{
	deltaTime = _deltaTime;
}
void Item::render(HDC hdc)
{
	frameCounter += deltaTime;
	if (frameCounter > frameChageTimer) {
		frameIndex++;
		frameCounter = 0.f;
		if (frameIndex > curImage->getMaxFrameX())
			frameIndex = 0;
	}
	curImage->frameRender(hdc, collisionRect.left - 2, collisionRect.top - 2, frameIndex, frameIndexY);
}
void Item::debugRender(HDC hdc)
{
	switch (type)
	{
	case ItemType::ItemRangeUp:
		DrawColorRect(hdc, collisionRect, RGB(0, 0, 0));
		break;
	case ItemType::ItemSpeedUp:
		DrawColorRect(hdc, collisionRect, RGB(255, 0, 0));
		break;
	case ItemType::ItemBombLimitUp:
		DrawColorRect(hdc, collisionRect, RGB(0, 255, 0));
		break;
	//case ItemType::ItemKick:
	//	DrawColorRect(hdc, collisionRect, RGB(0, 0, 255));
	//	break;
	//case ItemType::ItemDart:
	//	DrawColorRect(hdc, collisionRect, RGB(255, 255, 0));
	//	break;
	}
}
void Item::release()
{
}

