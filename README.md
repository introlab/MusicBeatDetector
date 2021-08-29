# MusicBeatDetector
[![Actions Status](https://github.com/introlab/MusicBeatDetector/workflows/tests/badge.svg)](https://github.com/introlab/MusicBeatDetector/actions)

MusicBeatDetector is a small C++ library to estimate the song tempo and to detect if the beat is in the current frame. The algorithm can be used in real time and is based on [OBTAIN](https://arxiv.org/abs/1704.02216).

Author(s): Marc-Antoine Maheux

## Dependencies

* Most dependencies are part of the project with git submodules in the [MusicBeatDetector/3rdParty](MusicBeatDetector/3rdParty) directory. FFTW is copied because there is no buildable git repository.

## ROS Users
* [beat_detector_node](https://github.com/introlab/audio_utils#beat_detector_node) is a ROS node that integrates this library.

## Setup (Ubuntu)
The following subsections explain how to use the library on Ubuntu.

### Install Dependencies
```bash
sudo apt-get install cmake build-essential gfortran texinfo
```

### Setup Submodules
```bash
git submodule init
git submodule update
```

### Build
```bash
cd <<<repository dir>>>
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make
```

## Example
The following example shows how to use the library.

```cpp
#include <MusicBeatDetector/MusicBeatDetector.h>

#include <iostream>

using namespace introlab;
using namespace std;

void getNextAudioFrame(size_t frameSampleCount, float* data)
{
    ...
}

int main(int argc, char** argv)
{
    constexpr size_t SamplingFrequency = 44100;
    constexpr size_t FrameSampleCount = 128;
    constexpr size_t ChannelCount = 1; // Other values are not supported

    float data[FrameSampleCount] = {0};

    try
    {
        PcmAudioFrame frame(PcmAudioFrameFormat::Float, ChannelCount, FrameSampleCount, reinterpret_cast<uint8_t*>(data));
        MusicBeatDetector musicBeatDetector(SamplingFrequency, FrameSampleCount);
    
        while (true)
        {
            getNextAudioFrame(FrameSampleCount, data);

            Beat beat = musicBeatDetector.detect(frame);
            cout << "BPM=" << beat.bpm << ", isBeat=" << beat.isBeat << endl;       
        }
    }
    catch (const std::exception& e)
    {
        cout << e.what() << endl;
    }

    return 0;
}
```

## License

* [GPL-3.0 License ](LICENSE)

## Sponsor

![IntRoLab](https://introlab.3it.usherbrooke.ca/IntRoLab.png)

[IntRoLab - Intelligent / Interactive / Integrated / Interdisciplinary Robot Lab](https://introlab.3it.usherbrooke.ca)
