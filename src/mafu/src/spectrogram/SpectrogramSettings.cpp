//
// Created by Matt on 9/19/2021.
//

#include <file_viewer/spectrogram/SpectrogramSettings.h>
#include <meta/util/math.h>
#include <meta/audio/decibels.h>


SpectrogramSettings::SpectrogramSettings()
    : m_FFTOrder(10)
    , m_XOverlap(1)
    , m_Scale(Scale::LOG)
{
    std::vector<juce::Colour> colours = {
            juce::Colours::black,
            juce::Colours::darkblue,
            juce::Colours::purple,
            juce::Colours::darkred,
            juce::Colours::red,
            juce::Colours::orange,
            juce::Colours::yellow,
            juce::Colours::white,
    };

    m_Gradient.clearColours();
    const auto increment = 1.0f / float(colours.size() - 1);
    float position = 0;
    for (auto& colour : colours)
    {
        m_Gradient.addColour(position, colour);
        position += increment;
    }

    // Recalculate the bin size weights
    const auto halfft = getFFTSize() / 2;
    for (int i = 0; i < halfft; i++)
    {
        float x = float(i) / float(getFFTSize() / 2.0f);
        m_BinWeights.push_back(meta::Interpolate<float>::parabolic(1, 20, x, 0));
    }
}

void SpectrogramSettings::setGradient(const juce::ColourGradient& gradient)
{
    m_Gradient = gradient;
    m_Listeners.call([this] (Listener& l) { l.gradientChanged(this); });
}

void SpectrogramSettings::setScale(const SpectrogramSettings::Scale& scale)
{
    m_Scale = scale;
//    m_BinWeights.clear();

    m_Listeners.call([this] (Listener& l) { l.fftChanged(this); });
}

void SpectrogramSettings::setFFTOrder(int fftOrder)
{
    m_FFTOrder = fftOrder;
    m_Listeners.call([this] (Listener& l) { l.fftChanged(this); });
}

void SpectrogramSettings::setXOverlap(int overlap)
{
    m_XOverlap = overlap;
    m_Listeners.call([this] (Listener& l) { l.fftChanged(this); });
}

