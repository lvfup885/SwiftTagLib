
#import <CxxTagLibBridge/AudioMetadata.hpp>

/// constructor for `AudioMetadata` from `TagLib::ID3v1::Tag`.
AudioMetadata AudioMetadata::read_from_ID3v1_tag(const TagLib::ID3v1::Tag *tag) {
    auto metadata = AudioMetadata::read_from_tag(tag);
    metadata.tagSource |= TagSource::ID3v1;
    return metadata;
}

/// fills`TagLib::ID3v1::Tag` from `AudioMetadata`.
void AudioMetadata::write_to_ID3v1_tag(TagLib::ID3v1::Tag *tag) const {
    write_to_tag(tag);
}
