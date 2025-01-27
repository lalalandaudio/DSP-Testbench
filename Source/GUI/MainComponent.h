/*
  ==============================================================================

    MainComponent.h
    Created: 12 Jan 2018 11:52:07am
    Author:  Andrew Jerrim

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "SourceComponent.h"
#include "ProcessorComponent.h"
#include "MonitoringComponent.h"
#include "AnalyserComponent.h"

class MainContentComponent final : public AudioAppComponent, public ChangeListener
{
public:

    explicit MainContentComponent (AudioDeviceManager& deviceManager);
    ~MainContentComponent() = default;

    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;
    
    void paint (Graphics& g) override;
    void resized() override;

    void changeListenerCallback (ChangeBroadcaster* source) override;

    void triggerSnapshot();
    void resumeStreaming();
    void setAnalyserExpanded (bool shouldBeExpanded);

    ProcessorHarness* getProcessorHarness (const int index);
    SourceComponent* getSourceComponentA();

private:

    ThreadPool threadPool;
    OpenGLContext oglContext;

    std::unique_ptr<SourceComponent> srcComponentA{};
    std::unique_ptr<SourceComponent> srcComponentB{};
    std::unique_ptr<ProcessorComponent> procComponentA{};
    std::unique_ptr<ProcessorComponent> procComponentB{};
    std::unique_ptr<AnalyserComponent> analyserComponent{};
    std::unique_ptr<MonitoringComponent> monitoringComponent{};

    Atomic<bool> holdAudio;
    Atomic<long> sampleCounter;
    Atomic<long> holdSize;
    bool analyserIsExpanded = false;

    HeapBlock<char> srcBufferMemoryA{}, srcBufferMemoryB{}, tempBufferMemory{};
    dsp::AudioBlock<float> srcBufferA, srcBufferB, tempBuffer;

    void routeSourcesAndProcess (ProcessorComponent* processor, dsp::AudioBlock<float>&);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};