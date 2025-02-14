
#import "AudioMetadata.hpp"

/// constructor for `AudioMetadata` from `TagLib::ID3v1::Tag`.
AudioMetadata AudioMetadata::fromID3v1Tag(const TagLib::ID3v1::Tag *tag) {
    return AudioMetadata::fromTag(tag);
}

/// fills`TagLib::ID3v1::Tag` from `AudioMetadata`.
void AudioMetadata::fillID3v1Tag(TagLib::ID3v1::Tag *tag) const {
    fillTag(tag);
}
