#ifndef MUSIC_BEAT_DETECTOR_OBTAIN_TEMPO_ESTIMATOR_H
#define MUSIC_BEAT_DETECTOR_OBTAIN_TEMPO_ESTIMATOR_H

#include <MusicBeatDetector/Utils/ClassMacro.h>
#include <MusicBeatDetector/Utils/Math/CrossCorrelationCalculator.h>

#include <armadillo>

#include <cstddef>
#include <vector>

namespace introlab
{
    class BpmEstimator
    {
        struct CandidateScore
        {
            float maxScore;
            float varScore;
        };

        float m_ossSamplingFrequency;
        std::size_t m_minLag;
        std::size_t m_maxLag;
        std::size_t m_candidateCount;

        arma::fvec m_oss;

        CrossCorrelationCalculator m_crossCorrelationCalculator;

    public:
        BpmEstimator(
            float ossSamplingFrequency = 44100.0 / 128,
            std::size_t ossWindowSize = 1024,
            float minBpm = 50,
            float maxBpm = 180,
            std::size_t candidateCount = 10);
        virtual ~BpmEstimator();

        DECLARE_NOT_COPYABLE(BpmEstimator);
        DECLARE_NOT_MOVABLE(BpmEstimator);

        float estimate(float oss);

    private:
        arma::fvec calculateEnhancedAutoCorrelation();
        std::vector<std::size_t> calculateCandidateLags(const arma::fvec& enhancedAutoCorrelation);

        std::size_t getBestLag(const std::vector<size_t>& candidateLags);
        CandidateScore calcultateCandidateLagScore(size_t lag);
    };
}

#endif
