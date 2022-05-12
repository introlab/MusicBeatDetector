#ifndef MUSIC_BEAT_DETECTOR_OBTAIN_BEAT_CLASSIFIER_H
#define MUSIC_BEAT_DETECTOR_OBTAIN_BEAT_CLASSIFIER_H

#include <MusicBeatDetector/Utils/ClassMacro.h>

#include <armadillo>

#include <cstddef>

namespace introlab
{
    class BeatClassifier
    {
        float m_ossSamplingFrequency;
        arma::fvec m_cbss;

        size_t m_classificationCountAfterBeat;

    public:
        BeatClassifier(float ossSamplingFrequency = 44100.0 / 128, float minBpm = 50);
        virtual ~BeatClassifier();

        DECLARE_NOT_COPYABLE(BeatClassifier);
        DECLARE_NOT_MOVABLE(BeatClassifier);

        bool classify(float bpm, float cbss);

    private:
        arma::fvec generatePulseTrain(std::size_t beatPeriod);
    };
}

#endif
