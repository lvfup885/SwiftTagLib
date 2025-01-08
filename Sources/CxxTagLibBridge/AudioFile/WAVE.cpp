
#import "AudioFile.hpp"
#import <taglib/wavfile.h>

AUDIO_FILE_METADATA_READ_IMPLEMENTATION(AudioFile::WAVE, TagLib::RIFF::WAV::File, [&] (auto& file) {
    if (file.hasInfoTag()) {
        metadata->overlay(AudioMetadata::fromTag(file.InfoTag()));
    }
    if (file.hasID3v2Tag()) {
        metadata->overlay(AudioMetadata::fromID3v2Tag(file.ID3v2Tag()));
    }
});

AUDIO_FILE_METADATA_WRITE_IMPLEMENTATION(AudioFile::WAVE, TagLib::RIFF::WAV::File, [&] (auto& file) {
    if (file.hasInfoTag()) {
        metadata->fillTag(file.InfoTag());
    }
    metadata->fillID3v2Tag(file.ID3v2Tag());
});
