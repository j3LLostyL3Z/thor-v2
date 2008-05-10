// ThorUpdateThread.h: interface for the ThorUpdateThread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_THORUPDATETHREAD_H__645DF8D5_F418_4AF9_B5D4_D9310E6F9DBD__INCLUDED_)
#define AFX_THORUPDATETHREAD_H__645DF8D5_F418_4AF9_B5D4_D9310E6F9DBD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <juce.h>
#include "ThorConfig.h"

class ThorUpdateThread : public Thread, public Timer
{
	public:
		ThorUpdateThread(ThorConfig *_config);
		~ThorUpdateThread();
		void run();
		void timerCallback();

	private:
		URL *updateUrl;
		ThorConfig *config;
};

#endif // !defined(AFX_THORUPDATETHREAD_H__645DF8D5_F418_4AF9_B5D4_D9310E6F9DBD__INCLUDED_)
