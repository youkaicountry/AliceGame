#ifndef _IRREVENT__
#define _IRREVENT__
#include <irrlicht.h>

using namespace irr;

class CIrrLichtEvent : public IEventReceiver
{
public:
bool m_key_buf[256];
bool m_key_buf_old[256];
bool m_mouse_button_buf[3];
bool m_mouse_button_buf_old[3];
public:
CIrrLichtEvent();
virtual ~CIrrLichtEvent();

void Init()
{
memset(m_key_buf, 0, 256);
memset(m_key_buf_old, 0, 256);
memset(m_mouse_button_buf, 0, 3);
memset(m_mouse_button_buf_old, 0, 3);
}


virtual bool OnEvent(SEvent event)
{
switch(event.EventType)
{
case EET_KEY_INPUT_EVENT:
m_key_buf_old[event.KeyInput.Key] = m_key_buf[event.KeyInput.Key];
m_key_buf[event.KeyInput.Key] = event.KeyInput.PressedDown;
break;
case EET_MOUSE_INPUT_EVENT:
if (event.MouseInput.Event < EMIE_MOUSE_MOVED)
{
m_mouse_button_buf_old[event.MouseInput.Event%3] = m_mouse_button_buf[event.MouseInput.Event%3];
m_mouse_button_buf[event.MouseInput.Event%3] = ((event.MouseInput.Event/3)?false:true);
}
break;
}

return true;
}

bool IsKeyDown(int index)
{
return m_key_buf[index];
}

bool IsKeyUpDown(int index)
{
return (m_key_buf[index] && !m_key_buf_old[index]);
}

bool IsKeyDownUp(int index)
{
return (!m_key_buf[index] && m_key_buf_old[index]);
}

bool IsMouseButtonDown(int index)
{
return m_mouse_button_buf[index];
}

bool IsMouseButtonUpDown(int index)
{
return (m_mouse_button_buf[index] && !m_mouse_button_buf_old[index]);
}

bool IsMouseButtonDownUp(int index)
{
return (!m_mouse_button_buf[index] && m_mouse_button_buf_old[index]);
}
};

CIrrLichtEvent::CIrrLichtEvent(void)
{
    return;
}

CIrrLichtEvent::~CIrrLichtEvent(void)
{
    return;
}

#endif 
