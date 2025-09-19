/*
  ==============================================================================

	MainComponent.cpp
	Created: 30 Jan 2024 9:00:05pm
	Author:  cpng

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
	setSize(800, 600);

	if (juce::RuntimePermissions::isRequired(juce::RuntimePermissions::recordAudio)
		&& !juce::RuntimePermissions::isGranted(juce::RuntimePermissions::recordAudio))
	{
		juce::RuntimePermissions::request(juce::RuntimePermissions::recordAudio,
			[&](bool granted) { setAudioChannels(granted ? 2 : 0, 2); });
	}
	else
	{
		// Specify the number of input and output channels to open
		setAudioChannels(0, 2);
	}
	addAndMakeVisible(deckGUI1);
	addAndMakeVisible(deckGUI2);

	addAndMakeVisible(playlistComponent);
	addAndMakeVisible(soundEffect);

	setupSlider(controlSlider, controlLabel);

	formatManager.registerBasicFormats();
}

MainComponent::~MainComponent()
{
	shutdownAudio();
}

void MainComponent::setupSlider(juce::Slider& slider, juce::Label& label)
{
	addAndMakeVisible(slider);
	slider.addListener(this);
	slider.setRange(0.0, 1.0);
	slider.setValue(0.5);
	slider.setDoubleClickReturnValue(true, 0.5);
	slider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
	slider.setMouseCursor(juce::MouseCursor::DraggingHandCursor);
	slider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
	slider.setColour(juce::Slider::thumbColourId, juce::Colours::cyan);
	
	slider.setColour(juce::Slider::backgroundColourId, juce::Colours::darkcyan);
	slider.setColour(juce::Slider::trackColourId, juce::Colours::grey);

	label.setFont(customDesign.getSelectedFont());
	label.setColour(juce::Label::textColourId, juce::Colours::cyan);
	label.setText("< CROSSFADER >", juce::NotificationType::dontSendNotification);
	label.attachToComponent(&slider, true);
}

//==============================================================================
void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
	// Play sound effect component.
	playerSoundEffect.prepareToPlay(samplesPerBlockExpected, sampleRate);
	mixerSource.prepareToPlay(samplesPerBlockExpected, sampleRate);

	mixerSource.addInputSource(&player1, false);
	mixerSource.addInputSource(&player2, false);
	mixerSource.addInputSource(&playerSoundEffect, false);
}
void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
	mixerSource.getNextAudioBlock(bufferToFill);
}

void MainComponent::releaseResources()
{
	player1.releaseResources();
	player2.releaseResources();
	mixerSource.releaseResources();
	mixerSource.removeAllInputs();
	
	// Release sound effect component
	playerSoundEffect.releaseResources();
}

//==============================================================================
void MainComponent::paint(juce::Graphics& g)
{
	g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

	float fontSize = getHeight() * 0.07f;

	juce::Font font(discDesign.getSelectedFont().withHeight(fontSize));

	g.setFont(font);

	g.setColour(juce::Colours::cyan);

	g.drawText("3 [     [     O T O D E C K S     ]     ] 2", 
		0, 0, getWidth(), getHeight(), juce::Justification::centredTop, false);

}

void MainComponent::resized()
{
	float topMargin = getHeight() * 0.07f;

	float halfW = getWidth() * 0.5f;
	float halfH = getHeight() * 0.45f;
	float sliderH = halfH * 0.1f;

	deckGUI1.setBounds(0, topMargin, halfW, halfH);
	deckGUI2.setBounds(halfW, topMargin, halfW, halfH);
	controlSlider.setBounds(getWidth() * 0.2f, topMargin + halfH, getWidth() * 0.6f, sliderH);

	float width = getWidth() * 0.1f;
	float height = topMargin + halfH + sliderH;
	float playlistW = getWidth() * 0.6f;
	float playlistH = getHeight() - height;
	playlistComponent.setBounds(0, height, playlistW, playlistH);
	soundEffect.setBounds(playlistW, height, getWidth() - playlistW, playlistH);
}

// Crossfade to different deck
void MainComponent::sliderValueChanged(juce::Slider* slider)
{
	if (slider == &controlSlider)
    {
		// Adjust the volume of deckGUI1 inversely proportional to slider value 
		// Slide toward left
		deckGUI1.setVolume(1.0 - controlSlider.getValue());

		// Adjust the volume of deckGUI2 directly proportional to slider value
		// Slide toward right.
		deckGUI2.setVolume(controlSlider.getValue());
    }
}