#include "Sprite.h"



void CSprite::Init()
{
	Type = 0;
	Position.x = 0;
	Position.y = 0;
	Angle = 0;
	Scale = IW_GEOM_ONE;
	Colour.r = 0xff;
	Colour.g = 0xff;
	Colour.b = 0xff;
	Colour.a = 0xff;
}

bool CSprite::Update()
{
	return true;
}

void CSprite::Draw()
{
	
	if (Image == NULL || !Visible || Colour.a == 0)
		return;

	
	Transform.SetRot(Angle);
	
	Transform.ScaleRot(Scale);
	
	Transform.SetTrans(Position);
	
	Iw2DSetTransformMatrix(Transform);

	
	Iw2DSetColour(Colour);

	
	int x = -(Width / 2);
	int y = -(Height / 2);
	Iw2DDrawImage(Image, CIwSVec2(x, y), CIwSVec2(Width, Height));
}


void CSpriteManager::addSprite(CSprite* sprite)
{
	
	Sprites.push_back(sprite);
	sprite->setParent(this);
}

void CSpriteManager::removeSprite(CSprite* sprite)
{
	
	for (Iterator it = Sprites.begin(); it != Sprites.end(); ++it)
	{
		if (*it == sprite)
		{
			delete *it;
			Sprites.erase(it);
			break;
		}
	}
}

void CSpriteManager::Update()
{
	CIwList<CSprite*> Removals;

	
	for (Iterator it = Sprites.begin(); it != Sprites.end(); ++it)
	{
		if (!(*it)->Update())
			Removals.push_back(*it);
	}

	
	for (Iterator it = Removals.begin(); it != Removals.end(); ++it)
	{
		for (Iterator it2 = Sprites.begin(); it2 != Sprites.end(); ++it2)
		{
			if (*it2 == *it)
			{
				delete *it2;
				Sprites.erase(it2);
				break;
			}
		}
	}
	Removals.clear();

}

void CSpriteManager::Draw()
{
	
	for (Iterator it = Sprites.begin(); it != Sprites.end(); ++it)
		(*it)->Draw();
}

CSpriteManager::~CSpriteManager()
{
	
	for (Iterator it = Sprites.begin(); it != Sprites.end(); ++it)
		delete *it;

	Sprites.clear();
}

