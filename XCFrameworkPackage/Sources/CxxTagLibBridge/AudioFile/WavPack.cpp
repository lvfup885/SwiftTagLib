
#import "AudioFile.hpp"
#import <taglib/wavpackfile.h>

AUDIO_FILE_METADATA_READ_IMPLEMENTATION(AudioFile::WavPack, TagLib::WavPack::File, [&] (auto& file) {
    if (file.hasID3v1Tag()) {
        metadata->overlay(AudioMetadata::fromID3v1Tag(file.ID3v1Tag()));
    }
    if (file.hasAPETag()) {
        metadata->overlay(AudioMetadata::fromAPETag(file.APETag()));
    }
});

AUDIO_FILE_METADATA_WRITE_IMPLEMENTATION(AudioFile::WavPack, TagLib::WavPack::File, [&] (auto& file) {
    if (file.hasID3v1Tag()) {
        metadata->fillID3v1Tag(file.ID3v1Tag());
    }
    metadata->fillAPETag(file.APETag(true));
});
