/*
  ==============================================================================

    RBJCoefficients.h
    Created: 2 Jan 2022 3:35:54pm
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include <KMath.h>
namespace DSPCommon
{
    namespace RBJ 
    {
        DSP_COMMON_UNUSED static void lowpass(double* target, double sampleRate, double cutoff, double q)
        {
            const double omega = juce::MathConstants<double>::twoPi * (cutoff / sampleRate);
            const double cosOmega = std::cos(omega);
            const double alpha = std::sin(omega) / static_cast<double>(2 * q);
            target[0] = (1 - cosOmega) / 2.0; // a0
            target[1] = 1 - cosOmega; // a1
            target[2] = target[0]; // a2
            target[3] = 1 + alpha; // b0
            target[4] = -2 * cosOmega; // b1
            target[5] = 1 - alpha; // b2;
        }

        DSP_COMMON_UNUSED static void highpass(double* target, double sampleRate, double cutoff, double q)
        {
            const double omega = juce::MathConstants<double>::twoPi * (cutoff / sampleRate);
            const double cosOmega = std::cos(omega);
            const double alpha = std::sin(omega) / static_cast<double>(2 * q);
            target[0] = (1 + cosOmega) / 2.0; // a0
            target[1] = -1 * (1 + cosOmega); // a1
            target[2] = target[0]; // a2
            target[3] = 1 + alpha; // b0
            target[4] = -2 * cosOmega; // b1
            target[5] = 1 - alpha; // b2
        }

        DSP_COMMON_UNUSED static void allpass(double* target, double sampleRate, double cutoff, double q)
        {
            const double omega = juce::MathConstants<double>::twoPi * (cutoff / sampleRate);
            const double cosOmega = std::cos(omega);
            const double alpha = std::sin(omega) / static_cast<double>(2 * q);
            target[0] = 1 - alpha; // a0
            target[1] = -2 * cosOmega; // a1
            target[2] = 1 + alpha; // a2
            target[3] = target[2]; // b0
            target[4] = target[1]; // b1
            target[5] = target[0]; // b2
        }

        DSP_COMMON_UNUSED static void lowShelf(double* target, double sampleRate, double centreFreq, double dbGain, double slope)
        {
            const double omega = juce::MathConstants<double>::twoPi * (centreFreq / sampleRate);
            const double cosOmega = std::cos(omega);
            const double sinOmega = std::sin(omega);
            const double A = Kalide::KMath::fastPow(10, dbGain / 40.0);
            const double twoRootAa = sinOmega * Kalide::KMath::fastPow((Kalide::KMath::fastPow(A, 2) + 1) * ((1 / slope) - 1) + 2 * A, 0.5);
            target[0] = A * ((A + 1) - (A - 1) * cosOmega + twoRootAa); // a0
            target[1] = (2 * A) * ((A - 1) - (A + 1) * cosOmega); // a1
            target[2] = A * ((A + 1) - (A - 1) * cosOmega - twoRootAa); // a2
            target[3] = (A + 1) + (A - 1) * cosOmega + twoRootAa; // b0
            target[4] = -2 * ((A - 1) + (A + 1) * cosOmega); // b1
            target[5] = (A + 1) + (A - 1) * cosOmega - twoRootAa; // b2
        }

        DSP_COMMON_UNUSED static void highShelf(double* target, double sampleRate, double centreFreq, double dbGain, double slope)
        {
            const double omega = juce::MathConstants<double>::twoPi * (centreFreq / sampleRate);
            const double cosOmega = std::cos(omega);
            const double sinOmega = std::sin(omega);
            const double A = Kalide::KMath::fastPow(10, dbGain / 40.0);
            const double twoRootAa = sinOmega * Kalide::KMath::fastPow((Kalide::KMath::fastPow(A, 2) + 1) * ((1 / slope) - 1) + 2 * A, 0.5);
            target[0] = A * ((A + 1) + (A - 1) * cosOmega + twoRootAa); // a0
            target[1] = (-2 * A) * ((A - 1) + (A + 1) * cosOmega); // a1
            target[2] = A * ((A + 1) + (A - 1) * cosOmega - twoRootAa); // a2
            target[3] = (A + 1) - (A - 1) * cosOmega + twoRootAa; // b0
            target[4] = 2 * ((A - 1) - (A + 1) * cosOmega); // b1
            target[5] = (A + 1) - (A - 1) * cosOmega - twoRootAa; // b2
        }
    }
    
}