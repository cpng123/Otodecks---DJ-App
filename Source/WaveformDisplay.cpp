/*
  ==============================================================================

	WaveformDisplay.cpp
	Created: 30 Jan 2024 9:20:08pm
	Author:  cpng

  ==============================================================================
*/

#include <JuceHeader.h>
#include "WaveformDisplay.h"

//==============================================================================
WaveformDisplay::WaveformDisplay(juce::AudioFormatManager& formatManagerToUse,
	juce::AudioThumbnailCache& cacheToUse)
	: audioThumb(1000, formatManagerToUse, cacheToUse),
	fileLoaded(false),
	position(0.),
	customDesign()
{

	audioThumb.addChangeListener(this);

}

WaveformDisplay::~WaveformDisplay()
{
}

void WaveformDisplay::paint(juce::Graphics& g)
{
	g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));   // clear the background

	g.setColour(juce::Colours::darkcyan);
	g.drawRect(getLocalBounds(), 1);   // draw an outline around the component


	if (fileLoaded)
	{
		// Define gradient colors
		juce::ColourGradient gradient(juce::Colours::gold, 0, 0, juce::Colours::magenta, getWidth(), getHeight(), true);

		// Draw the waveform using the gradient fill
		g.setGradientFill(gradient);
		
		audioThumb.drawChannel(g,
			getLocalBounds(),
			0,
			audioThumb.getTotalLength(),
			0,
			1.0f);

		drawProgressionBar(g);
	}
	else
	{
		displayLoadTrackMessage(g);
	}
}

void WaveformDisplay::resized()
{

}

void WaveformDisplay::drawProgressionBar(juce::Graphics& g) const
{
	// Update the path position based on the music's progress
	
	float halfBarWidth = getWidth() * 0.015f;
	float pathPosition = (position * getWidth()) - halfBarWidth;
	float height = static_cast<float>(getHeight());

	// Draw bar
	juce::Path bar;
	bar.startNewSubPath(pathPosition, 0);
	bar.lineTo(pathPosition + getWidth() * 0.03f, 0);
	bar.lineTo(pathPosition + getWidth() * 0.015f, height * 0.07f);
	bar.lineTo(pathPosition + getWidth() * 0.015f, height * 0.93f);
	bar.lineTo(pathPosition + getWidth() * 0.03f, height);
	bar.lineTo(pathPosition, height);
	bar.lineTo(pathPosition + getWidth() * 0.015f, height * 0.93f);
	bar.lineTo(pathPosition + getWidth() * 0.015f, height * 0.07f);
	bar.closeSubPath();

	// Bar colour
	g.setColour(juce::Colour::fromRGBA(65, 255, 255, 255));
	g.fillPath(bar);
	g.strokePath(bar, juce::PathStrokeType(1.8f));
}

void WaveformDisplay::displayLoadTrackMessage(juce::Graphics& g)
{
	// Set font type
	juce::Font selectedFont = customDesign.getSelectedFont();
	g.setFont(selectedFont);
	
	// Font size
	g.setFont(20.0f);

	// Text colour and opacity
	g.setColour(juce::Colours::darkturquoise.withAlpha(0.5f));
	
	// Text properties
	g.drawText("Select track to load...",
		getLocalBounds(),
		juce::Justification::centred,
		true);
}

void WaveformDisplay::loadURL(juce::URL audioURL)
{
	audioThumb.clear();
	fileLoaded = audioThumb.setSource(new juce::URLInputSource(audioURL));
}

void WaveformDisplay::changeListenerCallback(juce::ChangeBroadcaster* source)
{
	repaint();
}

void WaveformDisplay::setPositionRelative(double pos)
{
	if (pos != position && !isnan(pos))
	{
		position = pos;
		repaint();
	}
}