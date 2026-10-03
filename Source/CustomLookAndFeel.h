/*
  ==============================================================================

    customLookAndFeel.h
    Created: 10 Mar 2024 7:13:34pm
    Author:  ziade

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class CustomLookAndFeel : public LookAndFeel_V4 {
public:
    CustomLookAndFeel();
    ~CustomLookAndFeel() override;

    void drawLinearSlider(Graphics& g, int x, int y, int width, int height,
        float sliderPos, float minSliderPos, float maxSliderPos,
        const Slider::SliderStyle style, Slider& slider) override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CustomLookAndFeel)
};