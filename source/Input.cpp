#include "Input.h"


CInput g_Input;


void HandleMultiTouchButtonCB(s3ePointerTouchEvent* event)
{
	
	CTouch* touch = g_Input.findTouch(event->m_TouchID);
    if (touch != NULL)
    {
		
        touch->active = event->m_Pressed != 0; 
        touch->x = event->m_x;
        touch->y = event->m_y;
    }
}

void HandleMultiTouchMotionCB(s3ePointerTouchMotionEvent* event)
{
	
	CTouch* touch = g_Input.findTouch(event->m_TouchID);
    if (touch != NULL)
    {
		
        touch->x = event->m_x;
        touch->y = event->m_y;
    }
}


void HandleSingleTouchButtonCB(s3ePointerEvent* event)
{
	CTouch* touch = g_Input.getTouch(0);
    touch->active = event->m_Pressed != 0;
    touch->x = event->m_x;
    touch->y = event->m_y;
}


void HandleSingleTouchMotionCB(s3ePointerMotionEvent* event)
{
	CTouch* touch = g_Input.getTouch(0);
    touch->x = event->m_x;
    touch->y = event->m_y;
}



CTouch*	CInput::findTouch(int id)
{
	if (!PointerAvailable)
		return NULL;

    
	for (int t = 0; t < MAX_TOUCHES; t++)
	{
		if (Touches[t].id == id)
			return &Touches[t];
		if (!Touches[t].active)
		{
            Touches[t].id = id;
			return &Touches[t];
		}
	}

	return NULL;
}

CTouch*	CInput::getTouchByID(int id)
{
	if (!PointerAvailable)
		return NULL;

	
	for (int t = 0; t < MAX_TOUCHES; t++)
	{
		if (Touches[t].active && Touches[t].id == id)
			return &Touches[t];
	}

	return NULL;
}

int CInput::getTouchCount() const
{
	if (!PointerAvailable)
		return 0;

	
	int count = 0;
	for (int t = 0; t < MAX_TOUCHES; t++)
	{
		if (Touches[t].active)
            count++;
	}

	return count;
}

bool CInput::Init()
{
	
    PointerAvailable = s3ePointerGetInt(S3E_POINTER_AVAILABLE) ? true : false;
	if (!PointerAvailable)
		return false;	

	if (PointerAvailable)
	{
		
		for (int t = 0; t < MAX_TOUCHES; t++)
		{
			Touches[t].active = false;
			Touches[t].id = 0;
		}

		
		IsMultiTouch = s3ePointerGetInt(S3E_POINTER_MULTI_TOUCH_AVAILABLE) ? true : false;

		
		if (IsMultiTouch)
		{
			s3ePointerRegister(S3E_POINTER_TOUCH_EVENT, (s3eCallback)HandleMultiTouchButtonCB, NULL);
			s3ePointerRegister(S3E_POINTER_TOUCH_MOTION_EVENT, (s3eCallback)HandleMultiTouchMotionCB, NULL);
		}
		else
		{
			s3ePointerRegister(S3E_POINTER_BUTTON_EVENT, (s3eCallback)HandleSingleTouchButtonCB, NULL);
			s3ePointerRegister(S3E_POINTER_MOTION_EVENT, (s3eCallback)HandleSingleTouchMotionCB, NULL);
		}
	}

	
    KeysAvailable = (s3eKeyboardGetInt(S3E_KEYBOARD_HAS_KEYPAD) || s3eKeyboardGetInt(S3E_KEYBOARD_HAS_ALPHA));

	
	OSKeyboardAvailable = s3eOSReadStringAvailable() == S3E_TRUE; 

	return true; 
}

void CInput::Release()
{
	if (PointerAvailable)
	{
		
		if (IsMultiTouch)
		{
			s3ePointerUnRegister(S3E_POINTER_TOUCH_EVENT, (s3eCallback)HandleMultiTouchButtonCB);
			s3ePointerUnRegister(S3E_POINTER_TOUCH_MOTION_EVENT, (s3eCallback)HandleMultiTouchMotionCB);
		}
		else
		{
			s3ePointerUnRegister(S3E_POINTER_BUTTON_EVENT, (s3eCallback)HandleSingleTouchButtonCB);
			s3ePointerUnRegister(S3E_POINTER_MOTION_EVENT, (s3eCallback)HandleSingleTouchMotionCB);
		}
	}
}

void CInput::Update()
{
	
	if (PointerAvailable)
		s3ePointerUpdate();

	
	if (KeysAvailable)
		s3eKeyboardUpdate();
}

bool CInput::isKeyDown(s3eKey key) const
{
	if (!KeysAvailable)
		return false;

	
	return (s3eKeyboardGetState(key) & S3E_KEY_STATE_DOWN) == S3E_KEY_STATE_DOWN;
}

bool CInput::isKeyUp(s3eKey key) const
{
	if (!KeysAvailable)
		return false;

	
	return (s3eKeyboardGetState(key) & S3E_KEY_STATE_UP) == S3E_KEY_STATE_UP;
}

bool CInput::wasKeyPressed(s3eKey key) const
{
	if (!KeysAvailable)
		return false;

	
	return (s3eKeyboardGetState(key) & S3E_KEY_STATE_PRESSED) == S3E_KEY_STATE_PRESSED;
}

bool CInput::wasKeyReleased(s3eKey key) const
{
	if (!KeysAvailable)
		return false;

	
	return (s3eKeyboardGetState(key) & S3E_KEY_STATE_RELEASED) == S3E_KEY_STATE_RELEASED;
}

const char* CInput::showOnScreenKeyboard(const char* prompt, int flags, const char* default_text)
{
	if (!OSKeyboardAvailable)
		return NULL;

	
	if (default_text != NULL)
		return s3eOSReadStringUTF8WithDefault(prompt, default_text, flags);
	else
		return s3eOSReadStringUTF8(prompt, flags);
}
