/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "UI/TunerReadout.h"

//==============================================================================
/**
*/
class GrimbletuneAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    GrimbletuneAudioProcessorEditor (GrimbletuneAudioProcessor&);
    ~GrimbletuneAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    GrimbletuneAudioProcessor& audioProcessor;
    Grimbletune::UI::TunerReadout m_tunerReadout;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GrimbletuneAudioProcessorEditor)
};
