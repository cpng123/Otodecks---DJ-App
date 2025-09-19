/*
  ==============================================================================

    SoundEffect.cpp
    Created: 21 Feb 2024 9:17:23pm
    Author:  ngchu

  ==============================================================================
*/

#include <JuceHeader.h>
#include "SoundEffect.h"

//==============================================================================
SoundEffect::SoundEffect(DJAudioPlayer* _player)
    : player(_player), isPlaying(false), currentSoundIndex(-1), customDesign()
{
    // Iterate through buttons vector and init them
    for (int i = 0; i < buttons.size(); ++i)
    {
        addAndMakeVisible(*buttons[i]);
        buttons[i]->addListener(this);
        
        // Apply custom design settings
        customDesign.buttonDesign(*buttons[i]);
    }

    setupSlider(volSlider, 0.5, 0.0, 1.0, volLabel, "< Volume >");
    setupSlider(speedSlider, 1.0, 0.0, 3.0, speedLabel, "< Speed >");

    // Load sound effect files when SoundEffect is constructed
    readAudioFiles();
}

SoundEffect::~SoundEffect()
{

}

void SoundEffect::setupSlider(juce::Slider& slider, float initialValue,
    float minValue, float maxValue, juce::Label& label, const juce::String& labelText)
{
    addAndMakeVisible(slider);
    slider.addListener(this);
    slider.setRange(minValue, maxValue);
    slider.setValue(initialValue);
    slider.setSliderStyle(juce::Slider::Rotary);
    slider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    slider.setDoubleClickReturnValue(true, initialValue);
    slider.setMouseCursor(juce::MouseCursor::DraggingHandCursor);
    slider.setLookAndFeel(&customDesign);

    label.setFont(customDesign.getSelectedFont());
    label.setColour(juce::Label::textColourId, juce::Colours::cyan);
    label.setText(labelText, juce::NotificationType::dontSendNotification);
    label.attachToComponent(&slider, true);
}

void SoundEffect::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.setColour (juce::Colours::darkcyan);
    g.drawRect (getLocalBounds(), 1);

    // Calculate the font size based on the component's height
    float fontSize = getHeight() * 0.065f;

    // Create the font using the custom typeface and calculated size
    juce::Font font(customDesign.getSelectedFont().withHeight(fontSize));

    // Set the font for drawing the text
    g.setFont(font);

    // Set the text color
    g.setColour(juce::Colours::cyan);

    // Calculate the vertical position based on a percentage of the component's height
    float verticalPosition = getHeight() * 0.02f;

    // Calculate the bounds for the text
    juce::Rectangle<int> textBounds = getLocalBounds().reduced(0, verticalPosition);

    // Draw the text
    g.drawText("<<  SOUND  EFFECTS  >>", textBounds, juce::Justification::centredTop, false);
}

void SoundEffect::resized()
{
    float width = getWidth() / 3;
    float height = getHeight() / 4;

    float startH = getHeight() * 0.11f;
    float btnW = width * 0.85f;
    float btnH = height * 0.8f;
    float btnMarginX = width * 0.075f;
    float btnMarginY = height * 0.1f;
    
    sound1.setBounds(btnMarginX * 2           , startH, btnW, btnH);
    sound2.setBounds(btnMarginX * 3 + btnW    , startH, btnW, btnH);
    sound3.setBounds(btnMarginX * 4 + btnW * 2, startH, btnW, btnH);

    sound4.setBounds(btnMarginX * 2           , startH + btnH + btnMarginY, btnW, btnH);
    sound5.setBounds(btnMarginX * 3 + btnW    , startH + btnH + btnMarginY, btnW, btnH);
    sound6.setBounds(btnMarginX * 4 + btnW * 2, startH + btnH + btnMarginY, btnW, btnH);

    sound7.setBounds(btnMarginX * 2           , startH + (btnH * 2) + (btnMarginY * 2), btnW, btnH);
    sound8.setBounds(btnMarginX * 3 + btnW    , startH + (btnH * 2) + (btnMarginY * 2), btnW, btnH);
    sound9.setBounds(btnMarginX * 4 + btnW * 2, startH + (btnH * 2) + (btnMarginY * 2), btnW, btnH);

    float bottomH = startH + (btnH * 3) + (btnMarginY * 4);
    float sliderSize = btnW * 0.55;
    float bottomW = getWidth() / 6;
    volSlider.setBounds(bottomW * 1.75, bottomH, sliderSize, sliderSize);
    speedSlider.setBounds(bottomW * 4.25, bottomH, sliderSize, sliderSize);
}

void SoundEffect::buttonClicked(juce::Button* button)
{
    // Vector of sound effect names corresponding to each buttons
    std::vector<std::string> soundEffects = {
        "beat1", "beat2", "beat3", 
        "DJ Intro", "heartbeat", "alarm", 
        "sweep down", "clap", "boo"
    };

    // Iterate through the buttons vector to find the clicked button
    for (int i = 0; i < buttons.size(); ++i)
    {
        if (button == buttons[i])
        {
            // If the clicked button is already playing, 
            // click the same button again to stop playback.
            if (isPlaying && i == currentSoundIndex)
            {
                // Stop playback
                player->stop();
                // Update flag
                isPlaying = false;
                DBG("< Stopped > playback of sound effect: " << soundEffects[i]);
                return;
            }
            // Stop playback of any currently playing sound effect
            // if the clicked button was different.
            if (isPlaying)
            {
                player->stop();
            }

            // Play the selected sound effect.
            playSoundEffect(soundEffects[i]);
            DBG("< Started > playback of sound effect: " << soundEffects[i]);
            
            // Update flags
            isPlaying = true;
            currentSoundIndex = i;
            return;
            
        }
    }
}

void SoundEffect::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &volSlider)
    {
        player->setGain(slider->getValue());
    }
    
    if (slider == &speedSlider)
    {
        player->setSpeed(slider->getValue());
    }
}

void SoundEffect::readAudioFiles()
{
    // Construct the directory path for sound effect audio files
    juce::File directory = juce::File::getCurrentWorkingDirectory()
        .getParentDirectory()
        .getParentDirectory()
        .getChildFile("SoundEffect");

    // Check if the directory exists
    if (!directory.isDirectory())
    {
        DBG("Error: SoundEffect directory not found.");
        return;
    }

    // Search for the audio file with ".mp3" or ".wav" extension
    juce::Array<juce::File> soundEffectFiles;
    directory.findChildFiles(soundEffectFiles, juce::File::findFiles, false, "*.mp3;*.wav");

    // Ensure sound effect file was found
    if (soundEffectFiles.isEmpty())
    {
        DBG("Error: Sound effect files not found in the SoundEffect directory.");
        return;
    }

    // Iterate through the sound effect files
    for (const juce::File& file : soundEffectFiles)
    {
        // Extract the sound effect's title
        juce::String soundTitle = file.getFileNameWithoutExtension();
        
        // Convert sound effect's URL as string
        juce::String soundURL = juce::URL{ file }.toString(false);
        
        // Add into the list
        soundEffects.push_back({ soundTitle,soundURL });
    }
}


void SoundEffect::playSoundEffect(const juce::String& soundEffectTitle)
{
    // Iterate through sound effects
    for (int i = 0; i < soundEffects.size(); ++i)
    {
        // If the sound effect's title match
        if (soundEffects[i].getAudioTrackTitle() == soundEffectTitle)
        {
            // Then load the sound effect into player
            player->loadURL(soundEffects[i].getAudioTrackURL());

            DBG("Sound effect are loaded: " << soundEffectTitle);

            player->replay(true);

            // Start playing the sound effect
            player->start();
            return;
        }
    }
    DBG("Error: Sound effect not found: " << soundEffectTitle);
}
