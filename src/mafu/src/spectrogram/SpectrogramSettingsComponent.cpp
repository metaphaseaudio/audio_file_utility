//
// Created by Matt on 9/6/2021.
//

#include <file_viewer/spectrogram/SpectrogramSettingsComponent.h>


SpectrogramSettingsComponent::SpectrogramSettingsComponent(SpectrogramSettings& settings)
    : r_Settings(settings)
    , m_SelectScaleLabel("Freq Scale", "Frequency Scale:")
    , m_SelectFFTSizeLabel("FFT Size", "FFT Size")
    , m_SelectXOverlapLabel("X Overlap", "Overlap")
    , m_GainMinLabel("Gain Min", "Gain Min")
    , m_GainMaxLabel("Gain Max", "Gain Max")
{
    addAndMakeVisible(m_SelectScaleLabel); addAndMakeVisible(m_SelectScale);
    addAndMakeVisible(m_SelectFFTSizeLabel); addAndMakeVisible(m_SelectFFTSize);
    addAndMakeVisible(m_SelectXOverlapLabel); addAndMakeVisible(m_SelectXOverlap);
    addAndMakeVisible(m_GainMinLabel); addAndMakeVisible(m_GainMin);
    addAndMakeVisible(m_GainMaxLabel); addAndMakeVisible(m_GainMax);

    addAndMakeVisible(m_GradientDesigner);
    m_GradientDesigner.setGradient(r_Settings.getGradient());
    m_GradientDesigner.addChangeListener(this);

    m_SelectScale.addItemList({"Linear", "Log", "Mel"}, 1);
    m_SelectScale.setSelectedId(r_Settings.getScale() + 1, juce::dontSendNotification);
    m_SelectScale.addListener(this);

    m_SelectFFTSize.addItemList({"16", "32", "64", "128", "256", "512", "1024", "2048", "4096"}, 4);
    m_SelectFFTSize.setSelectedId(r_Settings.getFFTOrder(), juce::dontSendNotification);
    m_SelectFFTSize.addListener(this);

    m_SelectXOverlap.addItemList({"1x", "2x" ,"3x", "4x", "5x", "6x", "7x", "8x"}, 1);
    m_SelectXOverlap.setSelectedId(r_Settings.getXOverlap(), juce::dontSendNotification);
    m_SelectXOverlap.addListener(this);

    setSize(700, 700);
}

void SpectrogramSettingsComponent::resized()
{
    auto localBounds = getLocalBounds();
    m_GradientDesigner.setBounds(localBounds.removeFromTop(44));
    localBounds.removeFromTop(2);

    const auto halfWidth = localBounds.getWidth() / 2;

    auto rowBounds = localBounds.removeFromTop(22);
    m_SelectScaleLabel.setBounds(rowBounds.removeFromLeft(halfWidth));
    m_SelectScale.setBounds(rowBounds);
    localBounds.removeFromTop(2);

    rowBounds = localBounds.removeFromTop(22);
    m_SelectXOverlapLabel.setBounds(rowBounds.removeFromLeft(halfWidth));
    m_SelectXOverlap.setBounds(rowBounds);
    localBounds.removeFromTop(2);

    rowBounds = localBounds.removeFromTop(22);
    m_SelectFFTSizeLabel.setBounds(rowBounds.removeFromLeft(halfWidth));
    m_SelectFFTSize.setBounds(rowBounds);
    localBounds.removeFromTop(2);
}

void SpectrogramSettingsComponent::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    if (source == &m_GradientDesigner) { r_Settings.setGradient(m_GradientDesigner.getGradient()); }
}

void SpectrogramSettingsComponent::comboBoxChanged(juce::ComboBox* comboBoxThatHasChanged)
{
    if (comboBoxThatHasChanged == &m_SelectScale)
        { r_Settings.setScale(SpectrogramSettings::Scale(m_SelectScale.getSelectedId() - 1)); }
    if (comboBoxThatHasChanged == &m_SelectFFTSize)
        { r_Settings.setFFTOrder(m_SelectFFTSize.getSelectedId()); }
    if (comboBoxThatHasChanged == &m_SelectXOverlap)
        { r_Settings.setXOverlap(m_SelectXOverlap.getSelectedId()); }
}
