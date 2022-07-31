/*
  ==============================================================================

    Macros.h
    Created: 31 Jul 2022 3:57:54pm
    Author:  Syl

  ==============================================================================
*/

#pragma once

#ifndef FFT_SIZE 
    #define FFT_SIZE 4096
#endif

#ifndef GT_INLINE 
    #define GT_INLINE __forceinline
#endif 

#ifndef GT_UNUSED 
    #define GT_UNUSED [[maybe_unused]]
#endif

#ifndef GET_MESSAGE_MANAGER 
    #define GET_MESSAGE_MANAGER() juce::MessageManager::getInstance()
#endif

#ifndef GET_DSP
    #define GET_DSP() Grimbletune::DSP::DSPUtils::getInstance()
#endif

