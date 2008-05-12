// ThorWorkerThread.cpp: implementation of the ThorWorkerThread class.
//
//////////////////////////////////////////////////////////////////////

#include "ThorWorkerThread.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ThorWorkerThread::ThorWorkerThread(ThorConfig *_config) : Thread (T("worker"))
{
	processingFileName = String::empty;
	processingArchive = String::empty;

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
		bool ret;
		if (!inFile->exists())
		{
			warn (T("Can't open input file: ") + inFile->getFullPathName());

			deleteAndZero (inFile);
			return;
		}

		if (inFile->hasFileExtension (T("zip")))
		{
			ret = zip2any (inFile);

			if (threadShouldExit())
			{
				deleteAndZero (inFile);
				return;
			}
			Logger::writeToLog (T("zip: ") +  inFile->getFullPathName());
		}
		else
		{
			ret = convertAudioFile (inFile);

			if (threadShouldExit())
			{
				deleteAndZero (inFile);
				return;
			}
			Logger::writeToLog (T("audio: ") + inFile->getFullPathName());
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

bool ThorWorkerThread::zip2any (File *in)
{
	Logger::writeToLog (T("zip2any()"));

	ZipFile *zIn = new ZipFile (*in);
	bool ret;
	zHandle = 0;

	if (zIn)
	{
		processingArchive = in->getFullPathName();

		for (int k=0; k<zIn->getNumEntries(); k++)
		{
			if (threadShouldExit())
			{
				deleteAndZero (zIn);
				return (false);
			}

			const ZipFile::ZipEntry *zInEntry = zIn->getEntry(k);
			
			Logger::writeToLog (T("entry: ") + zInEntry->filename);

			if (zInEntry)
			{
				Logger::writeToLog (T("entry is valid"));

				InputStream *inStream = zIn->createStreamForEntry(k);
				String fName = zInEntry->filename;
				processingFileName = fName;

				File *outFile = 0;

				if (inStream)
				{
					Logger::writeToLog (T("in stream is valid"));

					if (fName.toLowerCase().endsWith (T("wav")))
					{
						File *outDir = new File (in->withFileExtension(String::empty));
						File *outFile = new File (outDir->getFullPathName() + T("/") + fName.upToFirstOccurrenceOf (T(".wav"), false, true) + T(".") + config->getFileExtension());
						
						if (!outDir->exists())
						{
							outDir->createDirectory();
						}

						if (outFile->exists())
						{
							int k = AlertWindow::showYesNoCancelBox (AlertWindow::WarningIcon, T("Warning!"), T("Target file exists, overwrite?"), T("Yes"), T("No"), T("Cancel"));
		
							if (k == 0 || k == 2)
							{
								if (outFile)
									deleteAndZero (outFile);
								if (inStream)
									deleteAndZero (inStream);
								if (zHandle)
									CloseZip (zHandle);
								return (false);
							}
						}

						Logger::writeToLog (T("convert: ") + fName);
						ret = convertAudioFile (inStream, outFile, FORMAT_WAV);

						zipOutput (in, outFile);

						if (outFile)
							deleteAndZero (outFile);
						if (inStream)
							deleteAndZero (inStream);
					}
					else if (fName.toLowerCase().endsWith (T("flac")))
					{
						File *outDir = new File (in->withFileExtension(String::empty));
						File *outFile = new File (outDir->getFullPathName() + T("/") + fName.upToFirstOccurrenceOf (T(".flac"), false, true) + T(".wav"));
						
						if (!outDir->exists())
						{
							outDir->createDirectory();
						}

						if (outFile->exists())
						{
							int k = AlertWindow::showYesNoCancelBox (AlertWindow::WarningIcon, T("Warning!"), T("Target file exists, overwrite?"), T("Yes"), T("No"), T("Cancel"));
		
							if (k == 0 || k == 2)
							{
								if (outFile)
									deleteAndZero (outFile);
								if (inStream)
									deleteAndZero (inStream);
								if (zHandle)
									CloseZip (zHandle);
								return (false);
							}
						}

						Logger::writeToLog (T("convert: ") + fName);
						ret = convertAudioFile (inStream, outFile, FORMAT_WAV);

						zipOutput (in, outFile);

						if (outFile)
							deleteAndZero (outFile);

						continue;
					}
					else if (fName.toLowerCase().endsWith (T("ogg")))
					{
						Logger::writeToLog (T("ogg()"));
						File *outDir = new File (in->withFileExtension(String::empty));
						File *outFile = new File (outDir->getFullPathName() + T("/") + fName.upToFirstOccurrenceOf (T(".ogg"), false, true) + T(".wav"));
						
						if (!outDir->exists())
						{
							outDir->createDirectory();
						}

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

						Logger::writeToLog (T("convert: ") + fName);
						ret = convertAudioFile (inStream, outFile, FORMAT_OGG);

						zipOutput (in, outFile);

						if (outFile)
							deleteAndZero (outFile);
						if (inStream)
							deleteAndZero (inStream);
					}
					else
					{
						/* non-audio file, just move it from zip to directory */
						Logger::writeToLog (T("non-audio()"));
						File *outDir = new File (in->withFileExtension(String::empty));
						File *outFile = new File (outDir->getFullPathName() + T("/") + fName);
						
						if (!outDir->exists())
						{
							outDir->createDirectory();
						}

						if (outFile->exists())
						{
							int k = AlertWindow::showYesNoCancelBox (AlertWindow::WarningIcon, T("Warning!"), T("Target file exists, overwrite?"), T("Yes"), T("No"), T("Cancel"));
		
							if (k == 0 || k == 2)
							{
								if (outFile)
									deleteAndZero (outFile);
								if (inStream)
									deleteAndZero (inStream);
								if (zHandle)
									CloseZip (zHandle);
								return (false);
							}
						}

						OutputStream *outStream = outFile->createOutputStream();

						if (outStream)
						{
							outStream->writeFromInputStream (*inStream, -1);
						}

						if (outStream)
							deleteAndZero (outStream);

						zipOutput (in, outFile);

						if (outFile)
							deleteAndZero (outFile);
						if (inStream)
							deleteAndZero (inStream);
					}
					Logger::writeToLog (T("end one loop run"));
				}
			}
		}

		deleteAndZero (zIn);
		if (zHandle)
			CloseZip (zHandle);
		processingArchive = String::empty;
		processingFileName = String::empty;
		return (true);
	}
	else
	{
		if (zHandle)
			CloseZip (zHandle);
		return (false);
	}
}

bool ThorWorkerThread::convertAudioFile (InputStream *in, File *out, int t)
{
	Logger::writeToLog (T("convert audio from stream base"));
	OutputStream *outStream = 0;
	bool ret;

	outStream = out->createOutputStream();

	if (!outStream)
	{
		return (false);
	}

	switch (t)
	{
		case FORMAT_WAV:
			ret = wav2any (in, outStream);
			break;
		case FORMAT_FLAC:
			ret = flac2wav (in, outStream);
			break;
		case FORMAT_OGG:
			ret = ogg2wav (in, outStream);
			break;
		case FORMAT_UNKNOWN:
			break;
		default:
			break;
	}

	if (outStream)
		deleteAndZero (outStream);

	return (ret);
}

bool ThorWorkerThread::convertAudioFile (File *in)
{
	Logger::writeToLog (T("converting"));
	OutputStream *outStream = 0;

	if (in->exists())
	{
		bool ret;
		InputStream *inStream = in->createInputStream();
		processingFileName = in->getFullPathName();

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
		samplesRead	= k;
		samplesToRead = oggFormatReader->lengthInSamples;

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

	return (false);
}

bool ThorWorkerThread::flac2wav (InputStream *in, OutputStream *out)
{
	FlacAudioFormat *flacReader = new FlacAudioFormat();
	AudioFormatReader *flacFormatReader = flacReader->createReaderFor (in, false);
	
	if (!flacFormatReader)
	{
		return (false);
	}

	WavAudioFormat *wavF = new WavAudioFormat();
	AudioFormatWriter *wavFormatWriter = wavF->createWriterFor (out, flacFormatReader->sampleRate, flacFormatReader->numChannels, flacFormatReader->bitsPerSample, 0, (int)1);

	if (!wavFormatWriter)
	{
		return (false);
	}

	AudioSampleBuffer *ioBuff = new AudioSampleBuffer (flacFormatReader->numChannels, (int)flacFormatReader->lengthInSamples);

	if (!ioBuff)
	{
		return (false);
	}

	for (int64 k=0; k<flacFormatReader->lengthInSamples; k=k+config->getBuffSize())
	{
		samplesRead	= k;
		samplesToRead = flacFormatReader->lengthInSamples;

		if (threadShouldExit())
		{			
			procProgress = 0;
			sendChangeMessage (this);
			return (true);
		}

		if ((flacFormatReader->lengthInSamples - k) < config->getBuffSize())
		{
			ioBuff->readFromAudioReader (flacFormatReader, (int)k, (int)(flacFormatReader->lengthInSamples - k), (int)k, true, true);
			if (wavFormatWriter)
			{
				ioBuff->writeToAudioWriter (wavFormatWriter, (int)k, (int)flacFormatReader->lengthInSamples - (int)k);
			}

			procProgress = 1.0f;
			sendChangeMessage (this);

			return (true);
		}
		else
		{
			ioBuff->readFromAudioReader (flacFormatReader, (int)k, config->getBuffSize(), (int)k, true, true);
			if (wavFormatWriter)
			{
				ioBuff->writeToAudioWriter (wavFormatWriter, (int)k, config->getBuffSize());
			}

			procProgress = (float)k/flacFormatReader->lengthInSamples;
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
		samplesRead	= k;
		samplesToRead = wavFormatReader->lengthInSamples;
		
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
		samplesRead	= k;
		samplesToRead = wavFormatReader->lengthInSamples;

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

String ThorWorkerThread::getStatusString()
{
	return (processingArchive + T("::") + processingFileName);
}

int64 ThorWorkerThread::getSamplesRead()
{
	return (samplesRead);
}

int64 ThorWorkerThread::getSamplesToRead()
{
	return (samplesToRead);
}

void ThorWorkerThread::zipOutput (File *inZip, File *f)
{
	if (config->getDefaultOutputAction() == 0 || config->getDefaultOutputAction() == 2)
	{
		if (!zHandle)
		{
			zHandle = CreateZip (inZip->withFileExtension (T(".thor.zip")).getFullPathName(), 0);
			if (!zHandle)
				return;
		}
		String fPath = f->getFullPathName();
		String fName = f->getFileName();

		ZipAdd (zHandle, fName, fPath);
	}
	else
	{
		return;
	}
}