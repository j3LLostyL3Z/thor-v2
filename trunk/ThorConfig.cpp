// ThorConfig.cpp: implementation of the ThorConfig class.
//
//////////////////////////////////////////////////////////////////////

#include "ThorConfig.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ThorConfig::ThorConfig()
{
	
	thorProperties = 0;
	File f (PropertiesFile::getDefaultAppSettingsFile (T("thor"), T("settings"), String::empty, false));

	if (!f.existsAsFile())
	{
		f.create();
	}

	thorProperties = new PropertiesFile (f, 0, PropertiesFile::storeAsXML);

	defaultEncodeFormat		= thorProperties->getValue (T("defaultEncodeFormat"), T("flac"));
	defaultOggQuality		= thorProperties->getIntValue (T("defaultOggQuality"), 1);
	defaultBufferSize		= thorProperties->getIntValue (T("defaultBufferSize"), 4096);
	defaultTempDir			= thorProperties->getValue (T("defaultTempDir"), T("/thorOut"));
	defaultRectangle		= thorProperties->getValue (T("defaultRectangle"), T("10 10 130 172"));
	defaultWorkerPriority	= thorProperties->getIntValue (T("defaultWorkerPriority"), 5);
	defaultVersionUrl		= thorProperties->getValue (T("defaultVersionUrl"), T("http://svn.sndlab.com/thor"));
	defaultVersionCheck		= thorProperties->getBoolValue (T("defaultVersionCheck"), 0);
	defaultWindowAlpha		= thorProperties->getDoubleValue (T("defaultWindowAlpha"), 1.0);
}

ThorConfig::~ThorConfig()
{
	Logger::writeToLog (T("write settings"));
	thorProperties->setValue (T("defaultEncodeFormat"), defaultEncodeFormat);
	thorProperties->setValue (T("defaultOggQuality"), defaultOggQuality);
	thorProperties->setValue (T("defaultBufferSize"), defaultBufferSize);
	thorProperties->setValue (T("defaultTempDir"), defaultTempDir);
	thorProperties->setValue (T("defaultRectangle"), defaultRectangle);
	thorProperties->setValue (T("defaultWorkerPriority"), defaultWorkerPriority);
	thorProperties->setValue (T("defaultVersionUrl"), defaultVersionUrl);
	thorProperties->setValue (T("defaultVersionCheck"), defaultVersionCheck);
	thorProperties->setValue (T("defaultWindowAlpha"), defaultWindowAlpha);

	thorProperties->save();

	if (thorProperties)
		deleteAndZero (thorProperties);
}

double ThorConfig::getWindowAlpha ()
{
	return (defaultWindowAlpha);
}

String ThorConfig::getTempDir ()
{
	return (defaultTempDir);
}

unsigned int ThorConfig::getBuffSize()
{
	return (defaultBufferSize);
}

String ThorConfig::getFileExtension()
{
	return (defaultEncodeFormat);
}

Rectangle ThorConfig::getRect ()
{
	return (Rectangle::fromString (defaultRectangle));
}

void ThorConfig::setRect (Rectangle rect)
{
	defaultRectangle = rect.toString();
}

int ThorConfig::getOggQuality()
{
	return (defaultOggQuality);
}

void ThorConfig::setOggQuality(int q)
{
	defaultOggQuality = q;
}

void ThorConfig::setFileExtension (String ext)
{
	defaultEncodeFormat = ext.toLowerCase();
}

int ThorConfig::getWorkerPriority ()
{
	return (defaultWorkerPriority);
}

bool ThorConfig::getVersionCheck()
{
	return (defaultVersionCheck);
}

void ThorConfig::setVersionCheck(bool v)
{
	defaultVersionCheck = v;
}

String ThorConfig::getVersionUrl()
{
	return (defaultVersionUrl);
}