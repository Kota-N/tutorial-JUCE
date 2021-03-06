/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TutorialAudioProcessor::TutorialAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

TutorialAudioProcessor::~TutorialAudioProcessor()
{
}

//==============================================================================
const juce::String TutorialAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool TutorialAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool TutorialAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool TutorialAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double TutorialAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int TutorialAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int TutorialAudioProcessor::getCurrentProgram()
{
    return 0;
}

void TutorialAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String TutorialAudioProcessor::getProgramName (int index)
{
    return {};
}

void TutorialAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void TutorialAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void TutorialAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool TutorialAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void TutorialAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    buffer.clear();
    
    juce::MidiBuffer processedMidi;
    int time;
    juce::MidiMessage m;
    
    for (juce::MidiBuffer::Iterator i (midiMessages); i.getNextEvent(m, time);)
    {
        if (m.isNoteOn())
        {
            uint8 newVel = (uint8)noteOnVel;
            m = juce::MidiMessage::noteOn(m.getChannel(), m.getNoteNumber(), newVel);
        }
        else if (m.isNoteOff())
        {
        }
        else if (m.isAftertouch())
        {
        }
        else if (m.isPitchWheel())
        {
        }
        
        processedMidi.addEvent(m, time);
    }
    
    midiMessages.swapWith(processedMidi);
}

//==============================================================================
bool TutorialAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* TutorialAudioProcessor::createEditor()
{
    return new TutorialAudioProcessorEditor (*this);
}

//==============================================================================
void TutorialAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void TutorialAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TutorialAudioProcessor();
}
