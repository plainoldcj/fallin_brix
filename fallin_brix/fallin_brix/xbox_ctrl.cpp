// xbox_ctrl.cpp

#include "xbox_ctrl.h"

void XBoxCtrl::Rumble(unsigned int low,
					  unsigned int high,
					  float secs)
{
	_secsPassed = 0.0f;
	_timer = secs;

	//for(int i = 0; i < 4; ++i)
	{
		XINPUT_VIBRATION vibration;
		ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
		vibration.wLeftMotorSpeed = high;
		vibration.wRightMotorSpeed = low;
		XInputSetState(0, &vibration);
	}
}

void XBoxCtrl::Update(float secsPassed)
{
	_secsPassed += secsPassed;
	if(_timer < _secsPassed)
	{
		//for(int i = 0; i < 4; ++i)
		{
			XINPUT_VIBRATION vibration;
			ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
			vibration.wLeftMotorSpeed = 0;
			vibration.wRightMotorSpeed = 0;
			XInputSetState(0, &vibration);
		}
	}
}