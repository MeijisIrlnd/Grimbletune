/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "./Audio/Tuner.h"

//==============================================================================
/**
*/
using namespace Grimbletune::Audio;
class GrimbletuneAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    GrimbletuneAudioProcessor();
    ~GrimbletuneAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, GT_UNUSED juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (GT_UNUSED int index) override;
    const juce::String getProgramName (GT_UNUSED int index) override;
    void changeProgramName (GT_UNUSED int index, GT_UNUSED const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (GT_UNUSED juce::MemoryBlock& destData) override;
    void setStateInformation (GT_UNUSED const void* data, GT_UNUSED int sizeInBytes) override;

    Tuner* getTuner() { return &m_tuner; }
private:
    Tuner m_tuner;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GrimbletuneAudioProcessor)
};
