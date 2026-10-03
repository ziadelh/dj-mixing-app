/*
  ==============================================================================

    PlaylistComponent.h
    Created: 5 Mar 2024 5:47:27pm
    Author:  ziade

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class DeckGUI;

//==============================================================================
/**
    The track library: lists the loaded tracks with their length, filters them
    with the search bar and sends a track to either deck.
*/
class PlaylistComponent : public juce::Component,
    public juce::TableListBoxModel,
    public juce::Button::Listener,
    public juce::TextEditor::Listener,
    public juce::FileDragAndDropTarget,
    public juce::AudioSource {
public:
    PlaylistComponent(AudioFormatManager& formatManagerToUse);
    ~PlaylistComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    int getNumRows() override;
    void paintRowBackground(Graphics&, int rowNumber, int width, int height, bool rowIsSelected) override;
    void paintCell(Graphics&, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;
    Component* refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component* existingComponentToUpdate) override;

    void buttonClicked(Button* button) override;

    // drag and drop
    bool isInterestedInFileDrag(const StringArray& files) override;
    void filesDropped(const StringArray& files, int x, int y) override;

    // search bar
    void textEditorTextChanged(TextEditor&) override;

    // load tracks
    void promptLoadButton();
    void setDecks(DeckGUI* leftDeck, DeckGUI* rightDeck);

private:
    /** Adds an audio file to the library. Files JUCE cannot read as audio are ignored. */
    void addTrack(const File& file);

    /** Rebuilds the list of rows that match the search text and refreshes the table. */
    void updateVisibleRows();

    //playlist table
    TableListBox tableComponent;
    TextEditor searchBar;
    Label searchSet;

    //load button
    TextButton loadButton{ "LOAD" };

    // every loaded track (full path) and its length in seconds, in the same order
    std::vector<std::string> library;
    std::vector<int> trackDurations;

    // indices into library of the tracks that match the search text (the rows shown)
    std::vector<int> visibleRows;

    AudioFormatManager& formatManagerToUse;
    FileChooser fChooser;

    DeckGUI* deck1 = nullptr;
    DeckGUI* deck2 = nullptr;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlaylistComponent)
};
