/*
  ==============================================================================

    DiscDesign.h
    Created: 24 Feb 2024 7:14:12pm
    Author:  ngchu

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

/**
 * The DiscDesign class manages a custom look and feel for the Disc DJ components.
 *
 * This class inherits from LookAndFeel_V4 to handles custom Disc DJ design properties.
 */
class DiscDesign : public juce::LookAndFeel_V4
{
public:
    /**
     * Constructor for the DiscDesign class.
     */
    DiscDesign();

    /**
     * Destructor for the DiscDesign class.
     */
    ~DiscDesign();

    /**
     * Retrieves Nero_otf font for custom design.
     *
     * @return Selected font type.
     */
    juce::Font getSelectedFont();

    /**
     * Customize rotary slider for DJ disc from LookAndFeel_V4
     * 
     * @param g                         The Graphics object used for drawing.
     * @param x                         The x-coordinate of the slider.
     * @param y                         The y-coordinate of the slider.
     * @param width                     The width of the slider.
     * @param height                    The height of the slider.
     * @param sliderPosProportional     The proportional position of the slider.
     * @param rotaryStartAngle          The start angle of the rotary slider.
     * @param rotaryEndAngle            The end angle of the rotary slider.
     * @param slider                    The Slider object being drawn.
     */
    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height,
        float sliderPosProportional, float rotaryStartAngle,
        float rotaryEndAngle, juce::Slider& slider) override;

    /**
     * Sets the rotation angle for the disc image.
     * 
     * @param angle The rotation angle to be set.
     */
    void setRotationAngle(double angle);

private:
    /**
     * Init the rotation angle for the disc image.
     */
    double rotationAngle = 0.0;
};