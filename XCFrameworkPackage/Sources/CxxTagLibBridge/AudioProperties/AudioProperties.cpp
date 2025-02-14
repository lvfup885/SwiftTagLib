
#import "AudioProperties.hpp"

void AudioProperties::fillFromProperties(const TagLib::AudioProperties &properties) {
    lengthInSeconds = properties.lengthInSeconds();
    channels = properties.channels();
    sampleRate = properties.sampleRate();
    bitrate = properties.bitrate();
}
