
#import "AudioFile.hpp"
#import <taglib/mp4file.h>

AUDIO_FILE_METADATA_READ_IMPLEMENTATION(AudioFile::MP4, TagLib::MP4::File, [&] (auto& file) {
    if (file.tag()) {
        metadata->overlay(AudioMetadata::fromMP4Tag(file.tag()));
    }
});

AUDIO_FILE_METADATA_WRITE_IMPLEMENTATION(AudioFile::MP4, TagLib::MP4::File, [&] (auto& file) {
    metadata->fillMP4Tag(file.tag());
});
