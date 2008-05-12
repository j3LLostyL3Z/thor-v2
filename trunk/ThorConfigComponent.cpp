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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "ThorConfigComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
ThorConfigComponent::ThorConfigComponent (ThorConfig *_config)
    : label (0),
      thorConfigEncodeFormat (0),
      label2 (0),
      thorOggQuality (0),
      thorVersionCheck (0),
      label3 (0),
      thorOutputAction (0),
      internalCachedImage1 (0)
{
    addAndMakeVisible (label = new Label (T("new label"),
                                          T("Ogg quality")));
    label->setFont (Font (12.0000f, Font::plain));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (thorConfigEncodeFormat = new ComboBox (T("new combo box")));
    thorConfigEncodeFormat->setEditableText (false);
    thorConfigEncodeFormat->setJustificationType (Justification::centredLeft);
    thorConfigEncodeFormat->setTextWhenNothingSelected (String::empty);
    thorConfigEncodeFormat->setTextWhenNoChoicesAvailable (T("(no choices)"));
    thorConfigEncodeFormat->addItem (T("Ogg"), 1);
    thorConfigEncodeFormat->addItem (T("Flac"), 2);
    thorConfigEncodeFormat->addListener (this);

    addAndMakeVisible (label2 = new Label (T("new label"),
                                           T("Encode To:")));
    label2->setFont (Font (12.0000f, Font::plain));
    label2->setJustificationType (Justification::centredLeft);
    label2->setEditable (false, false, false);
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (thorOggQuality = new ComboBox (T("Ogg Quality")));
    thorOggQuality->setEditableText (false);
    thorOggQuality->setJustificationType (Justification::centredLeft);
    thorOggQuality->setTextWhenNothingSelected (String::empty);
    thorOggQuality->setTextWhenNoChoicesAvailable (T("(no choices)"));
    thorOggQuality->addItem (T("Low"), 1);
    thorOggQuality->addItem (T("Medium"), 2);
    thorOggQuality->addItem (T("High"), 3);
    thorOggQuality->addListener (this);

    addAndMakeVisible (thorVersionCheck = new ToggleButton (T("new toggle button")));
    thorVersionCheck->setButtonText (T("version check"));
    thorVersionCheck->addButtonListener (this);
    thorVersionCheck->setToggleState (true, false);

    addAndMakeVisible (label3 = new Label (T("new label"),
                                           T("Output:")));
    label3->setFont (Font (12.0000f, Font::plain));
    label3->setJustificationType (Justification::centredLeft);
    label3->setEditable (false, false, false);
    label3->setColour (TextEditor::textColourId, Colours::black);
    label3->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (thorOutputAction = new ComboBox (T("Ogg Quality")));
    thorOutputAction->setEditableText (false);
    thorOutputAction->setJustificationType (Justification::centredLeft);
    thorOutputAction->setTextWhenNothingSelected (String::empty);
    thorOutputAction->setTextWhenNoChoicesAvailable (T("(no choices)"));
    thorOutputAction->addItem (T("Kepp and create ZIP"), 1);
    thorOutputAction->addItem (T("Keep output DIR (no ZIP)"), 2);
    thorOutputAction->addItem (T("Keep both"), 3);
    thorOutputAction->addListener (this);

    internalCachedImage1 = ImageCache::getFromMemory (vorbis_png, vorbis_pngSize);

    //[UserPreSize]
	config = _config;
    //[/UserPreSize]

    setSize (256, 106);

    //[Constructor] You can add your own custom stuff here..
	thorOggQuality->setSelectedItemIndex (config->getOggQuality(), false);
	thorVersionCheck->setToggleState (config->getVersionCheck(), false);
	thorOutputAction->setSelectedItemIndex (config->getDefaultOutputAction(), false);

	if (config->getFileExtension() == T("flac"))
	{
		thorConfigEncodeFormat->setSelectedId (2);
	}

	if (config->getFileExtension() == T("ogg"))
	{
		thorConfigEncodeFormat->setSelectedId (1);
	}
    //[/Constructor]
}

ThorConfigComponent::~ThorConfigComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    deleteAndZero (label);
    deleteAndZero (thorConfigEncodeFormat);
    deleteAndZero (label2);
    deleteAndZero (thorOggQuality);
    deleteAndZero (thorVersionCheck);
    deleteAndZero (label3);
    deleteAndZero (thorOutputAction);
    ImageCache::release (internalCachedImage1);

    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void ThorConfigComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.setColour (Colours::grey);
    g.drawRoundedRectangle (5.0f, 4.0f, 246.0f, 98.0f, 10.0000f, 3.0000f);

    g.setColour (Colours::black.withAlpha (0.3000f));
    g.drawImage (internalCachedImage1,
                 6, 4, 97, 97,
                 0, 0, internalCachedImage1->getWidth(), internalCachedImage1->getHeight());

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void ThorConfigComponent::resized()
{
    label->setBounds (24, 24, 63, 16);
    thorConfigEncodeFormat->setBounds (128, 27, 112, 16);
    label2->setBounds (136, 11, 63, 16);
    thorOggQuality->setBounds (16, 40, 88, 16);
    thorVersionCheck->setBounds (176, 82, 64, 16);
    label3->setBounds (136, 48, 63, 16);
    thorOutputAction->setBounds (128, 64, 112, 16);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void ThorConfigComponent::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == thorConfigEncodeFormat)
    {
        //[UserComboBoxCode_thorConfigEncodeFormat] -- add your combo box handling code here..
		config->setFileExtension (thorConfigEncodeFormat->getText());
        //[/UserComboBoxCode_thorConfigEncodeFormat]
    }
    else if (comboBoxThatHasChanged == thorOggQuality)
    {
        //[UserComboBoxCode_thorOggQuality] -- add your combo box handling code here..
		config->setOggQuality (thorOggQuality->getSelectedItemIndex());
        //[/UserComboBoxCode_thorOggQuality]
    }
    else if (comboBoxThatHasChanged == thorOutputAction)
    {
        //[UserComboBoxCode_thorOutputAction] -- add your combo box handling code here..
		config->setDefaultOutputAction (thorOutputAction->getSelectedItemIndex());
        //[/UserComboBoxCode_thorOutputAction]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}

void ThorConfigComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == thorVersionCheck)
    {
        //[UserButtonCode_thorVersionCheck] -- add your button handler code here..
		config->setVersionCheck (thorVersionCheck->getToggleState());
        //[/UserButtonCode_thorVersionCheck]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ThorConfigComponent" componentName=""
                 parentClasses="public Component" constructorParams="ThorConfig *_config"
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330000013" fixedSize="1" initialWidth="256"
                 initialHeight="106">
  <BACKGROUND backgroundColour="ffffff">
    <ROUNDRECT pos="5 4 246 98" cornerSize="10" fill="solid: 2aa56f" hasStroke="1"
               stroke="3, mitered, butt" strokeColour="solid: ff808080"/>
    <IMAGE pos="6 4 97 97" resource="vorbis_png" opacity="0.3" mode="0"/>
  </BACKGROUND>
  <LABEL name="new label" id="c8af4e3423af1114" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="24 24 63 16" edTextCol="ff000000"
         edBkgCol="0" labelText="Ogg quality" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="new combo box" id="9801cce4d3b9bab5" memberName="thorConfigEncodeFormat"
            virtualName="" explicitFocusOrder="0" pos="128 27 112 16" editable="0"
            layout="33" items="Ogg&#10;Flac" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="new label" id="f96cbe09a7ab8edf" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="136 11 63 16" edTextCol="ff000000"
         edBkgCol="0" labelText="Encode To:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="12"
         bold="0" italic="0" justification="33"/>
  <COMBOBOX name="Ogg Quality" id="a859280644cb0bc4" memberName="thorOggQuality"
            virtualName="" explicitFocusOrder="0" pos="16 40 88 16" editable="0"
            layout="33" items="Low&#10;Medium&#10;High" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <TOGGLEBUTTON name="new toggle button" id="edb3686e8aab12d" memberName="thorVersionCheck"
                virtualName="" explicitFocusOrder="0" pos="176 82 64 16" buttonText="version check"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="1"/>
  <LABEL name="new label" id="83f67d8edfb4e0" memberName="label3" virtualName=""
         explicitFocusOrder="0" pos="136 48 63 16" edTextCol="ff000000"
         edBkgCol="0" labelText="Output:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="12"
         bold="0" italic="0" justification="33"/>
  <COMBOBOX name="Ogg Quality" id="31caefcfceb806" memberName="thorOutputAction"
            virtualName="" explicitFocusOrder="0" pos="128 64 112 16" editable="0"
            layout="33" items="Kepp and create ZIP&#10;Keep output DIR (no ZIP)&#10;Keep both"
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif

//==============================================================================
// Binary resources - be careful not to edit any of these sections!

// JUCER_RESOURCE: vorbis_png, 5411, "C:\media\vorbis.png"
static const unsigned char resource_ThorConfigComponent_vorbis_png[] = { 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,96,0,0,0,96,8,6,0,0,0,226,152,119,56,0,0,0,1,115,82,71,66,0,174,206,28,233,
0,0,0,6,98,75,71,68,0,255,0,255,0,255,160,189,167,147,0,0,0,9,112,72,89,115,0,0,11,19,0,0,11,19,1,0,154,156,24,0,0,0,7,116,73,77,69,7,216,5,4,20,5,45,86,188,143,89,0,0,20,163,73,68,65,84,120,218,237,157,
121,120,84,229,189,199,63,103,150,204,62,147,109,178,1,217,200,2,38,33,32,136,128,86,110,181,184,64,177,245,90,92,90,90,107,125,212,167,98,107,173,86,171,118,185,94,111,185,106,173,182,94,173,189,214,
214,218,86,110,41,86,105,113,1,23,68,92,89,76,9,16,33,9,129,44,144,117,146,201,172,153,229,204,156,251,199,36,3,147,89,146,88,50,33,237,252,158,39,79,158,156,115,222,115,206,251,253,190,191,247,253,109,
231,141,32,73,18,41,153,58,145,165,32,72,17,144,34,32,37,41,2,82,4,164,36,69,64,138,128,148,164,8,72,17,144,146,20,1,41,2,82,146,34,96,92,242,220,166,87,165,197,43,191,33,13,218,157,165,41,2,166,0,252,
91,239,125,20,139,197,193,197,215,124,187,101,186,146,32,76,199,104,232,8,248,165,133,101,200,101,114,6,109,189,100,103,27,216,253,234,111,133,148,6,36,25,124,128,116,83,14,22,139,131,27,238,92,47,165,
52,32,73,224,43,84,42,36,189,241,100,71,134,134,176,246,180,241,217,11,22,240,155,71,238,21,82,4,76,18,248,229,11,150,82,124,209,66,10,74,243,201,51,43,194,231,237,142,32,61,93,118,142,254,189,137,165,
179,178,120,248,150,171,132,20,1,167,17,252,219,31,125,158,203,214,173,165,108,142,25,165,34,49,182,67,30,17,209,149,198,119,206,153,75,190,81,45,164,8,248,7,228,15,219,118,73,191,254,232,48,159,185,100,
14,26,181,98,66,109,149,182,52,238,94,94,147,34,96,162,226,106,126,77,146,124,118,92,65,45,127,253,96,43,115,74,35,223,113,80,145,75,155,126,33,54,101,126,194,251,216,29,65,50,108,34,183,94,178,88,48,
40,229,41,2,198,35,182,189,79,75,134,154,171,145,169,76,0,4,189,54,236,127,91,141,73,209,0,94,55,40,20,32,200,32,32,210,163,44,101,119,250,151,104,50,46,199,35,55,196,189,103,119,159,200,151,203,203,88,
86,156,37,164,8,72,32,206,134,141,146,182,236,210,48,248,35,18,244,218,112,189,183,26,125,166,0,157,205,224,178,129,252,228,116,228,145,212,236,49,93,201,78,243,13,113,239,221,111,13,240,205,170,179,168,
200,209,11,41,2,98,136,216,252,140,228,56,242,42,25,151,189,8,192,35,15,61,68,93,125,61,27,54,108,8,45,172,31,223,130,90,123,108,120,72,183,67,95,107,4,9,72,65,122,228,197,108,201,191,143,30,117,249,184,
215,132,38,251,144,180,215,98,167,195,101,167,207,227,65,12,250,81,200,148,220,84,89,70,133,81,51,233,100,157,25,142,88,215,27,146,188,245,65,212,57,121,17,135,103,23,23,199,190,62,175,16,116,38,144,130,
167,12,37,25,185,193,118,214,30,191,141,10,247,219,49,155,53,219,7,185,225,206,245,146,195,31,224,229,14,139,244,163,186,195,210,239,154,15,113,212,126,28,127,192,78,186,210,71,182,74,34,77,230,255,23,
210,0,223,96,169,244,206,162,22,102,150,227,238,11,160,89,188,9,153,58,114,10,18,109,29,248,247,95,139,58,251,228,60,47,137,34,194,161,15,34,181,224,20,109,104,75,171,225,221,172,175,211,166,91,8,128,
63,8,22,175,140,214,189,205,20,84,205,162,40,51,45,238,43,13,250,211,120,228,156,228,88,79,83,78,128,180,235,70,137,180,38,80,107,67,157,111,213,96,186,240,217,136,69,216,182,253,122,210,139,135,162,27,
31,111,6,123,95,130,155,7,177,9,102,118,41,206,161,193,120,9,65,99,105,194,197,122,132,168,115,204,69,124,126,86,246,63,39,1,14,127,128,255,109,236,146,108,126,31,158,128,196,146,190,199,249,247,226,166,
136,107,220,125,1,208,84,15,123,85,7,209,154,227,152,144,214,94,56,126,56,182,22,196,146,128,8,64,155,186,150,63,22,254,207,148,143,126,0,69,178,71,252,150,14,139,212,51,212,139,73,41,161,82,192,86,227,
215,9,88,223,98,77,198,91,225,107,66,128,31,10,253,161,143,111,191,191,34,95,137,215,112,62,157,242,74,252,74,53,0,45,234,5,172,232,125,146,47,136,155,162,27,12,19,213,174,153,31,243,126,238,128,192,181,
165,37,73,197,35,233,4,84,154,116,188,212,38,231,44,147,136,82,6,69,186,32,91,236,43,208,218,109,172,50,238,29,247,125,182,138,171,217,167,58,23,70,249,98,198,129,22,46,244,191,6,66,252,105,169,209,112,
65,204,83,153,170,28,22,102,37,215,76,77,186,21,180,48,75,47,148,28,106,228,79,191,125,147,173,159,184,176,249,5,42,141,34,127,241,172,162,201,91,48,174,123,52,4,106,249,56,112,110,212,220,237,26,56,198,
61,3,183,97,16,156,241,29,61,193,28,211,76,109,239,23,185,185,50,63,233,62,66,210,9,120,110,211,171,210,83,143,61,141,174,177,29,247,179,27,121,239,157,22,108,126,129,217,38,37,223,179,172,163,91,204,
72,108,177,6,243,217,42,174,142,4,213,47,80,210,251,87,214,15,92,159,16,124,164,32,59,51,175,139,121,234,157,151,118,240,157,123,30,74,186,69,162,72,54,248,35,241,124,0,89,81,33,126,155,147,70,27,44,206,
134,5,153,18,111,218,255,141,181,153,47,197,183,26,130,30,62,27,248,35,180,127,18,62,102,144,134,40,151,26,67,33,138,4,210,164,94,194,254,140,207,199,60,103,176,137,108,217,249,33,55,220,185,94,74,102,
62,65,49,21,224,203,101,114,200,200,164,228,43,151,82,155,33,2,161,129,167,148,65,145,201,150,240,62,185,244,145,215,250,202,4,109,221,32,77,234,37,108,201,191,47,254,53,42,5,51,115,139,216,242,250,7,
73,37,65,49,37,224,3,88,7,56,182,189,14,225,130,185,168,84,26,0,188,222,33,62,39,237,71,202,23,17,20,145,175,38,137,34,194,96,15,66,87,11,200,100,39,71,123,64,164,77,93,75,187,102,62,3,110,31,111,31,14,
249,15,42,93,38,121,85,249,152,211,68,60,114,99,220,240,196,104,73,54,9,147,238,7,196,4,63,129,172,40,106,161,36,195,202,162,153,3,44,44,28,24,94,97,61,97,27,222,137,145,46,85,9,3,250,74,122,149,101,17,
145,80,191,40,177,229,225,191,130,53,212,78,80,107,208,45,170,161,226,236,82,102,204,208,162,76,48,67,237,216,178,143,129,157,117,39,125,188,158,54,86,95,188,108,210,211,155,147,74,192,68,193,31,215,11,
43,21,8,89,57,100,207,41,36,183,188,128,76,115,8,252,222,163,61,244,119,15,210,187,227,163,216,214,70,81,33,185,181,37,20,84,205,162,32,61,45,130,12,139,87,224,163,63,190,139,239,112,164,67,152,12,18,
38,141,128,63,108,219,37,221,246,31,143,51,75,107,56,109,224,159,54,211,175,168,144,236,146,2,180,217,6,236,189,253,12,28,104,13,107,77,84,180,99,146,73,56,173,4,108,107,236,145,142,12,218,57,100,31,32,
43,67,142,40,6,112,15,9,244,30,237,161,239,88,47,150,166,248,29,61,211,68,80,42,144,244,70,4,167,157,142,227,45,147,70,194,105,33,96,91,99,143,180,253,120,39,106,83,32,97,194,124,200,35,210,218,208,75,
227,142,253,4,187,59,207,60,208,213,26,116,101,179,41,89,90,65,166,217,64,86,134,156,126,107,0,135,211,75,235,190,38,46,90,112,22,183,46,175,22,12,6,195,153,65,64,93,199,160,180,177,233,216,152,192,143,
150,214,14,55,127,127,234,5,36,191,120,198,140,118,243,121,139,152,187,172,146,172,140,216,211,165,95,148,80,42,4,186,251,68,230,26,51,249,218,217,165,167,37,207,60,33,2,130,30,27,67,29,31,72,50,149,137,
250,214,118,234,221,109,204,149,183,225,145,233,233,81,135,156,171,30,117,197,152,33,95,128,29,47,125,130,117,207,222,41,39,65,95,93,77,197,133,213,20,207,210,78,168,93,134,215,200,186,115,203,133,164,
17,224,235,59,32,249,122,63,65,95,117,117,136,12,175,13,199,206,251,48,246,255,102,216,163,152,120,178,188,181,195,205,193,215,235,162,172,143,201,148,98,195,32,231,87,133,194,29,221,185,249,156,95,37,
146,46,246,208,173,43,197,43,25,199,237,51,244,91,3,92,90,80,196,37,149,185,66,82,8,112,54,108,148,70,192,143,80,205,247,191,129,66,219,146,48,89,190,59,243,170,184,68,248,69,137,183,159,223,131,243,224,
193,73,7,127,237,18,129,91,191,125,51,105,230,154,145,65,133,123,199,58,76,129,61,161,11,148,105,32,5,241,160,165,73,119,30,251,141,151,134,51,106,241,222,93,235,82,113,197,220,146,79,157,236,31,155,0,
223,96,169,247,149,21,45,242,11,95,68,97,154,69,107,107,43,247,223,127,63,63,254,241,143,41,46,46,198,217,176,17,157,236,119,195,6,245,9,232,106,137,74,144,216,200,98,75,222,247,227,118,166,181,195,77,
221,227,127,138,161,231,153,232,102,23,96,46,206,71,163,83,133,162,150,13,173,184,246,78,156,172,185,25,22,158,125,242,7,97,240,71,36,156,238,148,15,65,215,145,144,195,55,242,254,49,82,155,241,180,225,
174,133,243,62,85,21,222,152,161,8,105,215,77,45,65,173,15,165,58,84,8,235,116,56,216,188,121,51,119,124,247,187,0,200,13,179,192,53,124,113,246,140,208,239,19,205,161,209,52,44,38,250,89,123,226,118,
182,152,239,138,25,12,155,145,175,97,95,81,33,193,182,118,4,181,6,109,245,108,42,151,85,147,83,160,67,43,31,85,148,101,117,132,31,55,17,240,159,184,222,31,6,127,195,134,13,28,58,120,144,7,214,175,71,97,
154,133,95,59,15,180,199,32,35,7,142,214,195,144,35,52,157,10,50,138,252,13,20,117,221,17,142,37,197,210,228,172,12,57,47,30,234,96,221,185,209,83,215,199,253,78,169,209,230,162,195,101,71,43,19,112,7,
37,190,54,187,136,124,109,154,48,54,1,135,126,46,161,106,67,149,158,131,251,200,86,244,85,87,83,93,83,131,213,106,13,95,18,232,125,13,116,167,180,201,158,1,118,203,201,78,140,136,92,193,234,254,71,152,
231,216,22,53,162,148,10,129,244,37,243,81,213,150,80,188,168,156,124,205,72,181,67,36,248,254,32,244,212,31,155,16,248,5,122,7,191,186,98,59,138,156,53,39,187,117,240,32,175,189,242,42,15,172,95,31,221,
160,180,54,146,4,0,65,70,133,119,55,107,219,191,21,183,236,229,136,251,36,38,77,246,33,105,123,151,149,35,246,126,116,114,95,216,235,182,5,66,125,232,28,242,145,175,77,27,99,10,114,182,74,210,158,85,161,
18,16,192,217,233,66,179,232,121,20,166,89,225,75,92,205,175,161,232,127,144,52,211,40,11,194,227,134,198,221,17,90,48,58,58,217,35,47,230,67,253,101,28,80,156,205,128,182,2,147,82,74,24,171,73,56,85,
37,242,200,191,248,50,115,47,168,96,200,42,160,57,119,83,84,209,23,128,227,173,11,208,23,232,34,3,127,241,42,46,2,34,239,102,92,71,125,250,202,136,210,72,155,95,64,102,23,200,204,209,99,243,57,162,52,
55,172,193,163,114,206,17,4,124,220,239,148,246,88,236,0,232,44,47,115,69,250,107,232,100,158,240,121,119,95,0,73,127,33,106,67,54,30,91,27,74,113,103,52,248,35,82,191,35,62,1,163,200,32,24,164,71,89,
138,58,232,98,211,140,245,49,71,152,63,8,219,158,125,111,66,22,211,77,243,247,114,243,26,192,144,9,128,189,127,30,166,243,31,138,92,159,222,187,27,131,169,46,42,250,202,209,122,240,184,198,12,113,127,
168,88,202,1,195,10,100,105,58,76,202,177,13,154,82,227,76,190,92,154,27,155,128,203,223,172,147,22,100,134,70,162,205,47,144,237,173,227,174,172,191,76,120,193,235,22,51,104,58,60,136,69,31,2,210,33,
152,24,80,21,211,230,55,242,115,71,252,242,65,2,34,63,169,216,25,123,54,60,216,203,161,231,94,30,243,217,105,115,42,16,211,67,235,213,207,230,109,226,130,106,41,98,100,59,45,106,180,51,191,16,210,234,
99,47,98,204,247,71,131,15,19,171,184,8,136,33,95,40,109,54,94,153,142,77,51,31,140,59,250,127,60,255,172,8,7,46,226,238,42,185,28,8,57,70,38,165,68,87,240,108,30,238,103,66,36,184,130,106,94,10,126,157,
129,242,172,200,145,230,23,88,217,249,80,194,182,77,218,101,49,143,91,188,2,135,254,246,193,184,130,108,53,215,92,64,145,46,180,134,60,99,63,27,135,253,133,112,178,95,80,40,48,228,137,32,134,250,19,154,
77,99,3,220,36,148,210,170,42,195,153,22,170,214,179,8,5,244,104,74,57,119,240,5,46,22,183,70,94,44,87,160,198,67,145,191,129,253,218,139,98,155,172,65,88,154,147,195,104,239,57,226,233,63,89,88,193,223,
218,251,57,230,28,2,201,73,190,38,200,17,113,33,175,216,219,198,93,177,240,123,241,155,12,72,209,224,127,174,243,161,232,23,31,165,210,141,186,243,99,190,248,71,47,238,30,87,16,47,104,143,204,7,87,26,
69,254,98,91,69,185,170,147,10,213,248,99,79,13,129,90,54,107,214,64,81,228,113,155,203,77,73,32,177,17,208,166,174,141,221,61,116,92,89,20,237,180,69,44,123,21,70,141,112,103,245,76,225,201,37,229,194,
121,185,5,180,185,100,20,233,130,60,231,254,18,117,238,226,49,95,124,171,184,58,10,124,171,203,205,229,39,126,148,24,124,66,213,10,177,76,212,19,39,220,248,234,14,140,15,57,235,0,7,254,180,147,29,123,
45,236,239,243,227,14,132,146,253,63,236,187,113,204,100,255,136,196,74,250,143,244,227,230,158,59,66,185,231,56,226,145,212,52,25,151,71,29,119,7,4,214,150,21,141,223,15,112,248,3,84,154,116,188,223,
171,199,29,112,80,155,33,242,132,237,58,126,171,189,63,225,203,59,28,110,170,92,27,9,138,222,240,177,165,67,91,201,151,186,199,156,67,95,159,121,75,236,8,170,205,57,161,245,199,119,184,137,129,195,77,
88,213,26,58,175,189,156,165,229,122,230,102,41,121,160,255,171,60,108,126,58,194,168,136,53,125,110,22,175,193,131,58,66,3,125,131,199,184,99,240,190,49,251,81,111,188,56,166,159,80,157,49,35,110,165,
117,76,2,190,255,241,81,9,201,137,82,38,133,205,169,42,83,96,204,206,175,9,252,30,44,141,144,166,30,63,98,1,145,45,230,187,104,210,126,246,180,134,29,36,141,6,207,246,15,105,204,89,193,226,108,72,55,228,
242,164,117,85,194,245,204,17,212,144,237,218,79,174,173,227,228,244,238,115,197,174,178,27,173,193,100,241,94,86,108,3,99,134,78,51,49,79,248,170,146,92,158,105,116,99,84,6,177,120,193,37,10,100,123,
187,162,170,208,34,236,230,238,99,96,233,136,4,127,56,48,103,17,242,248,224,68,200,20,84,26,52,152,179,53,24,149,161,1,49,218,158,62,45,146,145,201,204,155,174,160,212,64,216,183,208,202,37,150,166,91,
19,54,203,83,88,89,99,125,52,218,137,28,7,248,155,102,172,143,27,239,210,43,100,19,35,96,121,174,81,56,59,179,154,38,251,144,4,80,160,73,35,223,102,65,106,159,9,150,237,144,54,172,77,62,119,200,186,176,
247,135,204,53,185,2,27,89,180,105,231,211,166,174,141,136,134,214,245,116,208,250,194,27,97,128,244,85,101,84,126,166,130,2,121,26,202,211,29,117,179,14,208,183,175,5,211,226,10,178,84,1,44,94,129,126,
175,156,249,42,59,24,227,13,255,1,56,113,36,84,0,112,74,44,200,131,150,158,180,217,180,121,211,105,236,13,245,37,171,52,15,149,228,195,168,20,240,200,244,236,79,95,153,48,234,219,229,246,64,150,254,52,
38,100,124,131,165,244,239,105,137,208,154,123,54,112,52,80,70,225,194,114,10,170,138,48,25,64,163,86,96,119,4,113,123,130,124,244,251,55,99,102,193,18,37,203,1,234,118,157,66,220,167,208,4,153,74,13,
42,5,122,91,23,215,20,127,24,170,182,40,115,65,218,176,3,233,28,214,10,191,39,194,146,233,86,207,230,128,113,85,132,83,248,226,250,205,4,250,251,56,218,126,132,123,31,123,0,125,137,153,22,167,157,108,
149,52,70,44,106,102,76,11,232,211,19,16,203,201,176,59,75,47,190,230,219,45,14,39,104,84,26,200,8,77,57,194,208,16,146,103,104,92,247,24,33,35,61,195,16,142,124,186,15,182,140,187,253,68,99,68,249,58,
71,196,177,102,111,17,105,149,53,152,231,20,144,51,35,11,163,65,134,82,33,208,111,13,208,123,162,159,67,207,189,76,115,107,35,79,172,255,46,215,173,89,41,132,70,183,79,250,184,223,206,238,62,11,67,1,119,
148,55,60,214,247,6,167,53,41,31,69,194,52,150,145,164,60,128,224,180,35,122,189,28,109,63,18,1,126,244,84,19,34,163,97,208,138,86,22,186,164,196,152,158,240,99,143,211,94,150,50,153,36,8,74,5,66,65,1,
217,37,5,100,229,165,3,208,119,172,151,129,110,11,82,103,231,164,165,55,3,193,192,152,224,127,234,62,77,70,93,208,233,38,65,80,107,48,47,169,101,230,188,226,184,185,219,126,107,128,182,166,78,218,247,
52,18,108,107,159,22,224,79,26,1,167,139,4,65,169,64,87,57,135,121,23,215,144,151,63,190,123,248,69,137,93,219,14,197,173,144,59,147,192,159,84,2,254,97,18,50,50,153,123,249,50,230,86,231,76,248,185,253,
214,0,59,31,253,243,63,180,120,39,3,252,73,39,0,160,245,120,151,180,120,229,141,100,165,231,36,36,65,161,28,226,7,171,210,185,232,226,21,200,84,38,44,125,71,200,62,124,15,106,249,0,200,100,225,112,175,
77,153,71,163,105,217,152,158,115,107,135,155,166,237,7,113,53,30,158,240,218,144,44,240,147,66,0,64,125,67,179,180,226,218,219,19,146,240,31,95,84,113,249,186,71,35,221,141,190,3,4,62,186,18,181,204,
9,14,235,201,210,151,97,7,105,172,138,11,8,229,17,14,111,124,107,220,218,144,76,240,163,162,161,147,37,181,85,229,194,27,255,247,24,253,131,189,12,121,163,129,88,81,212,194,202,181,183,135,166,173,193,
65,62,120,239,125,0,210,204,53,4,242,175,14,229,105,43,23,135,235,142,16,100,168,5,15,159,177,63,207,186,99,87,179,184,127,99,124,39,168,58,7,243,146,218,132,235,140,172,168,16,221,162,106,116,139,170,
233,234,59,158,52,240,147,166,1,137,52,97,69,81,11,255,181,170,17,229,21,161,56,251,211,79,253,138,187,239,189,135,119,119,238,164,186,166,6,177,249,25,228,195,9,20,73,20,17,154,118,135,210,152,167,198,
106,134,203,71,94,136,19,143,233,238,19,249,240,177,13,39,167,162,225,114,151,210,5,21,100,20,101,68,120,178,38,165,137,111,85,149,37,237,19,165,164,127,168,125,42,9,151,87,116,242,224,87,58,240,40,50,
80,45,126,5,153,202,132,195,225,96,199,142,29,172,94,29,138,201,59,235,30,68,167,121,39,50,240,23,39,97,158,168,254,104,243,19,111,2,80,120,78,37,133,243,11,99,134,15,146,253,149,252,148,16,48,66,194,
21,215,223,75,253,237,59,208,207,95,4,128,107,104,57,250,179,191,31,113,93,208,107,99,104,215,154,232,47,229,143,55,131,173,39,118,196,114,88,27,246,27,46,97,151,230,82,6,165,80,97,128,47,8,102,181,20,
183,90,1,146,255,149,252,148,17,0,48,248,238,157,146,73,191,39,188,71,132,207,230,198,159,118,25,234,217,95,65,97,154,133,171,249,53,2,199,127,25,202,225,142,22,143,27,154,247,38,78,152,15,87,91,140,124,
63,54,34,241,246,20,242,7,161,50,61,178,98,225,159,142,128,175,238,172,15,63,204,230,11,240,211,236,39,163,114,181,62,155,155,160,63,128,42,93,19,187,90,33,172,70,59,64,153,134,67,210,211,44,47,195,45,
132,230,254,243,3,239,198,109,226,145,212,252,172,236,213,184,163,127,116,197,66,50,36,105,159,169,142,228,22,42,141,39,71,244,15,251,110,228,1,243,175,35,72,136,91,103,116,138,60,225,92,71,75,201,79,
194,127,143,204,231,230,238,55,57,223,21,159,128,118,245,188,152,199,221,1,129,213,133,69,76,197,190,114,73,251,82,190,194,168,17,206,203,53,83,111,85,208,53,20,122,236,220,44,37,191,24,252,18,174,224,
248,83,152,91,197,213,216,148,249,100,171,164,240,207,200,54,5,215,58,31,79,216,54,86,213,5,132,246,136,88,158,107,156,146,173,204,166,100,13,120,167,199,46,61,211,120,140,82,253,240,246,49,3,125,60,59,
227,23,99,182,107,8,212,178,89,92,19,53,119,103,244,188,193,109,238,255,78,216,214,35,169,121,178,100,99,148,153,234,11,234,248,94,77,249,148,237,170,56,37,91,150,45,207,53,10,191,92,90,45,124,98,83,160,
148,129,217,148,195,195,253,87,38,108,227,10,170,121,214,182,10,139,87,8,255,88,93,110,22,116,60,53,38,248,72,65,222,205,184,46,166,143,80,160,51,50,149,91,90,42,166,226,161,15,29,104,150,156,162,156,
28,141,22,176,99,82,74,104,201,75,216,70,39,243,240,83,227,127,34,52,188,55,190,154,211,83,192,223,175,91,193,238,172,171,99,158,54,171,167,246,19,218,41,33,192,226,149,129,52,72,190,122,2,211,159,99,
0,161,101,95,52,248,195,230,102,44,177,201,115,217,111,186,52,225,118,150,222,0,255,122,4,252,168,182,88,216,210,97,145,14,217,66,213,199,51,180,106,230,56,94,135,193,102,48,101,141,66,104,40,244,189,
129,195,122,178,228,37,32,210,164,93,70,155,102,1,61,234,50,142,104,22,242,246,150,131,184,143,28,71,145,174,39,61,47,147,89,75,203,18,110,204,55,34,29,46,59,144,59,101,4,156,89,59,231,58,91,37,177,235,
77,228,238,227,224,179,193,96,61,31,127,210,193,222,227,161,4,191,172,108,17,222,146,42,188,89,103,69,204,231,126,81,98,219,115,239,71,148,174,11,106,13,146,70,195,133,223,187,10,1,127,220,210,113,165,
220,200,221,53,229,66,138,128,241,6,240,50,50,209,207,40,64,173,75,67,159,109,192,105,113,48,208,214,29,85,242,114,188,167,141,159,254,240,22,174,91,179,82,136,85,185,224,14,8,248,130,201,219,160,117,
218,18,16,147,132,49,228,84,240,71,159,235,114,251,164,206,33,31,6,165,124,74,129,159,86,4,76,132,132,68,224,159,137,50,109,254,135,204,88,73,157,233,8,254,180,34,96,44,18,166,35,248,211,142,128,120,36,
76,87,240,67,126,140,36,77,203,159,125,7,155,36,115,205,42,201,92,179,74,250,221,159,95,145,166,107,63,166,229,63,114,59,117,97,222,247,73,243,244,28,249,211,205,10,250,103,149,212,127,83,77,17,144,34,
32,37,41,2,82,4,164,36,69,64,138,128,148,76,129,252,63,127,129,214,35,152,197,89,143,0,0,0,0,73,69,78,68,174,66,96,130,0,0};

const char* ThorConfigComponent::vorbis_png = (const char*) resource_ThorConfigComponent_vorbis_png;
const int ThorConfigComponent::vorbis_pngSize = 5411;
