#include "MainComponent.h"

MainComponent::MainComponent()
{
    levelSlider.setRange(0.0f, 0.25);
    levelSlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 100, 20);
    levelLabel.setText("Noise Level", juce::dontSendNotification);

    addAndMakeVisible(levelSlider);
    addAndMakeVisible(levelLabel);

    setSize(600, 100);
    

 
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
    juce::String message;
    message << "Preparando para tocar audio...\n";
    message << " samples por bloco esperados =  " << samplesPerBlockExpected << "\n";
    message << " sample rate =  " << sampleRate << "\n";
    juce::Logger::getCurrentLogger()->writeToLog(message);
    
}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{

    bufferToFill.clearActiveBufferRegion();

    auto level = (float)levelSlider.getValue();
    
    for (auto channel = 0; channel < bufferToFill.buffer->getNumChannels(); channel++)
    {
        auto* buffer = bufferToFill.buffer->getWritePointer(channel, bufferToFill.startSample);

        for (auto sample = 0; sample < bufferToFill.numSamples; ++sample)
            buffer[sample] = random.nextFloat() * level;
            
    }

}

void MainComponent::releaseResources()
{

    juce::Logger::getCurrentLogger()->writeToLog("encerrando recursos de audio");

}


void MainComponent::paint (juce::Graphics& g)
{

    g.fillAll(juce::Colours::black);
}

void MainComponent::resized()
{
    levelLabel.setBounds(10, 10, 90, 20);
    levelSlider.setBounds(100, 10, getWidth() - 110, 20);

}
