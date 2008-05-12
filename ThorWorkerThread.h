// ThorWorkerThread.h: interface for the ThorWorkerThread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_THORWORKERTHREAD_H__D9DF0B9E_6B5E_41E6_9C8D_E7CDF523D487__INCLUDED_)
#define AFX_THORWORKERTHREAD_H__D9DF0B9E_6B5E_41E6_9C8D_E7CDF523D487__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <juce.h>
#include "ThorConfig.h"
#include "zip/zip.h"

#define FORMAT_OGG		0
#define FORMAT_FLAC		1
#define FORMAT_WAV		2
#define FORMAT_UNKNOWN	1040

class ThorWorkerThread : public Thread  , public ChangeBroadcaster
{
	public:
		ThorWorkerThread(ThorConfig *_config);
		virtual ~ThorWorkerThread();
		void run();
		void setFile (const File f);
		void setOutputDir (const File f);
		double getProcProgress();
		void addFile (const File f);
		void clearFileList();
		bool convertAudioFile (InputStream *in, File *out);
		bool convertAudioFile (File *in);
		bool wav2flac (InputStream *in, OutputStream *out);
		bool wav2ogg (InputStream *in, OutputStream *out);
		bool ogg2wav (InputStream *in, OutputStream *out);
		bool flac2wav (InputStream *in, OutputStream *out);
		bool wav2any (InputStream *in, OutputStream *out);
		bool zip2any (File *in);
		void warn (String msg);
		void warnInWindow (String msg);
		bool convertAudioFile (InputStream *in, File *out, int t);
		String getStatusString();
	private:
		File *inputFile;
		File *outputDir;
		AudioFormatManager *formatManager;
		float procProgress;
		ThorConfig *config;
		String processingFileName;
		String processingArchive;
		OwnedArray <File> files;
};

#endif // !defined(AFX_THORWORKERTHREAD_H__D9DF0B9E_6B5E_41E6_9C8D_E7CDF523D487__INCLUDED_)
