#include <file_viewer/FileViewerComponent.h>
#include <utility>

//==============================================================================
FileViewerComponent::FileViewerComponent(juce::File filepath, juce::AudioBuffer<float>& data, double sample_rate, SpectrogramSettings& settings)
    : m_Filepath(std::move(filepath))
    , m_Data(data)
    , m_SampleRate(sample_rate)
    , m_Waveform(1)
    , m_Spectrogram(m_Data, settings)
    , m_TimeRuler(juce::Range<float>(1, 100))
    , m_FreqRuler(juce::Range<float>(1, 100))
{
    m_Waveform.setClip(data, sample_rate);
    addAndMakeVisible(m_Spectrogram);
    addAndMakeVisible(m_Waveform);
    addAndMakeVisible(m_TimeRuler);
    addAndMakeVisible(m_FreqRuler);
    setSize (600, 400);
}

//==============================================================================
void FileViewerComponent::paint (juce::Graphics& g)
{
    g.setColour(juce::Colours::black);
    g.fillAll();
}

void FileViewerComponent::resized()
{
    auto local_bounds = getLocalBounds();
    auto time_ruler = local_bounds.removeFromBottom(22).removeFromLeft(local_bounds.getWidth() - 22);
    auto freq_ruler = local_bounds.removeFromRight(22);

    m_Waveform.setBounds(local_bounds);
    m_Spectrogram.setBounds(local_bounds);
    m_TimeRuler.setBounds(time_ruler);
    m_FreqRuler.setBounds(freq_ruler);
}

juce::File FileViewerComponent::getFilepath() const { return m_Filepath; }


void FileViewerComponent::setWaveformSpectrogramRatio(float ratio)
{
//    jassert(ratio >= -1 && ratio <= 1);
    const auto alpha = ratio;
    const auto inv_alpha = 2.0 - alpha;
    m_Waveform.setAlpha(alpha);
    m_Spectrogram.setAlpha(inv_alpha);
}