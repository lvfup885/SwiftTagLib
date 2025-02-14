
#import "AudioFile.hpp"
#import <taglib/aifffile.h>

AUDIO_FILE_METADATA_READ_IMPLEMENTATION(AudioFile::AIFF, TagLib::RIFF::AIFF::File, [&] (auto& file) {
    if (file.tag()) {
        metadata->overlay(AudioMetadata::fromID3v2Tag(file.tag()));
    }
});

AUDIO_FILE_METADATA_WRITE_IMPLEMENTATION(AudioFile::AIFF, TagLib::RIFF::AIFF::File, [&] (auto& file) {
    metadata->fillID3v2Tag(file.tag());
});
