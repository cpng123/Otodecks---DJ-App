/*
  ==============================================================================

    CustomDesign.h
    Created: 15 Feb 2024 4:00:01pm
    Author:  ngchu

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "DJAudioPlayer.h"

/**
 * The CustomDesign class manages a custom look and feel for specifiec components,
 * overriding aspects of the default look and feel provided by LookAndFeel_V2 and LookAndFeel_V4.
 * 
 * This class inherits from LookAndFeel_V4 to handles custom design properties.
 */
class CustomDesign : public juce::LookAndFeel_V4
{
public:
    /**
     * Constructor for the CustomDesign class.
     */
    CustomDesign();

    /**
     * Destructor for the CustomDesign class.
     */
    ~CustomDesign();

    /**
     * Retrieves Expanse_otf font for custom design.
     * 
     * @return Selected font type.
     */
    juce::Font getSelectedFont();

    /**
     * Customizing search bar with different design properties from the PlaylistComponent.
     * 
     * @param searchBar The TextEditor used as a search bar.
     */
    void searchBarDesign(juce::TextEditor& searchBar);
    
    /** 
     * Customizing search bar's box from LookAndFeel_V4
     * 
     * @param g             Graphic context.
     * @param width         The box's width.
     * @param height        The box's height.
     * @param textEditor    The TextEditor used as a search bar.
     */
    void drawTextEditorOutline(juce::Graphics& g, int width, int height, juce::TextEditor& textEditor) override;

    /**
     * Customizing remove button as ImageButton from the PlaylistComponent.
     * 
     * @param button Pointer to the ImageButton used as a remove button.
     */
    void removeButtonDesign(juce::ImageButton* button);
  
    /** 
     * Customizing the playlist component's header column design from LookAndFeel_V2.
     * 
     * @param g             Graphics context.
     * @param header the    TableHeaderComponent being drawn.
     * @param columnName    The column's name.
     * @param columnID      The column's ID.
     * @param width         The column's width.
     * @param height        The column's height.
     * @param isMouseOver   Determine if the mouse is over the column.
     * @param isMouseDown   Determine if the mouse is pressed down over the column.
     * @param columnFlags   Flags indicating the column's state.
     * 
     */
    void drawTableHeaderColumn(juce::Graphics& g, juce::TableHeaderComponent& header,
        const juce::String& columnName, int /*columnId*/,
        int width, int height, bool isMouseOver, bool isMouseDown,
        int columnFlags) override;

    /**
     * Sets the design properties for TextButton including text colour, cursor, and other feels.
     * 
     * @param button The TextButton to apply the design to.
     */
    void buttonDesign(juce::TextButton& button);
    
    /** 
     * Customizing button text font from LookAndFeel_V4.
     * Determines the font size with selected font type.
     * 
     * @param button        The TextButton to apply the design to.
     * @param buttonHeight  The TextButton's height.
     * @return              Calculated font size and font type.
     */
    juce::Font getTextButtonFont(juce::TextButton& button, int buttonHeight) override;

    /**
     * Customizing button background with gradient outline from LookAndFeel_V4
     * 
     * @param g                             Graphic context.
     * @param button                        The button to draw the background for.
     * @param backgroundColour              The button background colour.
     * @param shouldDrawButtonAsHighlighted Determine if the button should be highlighted.
     * @param shouldDrawButtonAsDown        Determine if the button should be drawn as pressed down.
     */ 
    void drawButtonBackground(juce::Graphics& g, juce::Button& button, const juce::Colour& backgroundColour,
        bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;

    /** 
     * Customizing volume linear slider outline with gradient colour from LookAndFeel_V2
     * 
     * @param g         Graphics context.
     * @param x         The x-coordinate of the slider outline.
     * @param y         The y-coordinate of the slider outline.
     * @param width     The slider outline's width.
     * @param height    The slider outline's height.
     * @param style     The slider's style.
     * @param slider    The slider object being drawn.
     */
    void drawLinearSliderOutline(juce::Graphics& g, int x, int y, int	width, int	height,
        const juce::Slider::SliderStyle, juce::Slider& slider) override;

    /** 
     * Customize rotary slider for speed and volume sliders from LookAndFeel_V4
	 * 
     * @param g                     The graphics context to draw onto.
     * @param x                     The x-coordinate of the top-left corner of the bounding box.
     * @param y                     The y-coordinate of the top-left corner of the bounding box.
     * @param width                 The width of the bounding box.
     * @param height                The height of the bounding box.
     * @param sliderPosProportional The proportional position of the slider within its range.
     * @param rotaryStartAngle      The starting angle of the rotary slider.
     * @param rotaryEndAngle        The ending angle of the rotary slider.
     * @param slider                The rotary slider to be drawn.
     */
    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height,
		float sliderPosProportional, float rotaryStartAngle,
		float rotaryEndAngle, juce::Slider& slider) override;
};
