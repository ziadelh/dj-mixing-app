/*
  ==============================================================================

    DeckGUI.cpp
    Created: 28 Jan 2024 12:38:57pm
    Author:  ziade

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DeckGUI.h"

//==============================================================================
DeckGUI::DeckGUI(DJAudioPlayer* _player,
    PlaylistComponent* _playlistComponent,
    AudioFormatManager& formatManagerToUse,
    AudioThumbnailCache& cacheToUse,
    int deckToUse):
    player(_player),
    playlistComponent(_playlistComponent),
    waveformDisplay(formatManagerToUse, cacheToUse),
    deck(deckToUse)
{
    //waveform viewer
    addAndMakeVisible(waveformDisplay);

    //play and stop buttons
    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    //position slider
    addAndMakeVisible(positionSlider);
    addAndMakeVisible(speedSlider);

    playButton.addListener(this);
    stopButton.addListener(this);

    positionSlider.addListener(this);
    speedSlider.addListener(this);

    positionSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    positionSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);

    speedSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    speedSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);

    speedSlider.setRange(0.5, 2, 0);
    speedSlider.setMouseDragSensitivity(80);


    startTimer(200);

    addMouseListener(this, true);

   
}

DeckGUI::~DeckGUI()
{
    stopTimer();
}

bool DeckGUI::isInterestedInFileDrag(const StringArray& files) {
    return true;
}
void DeckGUI::filesDropped(const StringArray& files, int x, int y) {
    
    // a file dropped on a deck loads the first one, with its waveform
    if (files.size() > 0) {
        loadTrack(files[0]);
    }
    
}

void DeckGUI::loadTrack(const juce::String& trackFilePath) {
    player->loadURL(juce::URL(juce::File(trackFilePath)));
    waveformDisplay.loadURL(juce::URL(juce::File(trackFilePath)));
}

void DeckGUI::buttonClicked(Button* button) {
    if (button == &playButton) {
        player->play();
    }
    if (button == &stopButton) {
        player->stop();
    }
}

void DeckGUI::mouseDown(const MouseEvent& event) {
    if (event.eventComponent == &waveformDisplay) {
        double clickX = event.position.x;
        double waveformWidth = waveformDisplay.getWidth();
        double relativePosition = clickX / waveformWidth;

        player->setPositionRelative(relativePosition);
        positionSlider.setValue(relativePosition);
    }
}


void DeckGUI::sliderValueChanged(Slider* slider) {
    if (slider == &positionSlider) {
        player->setPositionRelative(slider->getValue());
    }
    if (slider == &speedSlider) {
        player->setSpeed(slider->getValue());      
    }
}

void DeckGUI::timerCallback() {
    waveformDisplay.setPositionRelative(player->getPositionRelative());
}



void DeckGUI::paint (juce::Graphics& g)
{
    double margin = 4;
    double rowHeight = getWidth() / 12;

    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));

    g.setColour(juce::Colours::black);
    g.fillRect(0, 0, getWidth(), 4);
    g.fillRect(0, 0, 4, getHeight());
    g.fillRect(getWidth()-4, 0, 4, getHeight());
    g.fillRect(0, getHeight() - 4, getWidth(), 4);

    g.setColour(juce::Colours::black);
    g.fillRect(0, 0, getWidth(), rowHeight*5+margin);
}

void DeckGUI::resized()
{

    double columnWidth = getWidth() / 6;
    double rowHeight = getWidth() / 12;

    waveformDisplay.setBounds(columnWidth*0.25, rowHeight*0.5, columnWidth * 6 - columnWidth * 0.5, rowHeight * 4);
    
    
    if (deck == 0) {
        positionSlider.setBounds(columnWidth * 0.15, rowHeight * 5.5, columnWidth * 5, rowHeight * 8);
        speedSlider.setBounds(columnWidth * 5, rowHeight * 8, columnWidth, rowHeight * 8);
        playButton.setBounds(columnWidth * 0.5, rowHeight * 15, columnWidth * 1.5, rowHeight * 2);
        stopButton.setBounds(columnWidth * 3.5 , rowHeight * 15, columnWidth * 1.5, rowHeight * 2);
    }
    if(deck==1){
        positionSlider.setBounds(columnWidth, rowHeight * 5.5, columnWidth * 5, rowHeight * 8);
        speedSlider.setBounds(0, rowHeight * 8, columnWidth, rowHeight * 8);
        playButton.setBounds(columnWidth, rowHeight * 15, columnWidth * 1.5, rowHeight * 2);
        stopButton.setBounds(columnWidth * 4 , rowHeight * 15, columnWidth * 1.5, rowHeight * 2);
    }

}
