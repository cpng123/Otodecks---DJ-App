/*
  ==============================================================================

	PlaylistComponent.h
	Created: 30 Jan 2024 9:22:28pm
	Author:  cpng

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <string>
#include <vector>
#include "AudioTrack.h"
#include "DeckGUI.h"
#include "CustomDesign.h"
#include "DJAudioPlayer.h"

/**
 * PlaylistComponent class represent a GUI component for managing audio tracks 
 * in the playlist, including imports and loads tracks onto different decks, 
 * and searching for tracks.
 * 
 * This class inherits from juce::Component, juce::TableListBoxModel, 
 * juce::Button::Listener, juce::FileDragAndDropTarget, and juce::TextEditor::Listener
 * to handle various UI design and interaction functionalities.
 */
class PlaylistComponent : public juce::Component,
	public juce::TableListBoxModel,
	public juce::Button::Listener,
	public juce::FileDragAndDropTarget,
	public juce::TextEditor::Listener
{
public:
	/**
	 * Constructs of the PlaylistComponent.
	 *
	 * @param _formatManager	Reference to the audio format manager.
	 * @param deckGUI1			Pointer to the DeckGUI object for the first deck.
	 * @param deckGUI2			Pointer to the DeckGUI object for the second deck.
	 */
	PlaylistComponent(juce::AudioFormatManager& _formatManager, 
        DeckGUI* deckGUI1, 
        DeckGUI* deckGUI2);
	/**
	 * Destructor of the PlaylistComponent.
	 */
	~PlaylistComponent() override;

	/**
	 * Paints the PlaylistComponent.
	 *
	 * @param g Graphics context to perform drawing operations.
	 */
	void paint(juce::Graphics&) override;

	/**
	 * Called when the PlaylistComponent is resized.
	 */
	void resized() override;

	/**
	 * TableListBoxModel pure virtual functions.
	 * Return row number in the PlaylistComponent.
	 */ 
	int getNumRows() override;

	/**
	 * TableListBoxModel pure virtual functions.
	 * Paints the background for each row in the PlaylistComponent.
	 * 
	 * @param g					Graphics context to paint.
	 * @param rowNumber			Row index being painted.
	 * @param width				Row width.
	 * @param height			Row height.
	 * @param rowIsSelected		If the row is selected then it's True, otherwise it's False.
	 */
	void paintRowBackground(juce::Graphics&,
		int rowNumber,
		int width,
		int height,
		bool rowIsSelected) override;

	/**
	 * TableListBoxModel pure virtual functions.
	 * Paints cell content in the PlaylistComponent.
	 * 
	 * @param g					Graphics context to paint.
	 * @param rowNumber			Row index containing the cell.
	 * @param columnId			Column ID containing the cell.
	 * @param width				Row width.
	 * @param height			Row height.
	 * @param rowIsSelected		If the row is selected then it's True, otherwise it's False.
	 */
	void paintCell(juce::Graphics&,
		int rowNumber,
		int columnId,
		int width,
		int height,
		bool rowIsSelected) override;

	/**
	 * Refreshes component cell in the PlaylistComponent.
	 *
	 * @param rowNumber						Row index containing the cell.
	 * @param columnId						Column ID containing the cell.
	 * @param isRowSelected					If the row is selected then it's True, otherwise it's False.
	 * @param existingComponentToUpdate		The existing component to update, if any.
	 * @return								The updated component for the cell.
	 */
	juce::Component* refreshComponentForCell(int rowNumber,
		int columnId,
		bool isRowSelected,
		juce::Component* existingComponentToUpdate) override;

	/**
	 * Refreshes the headset icon component.
	 *
	 * @param rowNumber						Row index containing the cell.
	 * @param isRowSelected					If the row is selected then it's True, otherwise it's False.
	 * @param existingComponentToUpdate		The existing headset icon component to update, if any.
	 * @return								The updated headset icon component for the cell.
	 */
	juce::Component* refreshHeadsetIcon(int rowNumber,
		bool isRowSelected,
		juce::Component* existingComponentToUpdate);

	/**
	 * Refreshes the remove button component.
	 *
	 * @param rowNumber						Row index containing the cell.
	 * @param existingComponentToUpdate		The existing remove button component to update, if any.
	 * @return								The updated remove button component for the cell.
	 */
	juce::Component* refreshRemoveButton(int rowNumber,
		juce::Component* existingComponentToUpdate);

	/** 
	 * Button::Listener
	 * Called during button clicked.
	 * 
	 * @param button	Pointer to the each button that was clicked.
	 */
	void buttonClicked(juce::Button* button) override;

	/**
	 * Determines whether the PlaylilstComponent allow in file drag events.
	 * 
	 * @param files		Array of file paths being dragged.
	 * @return			True for allowing file drag events.
	 */
	bool isInterestedInFileDrag(const juce::StringArray& files) override;
	
	/**
	 * When files are drag and drop onto the PlaylistComponent, it will iterates 
	 * through the string array of selected dropped file and imports each of the
	 * audio track into PlaylistComponent.
	 * 
	 * @param files		Array of file that have been dropped onto the PlaylistComponent.
	 * @param x			The x-coordinate of the drop location.
	 * @param y			The y-coordinate of the drop location.
	 */
	void filesDropped(const juce::StringArray& files, int x, int y) override;

private:
	/**
	 * Initialize button to add and make visible with custom design
	 *
	 * @param button Reference to the buttons to init.
	 */
	void initializeButton(juce::TextButton& button);

	// Import audio track
	/**
	 * Imports audio track specified by the given file.
	 * Then, retrieves the track's title, URL, and length, and adds it to the playlist if it's unique.
	 * Finally, updates the table component to reflect the changes.
	 *
	 * @param audioTrackFile		The file representing the audio track to import.
	 */
	void importAudioTrack(const juce::File& audioTrackFile);

	/**
	 * Extracts audio track's title from the provided file.
	 *
	 * @param audioTrackFile		The file representing the audio track.
	 * @return						The audio track's title.
	 */
	juce::String getAudioTrackTitle(const juce::File& audioTrackFile);

	/**
	 * Extracts audio track's URL from the provided file.
	 *
	 * @param audioTrackFile		The file representing the audio track.
	 * @return						The audio track's URL.
	 */
	juce::String getAudioTrackURL(const juce::File& audioTrackFile);

	/**
	 * Retrieves the formatted length of the audio track specified by the URL.
	 *
	 * @param audioURL				The audio track's URL.
	 * @return						The formatted length of the audio track in "hour:minute:second" format.
	 */
	juce::String getFormattedAudioTrackLength(const juce::URL& audioURL);

	/**
	 * Extracts audio track's type from the provided file.
	 *
	 * @param audioTrackFile		The file representing the audio track.
	 * @return						The audio track's type.
	 */
	juce::String getAudioFileType(const juce::File& audioTrackFile);

	/**
	 * Checks if the audio track with the given title already exists in the playlist.
	 *
	 * @param importedTrackTitle	The audio track's title to check.
	 * @return						True if the audio track exists; otherwise, False.
	 */
	bool audioTrackExist(const juce::String& importedTrackTitle) const;

	/**
	 * Loads selected audio track onto the specified deck.
	 *
	 * @param deckGUI				The deckGUI to load the track into.
	 * @param selectedRow			The selected audio track's index in the playlist.
	 */
	void loadTrackToDeck(DeckGUI* deckGUI, int selectedRow);

	/**
	 * Removes audio track at the specified index from the playlist.
	 *
	 * @param id					The audio track's index to remove.
	 */
	void removeSelectedTrack(int id);

	/**
	 * TextEditor::Listener
	 * Called when the text within the text editor changes.
	 * Searches for specified title in the playlist.
	 * Highlight the first matching title.
	 * Deselect all tracks if no match is found.
	 *
	 * @param searchText			Reference to the text editor containing the search query.
	 */
	void textEditorTextChanged(juce::TextEditor& searchText) override;

	juce::AudioFormatManager& formatManager;
	juce::TableListBox tableComponent;
	
	/** 
	 * Vector to store relevant metadata of each audio track.
	 */
	std::vector<AudioTrack> audioTracks;

	/** 
	 * Select audio track files.
	 */
	juce::FileChooser chooser{ "< Select audio track... >" };

	/** 
	 * Buttons to import audio tracks and load to Deck A or B
	 */
	juce::TextButton importTrackButton{ "IMPORT TRACK" }
					,loadToDeckAButton{ "LOAD DECK A" }
					,loadToDeckBButton{ "LOAD DECK B" };
	
	/** 
	 * Remove button
	 */
	juce::ImageButton* removeButton = nullptr;

	/** 
	 * Search bar
	 */
	juce::TextEditor searchBar;
	
	/** 
	 * Pointer to both decks
	 */
	DeckGUI* deckGUI1; 
	DeckGUI* deckGUI2;
	
	/**
	 * Pointer to DJAudioPlater
	 */
	DJAudioPlayer* player;

	/**
	 * Custom design for UI elements 
	 */
	CustomDesign customDesign;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlaylistComponent)
};
