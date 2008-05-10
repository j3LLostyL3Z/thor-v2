/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  5 May 2008 7:57:03 pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.11

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_THORABOUT_THORABOUT_37E850BF__
#define __JUCER_HEADER_THORABOUT_THORABOUT_37E850BF__

//[Headers]     -- You can add your own extra header files here --
#include "juce.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class ThorAbout  : public Component
{
public:
    //==============================================================================
    ThorAbout ();
    ~ThorAbout();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();

    // Binary resources:
    static const char* news_item_pic_png;
    static const int news_item_pic_pngSize;

    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    Label* label;
    HyperlinkButton* hyperlinkButton;
    Image* internalCachedImage2;

    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    ThorAbout (const ThorAbout&);
    const ThorAbout& operator= (const ThorAbout&);
};


#endif   // __JUCER_HEADER_THORABOUT_THORABOUT_37E850BF__
