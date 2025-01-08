
#import "AudioFile.hpp"
#import <taglib/vorbisfile.h>

AUDIO_FILE_METADATA_READ_IMPLEMENTATION(AudioFile::OggVorbis, TagLib::Ogg::Vorbis::File, [&] (auto& file) {
    if (file.tag()) {
        metadata->overlay(AudioMetadata::fromXiphComment(file.tag()));
    }
});

AUDIO_FILE_METADATA_WRITE_IMPLEMENTATION(AudioFile::OggVorbis, TagLib::Ogg::Vorbis::File, [&] (auto& file) {
    metadata->fillXiphComment(file.tag());
});
