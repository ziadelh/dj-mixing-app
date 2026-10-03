/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "DJAudioPlayer.h"
#include "DeckGUI.h"
#include "PlaylistComponent.h"
#include "mixerComponent.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent : public AudioAppComponent {
public:
    MainComponent();
    ~MainComponent();

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    void paint(Graphics& g) override;
    void resized() override;

private:
    AudioFormatManager formatManager;        
    AudioThumbnailCache thumbCache{ 100 };    
    DJAudioPlayer player1{ formatManager };    
    DJAudioPlayer player2{ formatManager };    

    DeckGUI leftDeck{ &player1, &tracklist, formatManager, thumbCache, 0 }; 
    DeckGUI rightDeck{ &player2, &tracklist, formatManager, thumbCache, 1 }; 

    mixerComponent audioMixer;              
    MixerAudioSource mixerSource;            
    PlaylistComponent tracklist{ formatManager }; 

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};