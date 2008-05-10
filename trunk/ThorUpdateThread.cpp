// ThorUpdateThread.cpp: implementation of the ThorUpdateThread class.
//
//////////////////////////////////////////////////////////////////////

#include "ThorUpdateThread.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ThorUpdateThread::ThorUpdateThread(ThorConfig *_config) : Thread (T("update"))
{
	config = _config;
	updateUrl = 0;
}

ThorUpdateThread::~ThorUpdateThread()
{
	if (updateUrl)
		deleteAndZero (updateUrl);
}

void ThorUpdateThread::run()
{
	startTimer (5000);

	Logger::writeToLog (T("check for updates"));
	updateUrl = new URL(config->getVersionUrl() + T("/thor.md5"));

	if (threadShouldExit())
	{
		deleteAndZero (updateUrl);
		return;
	}

	String md5 = updateUrl->readEntireTextStream();

	if (threadShouldExit())
	{
		deleteAndZero (updateUrl);
		return;
	}

	if (!md5.isEmpty())
	{
		File exe = File::getSpecialLocation(File::currentExecutableFile);
		MD5 thorMD5 (exe);

		if (threadShouldExit())
		{
			deleteAndZero (updateUrl);
			return;
		}

		String remoteMd5 = md5.upToFirstOccurrenceOf (T(" "), false, true).toLowerCase();
		String localMd5 = thorMD5.toHexString();

		if (threadShouldExit())
		{
			deleteAndZero (updateUrl);
			return;
		}
		
		if (localMd5 != remoteMd5)
		{
			AlertWindow::showMessageBox (AlertWindow::InfoIcon, T("Update"), T("New version of Thor available"), T("Ok"));
		}

		if (threadShouldExit())
		{
			deleteAndZero (updateUrl);
			return;
		}
	}

	deleteAndZero (updateUrl);
	return;
}

void ThorUpdateThread::timerCallback()
{
	Logger::writeToLog (T("timeout reached, exit update thread"));
	if (updateUrl)
		deleteAndZero (updateUrl);

	stopTimer();
	stopThread(150);
	signalThreadShouldExit ();

	return;
}