
#import "AudioMetadata.hpp"
#import <taglib/attachedpictureframe.h>
#import <taglib/id3v2frame.h>
#import <taglib/popularimeterframe.h>
#import <taglib/textidentificationframe.h>

/// constructor for `AudioMetadata` from `TagLib::ID3v2::Tag`.
AudioMetadata AudioMetadata::fromID3v2Tag(const TagLib::ID3v2::Tag *tag) {
    AudioMetadata metadata = AudioMetadata::fromTag(tag);
    auto frameList = tag->frameListMap()["TDRC"];
    if (!frameList.isEmpty()) {
        /*
         The timestamp fields are based on a subset of ISO 8601. When being as
         precise as possible the format of a time string is
         yyyy-MM-ddTHH:mm:ss (year, "-", month, "-", day, "T", hour (out of
         24), ":", minutes, ":", seconds), but the precision may be reduced by
         removing as many time indicators as wanted. Hence valid timestamps
         are
         yyyy, yyyy-MM, yyyy-MM-dd, yyyy-MM-ddTHH, yyyy-MM-ddTHH:mm and
         yyyy-MM-ddTHH:mm:ss. All time stamps are UTC. For durations, use
         the slash character as described in 8601, and for multiple non-
         contiguous dates, use multiple strings, if allowed by the frame
         definition.
         */
        metadata.releaseDate = frameList.front()->toString().toCString(true);
    }

    // Extract composer if present
    frameList = tag->frameListMap()["TCOM"];
    if (!frameList.isEmpty()) {
        metadata.composer = frameList.front()->toString().toCString();
    }

    // Extract album artist
    frameList = tag->frameListMap()["TPE2"];
    if (!frameList.isEmpty()) {
        metadata.albumArtist = frameList.front()->toString().toCString();
    }

    // BPM
    frameList = tag->frameListMap()["TBPM"];
    if (!frameList.isEmpty()) {
        bool ok = false;
        int bpm = frameList.front()->toString().toInt(&ok);
        if (ok) {
            metadata.beatPerMinute = bpm;
        }
    }

    // Rating
    TagLib::ID3v2::PopularimeterFrame *popularimeter = nullptr;
    frameList = tag->frameListMap()["POPM"];
    if (
        !frameList.isEmpty()
        && nullptr != (popularimeter = dynamic_cast<TagLib::ID3v2::PopularimeterFrame *>(frameList.front()))
    ) {
        metadata.rating = popularimeter->rating();
    }

    // Extract total tracks if present
    frameList = tag->frameListMap()["TRCK"];
    if (!frameList.isEmpty()) {
        // Split the tracks at '/'
        TagLib::String string = frameList.front()->toString();
        bool ok;
        auto pos = string.find("/", 0);
        if (-1 != pos) {
            auto upos = static_cast<unsigned int>(pos);
            int trackNumber = string.substr(0, upos).toInt(&ok);
            if(ok) {
                metadata.trackNumber = trackNumber;
            }
            int trackTotal = string.substr(upos + 1).toInt(&ok);
            if(ok) {
                metadata.trackTotal = trackTotal;
            }
        } else if (string.length()) {
            int trackNumber = string.toInt(&ok);
            if (ok) {
                metadata.trackNumber = trackNumber;
            }
        }
    }

    // Extract disc number and total discs
    frameList = tag->frameListMap()["TPOS"];
    if (!frameList.isEmpty()) {
        // Split the tracks at '/'
        TagLib::String string = frameList.front()->toString();
        bool ok;
        auto pos = string.find("/", 0);
        if (-1 != pos) {
            auto upos = static_cast<unsigned int>(pos);
            int discNumber = string.substr(0, upos).toInt(&ok);
            if (ok) {
                metadata.discNumber = discNumber;
            }
            int discTotal = string.substr(upos + 1).toInt(&ok);
            if (ok) {
                metadata.discTotal = discTotal;
            }
        } else if (string.length()) {
            int discNumber = string.toInt(&ok);
            if(ok) {
                metadata.discNumber = discNumber;
            }
        }
    }

    // Lyrics
    frameList = tag->frameListMap()["USLT"];
    if (!frameList.isEmpty()) {
        metadata.lyrics = frameList.front()->toString().toCString(true);
    }

    // Extract compilation if present (iTunes TCMP tag)
    frameList = tag->frameListMap()["TCMP"];
    if (!frameList.isEmpty()) {
        // It seems that the presence of this frame indicates a compilation
        metadata.compilation = true;
    }

    // Extract ISRC id
    frameList = tag->frameListMap()["TSRC"];
    if (!frameList.isEmpty()) {
        metadata.internationalStandardRecordingCode = frameList.front()->toString().toCString(true);
    }

    // MusicBrainz
    auto musicBrainzReleaseIDFrame = TagLib::ID3v2::UserTextIdentificationFrame
        ::find(const_cast<TagLib::ID3v2::Tag *>(tag), "MusicBrainz Album Id");
    if (musicBrainzReleaseIDFrame) {
        metadata.musicBrainzReleaseID = musicBrainzReleaseIDFrame->fieldList().back().toCString(true);
    }

    auto musicBrainzRecordingIDFrame = TagLib::ID3v2::UserTextIdentificationFrame
        ::find(const_cast<TagLib::ID3v2::Tag *>(tag), "MusicBrainz Track Id");
    if (musicBrainzRecordingIDFrame) {
        metadata.musicBrainzRecordingID = musicBrainzRecordingIDFrame->fieldList().back().toCString(true);
    }

    #warning there's much more that SFBAudioEngine extracts from ID3v2Tag, but let's just cover this for now. In more details the skipped things are: sorting & grouping, ReplayGain, RVA2 and LAME headers.

    for (auto iterator: tag->frameListMap()["APIC"]) {
        TagLib::ID3v2::AttachedPictureFrame *frame = dynamic_cast<TagLib::ID3v2::AttachedPictureFrame *>(iterator);
        if (frame) {
            auto picture = AudioMetadata::Picture::fromID3v2Picture(frame);
            metadata.attachedPictures.push_back(picture);
        }
    }
    return metadata;
}

#import <taglib/unsynchronizedlyricsframe.h>
//#import <taglib/relativevolumeframe.h>

/// fills`TagLib::ID3v2::Tag` from `AudioMetadata`.
void AudioMetadata::fillID3v2Tag(TagLib::ID3v2::Tag *tag) const {
    auto apply_specific_frame = [&] (const TagLib::ByteVector &id, auto create) {
        tag->removeFrames(id);
        tag->addFrame(create(id));
    };
    /// apply text frame from text
    auto apply_text = [&] (const TagLib::ByteVector &id, std::string value) {
        apply_specific_frame(id, [&] (auto id) {
            auto frame = new TagLib::ID3v2::TextIdentificationFrame(id, TagLib::String::Latin1);
            frame->setText(TagLib::String(value));
            return frame;
        });
    };
    /// apply text to `UserTextIdentificationFrame` by searching for it
    auto find_and_apply_user_text = [&] (const char* id, std::string value) {
        auto foundFrame = TagLib::ID3v2::UserTextIdentificationFrame::find(tag, id);
        if (foundFrame) {
            tag->removeFrame(foundFrame);
        }
        auto frame = new TagLib::ID3v2::UserTextIdentificationFrame();
        frame->setDescription(id);
        frame->setText(TagLib::String(value));
        tag->addFrame(frame);
    };

    // Use UTF-8 as the default encoding
    TagLib::ID3v2::FrameFactory::instance()->setDefaultTextEncoding(TagLib::String::UTF8);

    // Album title
    tag->setAlbum(TagLib::String(albumTitle));
    // Artist
    tag->setArtist(TagLib::String(artist));
    // Composer
    apply_text("TCOM", composer);
    // Genre
    tag->setGenre(TagLib::String(genre));
    // Date
    apply_text("TDRC", releaseDate);
    if (!releaseDate.empty() && releaseDate.size() >= 4) {
        /*
         The timestamp fields are based on a subset of ISO 8601. When being as
         precise as possible the format of a time string is
         yyyy-MM-ddTHH:mm:ss (year, "-", month, "-", day, "T", hour (out of
         24), ":", minutes, ":", seconds), but the precision may be reduced by
         removing as many time indicators as wanted. Hence valid timestamps
         are
         yyyy, yyyy-MM, yyyy-MM-dd, yyyy-MM-ddTHH, yyyy-MM-ddTHH:mm and
         yyyy-MM-ddTHH:mm:ss. All time stamps are UTC. For durations, use
         the slash character as described in 8601, and for multiple non-
         contiguous dates, use multiple strings, if allowed by the frame
         definition.
         */
        const std::string yearSubstring = releaseDate.substr(0, 4);
        if (std::all_of(yearSubstring.begin(), yearSubstring.end(), isdigit)) {
            unsigned int year = static_cast<unsigned int>(std::stoul(yearSubstring));
            tag->setYear(year);
        }
    }
    // Comment
    tag->setComment(TagLib::String(comment));
    // Album artist
    apply_text("TPE2", albumArtist);
    // Track title
    tag->setTitle(TagLib::String(title));
    // BPM
    apply_text("TBPM", std::to_string(beatPerMinute));
    // Rating
    apply_specific_frame("POPM", [&] (auto id) {
        auto frame = new TagLib::ID3v2::PopularimeterFrame();
        frame->setRating(rating);
        return frame;
    });
    // Track number and total tracks
    apply_text("TRCK", std::to_string(trackNumber) + "/" + std::to_string(trackTotal));
    // Compilation
    // iTunes uses the TCMP frame for this, which isn't in the standard, but we'll use it for compatibility
    apply_text("TCMP", compilation ? "1" : "0");
    // Disc number and total discs
    apply_text("TPOS", std::to_string(discNumber) + "/" + std::to_string(discTotal));
    // Lyrics
    apply_specific_frame("USLT", [&] (auto id) {
        auto frame = new TagLib::ID3v2::UnsynchronizedLyricsFrame(TagLib::String::UTF8);
        frame->setText(TagLib::String(lyrics));
        return frame;
    });
    /// ISRC
    apply_text("TSRC", internationalStandardRecordingCode);
    // MusicBrainz
    find_and_apply_user_text("MusicBrainz Album Id", musicBrainzReleaseID);
    find_and_apply_user_text("MusicBrainz Track Id", musicBrainzRecordingID);

    #warning ignored metadata sorting and grouping

    #warning ignored metadata replay gain

    // Album art
    tag->removeFrames("APIC");
    if (!attachedPictures.empty()) {
        for (auto picture: attachedPictures) {
            tag->addFrame(picture.asID3v2Picture()/*.release()*/);
        }
    }
}
