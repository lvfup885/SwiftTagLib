
#import "AudioFile.hpp"
#import <taglib/dsffile.h>

AUDIO_FILE_METADATA_READ_IMPLEMENTATION(AudioFile::DSF, TagLib::DSF::File, [&] (auto& file) {
    if (file.tag()) {
        metadata->overlay(AudioMetadata::fromID3v2Tag(file.tag()));
    }
});

AUDIO_FILE_METADATA_WRITE_IMPLEMENTATION(AudioFile::DSF, TagLib::DSF::File, [&] (auto& file) {
    metadata->fillID3v2Tag(file.tag());
});
