/*
  ==============================================================================

    DSPUtils.cpp
    Created: 27 Jul 2022 4:42:19am
    Author:  Syl

  ==============================================================================
*/

#include "DSPUtils.h"
namespace Grimbletune::DSP
{
    std::mutex DSPUtils::m_mutex;
    DSPUtils* DSPUtils::m_instance{ nullptr };

    DSPUtils::DSPUtils() : m_midiToString(128)
    {
        for (auto i = 0; i < 128; i++) {
            if (i < 21) m_midiToString[i] = "";
        }
    }

    DSPUtils::~DSPUtils()
    {
    }

    void DSPUtils::startup()
    {
        getInstance();
    }

    DSPUtils* DSPUtils::getInstance()
    {
        std::scoped_lock<std::mutex> sl(m_mutex);
        if (m_instance == nullptr) {
            m_instance = new DSPUtils();
        }
        return m_instance;
    }
    void DSPUtils::shutdown()
    {
        std::scoped_lock<std::mutex> sl(m_mutex);
        delete m_instance;
        m_instance = nullptr;
    }

    void DSPUtils::prepare(double sampleRate)
    {
        m_sampleRate = sampleRate;
    }

    // https://fftguitartuner.files.wordpress.com/2011/03/ee113d-final-report2.pdf
    void DSPUtils::getFundamental(std::vector<float> fftData)
    {
        //std::vector<float> upsampledData((fftData.size() * 2) + 1);
        //juce::LagrangeInterpolator interpolator;
        //interpolator.process(2, fftData.data(), upsampledData.data(), static_cast<int>(upsampledData.size()));

        auto max = FLT_MIN;
        int fundamental = 0;
        for (auto k = 0; k < FFT_SIZE / 8; k++) {
            auto currentSum = fftData[k] * fftData[k * 2] * fftData[k * 3];
            if (currentSum > max && k > 0) {
                max = currentSum;
                fundamental = k;
            }
        }
        auto res = fundamental * (m_sampleRate * 2) / FFT_SIZE;
        DBG(res);
        if (m_listener != nullptr) {
            m_listener->onNewFundamental(res);
        }
    }
}