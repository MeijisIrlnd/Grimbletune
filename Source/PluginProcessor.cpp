/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
GrimbletuneAudioProcessor::GrimbletuneAudioProcessor()
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
    Grimbletune::DSP::DSPUtils::startup();
}

GrimbletuneAudioProcessor::~GrimbletuneAudioProcessor()
{
    Grimbletune::DSP::DSPUtils::shutdown();
}

//==============================================================================
const juce::String GrimbletuneAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool GrimbletuneAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool GrimbletuneAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool GrimbletuneAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double GrimbletuneAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int GrimbletuneAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int GrimbletuneAudioProcessor::getCurrentProgram()
{
    return 0;
}

void GrimbletuneAudioProcessor::setCurrentProgram (GT_UNUSED int index)
{
}

const juce::String GrimbletuneAudioProcessor::getProgramName (GT_UNUSED int index)
{
    return {};
}

void GrimbletuneAudioProcessor::changeProgramName (GT_UNUSED int index, GT_UNUSED const juce::String& newName)
{
}

//==============================================================================
void GrimbletuneAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    GET_DSP()->prepare(sampleRate);
    m_tuner.prepareToPlay(samplesPerBlock, sampleRate);
}

void GrimbletuneAudioProcessor::releaseResources()
{
    m_tuner.releaseResources();
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool GrimbletuneAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
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

void GrimbletuneAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, GT_UNUSED juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    GT_UNUSED auto totalNumInputChannels  = getTotalNumInputChannels();
    GT_UNUSED auto totalNumOutputChannels = getTotalNumOutputChannels();
    m_tuner.processBlock(buffer);
}

//==============================================================================
bool GrimbletuneAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* GrimbletuneAudioProcessor::createEditor()
{
    return new GrimbletuneAudioProcessorEditor (*this);
}

//==============================================================================
void GrimbletuneAudioProcessor::getStateInformation (GT_UNUSED juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void GrimbletuneAudioProcessor::setStateInformation (GT_UNUSED const void* data, GT_UNUSED int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new GrimbletuneAudioProcessor();
}
