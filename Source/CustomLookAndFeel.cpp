/*
  ==============================================================================

    customLookAndFeel.cpp
    Created: 10 Mar 2024 7:13:34pm
    Author:  ziade

  ==============================================================================
*/

#include <JuceHeader.h>
#include "CustomLookAndFeel.h"

//==============================================================================
CustomLookAndFeel::CustomLookAndFeel() {

}

CustomLookAndFeel::~CustomLookAndFeel() {

}

void CustomLookAndFeel::drawLinearSlider(Graphics& g, int x, int y, int width, int height,
    float sliderPos, float minSliderPos, float maxSliderPos,
    const Slider::SliderStyle style, Slider& slider) {
    //number of notches
    const int notches = 15;
    float notchSpacing = height / notches;

    if (slider.isVertical()) {
        auto centerLine = (x + width) / 2.0f;
        auto sliderThickness = width / 8.0f;

        // draw notches for the slider.
        for (int i = 0; i <= notches; i++) {
            auto position = jmap(static_cast<float>(i), 0.0f, static_cast<float>(notches), static_cast<float>(y), static_cast<float>(y + height));

            g.setColour(i > 0 && i < notches ? Colours::lightgrey : Colours::darkgrey);
            g.drawLine(centerLine, position, centerLine, position, sliderThickness / 4.0f);
        }

        g.setColour(Colours::darkgrey.withAlpha(0.5f));
        g.fillRoundedRectangle(centerLine - sliderThickness / 2.0f, static_cast<float>(y), sliderThickness, static_cast<float>(height), 10.0f);

        g.setColour(Colours::lightslategrey);
        g.fillRect(x + width / 4.0f, sliderPos - notchSpacing * 0.4f, width / 2.0f, notchSpacing * 0.75f);
    }
}

