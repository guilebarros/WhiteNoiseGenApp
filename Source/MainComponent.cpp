#include "MainComponent.h"

MainComponent::MainComponent()
{

    setSize (800, 600);
    

 
    if (juce::RuntimePermissions::isRequired (juce::RuntimePermissions::recordAudio)
        && ! juce::RuntimePermissions::isGranted (juce::RuntimePermissions::recordAudio))
    {
        juce::RuntimePermissions::request (juce::RuntimePermissions::recordAudio,
                                           [&] (bool granted) { setAudioChannels (granted ? 2 : 0, 2); });
    }
    else
    {
        
        setAudioChannels (0,2);
    }
}

MainComponent::~MainComponent()
{
   
    shutdownAudio();
}


void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    
}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{

    bufferToFill.clearActiveBufferRegion();

    for (auto channel = 0; channel < bufferToFill.buffer->getNumChannels(); channel++)
    {
        auto* buffer = bufferToFill.buffer->getWritePointer(channel, bufferToFill.startSample);

        for (auto sample = 0; sample < bufferToFill.numSamples; ++sample)
        {
            buffer[sample] = random.nextFloat() * 0.25f - 0.125f;
            DBG(sample);
        }
    }



}

void MainComponent::releaseResources()
{

}


void MainComponent::paint (juce::Graphics& g)
{

    g.fillAll(juce::Colours::transparentBlack);
}

void MainComponent::resized()
{

}
