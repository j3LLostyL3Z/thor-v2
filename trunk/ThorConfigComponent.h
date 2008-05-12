/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  12 May 2008 3:16:52 pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.11

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_THORCONFIGCOMPONENT_THORCONFIGCOMPONENT_B43A9D4E__
#define __JUCER_HEADER_THORCONFIGCOMPONENT_THORCONFIGCOMPONENT_B43A9D4E__

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
    Label* label3;
    ComboBox* thorOutputAction;
    Image* internalCachedImage1;

    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    ThorConfigComponent (const ThorConfigComponent&);
    const ThorConfigComponent& operator= (const ThorConfigComponent&);
};


#endif   // __JUCER_HEADER_THORCONFIGCOMPONENT_THORCONFIGCOMPONENT_B43A9D4E__
