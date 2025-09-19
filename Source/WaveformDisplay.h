/*
  ==============================================================================

	WaveformDisplay.h
	Created: 30 Jan 2024 9:20:08pm
	Author:  cpng

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "CustomDesign.h"

/**
 * WaveformDisplay class is responsible for displaying the waveform of an audio track.
 * It uses an AudioThumbnail to visualize the waveform and provides methods to load
 * audio tracks, set the current position, and draw a progression bar.
 * 
 * This class inherits from juce::Component and juce::ChangeListener to handle UI 
 * rendering and change events respectively.
 */
class WaveformDisplay : public juce::Component,
						public juce::ChangeListener
{
public: 
	/**
	 * Constructor for WaveformDiaplay class.
	 * 
	 * @param formatManagerToUse   The AudioFormatManager to use for audio formats.
     * @param cacheToUse           The AudioThumbnailCache to use for thumbnail caching.
	 */
	WaveformDisplay(juce::AudioFormatManager& formatManagerToUse,
		juce::AudioThumbnailCache& cacheToUse);

	/**
	 * Destructor for the WaveformDisplay class.
	 */
	~WaveformDisplay() override;

	/**
	 * Paints the waveform display component.
	 * 
	 * @param g    The Graphics context to paint.
	 */
	void paint(juce::Graphics&) override;

	/**
	 * Resizes the waveform display component.
	 */
	void resized() override;

	/**
	 * Draws the progression bar indicating the current position of the audio track.
	 *
	 * @param g    The Graphics context to draw.
	 */
	void drawProgressionBar(juce::Graphics& g) const;

	/**
	 * Displays a message indicating that no track is loaded.
	 *
	 * @param g    The Graphics context to draw.
	 */
	void displayLoadTrackMessage(juce::Graphics& g);

	/**
	 * Loads an audio track from the specified URL.
	 *
	 * @param audioURL     The URL of the audio track to load.
     */
	void loadURL(juce::URL audioURL);

	/**
	 * Callback function invoked when the change broadcaster sends a change signal.
	 *
	 * @param source   The ChangeBroadcaster object that triggered the change.
	 */
	void changeListenerCallback(juce::ChangeBroadcaster* source) override;

	/**
	 * Sets the relative position of the progression bar.
	 *
	 * @param pos  The relative position (0.0 to 1.0) of the progression bar.
	 */
	void setPositionRelative(double pos);

private:
	/**
	 * The audio thumbnail for displaying waveforms.
	 */
	juce::AudioThumbnail audioThumb;

	/**
	 * Flag to indicate whether a file is loaded.
	 */
	bool fileLoaded;

	/**
	 * The position of the progression bar.
	 */
	double position;

	/**
	 * Custom design settings for the waveform display.
	 */
	CustomDesign customDesign;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WaveformDisplay)
};