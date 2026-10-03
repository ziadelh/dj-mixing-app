/*
  ==============================================================================

    WaveformDisplay.h
    Created: 4 Mar 2024 8:09:03pm
    Author:  ziade

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class WaveformDisplay  : public juce::Component,
    public juce::ChangeListener
{
public:
    WaveformDisplay(AudioFormatManager& formatManagerToUse, 
        AudioThumbnailCache& cacheToUse);
    ~WaveformDisplay() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void loadURL(URL audioURL);

    void changeListenerCallback(ChangeBroadcaster* source) override;

    void setPositionRelative(double pos);

private:
    AudioThumbnail audioThumbnail;
    bool fileLoaded;
    double position;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformDisplay)
};
