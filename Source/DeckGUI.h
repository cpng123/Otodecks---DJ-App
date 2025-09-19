/*
  ==============================================================================

	DeckGUI.h
	Created: 30 Jan 2024 9:15:56pm
	Author:  cpng

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include "WaveformDisplay.h"
#include "AudioTrack.h"
#include "CustomDesign.h"
#include "DiscDesign.h"

//==============================================================================
/**
 * DeckGUI class handles the graphical user interface for controlling audio playback
 * including various buttons, sliders and waveform displays.
 * 
 * This class inherits from juce::Component, juce::Button::Listener, juce::Slider::Listener,
 * juce::FileDragAndDropTarget, and juce::Timer to handle various UI 
 * and interaction functionalities.
 */
class DeckGUI : public juce::Component,
	public juce::Button::Listener,
	public juce::Slider::Listener,
	public juce::FileDragAndDropTarget,
	public juce::Timer
{
public:
	/**
	 * Constructor for the DeckGUI class.
	 *
	 * @param _player				Reference to the DJAudioPlayer.
	 * @param formatManagerToUse	Reference to the AudioFormatManager.
	 * @param cacheToUse			Reference to the AudioThumbnailCache.
	 * @param isDeckGUI1			Boolean flag indicating whether this DeckGUI instance 
	 *								is associated with first deck (true).
	 */
	DeckGUI(DJAudioPlayer* player,
		juce::AudioFormatManager& formatManagerToUse,
		juce::AudioThumbnailCache& cacheToUse,
		bool isDeckGUI1);
	
	/**
	 * Destructor for the DeckGUI class.
	 */
	~DeckGUI();

	/**
	 * Paint method override to perform custom drawing.
	 *
	 * @param g Graphics context to perform drawing operations.
	 */
	void paint(juce::Graphics& g) override;

	/**
	 * Resized method override to handle component resizing.
	 */
	void resized() override;

	/**
	 * ButtonClicked method override to handle button click events.
	 *
	 * @param button Pointer to the clicked button.
	 */
	void buttonClicked(juce::Button*) override;

	/**
	 * Handles slider value changes in the DeckGUI component.
	 *
	 * @param slider The slider whose value has changed.
	 */
	void sliderValueChanged(juce::Slider* slider) override;

	/**
	 * Allow file drag events.
	 *
	 * @param files		An array of file paths being dragged.
	 * @return			True if the DeckGUI is interested in file drag events, otherwise false.
	 */
	bool isInterestedInFileDrag(const juce::StringArray& files) override;

	/**
	 * Called when files are dropped onto the DeckGUI.
	 *
	 * @param files		An array of file paths that were dropped.
	 * @param x			The x-coordinate of the drop location.
	 * @param y			The y-coordinate of the drop location.
	 */
	void filesDropped(const juce::StringArray& files, int x, int y) override;

	/**
	 * Callback function called by the timer to update the waveform display position.
	 */
	void timerCallback() override;

	/**
	 * Loads audio URL into the player and waveform display.
	 *
	 * @param audioURL	The URL of the audio to load.
	 */
	void loadToPlaylist(const juce::URL& audioURL);

	/**
	 * Sets the volume level of DeckGUI's associated player.
	 * Being call from MainComponent to adjusts the crossfade volume between two deck.
	 * 
	 * @param volume The volume level.
	 */
	void setVolume(double volume);

private:
	/**
	 * Setup sliders with specified parameters.
	 *
	 * @param slider			Reference to the slider object to set up.
	 * @param initialValue		Initial value of the slider.
	 * @param minValue			Minimum value of the slider.
	 * @param maxValue			Maximum value of the slider.
	 * @param doubleclick		Determines whether double-click is enabled.
	 * @param style				Style of the slider.
	 * @param useCustomDesign	Indicates if custom design is used.
	 * @param setColour			Indicates if slider color should be set.
	 * @param setDiscDesign		Indicates if disc design is used.
	 */
	void setupSlider(juce::Slider& slider, float initialValue,
		float minValue, float maxValue, bool doubleclick,
		juce::Slider::SliderStyle style, bool useCustomDesign, 
		bool setColour, bool setDiscDesign);

	/**
	 * Setup label for slider with specified design.
	 * 
	 * @param label				Label for slider.
	 * @param slider			Reference to the slider object to setup.
	 */
	void setupLabel(juce::Label& label, juce::Slider& slider);

	/**
	 * Sets up image button with specified parameters.
	 *
	 * @param button			Reference to the image button object to setup.
	 * @param imageData			Pointer to the image data.
	 * @param imageDataSize		Size of the image data.
	 */
	void setupImageButton(juce::ImageButton& button, const char* imageData, int imageDataSize);

	/**
	 * Sets up play and pause buttons.
	 */
	void setupPlayPauseButton();

	/**
	 * Handles the action when the stop button is clicked.
	 */
	void handleStopButton();

	/**
	 * Handles the action when the play/pause button is clicked.
	 */
	void handlePlayPauseButton();

	/**
	 * Handles the action when the fast forward button is clicked.
	 */
	void handleFastForwardButton();

	/**
	 * Handles the action when the rewind button is clicked.
	 */
	void handleRewindButton();

	/**
	 * Handles the action when the replay button is clicked.
	 */
	void handleReplayButton();

	/**
	 * Sets the images and mouse cursor for the given ImageButton with image data.
	 *
	 * @param button			The ImageButton to set images for.
	 * @param imageData			A pointer to the image data.
	 * @param imageDataSize		The size of the image data.
	 */
	void setImageButton(juce::ImageButton& button, 
		const void* imageData, int imageDataSize);

	/**
	 * Enumeration representing the state of playback.
	 */
	enum class PlayState { Play, Pause };

	/**
	 * Set current state of playback.
	 */
	PlayState playState{ PlayState::Pause };

	/**
	 * Updates the UI when the playback is in the playing state.
	 */
	void playing();

	/**
	 * Updates the UI when the playback is in the pausing state.
	 */
	void pausing();

	/**
	 * Image used for the play and pause button.
	 */
	juce::Image playImage, pauseImage;

	/**
	 * Button to stop, play, pause, fast forward, rewind, and replay audio.
	 */
	juce::ImageButton imgStopButton { "STOP" }
					 ,imgPlayButton { "PLAY" }
					 ,imgPauseButton{ "PAUSE" }
					 ,imgFastButton { "FAST FORWARD" }
					 ,imgRewindButton { "REWIND" }
					 ,imgReplayButton { "REPLAY" };

	/**
	* Slider for volume, speed, and audio position control.
	*/
	juce::Slider volSlider, speedSlider, posSlider, discSlider;

	/**
	 * Label for displaying the speed title term.
	 */
	juce::Label speedLabel;

	/**
	 * File chooser for selecting audio files.
	 */
	juce::FileChooser fChooser{ "Select a file..." };

	/**
	 * Pointer to the DJ audio player.
	 */
	DJAudioPlayer* player;

	/**
	 * Waveform display component.
	 */
	WaveformDisplay waveformDisplay;

	/**
	 * Custom design for UI elements.
	 */
	CustomDesign customDesign;

	/**
	 * Custom design for the Disc DJ.
	 */
	DiscDesign discDesign;

	/**
	 * Used to check if the audio track loaded to the deck.
	 */
	bool trackLoaded;

	/**
	 * Used to customize deckGUI 1 and 2 resized position.
	 */
	bool isDeckGUI1;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DeckGUI)
};