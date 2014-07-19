#include "Cloud.h"
#include "Game.h"



void Cloud::Init()
{
	Type = ST_None;
	Velocity.x = 0;
	Velocity.y = 0;
}

bool Cloud::Update()
{
	CSprite::Update();

	
	Position.x += Velocity.x;
	Position.y += Velocity.y;

	
	if (Position.x >= Iw2DGetSurfaceWidth() + Width)
	{
		Position.x = -Width;
	}

	return true;

}

