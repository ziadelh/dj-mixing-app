/*
  ==============================================================================

    CustomPosSlider.cpp
    Created: 10 Mar 2024 7:11:38pm
    Author:  ziade

  ==============================================================================
*/

#include <JuceHeader.h>
#include "CustomPosSlider.h"

//==============================================================================
CustomPosSlider::CustomPosSlider() {

}

CustomPosSlider::~CustomPosSlider() {

}

void CustomPosSlider::drawRotarySlider(Graphics& g, int x, int y, int width, int height,
    float sliderPos, const float rotaryStartAngle,
    const float rotaryEndAngle, Slider&) {
    //dimensions of the slider's circle.
    auto diameter = jmin(width, height) - 8.0f; 
    auto radius = diameter / 2.0f;
    auto centreX = x + width * 0.5f;
    auto centreY = y + height * 0.5f;
    auto rx = centreX - radius;
    auto ry = centreY - radius;
    auto rw = radius * 2.0f;

    //current angle.
    auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

    g.setColour(Colours::darkgrey);
    g.fillEllipse(rx, ry, rw, rw);

    //slider's outline.
    g.setColour(Colours::white);
    g.drawEllipse(rx, ry, rw, rw, 2.0f); 

    //slider's pointer.
    Path pointer;
    auto pointerLength = radius * 0.5f; 
    auto pointerThickness = 3.0f; 
    pointer.addRectangle(-pointerThickness / 2.0f, -pointerLength, pointerThickness, pointerLength);
    pointer.applyTransform(AffineTransform::rotation(angle).translated(centreX, centreY));

    g.setColour(Colours::lavender); 
    g.fillPath(pointer);
}