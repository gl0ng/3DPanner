/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.2.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "PluginEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
_3DPannerAudioProcessorEditor::_3DPannerAudioProcessorEditor (3DPannerAudioProcessor& ownerFilter)
    : AudioProcessorEditor(ownerFilter)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (WidthCtrlSld = new Slider ("Width Factor Slider"));
    WidthCtrlSld->setRange (0, 5, 0.1);
    WidthCtrlSld->setSliderStyle (Slider::LinearHorizontal);
    WidthCtrlSld->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    WidthCtrlSld->addListener (this);

    addAndMakeVisible (label = new Label ("new label",
                                          TRANS("Stereo Width Factor:")));
    label->setFont (Font (15.00f, Font::plain));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (Label::textColourId, Colours::grey);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (BypassBtn = new TextButton ("Bypass Button"));
    BypassBtn->setButtonText (TRANS("Stereo Width Bypass"));
    BypassBtn->addListener (this);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
	getProcessor()->RequestUIUpdate();// UI update must be done each time a new editor is constructed
	startTimer(200);//starts timer with interval of 200mS
	BypassBtn->setClickingTogglesState(true);
    //[/Constructor]
}

_3DPannerAudioProcessorEditor::~_3DPannerAudioProcessorEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    WidthCtrlSld = nullptr;
    label = nullptr;
    BypassBtn = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void _3DPannerAudioProcessorEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::black);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void _3DPannerAudioProcessorEditor::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    WidthCtrlSld->setBounds (16, 40, 352, 24);
    label->setBounds (8, 16, 150, 24);
    BypassBtn->setBounds (16, 72, 344, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void _3DPannerAudioProcessorEditor::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == WidthCtrlSld)
    {
        //[UserSliderCode_WidthCtrlSld] -- add your slider handling code here..
        //[/UserSliderCode_WidthCtrlSld]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void _3DPannerAudioProcessorEditor::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == BypassBtn)
    {
        //[UserButtonCode_BypassBtn] -- add your button handler code here..
        //[/UserButtonCode_BypassBtn]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void SteroWidthCtrlAudioProcessorEditor::timerCallback()
{
	StereoWidthCtrlAudioProcessor* ourProcessor = getProcessor();
	//exchange any data you want between UI elements and the Plugin "ourProcessor"
	if (ourProcessor->NeedsUIUpdate())
	{
		BypassBtn->setToggleState(1.0f == ourProcessor->getParameter(StereoWidthCtrlAudioProcessor::MasterBypass), dontSendNotification);
		WidthCtrlSld->setValue(ourProcessor->getParameter(StereoWidthCtrlAudioProcessor::StereoWidth), dontSendNotification);
		ourProcessor->ClearUIUpdateFlag();
	}
}

void StereoWidthCtrlAudioProcessorEditor::sliderValueChanged(Slider* sliderThatWasMoved)
{
	//[UsersliderValueChanged_Pre]
	StereoWidthCtrlAudioProcessor* ourProcessor = getProcessor();
	//[/UsersliderValueChanged_Pre]

	if (sliderThatWasMoved == WidthCtrlSld)
	{
		//[UserSliderCode_WidthCtrlSld] -- add your slider handling code here..
		ourProcessor->setParameter(StereoWidthCtrlAudioProcessor::StereoWidth, (float)WidthCtrlSld->getValue());
		//Note OSX - some hosts use extra GUIs which may need update - you can notify them as well by replacing "setParameter" with "setParameterNotifyingHost" using the same arguments
		//[/UserSliderCode_WidthCtrlSld]
	}

	//[UsersliderValueChanged_Post]
	//[/UsersliderValueChanged_Post]
}

void StereoWidthCtrlAudioProcessorEditor::buttonClicked(Button* buttonThatWasClicked)
{
	//[UserbuttonClicked_Pre]
	StereoWidthCtrlAudioProcessor* ourProcessor = getProcessor();
	//[/UserbuttonClicked_Pre]

	if (buttonThatWasClicked == BypassBtn)
	{
		//[UserButtonCode_BypassBtn] -- add your button handler code here..
		ourProcessor->setParameter(StereoWidthCtrlAudioProcessor::MasterBypass, (float)BypassBtn->getToggleState());
		//Note OSX - some hosts use extra GUIs which may need update - you can notify them as well by replacing "setParameter" with "setParameterNotifyingHost" using the same arguments
		//[/UserButtonCode_BypassBtn]
	}

	//[UserbuttonClicked_Post]
	//[/UserbuttonClicked_Post]
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="_3DPannerAudioProcessorEditor"
                 componentName="" parentClasses="public AudioProcessorEditor, public Timer"
                 constructorParams="3DPannerAudioProcessor&amp; ownerFilter" variableInitialisers="AudioProcessorEditor(ownerFilter)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ff000000"/>
  <SLIDER name="Width Factor Slider" id="5c5f71317e637921" memberName="WidthCtrlSld"
          virtualName="" explicitFocusOrder="0" pos="16 40 352 24" min="0"
          max="5" int="0.10000000000000001" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="54ce6c014d72be82" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="8 16 150 24" textCol="ff808080" edTextCol="ff000000"
         edBkgCol="0" labelText="Stereo Width Factor:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="Bypass Button" id="f13c0b49dec8e55" memberName="BypassBtn"
              virtualName="" explicitFocusOrder="0" pos="16 72 344 24" buttonText="Stereo Width Bypass"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
