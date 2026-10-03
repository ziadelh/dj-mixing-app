/*
  ==============================================================================

    PlaylistComponent.cpp
    Created: 5 Mar 2024 5:47:27pm
    Author:  ziade

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlaylistComponent.h"
#include "DeckGUI.h"

//==============================================================================
PlaylistComponent::PlaylistComponent(AudioFormatManager& _formatManagerToUse)
    : formatManagerToUse(_formatManagerToUse), fChooser("Select a file...") {

    addAndMakeVisible(tableComponent);
    tableComponent.getHeader().addColumn("TRACK TITLE", 1, 250);
    tableComponent.getHeader().addColumn("DURATION", 2, 100);
    tableComponent.getHeader().addColumn("ADD to Deck 1", 3, 100);
    tableComponent.getHeader().addColumn("ADD to Deck 2", 4, 100);
    tableComponent.setModel(this);

    addAndMakeVisible(searchSet);
    searchSet.setText("Search", juce::dontSendNotification);

    addAndMakeVisible(searchBar);
    searchBar.addListener(this);

    addAndMakeVisible(loadButton);
    loadButton.addListener(this);
}

PlaylistComponent::~PlaylistComponent()
{
}

int PlaylistComponent::getNumRows() {
    return static_cast<int>(visibleRows.size());
}

//=====================================================================
void PlaylistComponent::paintRowBackground(Graphics& g,
                                            int rowNumber,
                                            int width,
                                            int height,
                                            bool rowIsSelected) {
    g.fillAll(rowIsSelected ? Colours::orange : Colours::darkgrey);
}

void PlaylistComponent::paintCell(Graphics& g,
                                    int rowNumber,
                                    int columnId,
                                    int width,
                                    int height,
                                    bool rowIsSelected)
{
    if (rowNumber < 0 || rowNumber >= static_cast<int>(visibleRows.size())) {
        return;
    }

    const int track = visibleRows[rowNumber];

    if (columnId == 1) {
        String fileName = File(library[track]).getFileName();
        g.drawText(fileName, 2, 0, width - 4, height, Justification::centredLeft, true);
    }
    else if (columnId == 2) {
        g.drawText(String(trackDurations[track]) + "s", 2, 0, width - 4, height, Justification::centredLeft, true);
    }
}

Component* PlaylistComponent::refreshComponentForCell(int rowNumber, int columnId, bool /*isRowSelected*/, Component* existingComponentToUpdate) {
    //buttons that send the row's track to the left or right deck
    if (columnId == 3 || columnId == 4) {
        String id = String(rowNumber) + "_" + (columnId == 3 ? "LEFT" : "RIGHT");

        TextButton* btn = static_cast<TextButton*>(existingComponentToUpdate);
        if (btn == nullptr) {
            btn = new TextButton();
            btn->addListener(this);
        }

        btn->setButtonText(columnId == 3 ? "<--" : "-->");
        btn->setComponentID(id);
        btn->setColour(TextButton::buttonColourId, Colours::darkslateblue);
        return btn;
    }
    return existingComponentToUpdate;
}

//=====================================================================
void PlaylistComponent::buttonClicked(Button* button) {
    //load button click
    if (button == &loadButton) {
        promptLoadButton();
        return;
    }

    //button ids look like "<row>_LEFT" or "<row>_RIGHT"
    StringArray parts;
    parts.addTokens(button->getComponentID(), "_", "");
    if (parts.size() < 2) return;

    int rowNumber = parts[0].getIntValue();
    bool isLeftDeck = parts[1] == "LEFT";

    if (rowNumber >= 0 && rowNumber < static_cast<int>(visibleRows.size())) {
        String trackPath = library[visibleRows[rowNumber]];
        DeckGUI* targetDeck = isLeftDeck ? deck1 : deck2;
        if (targetDeck != nullptr) {
            targetDeck->loadTrack(trackPath);
        }
    }
}

//=====================================================================
bool PlaylistComponent::isInterestedInFileDrag(const StringArray& files) {
    return true;
}

void PlaylistComponent::filesDropped(const StringArray& files, int x, int y) {
    for (const String& filename : files) {
        File file(filename);
        if (file.existsAsFile()) {
            addTrack(file);
        }
    }
    updateVisibleRows();
}

//====================================================================
void PlaylistComponent::textEditorTextChanged(TextEditor& textEditor) {
    updateVisibleRows();
}

//=====================================================================
void PlaylistComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate) {}
void PlaylistComponent::getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) {}
void PlaylistComponent::releaseResources(){}

void PlaylistComponent::promptLoadButton() {
    fChooser.launchAsync(FileBrowserComponent::canSelectMultipleItems | FileBrowserComponent::openMode,
        [this](const FileChooser& chooser) {
            for (const auto& file : chooser.getResults()) {
                addTrack(file);
            }
            updateVisibleRows();
        });
}

void PlaylistComponent::addTrack(const File& file) {
    // only audio files that JUCE can open are added
    std::unique_ptr<AudioFormatReader> reader(formatManagerToUse.createReaderFor(file));
    if (reader == nullptr) {
        return;
    }

    library.push_back(file.getFullPathName().toStdString());
    trackDurations.push_back(static_cast<int>(reader->lengthInSamples / reader->sampleRate));
}

void PlaylistComponent::updateVisibleRows() {
    const String searchText = searchBar.getText().trim();

    visibleRows.clear();
    for (int i = 0; i < static_cast<int>(library.size()); ++i) {
        if (searchText.isEmpty() || File(library[i]).getFileName().containsIgnoreCase(searchText)) {
            visibleRows.push_back(i);
        }
    }

    tableComponent.updateContent();
    tableComponent.repaint();
}

//====================================================================
void PlaylistComponent::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);
}

void PlaylistComponent::resized()
{
    tableComponent.setBounds(0, getHeight() / 8, getWidth(), getHeight() / 8 * 6);
    searchSet.setBounds(0, 0, getWidth() / 6, getHeight() / 8);
    searchBar.setBounds(getWidth() / 6, 0, getWidth() / 6 * 4, getHeight() / 8);
    loadButton.setBounds(getWidth() - getWidth()/6, 0, getWidth() / 6, getHeight() / 8);
}

void PlaylistComponent::setDecks(DeckGUI* leftDeck, DeckGUI* rightDeck) {
    deck1 = leftDeck;
    deck2 = rightDeck;
}
