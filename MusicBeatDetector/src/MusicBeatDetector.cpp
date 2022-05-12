#include <MusicBeatDetector/MusicBeatDetector.h>

#include <MusicBeatDetector/Utils/Math/Math.h>

using namespace introlab;


MusicBeatDetector::MusicBeatDetector(
    float samplingFrequency,
    size_t frameSampleCount,
    size_t ossFttWindowSize,
    size_t fluxHammingSize,
    size_t ossBpmWindowSize,
    float minBpm,
    float maxBpm,
    size_t bpmCandidateCount)
    : m_ossCalculator(frameSampleCount, ossFttWindowSize, fluxHammingSize),
      m_bpmEstimator(samplingFrequency / frameSampleCount, ossBpmWindowSize, minBpm, maxBpm, bpmCandidateCount),
      m_cbssCalculator(samplingFrequency / frameSampleCount, minBpm),
      m_beatClassifier(samplingFrequency / frameSampleCount, minBpm)
{
}

MusicBeatDetector::~MusicBeatDetector() {}

Beat MusicBeatDetector::detect(const PcmAudioFrame& frame)
{
    Beat beat;

    float oss = m_ossCalculator.calculate(frame);
    beat.bpm = m_bpmEstimator.estimate(oss);
    float cbss = m_cbssCalculator.calculate(beat.bpm, oss);
    beat.isBeat = m_beatClassifier.classify(beat.bpm, cbss);

    return beat;
}
