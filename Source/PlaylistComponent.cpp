/*
  ==============================================================================

	PlaylistComponent.cpp
	Created: 30 Jan 2024 9:22:28pm
	Author:  cpng

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlaylistComponent.h"

//==============================================================================
PlaylistComponent::PlaylistComponent(juce::AudioFormatManager& _formatManager, DeckGUI* _deckGUI1, DeckGUI* _deckGUI2)
	: formatManager(_formatManager), deckGUI1(_deckGUI1), deckGUI2(_deckGUI2), customDesign()
{
	// Init setup and config of table component
	tableComponent.getHeader().addColumn("d[^_^]b", 1, 50);
	tableComponent.getHeader().addColumn("TITLE", 2, 400);
	tableComponent.getHeader().addColumn("LENGTH", 3, 400);
	tableComponent.getHeader().addColumn("AUDIO TYPE", 4, 100);
	tableComponent.getHeader().addColumn("REMOVE", 5, 100);

	tableComponent.getHeader().setLookAndFeel(&customDesign);
	tableComponent.setModel(this);
	addAndMakeVisible(tableComponent);

	// Initialize and configure buttons
	initializeButton(importTrackButton);
	initializeButton(loadToDeckAButton);
	initializeButton(loadToDeckBButton);

	// Add listeners to buttons
	importTrackButton.addListener(this);
	loadToDeckAButton.addListener(this);
	loadToDeckBButton.addListener(this);

	// Add and configure search bar
	addAndMakeVisible(searchBar);
	searchBar.addListener(this);
	customDesign.searchBarDesign(searchBar);
}

PlaylistComponent::~PlaylistComponent()
{
}

// Initialize button with custom design
void PlaylistComponent::initializeButton(juce::TextButton& button)
{
	addAndMakeVisible(button);
	customDesign.buttonDesign(button);
}

void PlaylistComponent::paint(juce::Graphics& g)
{
	g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
	g.setColour(juce::Colours::darkcyan);
	g.drawRect(getLocalBounds(), 1);
}

void PlaylistComponent::resized()
{
	float width = getWidth() / 3;
	float height = getHeight() / 10;
	
	searchBar.setBounds(0, 0, getWidth(), height);
	
	loadToDeckAButton.setBounds(width * 0, height, width, height);
	importTrackButton.setBounds(width * 1, height, width, height);
	loadToDeckBButton.setBounds(width * 2, height, width, height);
	
	tableComponent.setBounds(0, height * 2, getWidth(), height * 8);

	tableComponent.getHeader().setColumnWidth(1, getWidth() * 0.1);
	tableComponent.getHeader().setColumnWidth(2, getWidth() * 0.4);
	tableComponent.getHeader().setColumnWidth(3, getWidth() * 0.18);
	tableComponent.getHeader().setColumnWidth(4, getWidth() * 0.18);
	tableComponent.getHeader().setColumnWidth(5, getWidth() * 0.14);
}

int PlaylistComponent::getNumRows()
{
	return audioTracks.size();
}

void PlaylistComponent::paintRowBackground(juce::Graphics& g,
	int rowNumber,
	int width,
	int height,
	bool rowIsSelected)
{
	if (rowIsSelected)
	{
		g.fillAll(juce::Colour::fromRGBA(63, 174, 250, 200));
		// Selected row with stand out colour
		juce::ColourGradient gradient(juce::Colours::yellow, 0, 0, 
			juce::Colours::lightcoral, width * 0.6, height, true);
		// Border around selected row
		g.setGradientFill(gradient); // Fill the entire row with the gradient
		g.drawRect(0, 0, width, height, 2);
	}
	else
	{
		if (rowNumber % 2 == 0)
			// Even row
			g.fillAll(juce::Colours::transparentBlack);
		else
			// Odd row
			g.fillAll(juce::Colours::darkgrey);
	}
	// Set default text color
	g.setColour(juce::Colours::whitesmoke);
}

void PlaylistComponent::paintCell(juce::Graphics& g,
	int rowNumber,
	int columnID,
	int width,
	int height,
	bool rowIsSelected)
{
	juce::Font selectedFont = customDesign.getSelectedFont();
	g.setFont(selectedFont);

	if (columnID == 2)
	{
		g.drawText(audioTracks[rowNumber].getAudioTrackTitle(),
			2,
			0,
			width,
			height,
			juce::Justification::centredLeft,
			true);
	}
	if (columnID == 3)
	{
		g.drawText(audioTracks[rowNumber].getAudioTrackLength(),
			2,
			0,
			width,
			height,
			juce::Justification::centred,
			true);
	}
	if (columnID == 4)
	{
		g.drawText(audioTracks[rowNumber].getAudioFileType(),
			2,
			0,
			width,
			height,
			juce::Justification::centred,
			true);
	}
}

juce::Component* PlaylistComponent::refreshComponentForCell(int rowNumber,
	int columnID,
	bool isRowSelected,
	juce::Component* existingComponentToUpdate)
{
	if (columnID == 1)
	{
		return refreshHeadsetIcon(rowNumber, isRowSelected, existingComponentToUpdate);
	}
	// Remove bin icon
	if (columnID == 5)
	{
		return refreshRemoveButton(rowNumber, existingComponentToUpdate);
	}
	return existingComponentToUpdate;
}

juce::Component* PlaylistComponent::refreshHeadsetIcon(int rowNumber,
	bool isRowSelected,
	juce::Component* existingComponentToUpdate)
{
	juce::Image headsetImage;

	// Choose the image based on whether the row is selected or not
	if (isRowSelected)
	{
		headsetImage = juce::ImageCache::getFromMemory(BinaryData::headset2_png, BinaryData::headset2_pngSize);
	}
	else
	{
		headsetImage = juce::ImageCache::getFromMemory(BinaryData::headset1_png, BinaryData::headset1_pngSize);
	}

	if (headsetImage.isValid())
	{
		juce::ImageComponent* imageComponent = dynamic_cast<juce::ImageComponent*>(existingComponentToUpdate);

		if (imageComponent == nullptr)
		{
			imageComponent = new juce::ImageComponent();
			imageComponent->setImage(headsetImage);
			return imageComponent;
		}
		else
		{
			imageComponent->setImage(headsetImage);
			return imageComponent;
		}
	}
	else
	{
		// Log error or display error message
		DBG("Error loading image file");
	}
	return existingComponentToUpdate;
}

juce::Component* PlaylistComponent::refreshRemoveButton(int rowNumber,
	juce::Component* existingComponentToUpdate)
{
	if (existingComponentToUpdate == nullptr)
	{
		removeButton = new juce::ImageButton();

		// Set up remove button design using CustomDesign
		customDesign.removeButtonDesign(removeButton);

		juce::String id{ std::to_string(rowNumber) };
		removeButton->setComponentID(id);
		removeButton->addListener(this);

		existingComponentToUpdate = removeButton;
	}
	return existingComponentToUpdate;
}

void PlaylistComponent::buttonClicked(juce::Button* button)
{
	// Import track
	if (button == &importTrackButton)
	{
		DBG("< Import > button was clicked << Select audio track... >>");

		auto fileChooserFlags = juce::FileBrowserComponent::canSelectMultipleItems;
		chooser.launchAsync(fileChooserFlags, [this](const juce::FileChooser& choosers)
			{
				for (const auto& audioTrack : choosers.getResults())
				{
					juce::File audioTrackFile{ audioTrack };
					importAudioTrack(audioTrackFile);
				}
			});
	}
	// Loading selected audio track to either deck A or B
	if (button == &loadToDeckAButton || button == &loadToDeckBButton)
	{
		// There are case where no audio track are being selected, then it should be empty
		// only if audio track is selected, it will get the int index of the selected audio track
		// This will ensure that an audio track is being selected
		std::optional<int> selectedRow = tableComponent.getSelectedRow();
		if (selectedRow.has_value())
		{
			DeckGUI* deckGUI = (button == &loadToDeckAButton) ? deckGUI1 : deckGUI2;
			loadTrackToDeck(deckGUI, selectedRow.value());
		}
	}
	// Remove selected track
	if (button->getComponentID().isNotEmpty())
	{
		int id = button->getComponentID().getIntValue();
		DBG("< REMOVE > button was clicked << Removing audio track: " << audioTracks[id].getAudioTrackTitle() << " >> ");
		removeSelectedTrack(id);

		tableComponent.updateContent();
	}

}

// Import Audio Track
void PlaylistComponent::importAudioTrack(const juce::File& audioTrackFile)
{
	// Retrieve the title, URL, and length of audio track
	juce::String audioTrackTitle = getAudioTrackTitle(audioTrackFile);
	juce::String audioTrackURL = getAudioTrackURL(audioTrackFile);
	juce::String audioTrackLength = getFormattedAudioTrackLength(juce::URL(audioTrackURL));
	juce::String audioFileType = getAudioFileType(audioTrackFile);

	// Check if the audio track hasn't imported yet
	if (!audioTrackExist(audioTrackTitle))
	{
		// Then push it into the new AudioTeack instance
		AudioTrack uniqueAudioTrack{ audioTrackTitle, audioTrackURL , audioTrackLength, audioFileType};
		audioTracks.push_back(uniqueAudioTrack);

		// Update the table component, reflecting changes
		tableComponent.updateContent();
	}
	else
	{
		// If the track already imported, prompt this message
		DBG("< The audio track: << " << audioTrackTitle << " >> has already been imported >");
	}
	// Update the table component regardless the track was added or not
	tableComponent.updateContent();
}

// Extract audio track title
juce::String PlaylistComponent::getAudioTrackTitle(const juce::File& audioTrackFile)
{
	juce::String fileName = audioTrackFile.getFileNameWithoutExtension();

	// Find the pos of the last "-"
	int dash = fileName.indexOf("-");

	if (dash != -1 && dash < fileName.length() - 1)
	{
		// Extract the title starting from the character after "-"
		return fileName.substring(dash + 1).trim();
	}
	else
	{
		// Return the file name without extension if no "-" found or if it's the last character
		return fileName;
	}
}

// Extract audio track URL
juce::String PlaylistComponent::getAudioTrackURL(const juce::File& audioTrackFile)
{
	return juce::URL{ audioTrackFile }.toString(false);
}

// Extract audio track length
juce::String PlaylistComponent::getFormattedAudioTrackLength(const juce::URL& audioURL)
{
    // Create an AudioFormatReader for each audio track URL
    std::unique_ptr<juce::AudioFormatReader> reader(formatManager.createReaderFor(audioURL.createInputStream(false)));

    if (reader != nullptr) {
        // Get the length of the audio track in seconds
        double audioLengthInSeconds = reader->lengthInSamples / static_cast<double>(reader->sampleRate);

		// Convert to hours, minutes, and seconds
        int hours = static_cast<int>(audioLengthInSeconds / 3600);
        int minutes = static_cast<int>((audioLengthInSeconds - hours * 3600) / 60);
        int seconds = static_cast<int>(audioLengthInSeconds - hours * 3600 - minutes * 60);

        // Format the track length as hour:minute:second
        return juce::String::formatted("%02d : %02d : %02d", hours, minutes, seconds);
    }
    else {
        // Return default value if error occur
        return "00:00:00";
    }
}

juce::String PlaylistComponent::getAudioFileType(const juce::File& audioTrackFile)
{
	// Get file extension
	juce::String fileExtension = audioTrackFile.getFileExtension();

	// Convert to upper case for consistency
	fileExtension = fileExtension.toUpperCase();

	// Remove dot
	if (fileExtension.startsWithChar('.'))
	{
		fileExtension = fileExtension.substring(1);
	}

	// Return audio file type
	return fileExtension;
}


// Chekcs if audio track with same title already exists in the playlist.
bool PlaylistComponent::audioTrackExist(const juce::String& importedTrackTitle) const
{
	// Store the titles of imported audio tracks in a set
	std::unordered_set<juce::String> audioTrackTitles;

	// Populate with existing track titles
	for (const auto& track : audioTracks)
	{
		audioTrackTitles.insert(track.getAudioTrackTitle());
	}

	// Check if the imported track title exists.
	return audioTrackTitles.find(importedTrackTitle) != audioTrackTitles.end();
}

// Loads selected track to specified track.
void PlaylistComponent::loadTrackToDeck(DeckGUI* deckGUI, int selectedRow)
{
	// Ensure selected track index is within valid range.
	if (selectedRow < audioTracks.size())
	{
		// Retrieve title.
		juce::String audioTrackTitle = audioTracks[selectedRow].getAudioTrackTitle();

		// Printing message indicating the chosen deck (A or B) and the title of 
		// the selected track intended for loading.
		DBG("< LOAD DECK " << (deckGUI == deckGUI1 ? "A" : "B") 
			<< " > button was clicked << Loading " 
			<< audioTrackTitle 
			<< " to Deck " 
			<< (deckGUI == deckGUI1 ? "A" : "B") 
			<< " >>");

		// Check if the deckGUI is valid.
		if (deckGUI != nullptr)
		{
			// Get the URL of the selected audio track.
			juce::String audioURLString = audioTracks[selectedRow].getAudioTrackURL();
			juce::URL audioURL(audioURLString);

			// Load to specified deck.
			deckGUI->loadToPlaylist(audioURL);
		}
		else
		{
			// Prompt error message if deckGUI pointer is null.
			DBG("< DeckGUI is nullptr >");
		}
	}
	else
	{
		// Prompt error message if no audio track is selected.
		DBG("< No audio track selected >");
	}
}

// Allow importing audio track by dragging into the app.
bool PlaylistComponent::isInterestedInFileDrag(const juce::StringArray& files)
{
	return true;
}

// Handles the audio track that dropped onto the PlaylistComponent.
void PlaylistComponent::filesDropped(const juce::StringArray& files, int x, int y)
{
	// Iterate through the dropped files and add each track.
	for (const auto& file : files)
	{
		juce::File audioTrackFile{ file };
		importAudioTrack(audioTrackFile);
	}
}

// Remove selected audio track
void PlaylistComponent::removeSelectedTrack(int id)
{
	// Erase the audio track at the specified index
	audioTracks.erase(audioTracks.begin() + id);
}

// Searches for the particular audio track in the playlist.
void PlaylistComponent::textEditorTextChanged(juce::TextEditor& searchText)
{
	// Get the text in the search bar, trim whitespace, and convert to uppercase
	auto searchQuery = searchText.getText().trim().toUpperCase();
	
	// If search query is empty after trimming whitespace, deselect all rows
	if (searchQuery.isEmpty()) {
		tableComponent.deselectAllRows();
		return;
	}

	// Find the first matching track
	for (int trackIndex = 0; trackIndex < audioTracks.size(); ++trackIndex)
	{
		if (audioTracks[trackIndex].getAudioTrackTitle().containsIgnoreCase(searchQuery))
		{
			// Select the row when a match is found
			tableComponent.selectRow(trackIndex);
			return;
		}
	}
	// Deselect all rows if no match is found
	tableComponent.deselectAllRows();
}
