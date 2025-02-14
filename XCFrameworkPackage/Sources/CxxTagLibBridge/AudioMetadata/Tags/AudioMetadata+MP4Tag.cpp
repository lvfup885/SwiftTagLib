
#import "AudioMetadata.hpp"

/// constructor for `AudioMetadata` from `TagLib::MP4::Tag`.
AudioMetadata AudioMetadata::fromMP4Tag(const TagLib::MP4::Tag *tag) {
    AudioMetadata metadata = AudioMetadata::fromTag(tag);

    #warning some irrelevant metadata keys are ignored

    if (tag->contains("aART")) {
        metadata.albumArtist = tag->item("aART").toStringList().toString().toCString(true);
    }
    if (tag->contains("\251wrt")) {
        metadata.comment = tag->item("\251wrt").toStringList().toString().toCString(true);
    }
    if (tag->contains("\251day")) {
        metadata.releaseDate = tag->item("\251day").toStringList().toString().toCString(true);
    }
    if (tag->contains("trkn")) {
        auto track = tag->item("trkn").toIntPair();
        if (track.first) {
            metadata.trackNumber = track.first;
        }
        if (track.second) {
            metadata.trackTotal = track.second;
        }
    }
    if (tag->contains("disk")) {
        auto track = tag->item("disk").toIntPair();
        if (track.first) {
            metadata.discNumber = track.first;
        }
        if (track.second) {
            metadata.discTotal = track.second;
        }
    }
    if (tag->contains("cpil")) {
        if (tag->item("cpil").toBool()) {
            metadata.compilation = true;
        }
    }
    if (tag->contains("tmpo")) {
        auto bpm = tag->item("tmpo").toInt();
        if (bpm) {
            metadata.beatPerMinute = bpm;
        }
    }
    if (tag->contains("\241lyr")) {
        metadata.lyrics = tag->item("\251lyr").toStringList().toString().toCString(true);
    }
//    // Sorting
//    if (tag->contains("sonm")) {
//
//    }
//    if (tag->contains("soal")) {
//
//    }
//    if (tag->contains("soar")) {
//
//    }
//    if (tag->contains("soco")) {
//
//    }
    if (tag->contains("\251grp")) {
        metadata.lyrics = tag->item("\251grp").toStringList().toString().toCString(true);
    }
    // Album art
    if (tag->contains("covr")) {
        auto art = tag->item("covr").toCoverArtList();
        for (auto iterator: art) {
            auto picture = AudioMetadata::Picture::fromMP4Picture(iterator);
            metadata.attachedPictures.push_back(picture);
        }
    }
    // MusicBrainz
    if (tag->contains("---:com.apple.iTunes:MusicBrainz Album Id")) {
        metadata.musicBrainzReleaseID = tag->item("---:com.apple.iTunes:MusicBrainz Album Id").toStringList().toString().toCString(true);
    }
    if (tag->contains("---:com.apple.iTunes:MusicBrainz Track Id")) {
        metadata.musicBrainzRecordingID = tag->item("---:com.apple.iTunes:MusicBrainz Track Id").toStringList().toString().toCString(true);
    }
//    // ReplayGain
//    if (tag->contains("---:com.apple.iTunes:replaygain_reference_loudness")) {
//
//    }
//    if (tag->contains("---:com.apple.iTunes:replaygain_track_gain")) {
//
//    }
//    if (tag->contains("---:com.apple.iTunes:replaygain_track_peak")) {
//
//    }
//    if (tag->contains("---:com.apple.iTunes:replaygain_album_gain")) {
//
//    }
//    if (tag->contains("---:com.apple.iTunes:replaygain_album_peak")) {
//
//    }
    return metadata;
}

/// fills`TagLib::MP4::Tag` from `AudioMetadata`.
void AudioMetadata::fillMP4Tag(TagLib::MP4::Tag *tag) const {
    auto apply_item = [&] (const char* key, TagLib::MP4::Item item) {
        tag->removeItem(key);
        tag->setItem(key, item);
    };
    auto apply_string = [&] (const char* key, std::string value) {
        apply_item(key, TagLib::MP4::Item(TagLib::String(value)));
    };
    auto apply_number = [&] (const char* key, int value) {
        apply_item(key, TagLib::MP4::Item(value));
    };
    auto apply_bool = [&] (const char* key, bool value) {
        apply_item(key, TagLib::MP4::Item(value ? 1 : 0));
    };
    auto apply_pair = [&] (const char* key, int valueOne, int valueTwo) {
        apply_item(key, TagLib::MP4::Item(valueOne, valueTwo));
    };

    apply_string("\251nam", title);
    apply_string("\251ART", artist);
    apply_string("\251ALB", albumTitle);
    apply_string("aART", albumArtist);
    apply_string("\251gen", genre);
    apply_string("\251wrt", composer);
    apply_string("\251cmt", comment);
    apply_string("\251day", releaseDate);
    apply_pair("trkn", trackNumber, trackTotal);
    apply_pair("disk", discNumber, discTotal);
    apply_bool("cpil", compilation);
    apply_number("tmpo", beatPerMinute);
    apply_string("\251lyr", lyrics);

    // Sorting
    #warning ignored metadata sorting and grouping

    // MusicBrainz
    apply_string("---:com.apple.iTunes:MusicBrainz Album Id", musicBrainzReleaseID);
    apply_string("---:com.apple.iTunes:MusicBrainz Track Id", musicBrainzRecordingID);

    // ReplayGain
    #warning ignored metadata replay gain

    // Album Art
    if (!attachedPictures.empty()) {
        auto list = TagLib::MP4::CoverArtList();
        for (auto picture: attachedPictures) {
            list.append(picture.asMP4Picture());
        }
        tag->setItem("covr", list);
    } else {
        tag->removeItem("covr");
    }
}
