/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  12 May 2008 2:04:09 pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.11

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_THORMAINCOMPONENT_THORMAINCOMPONENT_D485A84D__
#define __JUCER_HEADER_THORMAINCOMPONENT_THORMAINCOMPONENT_D485A84D__

//[Headers]     -- You can add your own extra header files here --
#include "juce.h"
#include "ThorWorkerThread.h"
#include "ThorConfig.h"
#include "ThorConfigDialog.h"
#include "ThorUpdateThread.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class ThorMainComponent  : public Component,
                           public FileDragAndDropTarget,
                           public ChangeListener,
                           public ButtonListener
{
public:
    //==============================================================================
    ThorMainComponent (ThorConfig *_config);
    ~ThorMainComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void mouseDown (const MouseEvent& e);
    void mouseDrag (const MouseEvent& e);
	bool isInterestedInFileDrag (const StringArray &files);
	void fileDragEnter (const StringArray &files, int x, int y);
	void fileDragMove (const StringArray &files, int x, int y);
	void fileDragExit (const StringArray &files);
	void filesDropped (const StringArray &files, int x, int y);

	bool isZip (const File f);
	bool isCompressedAudio (const File f);
	bool isUncompressedAudio (const File f);

	void changeListenerCallback(void *ptr);
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);

    // Binary resources:
    static const char* bg_png;
    static const int bg_pngSize;
    static const char* help_png;
    static const int help_pngSize;
    static const char* burn_png;
    static const int burn_pngSize;
    static const char* options_png;
    static const int options_pngSize;
    static const char* news_item_pic_png;
    static const int news_item_pic_pngSize;
    static const char* processstop_png;
    static const int processstop_pngSize;

    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	ComponentDragger myDragger;
	Image *optionsImage;
	Image *leftImage;
	Image *rightImage;
	Image *exitImage;
	Image *helpImage;
	Image *splashImage;
	ProgressBar *thorProgressBar;
	double progressVar;
	ThorWorkerThread *worker;
	int thorMode;
	ThorConfig *config;
	TooltipWindow tooltipWindow;
	ThorConfigDialog *configDialog;
	ThorUpdateThread *updateThread;
    //[/UserVariables]

    //==============================================================================
    Label* thorDebug;
    ImageButton* thorStop;
    Label* thorDetails;
    Image* internalCachedImage1;
	
    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    ThorMainComponent (const ThorMainComponent&);
    const ThorMainComponent& operator= (const ThorMainComponent&);
};


#endif   // __JUCER_HEADER_THORMAINCOMPONENT_THORMAINCOMPONENT_D485A84D__
