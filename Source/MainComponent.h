/*
  ==============================================================================

	MainComponent.h
	Created: 30 Jan 2024 9:00:05pm
	Author:  cpng

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include "DeckGUI.h"
#include "PlaylistComponent.h"
#include "SoundEffect.h"
#include "AudioTrack.h"

class MainComponent : public juce::AudioAppComponent,
	public juce::Slider::Listener
{
public:
	/**
	 * Constructor for the MainComponent class.
	 * Sets up the main GUI components, including deckGUI1, deckGUI2, 
     * playlistComponent, soundEffect, and controlSlider.
	 */
	MainComponent();

	/**
	 * Destructor for the MainComponent class.
	 */
	~MainComponent() override;

	/** 
	 * Pure virtual function of AudioAppComponent class.
	 * Prepares the audio system to play audio.
	 *
	 * @param samplesPerBlockExpected	The sample numbers per audio block expected.
     * @param sampleRate				The sample rate for audio.
	 */
	void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
	
	/**
	 * Pure virtual function of AudioAppComponent class.
	 * Retrieves the next audio block to be played.
	 *
	 * @param bufferToFill				Reference to the AudioSourceChannelInfo struct
	 *									that holds information about the audio buffer to be filled.
	 */
	void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
	
	/**
	 * Pure virtual function of AudioAppComponent class.
	 * Releases the audio resources.
	 */
	void releaseResources() override;

	/**
	 * Paints the GUI.
	 * 
	 * @param g The Graphics object used for rendering.
	 */
	void paint(juce::Graphics& g) override;

	/**
	 * Resizes and positions the GUI components within the MainComponent.
	 */
	void resized() override;

	/**
	 * Handles slider value changes for the crossfade between Deck 1 and 2.
	 *
	 * @param slider The slider whose value has changed.
	 */
	void sliderValueChanged(juce::Slider* slider) override;

private:
	/**
	 * Manages audio formats.
	 */
	juce::AudioFormatManager formatManager;

	/**
	 * Cache for audio thumbnails.
	 */
	juce::AudioThumbnailCache thumbCache{ 100 };

	/** 
	 * Create 1st player with GUI on the left.
	 */
	DJAudioPlayer player1{ formatManager };
	DeckGUI deckGUI1{ &player1, formatManager, thumbCache, true };

	/** 
	 * Create 2nd player with GUI on the right.
	 */
	DJAudioPlayer player2{ formatManager };
	DeckGUI deckGUI2{ &player2, formatManager, thumbCache, false };

	/** 
	 * Mixes both players audio together.
	 */
	juce::MixerAudioSource mixerSource;

	/**
	 * Playlist component that interacts with the audio players.
	 */
	PlaylistComponent playlistComponent{ formatManager, &deckGUI1, &deckGUI2 };
	
	/**
	 * DJ audio player specifically for sound effects.
	 */
	DJAudioPlayer playerSoundEffect{ formatManager };

	/**
	 * Sound effect GUI component that interacts with the sound effect player.
	 */
	SoundEffect soundEffect{ &playerSoundEffect };

	/**
	 * Calling for the label font "Crossfader"
	 */
	CustomDesign customDesign;

	/**
	 * Calling for the label font for main title Ottodeck
	 */
	DiscDesign discDesign;

	/**
	 * Slider control for crossfading between the two players.
	 */
	juce::Slider controlSlider;

	/**
	 * Slider label for crossfading between the two players.
	 */
	juce::Label controlLabel;

	/**
	 * Setup and design sliders with specified parameters.
	 *
	 * @param slider			Reference to the slider object to set up.
	 * @param label             Label for slider.
	 */
	void setupSlider(juce::Slider& slider, juce::Label& label);

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
