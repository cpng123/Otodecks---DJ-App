/*
  ==============================================================================

    AudioTrack.cpp
    Created: 4 Feb 2024 2:42:19pm
    Author:  cpng

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AudioTrack.h"

// Constructor being called from PlaylistComponent class.
AudioTrack::AudioTrack(juce::String _audioTrackTitle,
	                   juce::String _audioTrackURL,
                       juce::String _audioTrackLength,
                       juce::String _audioFileType)
	: audioTrackTitle(_audioTrackTitle),
	  audioTrackURL(_audioTrackURL),
      audioTrackLength(_audioTrackLength),
      audioFileType(_audioFileType)
{

}

// Destructor
AudioTrack::~AudioTrack() 
{

}

// Constructor overloading being called from SoundEffect class.
AudioTrack::AudioTrack(juce::String _audioTrackTitle,
    juce::String _audioTrackURL)
    : audioTrackTitle(_audioTrackTitle),
    audioTrackURL(_audioTrackURL),
    audioTrackLength(""),
    audioFileType("")
{

}

// Getter for title
juce::String AudioTrack::getAudioTrackTitle() const
{
    return audioTrackTitle;
}

// Getter for URL
juce::String AudioTrack::getAudioTrackURL() const
{
    return audioTrackURL;
}

// Getter for length
juce::String AudioTrack::getAudioTrackLength() const
{
    return audioTrackLength;
}

// Getter for file type
juce::String AudioTrack::getAudioFileType() const
{
    return audioFileType;
}
