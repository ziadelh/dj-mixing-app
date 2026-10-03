/*
  ==============================================================================

    DJAudioPlayer.cpp
    Created: 28 Jan 2024 12:38:19pm
    Author:  ziade

  ==============================================================================
*/

#include "DJAudioPlayer.h"

DJAudioPlayer::DJAudioPlayer(AudioFormatManager& _formatManager)
    : formatManager(_formatManager),
    resampleSource(&transportSource, false, 2) {
    
}

DJAudioPlayer::~DJAudioPlayer() {

}

// Prepare
void DJAudioPlayer::prepareToPlay(int samplesPerBlockExpected, double sampleRate) {
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    resampleSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

//next block of audio 
void DJAudioPlayer::getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) {
    resampleSource.getNextAudioBlock(bufferToFill);
}

// Releases
void DJAudioPlayer::releaseResources() {
    transportSource.releaseResources();
    resampleSource.releaseResources();
}

// Load an audio file 
void DJAudioPlayer::loadURL(URL audioURL) {
    auto* reader = formatManager.createReaderFor(audioURL.createInputStream(URL::InputStreamOptions(URL::ParameterHandling::inAddress)));
    if (reader != nullptr) {
        std::unique_ptr<AudioFormatReaderSource> newSource(new AudioFormatReaderSource(reader, true));
        transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
        readerSource.reset(newSource.release());
    }
}

// Start
void DJAudioPlayer::play() {
    if (transportSource.getLengthInSeconds() > 0) {
        transportSource.start();
    }
}

// Stop
void DJAudioPlayer::stop() {
    transportSource.stop();
}

//playback position
void DJAudioPlayer::setPosition(double posInSecs) {
    transportSource.setPosition(posInSecs);
}

void DJAudioPlayer::setPositionRelative(double pos) {
    double length = transportSource.getLengthInSeconds();
    if (length > 0) {
        setPosition(length * pos);
    }
}

//volume of the playback 
void DJAudioPlayer::setGain(double gain) {
    transportSource.setGain(juce::jlimit(0.0, 1.0, gain));
}

//playback speed
void DJAudioPlayer::setSpeed(double ratio) {
    resampleSource.setResamplingRatio(ratio);
}

double DJAudioPlayer::getPositionRelative() {
    double length = transportSource.getLengthInSeconds();
    return length > 0 ? transportSource.getCurrentPosition() / length : 0.0;
}

