
#import "AudioFile.hpp"
#import <taglib/oggflacfile.h>

AUDIO_FILE_METADATA_READ_IMPLEMENTATION(AudioFile::OggFLAC, TagLib::Ogg::FLAC::File, [&] (auto& file) {
    if (file.tag()) {
        metadata->overlay(AudioMetadata::fromXiphComment(file.tag()));
    }
});

AUDIO_FILE_METADATA_WRITE_IMPLEMENTATION(AudioFile::OggFLAC, TagLib::Ogg::FLAC::File, [&] (auto& file) {
    metadata->fillXiphComment(file.tag());
});
