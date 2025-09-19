/*
  ==============================================================================

	DeckGUI.cpp
	Created: 30 Jan 2024 9:15:56pm
	Author:  cpng

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DeckGUI.h"

//==============================================================================
DeckGUI::DeckGUI(DJAudioPlayer* _player,
	juce::AudioFormatManager& formatManagerToUse,
	juce::AudioThumbnailCache& cacheToUse,
	bool isDeckGUI1)
	: player(_player),
	waveformDisplay(formatManagerToUse, cacheToUse),
	isDeckGUI1(isDeckGUI1)
{
	// Setup waveform display
	addAndMakeVisible(waveformDisplay);

	// Setup position slider
	setupSlider(posSlider, 0.0, 0.0, 1.0, false, 
		juce::Slider::LinearBar, false, true, false);
	
	// Setup volume slider
	setupSlider(volSlider, 0.5, 0.0, 1.0, true, 
		juce::Slider::LinearBarVertical, true, true, false);

	// Setup speed rotary slider with text label
	setupSlider(speedSlider, 1.0, 0.0, 3.0, true, 
		juce::Slider::Rotary, true, false, false);
	setupLabel(speedLabel, speedSlider);

	// Setup for the Disc DJ
	setupSlider(discSlider, 0.0, 0.0, 1.0, true, 
		juce::Slider::Rotary, false, false, true);
	
	// Setup buttons (stop, fast forward, rewind backward, replay)
	setupImageButton(imgStopButton, BinaryData::stop_png, BinaryData::stop_pngSize);
	setupImageButton(imgFastButton, BinaryData::forward_png, BinaryData::forward_pngSize);
	setupImageButton(imgRewindButton, BinaryData::rewind_png, BinaryData::rewind_pngSize);
	setupImageButton(imgReplayButton, BinaryData::replay_png, BinaryData::replay_pngSize);
	
	// Setup play and pause buttons
	setupPlayPauseButton();
	
	// Start timer
	startTimer(100);
}

DeckGUI::~DeckGUI()
{
	stopTimer();
}

void DeckGUI::setupSlider(juce::Slider& slider, float initialValue, 
	float minValue, float maxValue, bool doubleclick, 
	juce::Slider::SliderStyle style, bool useCustomDesign, 
	bool setColour, bool setDiscDesign)
{
	addAndMakeVisible(slider);
	slider.addListener(this);
	slider.setRange(minValue, maxValue);
	slider.setValue(initialValue);
	slider.setSliderStyle(style);
	slider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
	slider.setDoubleClickReturnValue(doubleclick, initialValue);
	slider.setMouseCursor(juce::MouseCursor::DraggingHandCursor);

	// Determine if using the override look and feel
	if (useCustomDesign)
	{
		slider.setLookAndFeel(&customDesign);
	}

	// Set track colour according to different slider
	if (setColour) 
	{
		if (&slider == &volSlider) {
			slider.setColour(juce::Slider::trackColourId, juce::Colours::cyan.withBrightness(0.8f));
		}
		else if (&slider == &posSlider) {
			slider.setColour(juce::Slider::trackColourId, juce::Colours::transparentWhite);
		}
	}

	if (setDiscDesign)
	{
		slider.setLookAndFeel(&discDesign);
	}
}

void DeckGUI::setupLabel(juce::Label& label, juce::Slider& slider)
{
	label.setFont(customDesign.getSelectedFont());
	label.setColour(juce::Label::textColourId, juce::Colours::cyan);
	label.setText("< SPEED >", juce::NotificationType::dontSendNotification);
	label.attachToComponent(&slider, false);
	label.setJustificationType(juce::Justification::centredTop);
}

// Sets up each of the image buttons
void DeckGUI::setupImageButton(juce::ImageButton& button, const char* imageData, int imageDataSize)
{
	setImageButton(button, imageData, imageDataSize);
	addAndMakeVisible(button);
	button.addListener(this);
}

// Setup play and pause buttons
void DeckGUI::setupPlayPauseButton()
{
	// Load play and pause button images from binary data
	playImage = juce::ImageCache::getFromMemory(BinaryData::play_png, BinaryData::play_pngSize);
	pauseImage = juce::ImageCache::getFromMemory(BinaryData::pause_png, BinaryData::pause_pngSize);

	// Setup play button with images and colours with mouse interaction
	imgPlayButton.setImages(false, true, true,
		playImage, 1.0f, juce::Colours::cyan.withAlpha(0.7f),
		playImage, 1.0f, juce::Colours::lightyellow,
		playImage, 1.0f, juce::Colours::cyan.brighter());

	addAndMakeVisible(imgPlayButton);
	addAndMakeVisible(imgPauseButton);

	// Add listeners to play and pause buttons
	imgPlayButton.addListener(this);
	imgPauseButton.addListener(this);

	// Set cursor
	imgPlayButton.setMouseCursor(juce::MouseCursor::PointingHandCursor);
}


void DeckGUI::paint(juce::Graphics& g)
{
	g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));   // clear the background

	g.setColour(juce::Colours::darkcyan);
	// draw an outline around the component
	g.drawRect(getLocalBounds(), 1);

	g.setColour(juce::Colours::cyan);
	g.setFont(customDesign.getSelectedFont().withHeight(16.0f));
	// Calculate the position of the text dynamically based on the component size
	int textX = getWidth() * 0.05;
	int textY = getHeight() * 0.025;
	int textWidth = getWidth(); // Example: 20% of the component width
	int textHeight = getHeight() / 10; // Example: 10% of the component height

	// Everytime audio is loaded, it extract metadata (title) and display
	if (!trackLoaded)
	{
		g.drawText(player->audioTrackTitle, textX, textY, textWidth, textHeight, juce::Justification::left, false);
	}
	else
	{
		g.drawText(player->audioTrackTitle, textX, textY, textWidth, textHeight, juce::Justification::left, false);
		trackLoaded = false;
		repaint();
	}
}

void DeckGUI::resized()
{
	float rowH = getHeight() * 0.1f;
	float rowW = getWidth() * 0.1f;
	float marginX = rowW * 0.15f;
	float marginY = rowH * 0.15f;
	float sliderSize = rowH * 1.61f;
	float btnSize = rowH * 1.3f;

	if (isDeckGUI1)
	{
		posSlider      .setBounds(0, rowH * 1.5, getWidth(), rowH * 2);
		waveformDisplay.setBounds(0, rowH * 1.5, getWidth(), rowH * 2);

		volSlider	   .setBounds(rowW * 8.85, (rowH * 3.5) + marginY, rowW, rowH * 6.2);
		discSlider	   .setBounds(rowW * 4.4, rowH * 3.8, rowW * 4, rowW * 4);

		speedSlider    .setBounds(rowW * 1.2, rowH * 4.7, sliderSize * 2, sliderSize);

		imgStopButton  .setBounds(rowW * 0.6, rowH * 6.5, btnSize, btnSize);
		imgPlayButton  .setBounds(rowW * 1.7, rowH * 7.1, btnSize*1.35, btnSize*1.35);
		imgReplayButton.setBounds(rowW * 3.1, rowH * 6.5, btnSize, btnSize);

		imgRewindButton.setBounds(rowW * 0.6, rowH * 8.2, btnSize, btnSize);
		imgFastButton  .setBounds(rowW * 3.1, rowH * 8.2, btnSize, btnSize);
	}
	else
	{
		posSlider.setBounds(0, rowH * 1.5, getWidth(), rowH * 2);
		waveformDisplay.setBounds(0, rowH * 1.5, getWidth(), rowH * 2);
		
		volSlider.setBounds(marginX, (rowH * 3.5) + marginY, rowW, rowH * 6.2);
		discSlider.setBounds(rowW * 1.6, rowH * 3.8, rowW * 4, rowW * 4);

		speedSlider.setBounds(rowW * 6.6, rowH * 4.7, sliderSize * 2, sliderSize);

		imgStopButton.setBounds(rowW * 6, rowH * 6.5, btnSize, btnSize);
		imgPlayButton.setBounds(rowW * 7.1, rowH * 7.1, btnSize * 1.35, btnSize * 1.35);
		imgReplayButton.setBounds(rowW * 8.5, rowH * 6.5, btnSize, btnSize);

		imgRewindButton.setBounds(rowW * 6, rowH * 8.2, btnSize, btnSize);
		imgFastButton.setBounds(rowW * 8.5, rowH * 8.2, btnSize, btnSize);
	}
}

void DeckGUI::buttonClicked(juce::Button* button)
{
	// Stop button
	if (button == &imgStopButton)
	{
		handleStopButton();
		return;
	}

	// Play and pause buttons are together
	if (button == &imgPlayButton)
	{
		handlePlayPauseButton();
		return;
	}

	// Fast forward 10 sec button
	if (button == &imgFastButton)
	{
		handleFastForwardButton();
		return;
	}

	// Rewind backward 10 sec button
	if (button == &imgRewindButton)
	{
		handleRewindButton();
		return;
	}

	// Replay button
	if (button == &imgReplayButton)
	{
		handleReplayButton();
		return;
	}
}

// Stop button
void DeckGUI::handleStopButton()
{
	DBG("< STOP > button was clicked << Playback stopped >>");
	player->stop();

	// Reset play button to its initial state
	imgPlayButton.setImages(false, true, true,
		playImage, 1.0f, juce::Colours::cyan.withAlpha(0.7f),
		playImage, 1.0f, juce::Colours::lightyellow,
		playImage, 1.0f, juce::Colours::cyan.brighter());

	playState = PlayState::Pause;
}

// Play and pause buttons
void DeckGUI::handlePlayPauseButton()
{
	if (playState == PlayState::Pause)
	{
		DBG("< PLAY > button was clicked << Playing >>");
		imgPlayButton.onClick = [this]() { playing(); };
	}
	else if (playState == PlayState::Play)
	{
		DBG("< PAUSE > button was clicked << Pausing >>");
		imgPlayButton.onClick = [this]() { pausing(); };
	}
}

// Fast forward button
void DeckGUI::handleFastForwardButton()
{
	DBG("< FAST FORWARD > button was clicked << Fast forward by 10 seconds >>");
	player->fastForward();
}

// Rewind button
void DeckGUI::handleRewindButton()
{
	DBG("< REWIND BACKWARD > button was clicked << Rewind backward by 10 seconds >>");
	player->rewind();
}

// Replay button
void DeckGUI::handleReplayButton()
{
	DBG("< REPLAY > button was clicked");
	bool replayEnable = imgReplayButton.getToggleState();
	imgReplayButton.setToggleState(!replayEnable, juce::NotificationType::dontSendNotification);
	player->replay(!replayEnable);
}

void DeckGUI::sliderValueChanged(juce::Slider* slider)
{
	// Volume slider
	if (slider == &volSlider)
	{
		player->setGain(slider->getValue());
	}

	// Speed slider
	if (slider == &speedSlider)
	{
		player->setSpeed(slider->getValue());
	}

	// Position slider
	if (slider == &posSlider)
	{
		player->setPositionRelative(slider->getValue());
	}

	if (slider == &discSlider)
	{
		player->setPositionRelative(slider->getValue());
	}
}

// Allow drag and drop of track into the Deck
bool DeckGUI::isInterestedInFileDrag(const juce::StringArray& files)
{
	return true;
}
void DeckGUI::filesDropped(const juce::StringArray& files, int x, int y)
{
	DBG("DeckGUI::filesDropped");
	if (files.size() == 1)
	{
		player->loadURL(juce::URL{ juce::File{files[0]} });
	}
}

// Called by timer to update waveform display position
void DeckGUI::timerCallback()
{
	double pos = player->getPositionRelative();
	if (pos > 0.0 && pos < 1.0)
	{
		waveformDisplay.setPositionRelative(pos);
		discSlider.setValue(pos);  

		double angle = pos * 360.0;

		discDesign.setRotationAngle(angle);
		repaint();
	}
}

// Loads audio URL into player and display waveform
void DeckGUI::loadToPlaylist(const juce::URL& audioURL)
{
	// Load audio URL into player
	player->loadURL(audioURL);

	// Load audio URL into waveform display
	waveformDisplay.loadURL(audioURL);

	// Flag indicate audio track loaded
	trackLoaded = true;
}

void DeckGUI::setImageButton(juce::ImageButton& button, const void* imageData, int imageDataSize)
{
	auto image = juce::ImageCache::getFromMemory(imageData, imageDataSize);
	
	if (image.isValid())
	{
		button.setImages(true, true, true,
			image, 1.0f, juce::Colours::cyan.withAlpha(0.7f),
			image, 1.0f, juce::Colours::lightyellow,
			image, 1.0f, juce::Colours::cyan.brighter());
	}

	// Change cursor
	button.setMouseCursor(juce::MouseCursor::PointingHandCursor);
}

void DeckGUI::playing()
{
	playState = PlayState::Play;
	imgPlayButton.setImages(false, true, true,
		pauseImage, 1.0f, juce::Colours::yellow,
		pauseImage, 1.0f, juce::Colours::lightyellow,
		pauseImage, 1.0f, juce::Colours::yellow);
	
	player->start();
}

void DeckGUI::pausing()
{
	playState = PlayState::Pause;
	imgPlayButton.setImages(false, true, true,
		playImage, 1.0f, juce::Colours::lawngreen,
		playImage, 1.0f, juce::Colours::lightyellow,
		playImage, 1.0f, juce::Colours::lawngreen);
	
	player->pause();
}

void DeckGUI::setVolume(double volume)
{
	// Ensure the volume level ramains within valid range
	if (volume < 0.0)
	{
		volume = 0.0;
	}
	else if (volume > 1.0)
	{
		volume = 1.0;
	}

	// Set the volume level of the associated player
	player->setGain(volume);
}