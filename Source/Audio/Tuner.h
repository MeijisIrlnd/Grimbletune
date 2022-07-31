/*
  ==============================================================================

    Tuner.h
    Created: 26 Jul 2022 5:46:31am
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../Macros.h"
#include "../DSP/DSPUtils.h"
#include <DSPBiquad.h>
namespace Grimbletune::Audio
{
    class Tuner
    {
    public: 
        Tuner();
        void prepareToPlay(GT_UNUSED int samplesPerBlockExpected, GT_UNUSED double sampleRate);
        void processBlock(juce::AudioBuffer<float>& buffer);
        void releaseResources();
    private: 
        GT_INLINE static int getOrder() {
            return static_cast<int>(std::log2(FFT_SIZE));
        }
        void pushToFifo(float sample) noexcept;
        juce::dsp::FFT m_fft;
        std::vector<float> m_fifo;
        std::vector<float> m_fftData;
        int m_fifoIndex{ false };
        bool m_nextFftBlockReady{ false };
        DSPCommon::Biquad m_lowpass, m_highpass;
        adamski::PitchMPM m_pitchTracker;

    };
}