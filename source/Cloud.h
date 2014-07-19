#if !defined(_CLOUD_H_)
#define _CLOUD_H_

#include "s3e.h"
#include "Iw2D.h"

#include "Sprite.h"


class Cloud : public CSprite
{
	
protected:
	CIwSVec2	Velocity;		

public:
	void		setVelocity(int vx, int vy)	{ Velocity.x = vx; Velocity.y = vy; }
	
protected:

public:
	Cloud() : CSprite() {}
	virtual ~Cloud()	{}

	void	Init();				
	bool	Update();			
};



#endif 
