/*
  ==============================================================================

    TunerReadout.cpp
    Created: 27 Jul 2022 5:29:24am
    Author:  Syl

  ==============================================================================
*/

#include "TunerReadout.h"

namespace Grimbletune::UI
{
    TunerReadout::TunerReadout()
    {
        m_noteLabel.setText("NONE", juce::dontSendNotification);
        addAndMakeVisible(&m_noteLabel);
        GET_DSP()->addListener(this);
    }

    TunerReadout::~TunerReadout()
    {
    }

    void TunerReadout::onNewFundamental(double newFundamental)
    {
        m_noteLabel.setText(std::to_string(newFundamental), juce::dontSendNotification);
    }

    void TunerReadout::paint(GT_UNUSED juce::Graphics& g)
    {
    }

    void TunerReadout::resized()
    {
        m_noteLabel.setBounds(getLocalBounds());
    }
}