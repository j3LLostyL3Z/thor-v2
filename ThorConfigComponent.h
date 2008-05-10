/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  5 May 2008 9:33:25 pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.11

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_THORCONFIGCOMPONENT_THORCONFIGCOMPONENT_6B5AAD41__
#define __JUCER_HEADER_THORCONFIGCOMPONENT_THORCONFIGCOMPONENT_6B5AAD41__

//[Headers]     -- You can add your own extra header files here --
#include "juce.h"
#include "ThorConfig.h"
#include "ThorAbout.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class ThorConfigComponent  : public Component,
                             public ComboBoxListener,
                             public ButtonListener
{
public:
    //==============================================================================
    ThorConfigComponent (ThorConfig *_config);
    ~ThorConfigComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
    void buttonClicked (Button* buttonThatWasClicked);

    // Binary resources:
    static const char* vorbis_png;
    static const int vorbis_pngSize;

    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	ThorConfig *config;
    //[/UserVariables]

    //==============================================================================
    Label* label;
    ComboBox* thorConfigEncodeFormat;
    Label* label2;
    ComboBox* thorOggQuality;
    ToggleButton* thorVersionCheck;
    Image* internalCachedImage1;

    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    ThorConfigComponent (const ThorConfigComponent&);
    const ThorConfigComponent& operator= (const ThorConfigComponent&);
};


#endif   // __JUCER_HEADER_THORCONFIGCOMPONENT_THORCONFIGCOMPONENT_6B5AAD41__
