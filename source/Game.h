#if !defined(_C_GAME_H_)
#define _C_GAME_H_

#include "s3e.h"
#include "Iw2D.h"
#include "IwGxFont.h"

#include "Sprite.h"

enum eSpriteType
{
	ST_None, 
	ST_Bucket, 
	ST_WaterDrop, 
};


// 
//

class CGame
{
	
protected:
	CSpriteManager*				SpriteManager;					
	int							Score;							
public:
	CSpriteManager*				getSpriteManager()				{ return SpriteManager; }
	void						addSprite(CSprite* sprite)		{ SpriteManager->addSprite(sprite); }
	void						removeSprite(CSprite* sprite)	{ SpriteManager->removeSprite(sprite); }
	void						updateScore(int amount);
	
protected:
	int							WaterDropTimer;

	
	CIw2DImage*					background_image;
	CIw2DImage*					bucket_image;
	CIw2DImage*					water_drop_image;
	CIw2DImage*					cloud_image;

	
	CIw2DFont*					Font;

	void	DrawScore();		

public:
	CGame() : SpriteManager(NULL)	{}

	void	Init();				
	void	Release();			
	void	Update();			
	void	Draw();				
};

extern CGame g_Game;




#endif 
