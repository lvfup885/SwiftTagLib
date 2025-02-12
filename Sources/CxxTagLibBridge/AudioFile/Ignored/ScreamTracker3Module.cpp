//
//#import "AudioFile.hpp"
//#import <taglib/s3mfile.h>
//
//AUDIO_FILE_METADATA_READ_IMPLEMENTATION(AudioFile::ScreamTracker3Module, TagLib::S3M::File, [&] (auto& file) {
//    if (file.tag()) {
//        metadata->overlay(AudioMetadata::fromTag(file.tag()));
//    }
//});
//
//AUDIO_FILE_METADATA_WRITE_IMPLEMENTATION(AudioFile::ScreamTracker3Module, TagLib::S3M::File, [&] (auto& file) {
//    if (file.tag()) {
//        metadata->fillTag(file.tag());
//    }
//});
