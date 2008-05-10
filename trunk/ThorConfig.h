// ThorConfig.h: interface for the ThorConfig class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_THORCONFIG_H__2891A1E0_0890_45CE_9460_AE2A8D3DFDFC__INCLUDED_)
#define AFX_THORCONFIG_H__2891A1E0_0890_45CE_9460_AE2A8D3DFDFC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <juce.h>

class ThorConfig  
{
	public:
		ThorConfig();
		~ThorConfig();
		String getTempDir();
		unsigned int getBuffSize();
		String getFileExtension();
		Rectangle getRect();
		void setRect(Rectangle r);
		int getOggQuality();
		void setOggQuality(int q);
		void setFileExtension (String ext);
		int getWorkerPriority ();
		bool getVersionCheck();
		void setVersionCheck(bool v);
		String getVersionUrl();

	private:
		String defaultEncodeFormat;
		int defaultOggQuality;
		PropertiesFile *thorProperties;
		String defaultTempDir;
		int defaultBufferSize;
		String defaultRectangle;
		int defaultWorkerPriority;
		String defaultVersionUrl;
		bool defaultVersionCheck;
};

#endif // !defined(AFX_THORCONFIG_H__2891A1E0_0890_45CE_9460_AE2A8D3DFDFC__INCLUDED_)
