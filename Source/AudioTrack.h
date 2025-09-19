/*
  ==============================================================================

    AudioTrack.h
    Created: 4 Feb 2024 2:42:19pm
    Author:  cpng

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

/**
 * AudioTrack class provides functionality to manage audio tracks with their
 * metadata including title, URL, length, and file type extension.
 */
class AudioTrack
{
public:
    /**
     * Constructor for AudioTrack object.
     * Used by PlaylistComponent.
     * 
     * @param _audioTrackTitle      Audio track's title.
     * @param _audioTrackURL        Audio track's URL.
     * @param _audioTrackLength     Audio track's length.
     * @param _audioFileType        Audio track's file type.
     */
    AudioTrack(juce::String _audioTrackTitle,
               juce::String _audioTrackURL,
               juce::String _audioTrackLength,
               juce::String _audioFileType);

    /**
     * Destructor for the AudioTrack.
     */
    ~AudioTrack();

    /**
     * Constructor for AudioTrack object.
     * Used by SoundEffect.
     *
     * @param _audioTrackTitle      Audio track's title.
     * @param _audioTrackURL        Audio track's URL.
     */
    AudioTrack(juce::String _audioTrackTitle,
               juce::String _audioTrackURL);

    /**
     * Retrieves the audio track's title.
     * 
     * @return audio track's title.
     */
    juce::String getAudioTrackTitle() const;

    /**
     * Retrieves the audio track's URL.
     *
     * @return audio track's URL.
     */
    juce::String getAudioTrackURL() const;

    /**
     * Retrieves the audio track's length.
     *
     * @return audio track's length.
     */
    juce::String getAudioTrackLength() const;
    
    /**
     * Retrieves the audio track's file type.
     *
     * @return audio track's file type.
     */
    juce::String getAudioFileType() const;


private:
    /**
     * Metadata of audio track.
     */
    juce::String audioTrackTitle
                ,audioTrackURL
                ,audioTrackLength
                ,audioFileType;
};