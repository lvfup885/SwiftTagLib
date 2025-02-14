//
//#import "AudioFile.hpp"
//#import <taglib/itfile.h>
//
//AUDIO_FILE_METADATA_READ_IMPLEMENTATION(AudioFile::ImpulseTrackerModule, TagLib::IT::File, [&] (auto& file) {
//    if (file.tag()) {
//        metadata->overlay(AudioMetadata::fromTag(file.tag()));
//    }
//});
//
//AUDIO_FILE_METADATA_WRITE_IMPLEMENTATION(AudioFile::ImpulseTrackerModule, TagLib::IT::File, [&] (auto& file) {
//    if (file.tag()) {
//        metadata->fillTag(file.tag());
//    }
//});
