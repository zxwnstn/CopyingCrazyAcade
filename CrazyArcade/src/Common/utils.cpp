﻿#include "Etc/stdafx.h"
#include "utils.h"

namespace UTIL
{
	
	float getDistance(float startX, float startY, float endX, float endY)
	{
		float x = endX - startX;
		float y = endY -  startY;

		return sqrtf(x * x + y * y);
	}

	float getAngle(float src_x, float src_y, float tar_x, float tar_y)
	{
		float dx = src_x - tar_x;
		float dy = src_y - tar_y;
		float angle =0.f;
		float distance = sqrtf(dx * dx + dy * dy);


		if (dx < 0 && dy < 0)
			angle = PI2 - acosf(dx / distance);
		if (dx < 0 && dy > 0)
			angle = PI + acosf(dx / distance);
		if (dx > 0 && dy > 0)
			angle = acosf(dx / distance);
		if (dx > 0 && dy < 0)
			angle = PI - acosf(dx / distance);
		

		return angle;
	}

	bool isCircleCircleCollision(Circle& c1, Circle& c2) {
		float dist = getDistance(c1.p.x, c1.p.y, c2.p.x, c2.p.y);
		if (dist <= c1.radius + c2.radius)
			return true;
		return false;
	}

	bool isCircleRectCollision(Circle & c1, FRECT rect)
	{
		rect.left -= c1.radius;
		rect.top -= c1.radius;
		rect.right += c1.radius;
		rect.bottom += c1.radius;

		if (rect.left <= c1.p.x  && c1.p.x <= rect.right)
			if(rect.top <= c1.p.y  && c1.p.y <= rect.bottom)
				return true;

		return false;
	}

	bool isRectRectCollision(const RECT & rect1, const RECT & rect2)
	{
		if (rect1.left < rect2.right && rect1.right > rect2.left &&
			rect1.top < rect2.bottom && rect1.bottom > rect2.top) {
			return true;
		}
		return false;
	}
	bool isRectRectCollision(const RECT & rect1, const FRECT & rect2)
	{
		if (rect1.left < rect2.right && rect1.right > rect2.left &&
			rect1.top < rect2.bottom && rect1.bottom > rect2.top) {
			return true;
		}
		return false;
	}


	bool isRectRectCollision(const FRECT & rect1, const FRECT & rect2)
	{
		if (rect1.left < rect2.right && rect1.right > rect2.left &&
			rect1.top < rect2.bottom && rect1.bottom > rect2.top) {
			return true;
		}
		return false;
	}

	bool isRectRectCollision(const IRECT & rect1, const IRECT & rect2)
	{
		if (rect1.left < rect2.right && rect1.right > rect2.left &&
			rect1.top < rect2.bottom && rect1.bottom > rect2.top) {
			return true;
		}
		return false;
	}

	bool isPointRectCollision(const POINT & point, const RECT & rect)
	{
		if ((rect.left < point.x && point.x < rect.right) &&
			(rect.top < point.y && point.y < rect.bottom))
			return true;
		return false;
	}

	bool isPointRectCollision(const POINT & point, const FRECT & rect)
	{
		if ((rect.left < point.x && point.x < rect.right) &&
			(rect.top < point.y && point.y < rect.bottom))
			return true;
		return false;
	}

	bool isPointRectCollision(const FPOINT & point, const RECT& rect) {
		if ((rect.left < point.x && point.x < rect.right) &&
			(rect.top < point.y && point.y < rect.bottom))
			return true;
		return false;
	}

	bool isPointRectCollision(const FPOINT & point, const FRECT& rect) {
		if ((rect.left < point.x && point.x < rect.right) &&
			(rect.top < point.y && point.y < rect.bottom))
			return true;
		return false;
	}

	bool isPointRectCollision(const POINT & point, const IRECT & rect)
	{
		if ((rect.left <= point.x && point.x <= rect.right) &&
			(rect.top <= point.y && point.y <= rect.bottom))
			return true;
		return false;
	}

	bool operator==(const IRECT& rect1, const IRECT& rect2) {
		if (rect1.left == rect2.left && rect1.right == rect2.right &&
			rect1.top == rect2.top && rect1.bottom == rect2.bottom)
			return true;
		return false;
	}
	void IRECT::setBpos() {
		bPos_x = (left - MAPOFFSET_X) / BLOCK_WIDTH;
		bPos_y = (top - MAPOFFSET_Y) / BLOCK_HEIGHT;
	}
	void IRECT::moveUp(int dist) {
		top -= dist;
		bottom -= dist;
	}
	void IRECT::moveDown(int dist) {
		top += dist;
		bottom += dist;
	}
	void IRECT::moveLeft(int dist) {
		left -= dist;
		right -= dist;
	}
	void IRECT::moveRight(int dist) {
		left += dist;
		right += dist;
	}
	void IRECT::reset() {
		bPos_x = -11;
		bPos_y = -1;
		left = -11;
		top = -11;
		right = -11;
		bottom = -11;
	}
}