
#import "AudioFile.hpp"
#import <taglib/mpegfile.h>

AUDIO_FILE_METADATA_READ_IMPLEMENTATION(AudioFile::MP3, TagLib::MPEG::File, [&] (auto& file) {
    if (file.hasAPETag()) {
        metadata->overlay(AudioMetadata::fromAPETag(file.APETag()));
    }
    if (file.hasID3v1Tag()) {
        metadata->overlay(AudioMetadata::fromID3v1Tag(file.ID3v1Tag()));
    }
    if (file.hasID3v2Tag()) {
        metadata->overlay(AudioMetadata::fromID3v2Tag(file.ID3v2Tag()));
    }
});

AUDIO_FILE_METADATA_WRITE_IMPLEMENTATION(AudioFile::MP3, TagLib::MPEG::File, [&] (auto& file) {
    if (file.hasAPETag()) {
        metadata->fillAPETag(file.APETag(true));
    }
    if (file.hasID3v1Tag()) {
        metadata->fillID3v1Tag(file.ID3v1Tag());
    }
    metadata->fillID3v2Tag(file.ID3v2Tag(true));
});
