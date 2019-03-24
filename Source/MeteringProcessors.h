/*
  ==============================================================================

    MeteringProcessors.h
    Created: 18 Jan 2018 4:01:46pm
    Author:  Andrew

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include <atomic>
#ifdef JUCE_CLANG
#include <mm_malloc.h>
#endif

class PeakMeterProcessor final : public dsp::ProcessorBase
{
public:

	PeakMeterProcessor() {};
    ~PeakMeterProcessor() = default;

	float getLevel (const int channelNum) const;
	float getLevelDb (const int channelNum) const;
	size_t getNumChannels () const;

    void prepare (const dsp::ProcessSpec& spec) override;
    void process (const dsp::ProcessContextReplacing<float>& context) override;
    void reset() override;

private:

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PeakMeterProcessor)

private:

    size_t numChannels = 0;
    HeapBlock <std::atomic <float>> envelopeContinuation;
	float releaseTimeConstant = 0.0f;
    const float antiDenormalFloat = 1e-15f;
    const float noSignalDbLevel = -150.0f;
};

class VUMeterProcessor final : public dsp::ProcessorBase
{
public:

	VUMeterProcessor() {};
    ~VUMeterProcessor() = default;

	float getLevel (const int channelNum) const;
	float getLevelDb (const int channelNum) const;
	size_t getNumChannels () const;

    void prepare (const dsp::ProcessSpec& spec) override;
    void process (const dsp::ProcessContextReplacing<float>& context) override;
    void reset() override;

private:

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VUMeterProcessor)

private:

    size_t numChannels = 0;
    HeapBlock <std::atomic <float>> envelopeContinuation;
	float timeConstant = 0.0f;
    const float antiDenormalFloat = 1e-15f;
    const float noSignalDbLevel = -150.0f;
};