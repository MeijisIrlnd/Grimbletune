/*
  ==============================================================================

    TunerReadout.h
    Created: 27 Jul 2022 5:29:24am
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../Macros.h"
#include "../DSP/DSPUtils.h"
namespace Grimbletune::UI
{
    // Subscribe to events from the tuner class when the fft is ready, then show on the screen..
    class TunerReadout : public juce::Component, public Grimbletune::DSP::DSPUtils::Listener
    {
    public: 
        TunerReadout();
        ~TunerReadout() override;
        void onNewFundamental(double newFundamental) override;
        void paint(GT_UNUSED juce::Graphics& g) override;
        void resized() override;
    private: 
        juce::Label m_noteLabel;
    };
}