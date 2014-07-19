#if !defined(_CINPUT_H_)
#define _CINPUT_H_

#include "IwGeom.h"
#include "s3ePointer.h"
#include "s3eKeyboard.h"
#include "s3eOSReadString.h"

#define MAX_TOUCHES		4


struct CTouch
{
public:
    int		x, y;		
    bool	active;		
    int		id;			
};


class CInput
{
	
private:
	bool		PointerAvailable;				
	bool		KeysAvailable;					
	bool		OSKeyboardAvailable;			
	bool		IsMultiTouch;					
	CTouch		Touches[MAX_TOUCHES];			
public:
	bool		isPointerAvailable() const { return PointerAvailable; }	
	bool		isKeysAvailable() const { return KeysAvailable; }		
	bool		isOSKeyboardAvailable() const { return OSKeyboardAvailable; }	
	bool		isMultiTouch() const { return IsMultiTouch; }		
	CTouch*		getTouchByID(int id);								
	CTouch*		getTouch(int index) { return &Touches[index]; }		
	CTouch*		findTouch(int id);									
	int			getTouchCount() const;								
	bool		isKeyDown(s3eKey key) const;
	bool		isKeyUp(s3eKey key) const;
	bool		wasKeyPressed(s3eKey key) const;
	bool		wasKeyReleased(s3eKey key) const;
	const char* showOnScreenKeyboard(const char* prompt, int flags = 0, const char* default_text = NULL);
	

private:
public:
	bool		Init();							
	void		Release();						
	void		Update();						
};

extern CInput g_Input;



#endif	