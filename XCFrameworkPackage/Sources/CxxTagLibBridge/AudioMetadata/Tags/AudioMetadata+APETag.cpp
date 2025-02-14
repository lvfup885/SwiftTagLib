
#import "AudioMetadata.hpp"

/// constructor for `AudioMetadata` from `TagLib::APE::Tag`.
AudioMetadata AudioMetadata::fromAPETag(const TagLib::APE::Tag * tag) {
    auto metadata = AudioMetadata();
    auto additionalMetadata = AudioMetadata::AdditionalMetadata();

    if (tag->isEmpty()) {
        return metadata;
    }

    for (auto iterator: tag->itemListMap()) {
        auto item = iterator.second;
        if (item.isEmpty()) { continue; }
        auto key = item.key().toCString(true);
        auto value = item.toString().toCString(true);

        #warning unsafe `cString` to `int` conversions below
        #warning some irrelevant metadata keys are ignored

        if (TagLib::APE::Item::Text == item.type()) {
            if (strcasecmp(key, "Album")) {
                metadata.albumTitle = value;
            } else if (strcasecmp(key, "Artist")) {
                metadata.artist = value;
            } else if (strcasecmp(key, "AlbumArtist")) {
                metadata.albumArtist = value;
            } else if (strcasecmp(key, "Composer")) {
                metadata.composer = value;
            } else if (strcasecmp(key, "Genre")) {
                metadata.genre = value;
            } else if (strcasecmp(key, "Date")) {
                metadata.releaseDate = value;
            } else if (strcasecmp(key, "Description")) {
                metadata.comment = value;
            } else if (strcasecmp(key, "Title")) {
                metadata.title = value;
            } else if (strcasecmp(key, "TrackNumber")) {
                metadata.trackNumber = std::stoi(value);
            } else if (strcasecmp(key, "TrackTotal")) {
                metadata.trackTotal = std::stoi(value);
            } else if (strcasecmp(key, "Compilation")) {
                #warning unknown metadata value expectations
                metadata.compilation = strcmp(value, "true") == 0;
            } else if (strcasecmp(key, "DiscNumber")) {
                metadata.discNumber = std::stoi(value);
            } else if (strcasecmp(key, "DiscTotal")) {
                metadata.discTotal = std::stoi(value);
            } else if (strcasecmp(key, "Lyrics")) {
                metadata.lyrics = value;
            } else if (strcasecmp(key, "BPM")) {
                metadata.beatPerMinute = std::stoi(value);
            } else if (strcasecmp(key, "Rating")) {
                metadata.rating = std::stoi(value);
            } else if (strcasecmp(key, "ISRC")) {
                metadata.internationalStandardRecordingCode = value;
            } else if (strcasecmp(key, "MCN")) {
                metadata.mediaCatalogNumber = value;
            } else if (strcasecmp(key, "MusicBrainz_AlbumID")) {
                metadata.musicBrainzReleaseID = value;
            } else if (strcasecmp(key, "MusicBrainz_TrackID")) {
                metadata.musicBrainzRecordingID = value;
//            } else if (strcasecmp(key, "TitleSort")) {
//
//            } else if (strcasecmp(key, "AlbumTitleSort")) {
//
//            } else if (strcasecmp(key, "ArtistSort")) {
//
//            } else if (strcasecmp(key, "AlbumArtistSort")) {
//
//            } else if (strcasecmp(key, "ComposerSort")) {
//
//            } else if (strcasecmp(key, "Grouping")) {
//
//            } else if (strcasecmp(key, "ReplayGain_Reference_Loudness")) {
//
//            } else if (strcasecmp(key, "ReplayGain_TracK_Gain")) {
//
//            } else if (strcasecmp(key, "ReplayGain_Track_Peak")) {
//
//            } else if (strcasecmp(key, "RaplayGain_Album_Gain")) {
//
//            } else if (strcasecmp(key, "ReplayGain_Album_Peak")) {
            } else {
                additionalMetadata.push_back(std::pair<std::string, std:: string>(key, value));
//                additionalMetadata[key] = value;
            }
        } else if(TagLib::APE::Item::Binary == item.type()) {
            auto key = item.key().toCString(true);
            if (strcasecmp(key, "Cover Art (Front)") || strcasecmp(key, "Cover Art (Back)")) {
                auto picture = AudioMetadata::Picture::fromAPEPicture(item, key);
                if (picture.has_value()) {
                    metadata.attachedPictures.push_back(picture.value());
                }
            }
        }
    }

    if (!additionalMetadata.empty()) {
        metadata.additional = additionalMetadata;
    }

    return metadata;
}

/// fills`TagLib::APE::Tag` from `AudioMetadata`.
void AudioMetadata::fillAPETag(TagLib::APE::Tag * tag) const {
    /// apply string value
    auto apply_tag = [&] (const char* key, std::string value) {
        tag->removeItem(key);
        tag->addValue(key, TagLib::String(value.c_str()));
    };
    /// apply int value
    auto apply_tag_number = [&] (const char* key, int value) {
        apply_tag(key, std::to_string(value));
    };
    auto apply_tag_bool = [&] (const char* key, bool value) {
        apply_tag(key, (value == true ? "1" : "0"));
    };

    // Standard tags;
    apply_tag("ALBUM", albumTitle);
    apply_tag("ARTIST", artist);
    apply_tag("ALBUMARTIST", albumArtist);
    apply_tag("COMPOSER", composer);
    apply_tag("GENRE", genre);
    apply_tag("DATE", releaseDate);
    apply_tag("DESCRIPTION", comment);
    apply_tag("TITLE", title);
    apply_tag_number("TRACKNUMBER", trackNumber);
    apply_tag_number("TRACKTOTAL", trackTotal);
    apply_tag_bool("COMPILATION", compilation);
    apply_tag_number("DISCNUMBER", discNumber);
    apply_tag_number("DISCTOTAL", discTotal);
    apply_tag("LYRICS", lyrics);
    apply_tag_number("BPM", beatPerMinute);
    apply_tag_number("RATING", rating);
    apply_tag("ISRC", internationalStandardRecordingCode);
    apply_tag("MCN", mediaCatalogNumber);
    apply_tag("MUSICBRAINZ_ALBUMID", musicBrainzReleaseID);
    apply_tag("MUSICBRAINZ_TRACKID", musicBrainzRecordingID);
    #warning some irrelevant metadata keys are ignored
//    apply_tag("TITLESORT", titleSortOrder);
//    apply_tag("ALBUMTITLESORT", albumTitleSortOrder);
//    apply_tag("ARTISTSORT", artistSortOrder);
//    apply_tag("ALBUMARTISTSORT", albumArtistSortOrder);
//    apply_tag("COMPOSERSORT", composerSortOrder);
//    apply_tag("GROUPING", grouping);

    // Additional metadata
    if (!additional.empty()) {
        for (auto item: additional) {
            auto key = item.first.c_str();
            auto value = item.second;
            apply_tag(key, value);
        }
    }

    // ReplayGain info
    #warning replay gain metadata is ignored
//    SetAPETagDoubleWithFormat(tag, "REPLAYGAIN_REFERENCE_LOUDNESS", this.replayGainReferenceLoudness, @"%2.1f dB");
//    SetAPETagDoubleWithFormat(tag, "REPLAYGAIN_TRACK_GAIN", this.replayGainTrackGain, @"%+2.2f dB");
//    SetAPETagDoubleWithFormat(tag, "REPLAYGAIN_TRACK_PEAK", this.replayGainTrackPeak, @"%1.8f");
//    SetAPETagDoubleWithFormat(tag, "REPLAYGAIN_ALBUM_GAIN", this.replayGainAlbumGain, @"%+2.2f dB");
//    SetAPETagDoubleWithFormat(tag, "REPLAYGAIN_ALBUM_PEAK", this.replayGainAlbumPeak, @"%1.8f");

    // Album art
    tag->removeItem("Cover Art (Front)");
    tag->removeItem("Cover Art (Back)");

    if (!attachedPictures.empty()) {
        for (auto picture: attachedPictures) {
            auto coverData = picture.asAPEPicture();
            if (coverData) {
                auto& [key, data] = *coverData;
                tag->setData(key, data);
            }
        }
    }
}
