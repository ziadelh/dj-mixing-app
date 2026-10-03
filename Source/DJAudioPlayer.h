/*
  ==============================================================================

	DJAudioPlayer.h
	Created: 28 Jan 2024 12:38:19pm
	Author:  ziade

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class DJAudioPlayer : public AudioSource {
public:
	DJAudioPlayer(AudioFormatManager& formatManager);
	~DJAudioPlayer();

	void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
	void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) override;
	void releaseResources() override;


	void loadURL(URL file);
	void play();
	void stop();
	void setPosition(double posInSecs);
	void setGain(double gain);
	void setSpeed(double ratio);
	void setPositionRelative(double pos);

	double getPositionRelative();

private:
	AudioFormatManager& formatManager;
	AudioTransportSource transportSource;
	std::unique_ptr<AudioFormatReaderSource> readerSource;
	ResamplingAudioSource resampleSource{ &transportSource, false, 2 };

};