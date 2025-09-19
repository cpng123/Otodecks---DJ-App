/*
  ==============================================================================

    DiscDesign.cpp
    Created: 24 Feb 2024 7:14:12pm
    Author:  ngchu

  ==============================================================================
*/

#include "DiscDesign.h"

DiscDesign::DiscDesign()
{

}

DiscDesign::~DiscDesign()
{

}

// Font type
juce::Font DiscDesign::getSelectedFont()
{
    return juce::Font(juce::Typeface::createSystemTypefaceFor(BinaryData::Nero_otf, BinaryData::Nero_otfSize));
}

void DiscDesign::drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height,
    float sliderPosProportional, float rotaryStartAngle,
    float rotaryEndAngle, juce::Slider& slider)
{
    // Set rotary parameters for the slider to be full circle
    slider.setRotaryParameters(juce::MathConstants<float>::pi,
        juce::MathConstants<float>::twoPi + juce::MathConstants<float>::pi,
        true);

    // Calculation for dimensions and position of slider
    float diameter = juce::jmin(width, height);
    float radius = diameter / 2;
    float Xcentre = x + width / 2.0f;
    float Ycentre = y + height / 2.0f;
    float Xradius = Xcentre - radius;
    float Yradius = Ycentre - radius;
    float angle = rotaryStartAngle + (sliderPosProportional * (rotaryEndAngle - rotaryStartAngle));

    // Create an affine transformation for rotation
    juce::AffineTransform rotation = juce::AffineTransform::rotation(angle).translated(Xcentre, Ycentre);

    // Load the disc image
    juce::Image discImage = juce::ImageCache::getFromMemory(BinaryData::disc_png, BinaryData::disc_pngSize);

    // Apply rotation to the graphics context
    g.addTransform(juce::AffineTransform::rotation(rotationAngle, Xcentre, Ycentre));

    // Fill slider area with the loaded disc image
    g.drawImageWithin(discImage, x, y, width, height, juce::RectanglePlacement::centred, false);
}

// Set the rotation angle for the disc image
void DiscDesign::setRotationAngle(double angle)
{
    // Slow down the rotate speed by 50%
    rotationAngle = angle * 0.5;
}