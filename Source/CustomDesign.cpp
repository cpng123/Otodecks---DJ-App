/*
  ==============================================================================

    CustomDesign.cpp
    Created: 15 Feb 2024 4:00:01pm
    Author:  ngchu

  ==============================================================================
*/

#include "CustomDesign.h"

CustomDesign::CustomDesign()
{

}

CustomDesign::~CustomDesign()
{

}

// Font type
juce::Font CustomDesign::getSelectedFont()
{
    return juce::Font(juce::Typeface::createSystemTypefaceFor(BinaryData::Expanse_otf, BinaryData::Expanse_otfSize));
}

// Customizing search bar with different design properties.
void CustomDesign::searchBarDesign(juce::TextEditor& searchBar)
{
    // Text being display when empty and it's colour
    searchBar.setTextToShowWhenEmpty("Search...", juce::Colours::darkturquoise.withAlpha(0.5f));
    
    // Mouse over will change curser
    searchBar.setMouseCursor(juce::MouseCursor::IBeamCursor);
    
    // Font Size
    searchBar.setFont(22.0f);
    
    // Font Type
    searchBar.setFont(getSelectedFont());
    
    // Font Colour when typing
    searchBar.setColour(juce::TextEditor::textColourId, juce::Colours::cyan);

    // Text Alignment
    searchBar.setJustification(juce::Justification::centredLeft);

    // Box outline colour
    searchBar.setColour(juce::TextEditor::outlineColourId, juce::Colours::darkcyan);

    // Box highlight when selected
    searchBar.setColour(juce::TextEditor::focusedOutlineColourId, juce::Colour::fromRGBA(63, 174, 250, 255));
    
    // When the text are being highlighted, the text colour will be changed
    searchBar.setColour(juce::TextEditor::highlightedTextColourId, juce::Colours::yellow);
    
    // Indentation from left
    searchBar.setIndents(15, 0);

    // Link to the drawTextEditorOutline function below
    searchBar.setLookAndFeel(this);
}

// Customizing search bar's box outline colour and thickness with rounded edges
void CustomDesign::drawTextEditorOutline(juce::Graphics& g, int width, int height, juce::TextEditor& textEditor)
{
    if (dynamic_cast<juce::AlertWindow*> (textEditor.getParentComponent()) == nullptr)
    {
        if (textEditor.isEnabled())
        {
            if (textEditor.hasKeyboardFocus(true) && !textEditor.isReadOnly())
            {
                // Draw focused outline with rounded edges and gradient fill
                juce::ColourGradient gradient(juce::Colours::yellow, 0, 0, juce::Colours::lightcoral, width, height, true);
                g.setGradientFill(gradient);
                g.drawRoundedRectangle(0, 0, width, height, 10.0f, 2.5f);
            }
            else
            {
                // Draw regular outline with rounded edges
                g.setColour(textEditor.findColour(juce::TextEditor::outlineColourId));
                g.drawRoundedRectangle(0, 0, width, height, 10.0f, 1.0f);
            }
        }
    }
}


// Customizing remove button
void CustomDesign::removeButtonDesign(juce::ImageButton* button)
{
    if (button != nullptr)
    {
        juce::Image binImage1 = juce::ImageCache::getFromMemory(BinaryData::bin1_png, BinaryData::bin1_pngSize);
        juce::Image binImage2 = juce::ImageCache::getFromMemory(BinaryData::bin2_png, BinaryData::bin2_pngSize);

        if (binImage1.isValid() && binImage2.isValid())
        {
            // Set Images
            button->setImages(true, true, true,
                binImage1, 1.0f, juce::Colours::lightgoldenrodyellow,
                binImage2, 1.0f, juce::Colours::red,
                binImage1, 1.0f, juce::Colours::red);

            // Change Cursor
            button->setMouseCursor(juce::MouseCursor::PointingHandCursor);
        }
        else
        {
            DBG("< Error loading bin image files >");
        }
    }
}

// Customizing the playlist component's header column
void CustomDesign::drawTableHeaderColumn(juce::Graphics& g, juce::TableHeaderComponent& header,
    const juce::String& columnName, int /*columnId*/,
    int width, int height, bool isMouseOver, bool isMouseDown,
    int columnFlags)
{
    // Colour change for mouse over event
    auto highlightColour = juce::Colours::darkgrey;

    // If mouse over then change colour
    if (isMouseOver)
        g.fillAll(highlightColour);

    juce::Rectangle<int> area(width, height);
    area.reduce(4, 0);

    if ((columnFlags & (juce::TableHeaderComponent::sortedForwards | juce::TableHeaderComponent::sortedBackwards)) != 0)
    {
        juce::Path sortArrow;
        sortArrow.addTriangle(0.0f, 0.0f,
            0.5f, (columnFlags & juce::TableHeaderComponent::sortedForwards) != 0 ? -0.8f : 0.8f,
            1.0f, 0.0f);

        g.setColour(juce::Colours::whitesmoke);
        g.fillPath(sortArrow, sortArrow.getTransformToScaleToFit(area.removeFromRight(height / 2).reduced(2).toFloat(), true));
    }

    // Set font and size
    juce::Font selectedFont = getSelectedFont().withHeight(18.0f);
    g.setFont(selectedFont);
    
    // Set font colour default is black, when mouse over then change to white
    g.setColour(juce::Colours::black);
    if (isMouseOver)
        g.setColour(juce::Colours::white);

    // Text Alignment
    g.drawFittedText(columnName, area, juce::Justification::centred, 1);
}

// Customizing TextButton with different look and feel.
void CustomDesign::buttonDesign(juce::TextButton& button)
{
    // Text colour
    button.setColour(juce::TextButton::textColourOffId, juce::Colours::cyan);

    // Change cursor
    button.setMouseCursor(juce::MouseCursor::PointingHandCursor);

    // Follow the overrided look and feel design - getTextButtonFont & drawButtonBackground
    button.setLookAndFeel(this);
}

// Customizing TextButton's font size with selected font type.
juce::Font CustomDesign::getTextButtonFont(juce::TextButton& button, int buttonHeight)
{
    // Font size
    float fontSize = juce::jmin(16.0f, (float)buttonHeight * 0.6f);

    // Font type
    return juce::Font(getSelectedFont()).withHeight(fontSize);
}

// Customizing button background with gradient outline
void CustomDesign::drawButtonBackground(juce::Graphics& g,
    juce::Button& button,
    const juce::Colour& backgroundColour,
    bool shouldDrawButtonAsHighlighted,
    bool shouldDrawButtonAsDown)
{
    // Button's curved corner
    auto cornerSize = 10.0f;
    auto bounds = button.getLocalBounds().toFloat().reduced(0.4f, 0.4f);

    // Adjust the outline colours
    juce::Colour outlineColour = juce::Colours::cyan; // default
    juce::Colour outlineColour2 = juce::Colours::yellow; // gradient 1
    juce::Colour outlineColour3 = juce::Colours::lightcoral; // gradient 2

    // Adjust the background color
    auto baseColour = backgroundColour.withMultipliedSaturation(button.hasKeyboardFocus(true) ? 1.3f : 0.9f)
        .withMultipliedAlpha(button.isEnabled() ? 1.0f : 0.5f);

    if (shouldDrawButtonAsDown || shouldDrawButtonAsHighlighted)
        baseColour = baseColour.contrasting(shouldDrawButtonAsDown ? 0.2f : 0.05f);

    g.setColour(baseColour);

    auto flatOnLeft = button.isConnectedOnLeft();
    auto flatOnRight = button.isConnectedOnRight();
    auto flatOnTop = button.isConnectedOnTop();
    auto flatOnBottom = button.isConnectedOnBottom();

    if (flatOnLeft || flatOnRight || flatOnTop || flatOnBottom)
    {
        juce::Path path;
        path.addRoundedRectangle(bounds.getX(), bounds.getY(),
            bounds.getWidth(), bounds.getHeight(),
            cornerSize, cornerSize,
            !(flatOnLeft || flatOnTop),
            !(flatOnRight || flatOnTop),
            !(flatOnLeft || flatOnBottom),
            !(flatOnRight || flatOnBottom));

        g.fillPath(path);

        // Change the outline color to gradient when mouse over
        if (shouldDrawButtonAsHighlighted) {
            // Yellow and coral gradient
            juce::ColourGradient gradient(outlineColour2, bounds.getX(), bounds.getY(),
                outlineColour3, bounds.getRight(), bounds.getBottom(), true);
            
            // Fill the gradient outline
            g.setGradientFill(gradient);

            // Set stroke outline thickness
            g.strokePath(path, juce::PathStrokeType(3.0f));

        }
        else {
            // Default cyan colour when mouse not over
            g.setColour(outlineColour);

            // Default stroke outline thickness
            g.strokePath(path, juce::PathStrokeType(1.0f));
        }
    }
    else
    {
        g.fillRoundedRectangle(bounds, cornerSize);

        // Change the outline color to gradient when mouse over
        if (shouldDrawButtonAsHighlighted) {
            // Yellow and coral gradient
            juce::ColourGradient gradient(outlineColour2, bounds.getX(), bounds.getY(),
                outlineColour3, bounds.getRight(), bounds.getBottom(), true);
            
            // Fill the gradient outline
            g.setGradientFill(gradient);

            // Set rounded rect stroke thickness
            g.drawRoundedRectangle(bounds, cornerSize, 3.0f);
        }
        else {
            // Default cyan colour when mouse not over
            g.setColour(outlineColour);

            // Default rounded rect stroke thickness
            g.drawRoundedRectangle(bounds, cornerSize, 1.0f);
        }
    }
}

// Customize the volume slider outline
void CustomDesign::drawLinearSliderOutline(juce::Graphics& g, int x, int y, int width, int height,
    const juce::Slider::SliderStyle, juce::Slider& slider)
{
    if (slider.getTextBoxPosition() == juce::Slider::NoTextBox)
    {
        // Define the gradient colors for the outline
        juce::ColourGradient gradient(juce::Colours::yellow, 0, 0, juce::Colours::lightcoral, width * 0.6, height, true);

        // Set the gradient fill for the outline
        g.setGradientFill(gradient);
       
        // Draw the rectangle outline with the gradient fill
        g.drawRect(x, y, width, height, 2);
    }
}

void CustomDesign::drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height,
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

    // Define gradient colors
    juce::ColourGradient gradient(juce::Colours::transparentBlack, Xcentre, Ycentre,
        juce::Colours::darkblue, Xcentre + radius, Ycentre + radius, true);

    // Fill
    g.setGradientFill(gradient);
    g.fillEllipse(Xradius, Yradius, diameter, diameter);
    
    // Outline
    g.setColour(juce::Colours::cyan);
    g.drawEllipse(Xradius, Yradius, diameter, diameter, -1.8f);

    // Draw minute marks around the rotary slider.
    g.setColour(juce::Colours::white);
    for (int i = 0; i < 30; ++i)
    {
        float angleRadians = rotaryStartAngle + (i / 30.0f) * (rotaryEndAngle - rotaryStartAngle);
        float lineInnerX = Xcentre + (radius - (radius * 0.2)) * std::cos(angleRadians);
        float lineInnerY = Ycentre + (radius - (radius * 0.2)) * std::sin(angleRadians);
        float lineOuterX = Xcentre + (radius - (radius * 0.01)) * std::cos(angleRadians);
        float lineOuterY = Ycentre + (radius - (radius * 0.01)) * std::sin(angleRadians);
        g.drawLine(lineInnerX, lineInnerY, lineOuterX, lineOuterY, 0.8f);
    }

    // Tick marks
    juce::Path tick;
    tick.addRectangle(0, -radius, 3.0f, radius * 0.7f);

    // Rotate and translate the tick marks to its centre position.
    g.fillPath(tick, juce::AffineTransform::rotation(angle).translated(Xcentre, Ycentre));
}