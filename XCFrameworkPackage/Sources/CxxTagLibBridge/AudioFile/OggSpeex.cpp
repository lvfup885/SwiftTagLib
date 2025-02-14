
#import "AudioFile.hpp"
#import <taglib/speexfile.h>

AUDIO_FILE_METADATA_READ_IMPLEMENTATION(AudioFile::OggSpeex, TagLib::Ogg::Speex::File, [&] (auto& file) {
    if (file.tag()) {
        metadata->overlay(AudioMetadata::fromXiphComment(file.tag()));
    }
});

AUDIO_FILE_METADATA_WRITE_IMPLEMENTATION(AudioFile::OggSpeex, TagLib::Ogg::Speex::File, [&] (auto& file) {
    metadata->fillXiphComment(file.tag());
});
