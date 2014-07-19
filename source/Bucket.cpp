#include "Bucket.h"

#include "Input.h"
#include "Game.h"
#include "WaterDrop.h"



void Bucket::Init()
{
	Type = ST_Bucket;
}

bool Bucket::Update()
{
	CSprite::Update();

	
	if (g_Input.getTouchCount() != 0)
	{
		Position.x = g_Input.getTouch(0)->x;
	}

	
	DoCollision();

	return true;
}

void Bucket::DoCollision()
{
	
	for (CSpriteManager::Iterator it = Parent->begin(); it != Parent->end(); ++it)
	{
		if ((*it)->getType() == ST_WaterDrop)
		{
			WaterDrop* drop = (WaterDrop*)*it;
			
			int dx = drop->getPosition().x - Position.x;
			if (dx < 0) dx = -dx;
			if (dx < 16)
			{
				
				int drop_y = drop->getPosition().y;
				if (drop_y > (Position.y - Height / 2) && drop_y < (Position.y + Height / 2))
				{
					
					drop->Destroy();

					
					g_Game.updateScore(1);
				}
			}
		}
	}
}


