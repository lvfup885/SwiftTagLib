
#import "AudioFile.hpp"
#import <taglib/trueaudiofile.h>

AUDIO_FILE_METADATA_READ_IMPLEMENTATION(AudioFile::TrueAudio, TagLib::TrueAudio::File, [&] (auto& file) {
    if (file.hasID3v1Tag()) {
        metadata->overlay(AudioMetadata::fromID3v1Tag(file.ID3v1Tag()));
    }
    if (file.hasID3v2Tag()) {
        metadata->overlay(AudioMetadata::fromID3v2Tag(file.ID3v2Tag()));
    }
});

AUDIO_FILE_METADATA_WRITE_IMPLEMENTATION(AudioFile::TrueAudio, TagLib::TrueAudio::File, [&] (auto& file) {
    if (file.hasID3v1Tag()) {
        metadata->fillID3v1Tag(file.ID3v1Tag());
    }
    metadata->fillID3v2Tag(file.ID3v2Tag(true));
});
