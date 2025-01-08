
#import "AudioFile.hpp"
#import <taglib/opusfile.h>

AUDIO_FILE_METADATA_READ_IMPLEMENTATION(AudioFile::OggOpus, TagLib::Ogg::Opus::File, [&] (auto& file) {
    if (file.tag()) {
        metadata->overlay(AudioMetadata::fromXiphComment(file.tag()));
    }
});

AUDIO_FILE_METADATA_WRITE_IMPLEMENTATION(AudioFile::OggOpus, TagLib::Ogg::Opus::File, [&] (auto& file) {
    metadata->fillXiphComment(file.tag());
});
