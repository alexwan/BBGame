#if !defined(_WATER_DROP_H_)
#define _WATER_DROP_H_

#include "s3e.h"
#include "Iw2D.h"

#include "Sprite.h"


class WaterDrop : public CSprite
{
	
protected:
	bool		Destroyed;		
	CIwSVec2	Velocity;		

public:
	void		setVelocity(int vx, int vy)	{ Velocity.x = vx; Velocity.y = vy; }
	void		Destroy()					{ Destroyed = true; }
	
protected:

public:
	WaterDrop() : CSprite() {}
	virtual ~WaterDrop()	{}

	void	Init();				
	bool	Update();			
};



#endif 
