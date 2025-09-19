/*
  ==============================================================================

    SoundEffect.h
    Created: 21 Feb 2024 9:17:23pm
    Author:  ngchu

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include "AudioTrack.h"
#include "CustomDesign.h"

/**
 * SoundEffect class handles sound effects and their playback.
 * 
 * This class inherits from juce::Component, juce::Button::Listener 
 * and juce::Slider::Listener to handle various interaction functionalities.
 */
class SoundEffect : public juce::Component,
                    public juce::Button::Listener,
                    public juce::Slider::Listener
{
public:
    /**
     * Constructor of SoundEffect class.
     * 
     * @param _player Pointer to the DJAudioPlayer.
     */
    SoundEffect(DJAudioPlayer* _player);

    /**
     * Destructor of SoundEffect class.
     */
    ~SoundEffect() override;

    /**
     * Paint method override to perform custom drawing.
     *
     * @param g Graphics context to perform drawing operations.
     */
    void paint (juce::Graphics& g) override;

    /**
     * Resized method override to handle component resizing.
     */
    void resized() override;

    /**
     * ButtonClicked method override to handle button click events.
     *
     * @param button Pointer to the clicked button.
     */
    void buttonClicked(juce::Button* button) override;

    /**
     * Handles slider value changes in the SoundEffect.
     *
     * @param slider The slider whose value has changed.
     */
    void sliderValueChanged(juce::Slider* slider) override;

private:
    /**
     * Setup and design sliders with specified parameters.
     *
     * @param slider			Reference to the slider object to set up.
     * @param initialValue		Initial value of the slider.
     * @param minValue			Minimum value of the slider.
     * @param maxValue			Maximum value of the slider.
     * @param label             Label for slider.
     * @param labelText         Set text label for each slider.
     */
    void setupSlider(juce::Slider& slider, float initialValue,
        float minValue, float maxValue, juce::Label& label, 
        const juce::String& labelText);

    /**
     * Read audio files from the Sound Effect directory.
     * Populates the soundEffects vector.
     */
    void readAudioFiles();

    /**
     * Plays each sound effects.
     * 
     * @param soundEffectTitle Title of the sound effect to be played.
     */
    void playSoundEffect(const juce::String& soundEffectTitle);

    /**
     * Vector to store AudioTrack objects representing sound effects.
     */
    std::vector<AudioTrack> soundEffects;

    /**
     * Declare text buttons for different sound effects.
     */
    juce::TextButton sound1{ "beat 1" }
                    ,sound2{ "beat 2" }
                    ,sound3{ "beat 3" }
                    ,sound4{ "DJ\nIntro" }
                    ,sound5{ "heartbeat" }
                    ,sound6{ "alarm" }
                    ,sound7{ "sweep\ndown" }
                    ,sound8{ "clap" }
                    ,sound9{ "boo" };

    /**
     * Vector pointers to text buttons.
     */
    std::vector<juce::TextButton*> buttons =
    {
        &sound1,&sound2,&sound3,
        &sound4,&sound5,&sound6,
        &sound7,&sound8,&sound9
    };

    /**
     * Slider for volume and speed control.
     */
    juce::Slider volSlider, speedSlider;

    /**
     * Label for volume and speed slider.
     */
    juce::Label volLabel, speedLabel;

    /**
     * Pointer to DJAudioPlayer.
     */
    DJAudioPlayer* player;

    /**
     * CustomDesign for customizing button appearance.
     */
    CustomDesign customDesign;

    /**
     * Audio format manager for managing audio formats.
     */
    juce::AudioFormatManager soundFormatManager;

    /**
     * Unique pointer to AudioFormatReaderSource to play sound effects.
     */
    std::unique_ptr<juce::AudioFormatReaderSource> soundEffect;

    /**
     * Audio transport source for playing audio files.
     */
    juce::AudioTransportSource transportSource;

    /**
     * Standard sample rate for audio playback.
     */
    double sampleRate = 44100.0;

    /**
     * Indicates whether a sound effect is currently playing.
     */
    bool isPlaying;

    /**
     * Index of the currently selected sound effect.
     */
    int currentSoundIndex;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SoundEffect)
};
