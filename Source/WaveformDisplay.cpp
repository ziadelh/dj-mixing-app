/*
  ==============================================================================

    WaveformDisplay.cpp
    Created: 4 Mar 2024 8:09:03pm
    Author:  ziade

  ==============================================================================
*/

#include <../JuceLibraryCode/JuceHeader.h>
#include "WaveformDisplay.h"

//==============================================================================
WaveformDisplay::WaveformDisplay(AudioFormatManager& formatManagerToUse,
    AudioThumbnailCache& cacheToUse):
    audioThumbnail(1000, formatManagerToUse, cacheToUse), 
    fileLoaded(false),
    position(0)
{
    
    audioThumbnail.addChangeListener(this);
    addMouseListener(this, true);
}


WaveformDisplay::~WaveformDisplay()
{
}

void WaveformDisplay::loadURL(URL audioURL) {
    audioThumbnail.clear();
    fileLoaded = audioThumbnail.setSource(new URLInputSource(audioURL)); 
}

void WaveformDisplay::changeListenerCallback(ChangeBroadcaster* source) {
    repaint();
}

void WaveformDisplay::setPositionRelative(double pos) {
    if (pos != position) {
        position = pos;
        repaint();
    }
}


void WaveformDisplay::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
    g.setColour(Colours::grey);
    g.drawRect(getLocalBounds(), 1);

    if (fileLoaded) {
        if (audioThumbnail.getTotalLength() > 0) {
            float playPos = position;

            juce::Rectangle<int> leftBounds(0, 0, playPos * getWidth(), getHeight());

            juce::Rectangle<int> rightBounds(playPos * getWidth(), 0, getWidth() - playPos * getWidth(), getHeight());

            g.setColour(Colours::cornflowerblue);
            audioThumbnail.drawChannel(g, leftBounds, 0, playPos * audioThumbnail.getTotalLength(), 0, 1.0f);

            g.setColour(Colours::beige);
            audioThumbnail.drawChannel(g, rightBounds, playPos * audioThumbnail.getTotalLength(), audioThumbnail.getTotalLength(), 0, 1.0f);

            g.setColour(Colours::darkred);
            g.drawLine(playPos * getWidth(), 0, playPos * getWidth(), getHeight(), 1.2f);

            
        }
    }
    else {
        g.setFont(20.0f);
        g.drawText("Not loaded yet", getLocalBounds(), Justification::centred, true);
    }
}


void WaveformDisplay::resized()
{

}
