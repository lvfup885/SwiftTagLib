//
//#import "AudioFile.hpp"
//#import <taglib/modfile.h>
//
//AUDIO_FILE_METADATA_READ_IMPLEMENTATION(AudioFile::ProTrackerModule, TagLib::Mod::File, [&] (auto& file) {
//    if (file.tag()) {
//        metadata->overlay(AudioMetadata::fromTag(file.tag()));
//    }
//});
//
//AUDIO_FILE_METADATA_WRITE_IMPLEMENTATION(AudioFile::ProTrackerModule, TagLib::Mod::File, [&] (auto& file) {
//    if (file.tag()) {
//        metadata->fillTag(file.tag());
//    }
//});
