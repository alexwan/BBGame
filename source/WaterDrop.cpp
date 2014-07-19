#include "WaterDrop.h"
#include "Game.h"



void WaterDrop::Init()
{
	Destroyed = false;
	Type = ST_WaterDrop;
	Velocity.x = 0;
	Velocity.y = 2 + (rand() * 4) / RAND_MAX;
	Position.x = 20 + (rand() * (Iw2DGetSurfaceWidth() - 40)) / RAND_MAX;
	Position.y = -20;
}

bool WaterDrop::Update()
{
	if (Destroyed)
		return false;	

	CSprite::Update();

	Position.x += Velocity.x;
	Position.y += Velocity.y;

	if (Position.y >= Iw2DGetSurfaceHeight() + 20)
	{
		return false;	
	}

	return true;

}

