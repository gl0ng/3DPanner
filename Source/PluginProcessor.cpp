/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
_3dpannerAudioProcessor::_3dpannerAudioProcessor()
{
	UserParams[MasterBypass] = 0.0f;//default to not bypassed
	UserParams[StereoWidth] = 1.0f;//default Width 1.0 (no change)
	mWidthControl.SetWidth(UserParams[StereoWidth]);//push VST default to effect
	UIUpdateFlag = true;//Request UI update
}

_3dpannerAudioProcessor::~_3dpannerAudioProcessor()
{
}

//==============================================================================
const String _3dpannerAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

int _3dpannerAudioProcessor::getNumParameters()
{
    return totalNumParam;
}

float _3dpannerAudioProcessor::getParameter (int index)
{
	switch (index)
	{
	case MasterBypass://example nothing special
		return UserParams[MasterBypass];
	case StereoWidth://example update from internal
		UserParams[StereoWidth] = mWidthControl.Getwidth();
		return UserParams[StereoWidth];
	default: return 0.0f;//invalid index
	}
}

void _3dpannerAudioProcessor::setParameter (int index, float newValue)
{
	switch (index)
	{
	case MasterBypass:
		UserParams[MasterBypass] = newValue;
		break;
	case StereoWidth:
		UserParams[StereoWidth] = newValue;
		mWidthControl.SetWidth(UserParams[StereoWidth]);
		break;
	default: return;
	}
	UIUpdateFlag = true;//Request UI update -- Some OSX hosts use alternate editors, this updates ours
}

const String _3dpannerAudioProcessor::getParameterName (int index)
{
	switch (index)
	{
	case MasterBypass: return "Master Bypass";
	case StereoWidth: return "StereoWidth Factor";
	default:return String::empty;
	}
}

const String _3dpannerAudioProcessor::getParameterText (int index)
{
	if (index >= 0 && index<totalNumParam)
		return String(UserParams[index]);//return parameter value as string
	else return String::empty;
}

const String _3dpannerAudioProcessor::getInputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

const String _3dpannerAudioProcessor::getOutputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

bool _3dpannerAudioProcessor::isInputChannelStereoPair (int index) const
{
    return true;
}

bool _3dpannerAudioProcessor::isOutputChannelStereoPair (int index) const
{
    return true;
}

bool _3dpannerAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool _3dpannerAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool _3dpannerAudioProcessor::silenceInProducesSilenceOut() const
{
    return false;
}

double _3dpannerAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int _3dpannerAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int _3dpannerAudioProcessor::getCurrentProgram()
{
    return 0;
}

void _3dpannerAudioProcessor::setCurrentProgram (int index)
{
}

const String _3dpannerAudioProcessor::getProgramName (int index)
{
    return String();
}

void _3dpannerAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void _3dpannerAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void _3dpannerAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

void _3dpannerAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
	if (getNumInputChannels()<2 || UserParams[MasterBypass])
	{
	}/*Nothing to do here - processing is in-place, so doing nothing is pass-through (for NumInputs=NumOutputs)*/
	else
	{//Not bypassed - do processing!
		float* leftData = buffer.getWritePointer(0);
		float* rightData = buffer.getWritePointer(1);
		for (long i = 0; i<buffer.getNumSamples(); i++)
			mWidthControl.ClockProcess(&leftData[i], &rightData[i]);
	}
}

//==============================================================================
bool _3dpannerAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* _3dpannerAudioProcessor::createEditor()
{
    return new _3dpannerAudioProcessorEditor (*this);
}

//==============================================================================
void _3dpannerAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.

	//Save UserParams/Data to file
	XmlElement root("Root");
	XmlElement *el;
	el = root.createNewChildElement("Bypass");
	el->addTextElement(String(UserParams[MasterBypass]));
	el = root.createNewChildElement("StereoWidth");
	el->addTextElement(String(UserParams[StereoWidth]));
	copyXmlToBinary(root, destData);
}

void _3dpannerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.

	//Load UserParams/Data from file
	XmlElement* pRoot = getXmlFromBinary(data, sizeInBytes);
	if (pRoot != NULL)
	{
		forEachXmlChildElement((*pRoot), pChild)
		{
			if (pChild->hasTagName("Bypass"))
			{
				String text = pChild->getAllSubText();
				setParameter(MasterBypass, text.getFloatValue());
			}
			else if (pChild->hasTagName("StereoWidth"))
			{
				String text = pChild->getAllSubText();
				setParameter(StereoWidth, text.getFloatValue());
			}
		}
		delete pRoot;
		UIUpdateFlag = true;//Request UI update
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new _3dpannerAudioProcessor();
}
