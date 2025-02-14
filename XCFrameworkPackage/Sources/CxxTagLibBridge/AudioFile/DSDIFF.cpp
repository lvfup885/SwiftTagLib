
#import "AudioFile.hpp"
#import <taglib/dsdifffile.h>

AUDIO_FILE_METADATA_READ_IMPLEMENTATION(AudioFile::DSDIFF, TagLib::DSDIFF::File, [&] (auto& file) {
    if (file.hasDIINTag()) {
        metadata->overlay(AudioMetadata::fromTag(file.DIINTag()));
    }
    if (file.hasID3v2Tag()) {
        metadata->overlay(AudioMetadata::fromID3v2Tag(file.ID3v2Tag()));
    }
});

AUDIO_FILE_METADATA_WRITE_IMPLEMENTATION(AudioFile::DSDIFF, TagLib::DSDIFF::File, [&] (auto& file) {
    metadata->fillTag(file.tag());
    metadata->fillID3v2Tag(file.ID3v2Tag());
});
