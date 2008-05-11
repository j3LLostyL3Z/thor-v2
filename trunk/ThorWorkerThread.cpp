// ThorWorkerThread.cpp: implementation of the ThorWorkerThread class.
//
//////////////////////////////////////////////////////////////////////

#include "ThorWorkerThread.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ThorWorkerThread::ThorWorkerThread(ThorConfig *_config) : Thread (T("worker"))
{
	formatManager = new AudioFormatManager ();
	formatManager->registerBasicFormats ();
	config = _config;
}

ThorWorkerThread::~ThorWorkerThread()
{
	if (formatManager)
		deleteAndZero (formatManager);
	files.clear();
}

void ThorWorkerThread::warn (String msg)
{
	AlertWindow::showMessageBox (AlertWindow::WarningIcon, T("Warning!"), msg, T("Ok"));
}

void ThorWorkerThread::warnInWindow (String msg)
{
}

void ThorWorkerThread::run()
{
	Logger::writeToLog (String::formatted (T("files:%d"), files.size()));

	for (int p=0; p<files.size(); p++)
	{
		Logger::writeToLog (files[p]->getFullPathName());

		File *inFile = new File (*files[p]);

		if (!inFile->exists())
		{
			warn (T("Can't open input file: ") + inFile->getFullPathName());

			deleteAndZero (inFile);
			return;
		}

		if (!convertAudioFile (inFile))
		{
			Logger::writeToLog (T("failed to convert: ") +  inFile->getFullPathName());
			warnInWindow (T("failed to convert: ") + inFile->getFullPathName());
		}
		else
		{
			Logger::writeToLog (T("successfully converted: ") +  inFile->getFullPathName());
			warnInWindow(T("success: ") + inFile->getFullPathName());
		}
		/* do the conversion */

		deleteAndZero (inFile);
	}
}

void ThorWorkerThread::setFile(const File f)
{
	inputFile = new File(f);
}

void ThorWorkerThread::setOutputDir (const File f)
{
	outputDir = new File(f);
}

double ThorWorkerThread::getProcProgress()
{
	return (procProgress);
}

void ThorWorkerThread::addFile (const File f)
{
	File *ptrF = new File (f);
	files.add(ptrF);
}

void ThorWorkerThread::clearFileList()
{
	if (!isThreadRunning())
	{
		files.clear();
	}
}

bool ThorWorkerThread::convertAudioFile (File *in)
{
	Logger::writeToLog (T("converting"));
	OutputStream *outStream = 0;

	if (in->exists())
	{
		bool ret;
		InputStream *inStream = in->createInputStream();

		if (inStream)
		{
			if (in->hasFileExtension (T("wav")))
			{
				File *outFile = new File (in->withFileExtension (config->getFileExtension()));

				if (outFile->exists())
				{
					int k = AlertWindow::showYesNoCancelBox (AlertWindow::WarningIcon, T("Warning!"), T("Target file exists, overwrite?"), T("Yes"), T("No"), T("Cancel"));
				
					if (k == 0 || k == 2)
					{
						if (outFile)
							deleteAndZero (outFile);

						if (inStream)
							deleteAndZero (inStream);

						return (false);
					}
				}
				outStream = outFile->createOutputStream();

				if (outFile && outStream)
				{
					ret = wav2any (inStream, outStream);

					deleteAndZero (outStream);
					deleteAndZero (outFile);
				}
				else
				{
					deleteAndZero (inStream);
					return (false);
				}
			}

			if (in->hasFileExtension (T("flac")))
			{
				File *outFile = new File (in->withFileExtension (T("wav")));

				if (outFile->exists())
				{
					int k = AlertWindow::showYesNoCancelBox (AlertWindow::WarningIcon, T("Warning!"), T("Target file exists, overwrite?"), T("Yes"), T("No"), T("Cancel"));
				
					if (k == 0 || k == 2)
					{
						if (outFile)
							deleteAndZero (outFile);

						if (inStream)
							deleteAndZero (inStream);

						return (false);
					}
				}
				outStream = outFile->createOutputStream();

				if (outFile && outStream)
				{
					ret = flac2wav (inStream, outStream);

					deleteAndZero (outStream);
					deleteAndZero (outFile);
				}
				else
				{
					deleteAndZero (inStream);
					return (false);
				}
			}

			if (in->hasFileExtension (T("ogg")))
			{
				File *outFile = new File (in->withFileExtension (T("wav")));

				if (outFile->exists())
				{
					int k = AlertWindow::showYesNoCancelBox (AlertWindow::WarningIcon, T("Warning!"), T("Target file exists, overwrite?"), T("Yes"), T("No"), T("Cancel"));
				
					if (k == 0 || k == 2)
					{
						if (outFile)
							deleteAndZero (outFile);

						if (inStream)
							deleteAndZero (inStream);

						return (false);
					}
				}
				outStream = outFile->createOutputStream();

				if (outFile && outStream)
				{
					ret = ogg2wav (inStream, outStream);

					deleteAndZero (outStream);
					deleteAndZero (outFile);
				}
				else
				{
					deleteAndZero (inStream);
					return (false);
				}
			}

			deleteAndZero (inStream);
			return (ret);
		}
		else
		{
			return (false);
		}
	}
	return (false);
}

bool ThorWorkerThread::ogg2wav (InputStream *in, OutputStream *out)
{
	OggVorbisAudioFormat *oggReader = new OggVorbisAudioFormat();
	AudioFormatReader *oggFormatReader = oggReader->createReaderFor (in, false);
	
	if (!oggFormatReader)
	{
		return (false);
	}

	WavAudioFormat *wavF = new WavAudioFormat();
	AudioFormatWriter *wavFormatWriter = wavF->createWriterFor (out, oggFormatReader->sampleRate, oggFormatReader->numChannels, oggFormatReader->bitsPerSample, 0, (int)1);

	if (!wavFormatWriter)
	{
		return (false);
	}

	AudioSampleBuffer *ioBuff = new AudioSampleBuffer (oggFormatReader->numChannels, (int)oggFormatReader->lengthInSamples);

	if (!ioBuff)
	{
		return (false);
	}

	for (int64 k=0; k<oggFormatReader->lengthInSamples; k=k+config->getBuffSize())
	{
		if (threadShouldExit())
		{			
			procProgress = 0;
			sendChangeMessage (this);
			return (true);
		}

		if ((oggFormatReader->lengthInSamples - k) < config->getBuffSize())
		{
			ioBuff->readFromAudioReader (oggFormatReader, (int)k, (int)(oggFormatReader->lengthInSamples - k), (int)k, true, true);
			if (wavFormatWriter)
			{
				ioBuff->writeToAudioWriter (wavFormatWriter, (int)k, (int)oggFormatReader->lengthInSamples - (int)k);
			}

			procProgress = 1.0f;
			sendChangeMessage (this);

			return (true);
		}
		else
		{
			ioBuff->readFromAudioReader (oggFormatReader, (int)k, config->getBuffSize(), (int)k, true, true);
			if (wavFormatWriter)
			{
				ioBuff->writeToAudioWriter (wavFormatWriter, (int)k, config->getBuffSize());
			}

			procProgress = (float)k/oggFormatReader->lengthInSamples;
			sendChangeMessage (this);
		}

		/* we need to exit ? */
		if (threadShouldExit())
		{
			procProgress = 0;
			sendChangeMessage (this);
			return (true);
		}
	}

	return (true);
}

bool ThorWorkerThread::flac2wav (InputStream *in, OutputStream *out)
{
	FlacAudioFormat *flacReader = new FlacAudioFormat();
	AudioFormatReader *flacFormatReader = flacReader->createReaderFor (in, false);

	WavAudioFormat *wavF = new WavAudioFormat();
	AudioFormatWriter *wavFormatWriter = wavF->createWriterFor (out, flacFormatReader->sampleRate, flacFormatReader->numChannels, flacFormatReader->bitsPerSample, 0, (int)1);

	return (false);
}

bool ThorWorkerThread::wav2flac (InputStream *in, OutputStream *out)
{
	Logger::writeToLog (String::formatted (T("wav2flac() in size: %d"), in->getTotalLength()));

	WavAudioFormat *wavReader = new WavAudioFormat();
	AudioFormatReader *wavFormatReader = wavReader->createReaderFor (in, false);

	if (!wavFormatReader)
	{
		Logger::writeToLog (T("can't create audioFormatReader"));
		return (false);
	}

	FlacAudioFormat *flacWriter = new FlacAudioFormat();
	AudioFormatWriter *flacFormatWriter = flacWriter->createWriterFor (out, wavFormatReader->sampleRate, wavFormatReader->numChannels, wavFormatReader->bitsPerSample, 0, (int)1);
	
	if (!flacFormatWriter)
	{
		Logger::writeToLog (T("can't create audioFormatWriter"));
		return (false);
	}

	AudioSampleBuffer *ioBuff = new AudioSampleBuffer (wavFormatReader->numChannels, (int)wavFormatReader->lengthInSamples);

	if (!ioBuff)
	{
		Logger::writeToLog (T("can't create AudioSampleBuffer"));
		return (false);
	}

	for (int64 k=0; k<wavFormatReader->lengthInSamples; k=k+config->getBuffSize())
	{
		Logger::writeToLog (String::formatted (T("write portion: %d"), k));
		if (threadShouldExit())
		{			
			procProgress = 0;
			sendChangeMessage (this);

			return (false);
		}

		if ((wavFormatReader->lengthInSamples - k) < config->getBuffSize())
		{
			ioBuff->readFromAudioReader (wavFormatReader, (int)k, (int)(wavFormatReader->lengthInSamples - k), (int)k, true, true);
			if (flacFormatWriter)
			{
				ioBuff->writeToAudioWriter (flacFormatWriter, (int)k, (int)wavFormatReader->lengthInSamples - (int)k);
			}

			procProgress = 1.0f;
			sendChangeMessage (this);

			Logger::writeToLog (String::formatted (T("progress: %.4f"), procProgress));

			return (true);
		}
		else
		{
			ioBuff->readFromAudioReader (wavFormatReader, (int)k, config->getBuffSize(), (int)k, true, true);

			if (flacFormatWriter)
			{
				ioBuff->writeToAudioWriter (flacFormatWriter, (int)k, config->getBuffSize());
			}

			procProgress = (float)k/wavFormatReader->lengthInSamples;
			sendChangeMessage (this);

			Logger::writeToLog (String::formatted (T("progress: %.4f"), procProgress));
		}

		/* we need to exit ? */
		if (threadShouldExit())
		{
			procProgress = 0;
			sendChangeMessage (this);

			return (false);
		}
	}

	return (false);
}

bool ThorWorkerThread::wav2ogg (InputStream *in, OutputStream *out)
{	
	Logger::writeToLog (String::formatted (T("wav2ogg() in size: %d"), in->getTotalLength()));

	WavAudioFormat *wavReader = new WavAudioFormat();
	AudioFormatReader *wavFormatReader = wavReader->createReaderFor (in, false);

	if (!wavFormatReader)
	{
		Logger::writeToLog (T("can't create audioFormatReader"));

		deleteAndZero (in);
		deleteAndZero (out);
		return (false);
	}

	OggVorbisAudioFormat *oggWriter = new OggVorbisAudioFormat();
	AudioFormatWriter *oggFormatWriter = oggWriter->createWriterFor (out, wavFormatReader->sampleRate, wavFormatReader->numChannels, wavFormatReader->bitsPerSample, 0, (int)config->getOggQuality());
	
	if (!oggFormatWriter)
	{
		Logger::writeToLog (T("can't create audioFormatWriter"));
		return (false);
	}

	AudioSampleBuffer *ioBuff = new AudioSampleBuffer (wavFormatReader->numChannels, (int)wavFormatReader->lengthInSamples);

	if (!ioBuff)
	{
		Logger::writeToLog (T("can't create AudioSampleBuffer"));
		return (false);
	}

	for (int64 k=0; k<wavFormatReader->lengthInSamples; k=k+config->getBuffSize())
	{
		if (threadShouldExit())
		{			
			procProgress = 0;
			sendChangeMessage (this);
			return (true);
		}

		if ((wavFormatReader->lengthInSamples - k) < config->getBuffSize())
		{
			ioBuff->readFromAudioReader (wavFormatReader, (int)k, (int)(wavFormatReader->lengthInSamples - k), (int)k, true, true);
			if (oggFormatWriter)
			{
				ioBuff->writeToAudioWriter (oggFormatWriter, (int)k, (int)wavFormatReader->lengthInSamples - (int)k);
			}

			procProgress = 1.0f;
			sendChangeMessage (this);

			return (true);
		}
		else
		{
			ioBuff->readFromAudioReader (wavFormatReader, (int)k, config->getBuffSize(), (int)k, true, true);
			if (oggFormatWriter)
			{
				ioBuff->writeToAudioWriter (oggFormatWriter, (int)k, config->getBuffSize());
			}

			procProgress = (float)k/wavFormatReader->lengthInSamples;
			sendChangeMessage (this);
		}

		/* we need to exit ? */
		if (threadShouldExit())
		{
			procProgress = 0;
			sendChangeMessage (this);
			return (true);
		}
	}

	return (false);
}

bool ThorWorkerThread::wav2any (InputStream *in, OutputStream *out)
{
	if (config->getFileExtension() == T("flac"))
	{
		return (wav2flac (in, out));
	}
	
	if (config->getFileExtension() == T("ogg"))
	{
		return (wav2ogg (in, out));
	}

	return (false);
}
