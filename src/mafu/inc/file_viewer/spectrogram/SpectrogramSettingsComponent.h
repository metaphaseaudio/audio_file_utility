//
// Created by Matt on 9/6/2021.
//

#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include <meta/gooey/GradientDesigner.h>
#include "SpectrogramSettings.h"


class SpectrogramSettingsComponent
    : public juce::Component
    , public juce::ChangeBroadcaster
    , juce::ChangeListener
    , juce::ComboBox::Listener
{
public:
    explicit SpectrogramSettingsComponent(SpectrogramSettings& settings);
    void resized() override;

private:
    void changeListenerCallback(juce::ChangeBroadcaster* source) override;
    void comboBoxChanged(juce::ComboBox* comboBoxThatHasChanged) override;

    SpectrogramSettings& r_Settings;
    meta::GradientDesigner m_GradientDesigner;
    juce::Label m_SelectScaleLabel, m_SelectFFTSizeLabel, m_SelectXOverlapLabel, m_GainMinLabel, m_GainMaxLabel;
    juce::ComboBox m_SelectScale, m_SelectFFTSize, m_SelectXOverlap;
    juce::Slider m_GainMin, m_GainMax;
};


