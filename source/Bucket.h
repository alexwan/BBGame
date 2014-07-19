#if !defined(_BUCKET_H_)
#define _BUCKET_H_

#include "s3e.h"
#include "Iw2D.h"

#include "Sprite.h"


class Bucket : public CSprite
{
	
protected:
public:

protected:
	void	DoCollision();

public:
	Bucket() : CSprite() { }
	virtual ~Bucket() {}

	void	Init();				
	bool	Update();			
};



#endif 
