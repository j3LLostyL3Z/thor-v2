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

void ThorWorkerThread::run()
{
	Logger::writeToLog (String::formatted (T("files:%d"), files.size()));

	for (int p=0; p<files.size(); p++)
	{
		Logger::writeToLog (files[p]->getFullPathName());
		File *inFile = new File (*files[p]);
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

bool ThorWorkerThread::convertAudioFile (File *in, File *out)
{
	if (in->exists())
	{
		InputStream *inStream = in->createInputStream();
		if (inStream)
		{
			return (convertAudioFile (inStream, out));
		}
		return (false);
	}
	return (false);
}

bool ThorWorkerThread::convertAudioFile (InputStream *in, File *out)
{
	OutputStream *outStream = 0;
	AudioFormatReader *audioReader = 0;
	AudioFormatWriter *audioWriter = 0;
	bool formatConvertResult = false;
	
	if (in)
	{
		audioReader = formatManager->createReaderFor (in);

		if (audioReader)
		{
			if (out->exists() && out->hasWriteAccess())
			{
				outStream = out->createOutputStream();
				if (outStream)
				{
					switch (getFormat(audioReader))
					{
						case FORMAT_OGG:
							formatConvertResult = ogg2wav(in, outStream);
							break;

						case FORMAT_FLAC:
							formatConvertResult = flac2wav(in, outStream);
							break;

						case FORMAT_WAV:
							formatConvertResult = any2wav (in, outStream);
							break;

						default:
							formatConvertResult = false;
							break;
					}
					return (formatConvertResult);

					/* end of output stream check */
				}
				/* end of output file existance and write access check */
			}
			/* end of audio reader check */
		}
		/* end of inStream check */
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
	WavAudioFormat *wavReader = new WavAudioFormat();
	AudioFormatReader *wavFormatReader = wavReader->createReaderFor (in, false);

	return (false);
}

bool ThorWorkerThread::wav2ogg (InputStream *in, OutputStream *out)
{
	WavAudioFormat *wavReader = new WavAudioFormat();
	AudioFormatReader *wavFormatReader = wavReader->createReaderFor (in, false);

	return (false);
}

bool ThorWorkerThread::any2wav (InputStream *in, OutputStream *out)
{
	WavAudioFormat *wavF = new WavAudioFormat();

	return (false);
}

int ThorWorkerThread::getFormat (AudioFormatReader *inFormat)
{
	if (inFormat->getFormatName() == T("WAV file"))
	{
		Logger::writeToLog (T("detected WAV format"));
		return (FORMAT_WAV);
	}

	if (inFormat->getFormatName() == T("FLAC file"))
	{
		Logger::writeToLog (T("detected FLAC format"));
		return (FORMAT_FLAC);
	}

	if (inFormat->getFormatName() == T("Ogg-Vorbis file"))
	{
		Logger::writeToLog (T("detected Ogg format"));
		return (FORMAT_OGG);
	}

	Logger::writeToLog (T("detected UNKNOWN format"));
	return (FORMAT_UNKNOWN);
}