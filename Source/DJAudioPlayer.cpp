/*
  ==============================================================================

	DJAudioPlayer.cpp
	Created: 30 Jan 2024 9:12:05pm
	Author:  cpng

  ==============================================================================
*/

#include "DJAudioPlayer.h"

DJAudioPlayer::DJAudioPlayer(juce::AudioFormatManager& _formatManager)
	: formatManager(_formatManager), 
	sampleRate(44100.0)
{

}

DJAudioPlayer::~DJAudioPlayer()
{

}

void DJAudioPlayer::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
	this->sampleRate = sampleRate;
	transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
	resampleSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void DJAudioPlayer::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
	resampleSource.getNextAudioBlock(bufferToFill);
}

void DJAudioPlayer::releaseResources()
{
	transportSource.releaseResources();
	resampleSource.releaseResources();
}

void DJAudioPlayer::loadURL(juce::URL audioURL)
{
	// Create audio reader from the URL
	auto* reader = formatManager.createReaderFor(audioURL.createInputStream(false));
	
	// Check if the reader is not null pointer which means successfully created
	if (reader != nullptr)
	{
		// Create new audio format reader source
		std::unique_ptr<juce::AudioFormatReaderSource> newSource(new juce::AudioFormatReaderSource(reader, true));
		
		// Set the source for transport source and release the unique pointer
		transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
		readerSource.reset(newSource.release());
	}

	// Get the title to display the title name on top of the DeckGUI when track are loaded
	audioTrackTitle = getTitle(audioURL);
}

// Sets audio player's gain (volume)
void DJAudioPlayer::setGain(double gain)
{
	if (gain < 0 || gain > 1.0)
	{
		DBG("DJAudioPlayer::setGain gain should be between 0 and 1");
	}
	else {
		transportSource.setGain(gain);
	}
}

// Sets playback speed
void DJAudioPlayer::setSpeed(double ratio)
{
	if (ratio <= 0 || ratio > 3.0)
	{
		DBG("DJAudioPlayer::setSpeed ratio should be between 0 and 3");
	}
	else {
		resampleSource.setResamplingRatio(ratio);
	}
}

// Sets playback position in sec
void DJAudioPlayer::setPosition(double posInSecs)
{
	transportSource.setPosition(posInSecs);
}

// Sets playback position relative to total length
void DJAudioPlayer::setPositionRelative(double pos)
{
	if (pos < 0 || pos > 1.0)
	{
		DBG("DJAudioPlayer::setPositionRelative pos should be between 0 and 1");
	}
	else 
	{
		// Calculate the position in sec relative to the total length 
		double posInSecs = transportSource.getLengthInSeconds() * pos;
		setPosition(posInSecs);
	}
}

// Return the playback position relative to the total length
double DJAudioPlayer::getPositionRelative()
{
	return transportSource.getCurrentPosition() / transportSource.getLengthInSeconds();
}

juce::String DJAudioPlayer::getTitle(const juce::URL& audioURL)
{
	return juce::File(audioURL.getLocalFile()).getFileNameWithoutExtension();
}

// Play the track
void DJAudioPlayer::start()
{
	transportSource.start();
}

// Pause the track
void DJAudioPlayer::pause()
{
	transportSource.stop();
}

// Stop the track
void DJAudioPlayer::stop()
{
	transportSource.setPosition(0);
	transportSource.stop();
}

// Fast forward 10 sec
void DJAudioPlayer::fastForward()
{
	auto position = transportSource.getNextReadPosition();
	
	// Calculate new position and fast forward by 10 sec
	auto newPosition = position + (sampleRate * 10.0);

	// Check if the pos is within the length of audio
	if (newPosition <= transportSource.getTotalLength())
	{
		transportSource.setNextReadPosition(newPosition);
	}
	else
	{
		// When exceeds the length of the audio, prevent fast forward
		DBG("Cannot fast-forward beyond end of audio");
	}
}

// Rewind backward 10 sec
void DJAudioPlayer::rewind()
{
	auto position = transportSource.getNextReadPosition();

	// Calculate new position and rewind backward by 10 sec
	auto newPosition = position - (sampleRate * 10.0);

	// Ensure the position is not before the start of the audio
	if (newPosition >= 0)
	{
		transportSource.setNextReadPosition(newPosition);
	}
	else
	{
		// Before the start of the audio, prevent rewind backward
		DBG("Cannot rewind beyond the start of the audio");
	}
}

// Replay audio track
void DJAudioPlayer::replay(bool replayEnable)
{
	if (readerSource != nullptr)
	{
		if (replayEnable)
		{
			DBG("<< Replay Enable >>");
		}
		else
		{
			DBG("<< Replay Disable >>");
		}

		// Set replay looping based on the replayEnable status
		readerSource->setLooping(replayEnable);
	}
	else
	{
		DBG("<< Cannot set looping for replay >>");
	}
}
