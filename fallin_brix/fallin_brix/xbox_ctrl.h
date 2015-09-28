// xbox_ctrl.h

#ifndef __XBOX_CTRL_H__
#define __XBOX_CTRL_H__

#if _MSC_VER > 1000
#pragma once
#endif

#include <windows.h>
#include <xinput.h>
#include <boost/smart_ptr.hpp>

#ifdef _MSC_VER
#pragma comment(lib, "xinput.lib")
#endif

class XBoxCtrl
{
private:
	XBoxCtrl(void) { }
	float _secsPassed;
	float _timer;
public:
	~XBoxCtrl(void) { Rumble(0, 0, 0.0f); }

	static boost::shared_ptr<XBoxCtrl> GetInstance(void)
	{
		static boost::shared_ptr<XBoxCtrl> instance;
		if(!instance) instance = boost::shared_ptr<XBoxCtrl>(new XBoxCtrl);
		return instance;
	}

	void Rumble(unsigned int low,
				unsigned int high,
				float secs);

	void Update(float secsPassed);
};

#endif