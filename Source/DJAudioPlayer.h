/*
  ==============================================================================

	DJAudioPlayer.h
	Created: 30 Jan 2024 9:12:05pm
	Author:  cpng

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

/**
 * The DJAudioPlayer class represents an audio player which 
 * provides functionalities to load, play, pause, stop, rewind, 
 * fast-forward, and set the playback position of audio tracks.
 */
class DJAudioPlayer : public juce::AudioSource
{
public:

	DJAudioPlayer(juce::AudioFormatManager& _formatManager);
	~DJAudioPlayer();

	/* 
	 * Prepare the audio source ready for playing.
	 * One of the pure virtual function by subclasses of AudioSource class.
	 * 
	 * @param samplesPerBlockExpected	The expected samples number per block.
	 * @param sampleRate					The audio sample rate.
	 */
	void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
	
	/*
	 * Retrieve and play next audio block.
	 * Pure virtual function.
	 * 
	 * @param bufferToFill Takes in information about the buffer to be filled.
	 */
	void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
	
	/*
	 * Release any audio resources including buffers allocated previously.
	 * This function will be called whenever the audio source are no longer required.
	 * Pure virtual function.
	 */
	void releaseResources() override;

	/** 
	 * Loads audio from the given URL.
	 * 
	 * @param audioURL The audio's URL to load.
	 */
	void loadURL(juce::URL audioURL);

	/** 
	 * Sets the gain of the audio player.
	 * 
	 * @param gain The gain value to set.
	 */
	void setGain(double gain);

	/** 
	 * Sets the playback 
	 
	 ratio of the audio player.
	 * 
	 * @param ratio The playback speed ratio to set.
	 */
	void setSpeed(double ratio);

	/** 
	 * Sets the playback position in seconds.
	 * 
	 * @param posInSecs The playback position to set in seconds.
	 */
	void setPosition(double posInSecs);

	/** 
	 * Sets the playback position relative to the total length.
	 * 
	 * @param pos The relative playback position.
     */
	void setPositionRelative(double pos);

	/** 
	 * Returns the playback position relative to the total length.
	 * 
	 * @return The relative playback position.
	 */
	double getPositionRelative();

	/** 
	 * Starts playback of the audio track. 
	 */
	void start();

	/**
	 * Pause playback of the audio track.
	 */
	void pause();

	/**
	 * Stops playback of the audio track and resets the position to the beginning.
	 */
	void stop();

	/**
	 * Fast-forwards the playback by 10 seconds.
	 */
	void fastForward();

	/**
	 * Rewinds the playback by 10 seconds.
	 */
	void rewind();

	/**
	 * Enables or disables replaying of the audio track.
	 * 
     * @param replayEnable True to enable replay, false to disable.
	 */
	void replay(bool replayEnable);

	/**
	 * Retrieves the audio track's title from the given URL.
	 *
	 * @param audioURL		The audio track's URL.
	 * @return				The audio track's title.
	 */
	juce::String getTitle(const juce::URL& audioURL);

	/**
	 * Audio track title.
	 */
	juce::String audioTrackTitle;

private:
	/**
	 * The AudioFormatManager used for audio file handling.
	 */
	juce::AudioFormatManager& formatManager;

	/**
	 * The source to read audio format.
	 */
	std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
	
	/**
	 * The transport source for audio playback.
	 */
	juce::AudioTransportSource transportSource;

	/**
	 * The resampling audio source for the sample rate conversion.
	 */
	juce::ResamplingAudioSource resampleSource{ &transportSource, false, 2 };
	
	/**
	 * The audio sample rate.
	 */
	double sampleRate;
};