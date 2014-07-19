#include "IwResManager.h"
#include "Input.h"

#include "Game.h"
#include "Bucket.h"
#include "WaterDrop.h"
#include "Cloud.h"


CGame g_Game;


void CGame::Init()
{
	
	SpriteManager = new CSpriteManager();

	
	IwGetResManager()->LoadGroup("Level1.group");

	
	background_image	= Iw2DCreateImageResource("background");
	bucket_image		= Iw2DCreateImageResource("bucket");
	water_drop_image	= Iw2DCreateImageResource("water_drop");
	cloud_image			= Iw2DCreateImageResource("cloud");

	
	Font = Iw2DCreateFontResource("trebuchet_12");

	
	int screen_width = Iw2DGetSurfaceWidth();
	int screen_height = Iw2DGetSurfaceHeight();

	
	CSprite* background_sprite = new CSprite();
	background_sprite->Init();
	background_sprite->setPosAngScale(screen_width / 2, screen_height / 2, 0, IW_GEOM_ONE);
	background_sprite->setImage(background_image);
	background_sprite->setDestSize(screen_width, screen_height);
	SpriteManager->addSprite(background_sprite);

	
	Cloud* cloud_sprite = new Cloud();
	cloud_sprite->Init();
	cloud_sprite->setPosAngScale(0, 50, 0, IW_GEOM_ONE);
	cloud_sprite->setImage(cloud_image);
	cloud_sprite->setVelocity(2, 0);
	SpriteManager->addSprite(cloud_sprite);
	cloud_sprite = new Cloud();
	cloud_sprite->Init();
	cloud_sprite->setPosAngScale(200, 150, 0, IW_GEOM_ONE);
	cloud_sprite->setImage(cloud_image);
	cloud_sprite->setVelocity(1, 0);
	SpriteManager->addSprite(cloud_sprite);
	cloud_sprite = new Cloud();
	cloud_sprite->Init();
	cloud_sprite->setPosAngScale(300, 100, 0, IW_GEOM_ONE);
	cloud_sprite->setImage(cloud_image);
	cloud_sprite->setVelocity(2, 0);
	SpriteManager->addSprite(cloud_sprite);

	
	Bucket* bucket_sprite = new Bucket();
	bucket_sprite->Init();
	bucket_sprite->setPosAngScale(screen_width / 2, (screen_height * 3) / 4, 0, IW_GEOM_ONE);
	bucket_sprite->setImage(bucket_image);
	SpriteManager->addSprite(bucket_sprite);

	
	WaterDropTimer = 85;

}

void CGame::Release()
{
	
	if (SpriteManager != NULL)
	{
		delete SpriteManager;
		SpriteManager = NULL;
	}

	
	if (Font != NULL)
	{
		delete Font;
		Font = NULL;
	}

	
	if (background_image != NULL)
	{
		delete background_image;
		background_image = NULL;
	}
	if (cloud_image != NULL)
	{
		delete cloud_image;
		cloud_image = NULL;
	}
	if (bucket_image != NULL)
	{
		delete bucket_image;
		bucket_image = NULL;
	}
	if (water_drop_image != NULL)
	{
		delete water_drop_image;
		water_drop_image = NULL;
	}
}

void CGame::Update()
{
	
	SpriteManager->Update();

	
	WaterDropTimer--;
	if (WaterDropTimer <= 0)
	{
		
		WaterDropTimer = 50;
		WaterDrop* drop_sprite = new WaterDrop();
		drop_sprite->Init();
		drop_sprite->setImage(water_drop_image);
		SpriteManager->addSprite(drop_sprite);
	}
}

void CGame::Draw()
{
	
	Iw2DSurfaceClear(0xff000000);

	
	SpriteManager->Draw();

	
	DrawScore();

	
	Iw2DSurfaceShow();
}

void CGame::updateScore(int amount)
{
	
	Score += amount;
}

void CGame::DrawScore()
{
	
	Iw2DSetFont(Font);

	
	Iw2DSetTransformMatrix(CIwMat2D::g_Identity);

	
	Iw2DSetColour(0xff000000);

	
	Iw2DDrawString("Score:", CIwSVec2(10, 10), CIwSVec2(200, 30), IW_2D_FONT_ALIGN_LEFT, IW_2D_FONT_ALIGN_TOP);

	
	char str[12];
	snprintf(str, 12, "%d", Score);

	
	Iw2DDrawString(str, CIwSVec2(100, 10), CIwSVec2(200, 30), IW_2D_FONT_ALIGN_LEFT, IW_2D_FONT_ALIGN_TOP);
}


