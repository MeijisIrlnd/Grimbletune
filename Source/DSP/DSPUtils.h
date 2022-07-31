/*
  ==============================================================================

    DSPUtils.h
    Created: 27 Jul 2022 4:42:19am
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include <vector>
#include <mutex>
#include <JuceHeader.h>
#include "../Macros.h"
namespace Grimbletune::DSP
{ 
    class DSPUtils
    {
    protected: 
        DSPUtils();
    public: 
        struct Listener
        {
            virtual ~Listener() { }
            virtual void onNewFundamental(double newFundamental) = 0;
        };
        ~DSPUtils();
        DSPUtils(const DSPUtils& other) = delete;
        DSPUtils(DSPUtils&& other) = delete;
        DSPUtils& operator=(const DSPUtils& other) = delete;
        static void startup();
        static DSPUtils* getInstance();
        static void shutdown();
        GT_INLINE void addListener(Listener* newListener) { m_listener = newListener; }
        void prepare(double sampleRate);
        // We want this to copy
        GT_INLINE void setFundamental(double newFundamental) {
            if (m_listener != nullptr) {
                m_listener->onNewFundamental(newFundamental);
            }
        }
        void getFundamental(std::vector<float> fftData);
    private: 
        static std::mutex m_mutex;
        static DSPUtils* m_instance;
        std::vector<juce::String> m_midiToString;
        double m_sampleRate{ 0 };
        Listener* m_listener{ nullptr };
    };
}