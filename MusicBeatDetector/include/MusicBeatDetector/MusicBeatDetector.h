#ifndef MUSIC_BEAT_DETECTOR_MUSIC_BEAT_DETECTOR_H
#define MUSIC_BEAT_DETECTOR_MUSIC_BEAT_DETECTOR_H

#include <MusicBeatDetector/Obtain/OssCalculator.h>
#include <MusicBeatDetector/Obtain/BpmEstimator.h>
#include <MusicBeatDetector/Obtain/CbssCalculator.h>
#include <MusicBeatDetector/Obtain/BeatClassifier.h>

#include <MusicBeatDetector/Utils/ClassMacro.h>

namespace introlab
{
    struct Beat
    {
        float bpm;
        bool isBeat;
    };

    /**
     *  Implement some parts of the OBTAIN algorithm (https://arxiv.org/abs/1704.02216)
     */
    class MusicBeatDetector
    {
        OssCalculator m_ossCalculator;
        BpmEstimator m_bpmEstimator;
        CbssCalculator m_cbssCalculator;
        BeatClassifier m_beatClassifier;

    public:
        MusicBeatDetector(
            float samplingFrequency,
            std::size_t frameSampleCount = 128,
            std::size_t ossFttWindowSize = 1024,
            std::size_t fluxHammingSize = 15,
            std::size_t ossBpmWindowSize = 1024,
            float minBpm = 50,
            float maxBpm = 180,
            std::size_t bpmCandidateCount = 10);
        virtual ~MusicBeatDetector();

        DECLARE_NOT_COPYABLE(MusicBeatDetector);
        DECLARE_NOT_MOVABLE(MusicBeatDetector);

        Beat detect(const PcmAudioFrame& frame);
    };
}

#endif
