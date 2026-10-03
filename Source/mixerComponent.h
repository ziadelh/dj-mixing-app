/*
  ==============================================================================

    mixerComponent.h
    Created: 10 Mar 2024 7:12:10pm
    Author:  ziade

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include "CustomLookAndFeel.h"

//==============================================================================
/*
*/
class mixerComponent : public juce::Component, public juce::Slider::Listener {
public:
    mixerComponent();
    ~mixerComponent() override;

    //sets the audio player
    void setDeck1(DJAudioPlayer* deckPlayerSource1);
    void setDeck2(DJAudioPlayer* deckPlayerSource2);

    //slider value change
    void sliderValueChanged(Slider* slider) override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    Slider volumeSlider1;
    Slider volumeSlider2;

    Label volumeLabel1; 
    Label volumeLabel2;

    DJAudioPlayer* deckPlayer1 = nullptr; 
    DJAudioPlayer* deckPlayer2 = nullptr;

    CustomLookAndFeel customLookAndFeel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(mixerComponent)
};