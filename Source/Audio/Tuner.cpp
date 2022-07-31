/*
  ==============================================================================

    Tuner.cpp
    Created: 26 Jul 2022 5:46:31am
    Author:  Syl

  ==============================================================================
*/

#include "Tuner.h"

namespace Grimbletune::Audio
{
    Tuner::Tuner() : m_fft(getOrder()), m_fifo(FFT_SIZE), m_fftData(FFT_SIZE * 2), m_lowpass(1, 1), m_highpass(1, 1), m_pitchTracker(FFT_SIZE)
    {
    }
    void Tuner::prepareToPlay(GT_UNUSED int samplesPerBlockExpected, double sampleRate)
    {
        m_pitchTracker.setBufferSize(FFT_SIZE);
        m_pitchTracker.setSampleRate(static_cast<int>(sampleRate));
        double coeffs[6];
        DSPCommon::RBJ::lowpass(coeffs, sampleRate, 1000, 0.1);
        m_lowpass.initialise(coeffs);
        DSPCommon::RBJ::highpass(coeffs, sampleRate, 100, 0.1);
        m_highpass.initialise(coeffs);
    }

    void Tuner::processBlock(juce::AudioBuffer<float>& buffer)
    {
        auto* rp = buffer.getReadPointer(0);
        for (auto sample = 0; sample < buffer.getNumSamples(); sample++) {
            //float filtered;
            //m_lowpass.processSample(&rp[sample], &filtered, 1);
            //m_highpass.processSample(&filtered, &filtered, 1);
            pushToFifo(rp[sample]);
        }

    }
    void Tuner::releaseResources()
    {
        m_lowpass.reset();
        m_highpass.reset();
    }

    void Tuner::pushToFifo(float sample) noexcept
    {
        if (m_fifoIndex == FFT_SIZE) {
            auto pitch = m_pitchTracker.getPitch(m_fifo.data());
            GET_MESSAGE_MANAGER()->callAsync([pitch]() { GET_DSP()->setFundamental(pitch); });
            //m_fft.performFrequencyOnlyForwardTransform(m_fifo.data());
            //std::fill(m_fftData.begin(), m_fftData.end(), 0.0f);
            //std::copy(m_fifo.begin(), m_fifo.end(), m_fftData.begin());
            //GET_MESSAGE_MANAGER()->callAsync([this]() {
            //    GET_DSP()->getFundamental(m_fftData);
            //});
            m_fifoIndex = 0;
        }
        m_fifo[static_cast<size_t>(m_fifoIndex)] = sample;
        ++m_fifoIndex;
    }
}