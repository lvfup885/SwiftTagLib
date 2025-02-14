
#import "AudioMetadata.hpp"

/// constructor for `AudioMetadata` from `TagLib::Ogg::XiphComment`.
AudioMetadata AudioMetadata::fromXiphComment(const TagLib::Ogg::XiphComment *tag) {
    auto metadata = AudioMetadata();
    auto additionalMetadata = AudioMetadata::AdditionalMetadata();

    for (auto iterator: tag->fieldListMap()) {
        auto key = iterator.first.toCString(true);
        auto value = iterator.second.front().toCString();

        #warning unsafe `cString` to `int` conversions below
        #warning some irrelevant metadata keys are ignored

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
            metadata.comment = strcmp(value, "true") == 0;
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
//        } else if (strcasecmp(key, "TitleSort")) {
//
//        } else if (strcasecmp(key, "AlbumTitleSort")) {
//
//        } else if (strcasecmp(key, "ArtistSort")) {
//
//        } else if (strcasecmp(key, "AlbumArtistSort")) {
//
//        } else if (strcasecmp(key, "ComposerSort")) {
//
//        } else if (strcasecmp(key, "Grouping")) {
//
//        } else if (strcasecmp(key, "ReplayGain_Reference_Loudness")) {
//
//        } else if (strcasecmp(key, "ReplayGain_TracK_Gain")) {
//
//        } else if (strcasecmp(key, "ReplayGain_Track_Peak")) {
//
//        } else if (strcasecmp(key, "RaplayGain_Album_Gain")) {
//
//        } else if (strcasecmp(key, "ReplayGain_Album_Peak")) {

        // TagLib parses "METADATA_BLOCK_PICTURE" and "COVERART" Xiph comments as pictures, so ignore them here
        } else if (strcasecmp(key, "Metadata_Block_Picture") || strcasecmp(key, "CoverArt")) {
            // specifically do nothing here
            continue;
        } else {
            additionalMetadata.push_back(std::pair<std::string, std:: string>(key, value));
//            additionalMetadata[key] = value;
        }

    }

    // add additional if needed
    if (!additionalMetadata.empty()) {
        metadata.additional = additionalMetadata;
    }
    // process pictures
    for (auto iterator: const_cast<TagLib::Ogg::XiphComment *>(tag)->pictureList()) {
        auto picture = AudioMetadata::Picture::fromFLACPicture(iterator);
        metadata.attachedPictures.push_back(picture);
    }

    return metadata;
}

/// fills`TagLib::Ogg::XiphComment` from `AudioMetadata`.
void AudioMetadata::fillXiphComment(TagLib::Ogg::XiphComment *tag) const {
    auto apply_string = [&] (const char *key, std::string value) {
        tag->removeFields(key);
        tag->addField(key, TagLib::String(value));
    };

    auto apply_number = [&] (const char *key, int value) {
        apply_string(key, std::to_string(value));
    };

    auto apply_bool = [&] (const char *key, bool value) {
        apply_string(key, value ? "1" : "0");
    };

    // Standard tags
    apply_string("ALBUM", albumTitle);
    apply_string("ARTIST", artist);
    apply_string("ALBUMARTIST", albumArtist);
    apply_string("COMPOSER", composer);
    apply_string("GENRE", genre);
    apply_string("DATE", releaseDate);
    apply_string("DESCRIPTION", comment);
    apply_string("TITLE", title);
    apply_number("TRACKNUMBER", trackNumber);
    apply_number("TRACKTOTAL", trackTotal);
    apply_bool("COMPILATION", compilation);
    apply_number("DISCNUMBER", discNumber);
    apply_number("DISCTOTAL", discTotal);
    apply_string("LYRICS", lyrics);
    apply_number("BPM", beatPerMinute);
    apply_number("RATING", rating);
    apply_string("ISRC", internationalStandardRecordingCode);
    apply_string("MCN", mediaCatalogNumber);
    apply_string("MUSICBRAINZ_ALBUMID", musicBrainzReleaseID);
    apply_string("MUSICBRAINZ_TRACKID", musicBrainzRecordingID);
    // Sorting
    #warning ignored metadata sorting and grouping
//    apply_string("TITLESORT", titleSortOrder);
//    apply_string("ALBUMTITLESORT", albumTitleSortOrder);
//    apply_string("ARTISTSORT", artistSortOrder);
//    apply_string("ALBUMARTISTSORT", albumArtistSortOrder);
//    apply_string("COMPOSERSORT", composerSortOrder);
//    apply_string("GROUPING", grouping);

    // Additional metadata
    if (!additional.empty()) {
        for (auto item: additional) {
            auto key = item.first.c_str();
            auto value = item.second;
            apply_string(key, value);
        }
    }

    // ReplayGain
    #warning ignored metadata replay gain

    // Album art
    tag->removeAllPictures();
    if (!attachedPictures.empty()) {
        for (auto picture: attachedPictures) {
            tag->addPicture(picture.asFlacPicture()/*.release()*/);
        }
    }
}
