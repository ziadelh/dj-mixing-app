/*
  ==============================================================================

    mixerComponent.cpp
    Created: 10 Mar 2024 7:12:10pm
    Author:  ziade

  ==============================================================================
*/

#include <JuceHeader.h>
#include "mixerComponent.h"


//==============================================================================
mixerComponent::mixerComponent() {
    //volume sliders
    addAndMakeVisible(volumeSlider1);
    addAndMakeVisible(volumeSlider2);

    volumeSlider1.addListener(this);
    volumeSlider2.addListener(this);

    volumeSlider1.setRange(0.0, 1.0);
    volumeSlider2.setRange(0.0, 1.0);
    volumeSlider1.setValue(0.5);
    volumeSlider2.setValue(0.5);

    volumeSlider1.setSliderStyle(Slider::SliderStyle::LinearVertical);
    volumeSlider2.setSliderStyle(Slider::SliderStyle::LinearVertical);

    volumeSlider1.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    volumeSlider2.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);

    volumeSlider1.setLookAndFeel(&customLookAndFeel);
    volumeSlider2.setLookAndFeel(&customLookAndFeel);

    volumeLabel1.setText("VOL1", juce::dontSendNotification);
    volumeLabel1.attachToComponent(&volumeSlider1, false);
    volumeLabel1.setJustificationType(juce::Justification::centred);

    volumeLabel2.setText("VOL2", juce::dontSendNotification);
    volumeLabel2.attachToComponent(&volumeSlider2, false);
    volumeLabel2.setJustificationType(juce::Justification::centred);
}

mixerComponent::~mixerComponent() {
    volumeSlider1.setLookAndFeel(nullptr);
    volumeSlider2.setLookAndFeel(nullptr);
}

void mixerComponent::setDeck1(DJAudioPlayer* deckPlayerSource1) {
    deckPlayer1 = deckPlayerSource1;
}

void mixerComponent::setDeck2(DJAudioPlayer* deckPlayerSource2) {
    deckPlayer2 = deckPlayerSource2;
}

void mixerComponent::sliderValueChanged(Slider* slider) {
    if (slider == &volumeSlider1 && deckPlayer1 != nullptr) {
        deckPlayer1->setGain(slider->getValue());
    }
    if (slider == &volumeSlider2 && deckPlayer2 != nullptr) {
        deckPlayer2->setGain(slider->getValue());
    }
}

void mixerComponent::paint(juce::Graphics& g) {
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void mixerComponent::resized() {
    auto columnWidth = getWidth() / 6;
    auto rowHeight = getHeight() / 12;

    volumeSlider1.setBounds(columnWidth - columnWidth / 2, rowHeight * 3, columnWidth, rowHeight * 8);
    volumeSlider2.setBounds(columnWidth * 5, rowHeight * 3, columnWidth, rowHeight * 8);
}