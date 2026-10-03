/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

MainComponent::MainComponent() {
    setSize(800, 600);

    if (RuntimePermissions::isRequired(RuntimePermissions::recordAudio) &&
        !RuntimePermissions::isGranted(RuntimePermissions::recordAudio)) {
        RuntimePermissions::request(RuntimePermissions::recordAudio,
            [&](bool granted) { if (granted) setAudioChannels(2, 2); });
    }
    else {
        setAudioChannels(0, 2);
    }

    //audio mixer connections
    audioMixer.setDeck1(&player1);
    audioMixer.setDeck2(&player2);

    //UI components
    addAndMakeVisible(leftDeck);
    addAndMakeVisible(rightDeck);
    addAndMakeVisible(tracklist);
    addAndMakeVisible(audioMixer);

    formatManager.registerBasicFormats();

    tracklist.setDecks(&leftDeck, &rightDeck);
}

MainComponent::~MainComponent() {
    shutdownAudio();
}

void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate) {
    tracklist.prepareToPlay(samplesPerBlockExpected, sampleRate);
    player1.prepareToPlay(samplesPerBlockExpected, sampleRate);
    player2.prepareToPlay(samplesPerBlockExpected, sampleRate);

    mixerSource.addInputSource(&player1, false);
    mixerSource.addInputSource(&player2, false);

    mixerSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void MainComponent::getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) {
    mixerSource.getNextAudioBlock(bufferToFill);
}

void MainComponent::releaseResources() {
    tracklist.releaseResources();
    mixerSource.removeAllInputs();
    mixerSource.releaseResources();
    player1.releaseResources();
    player2.releaseResources();
}

void MainComponent::paint(Graphics& g) {
    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
}

void MainComponent::resized() {
    leftDeck.setBounds(0, 0, getWidth() / 3, getHeight() / 3 * 2);
    rightDeck.setBounds(getWidth() / 3 * 2, 0, getWidth() / 3, getHeight() / 3 * 2);
    audioMixer.setBounds(getWidth() / 3, 0, getWidth() / 3, getHeight() / 3 * 2);
    tracklist.setBounds(0, getHeight() / 3 * 2, getWidth(), getHeight() / 3);
}
