
#import "AudioMetadata.hpp"

/// builds `AudioMetadata::Picture` from `TagLib::FLAC::Picture`.
AudioMetadata::Picture AudioMetadata::Picture::create_from_FLACPicture(const TagLib::FLAC::Picture *flacPicture) {
    auto pointer = flacPicture->data().data();
    auto size = flacPicture->data().size();
    auto picture = AudioMetadata::Picture {
        std::vector<char>(pointer, pointer + size),
        size
    };
    if (!flacPicture->description().isEmpty()) {
        picture.description = flacPicture->description().toCString(true);
    }
    picture.kind = static_cast<AudioMetadata::Picture::Kind>(flacPicture->type());
    return picture;
}

/// builds `AudioMetadata::Picture` from `TagLib::MP4::CoverArt`.
AudioMetadata::Picture AudioMetadata::Picture::create_from_MP4Picture(const TagLib::MP4::CoverArt coverArt) {
    auto pointer = coverArt.data().data();
    auto size = coverArt.data().size();
    return {
        std::vector<char>(pointer, pointer + size),
        size
    };
}

/// builds `AudioMetadata::Picture` from `TagLib::ID3v2::AttachedPictureFrame *`.
AudioMetadata::Picture AudioMetadata::Picture::create_from_ID3v2Picture(const TagLib::ID3v2::AttachedPictureFrame *frame) {
    auto pointer = frame->picture().data();
    auto size = frame->picture().size();
    auto picture = AudioMetadata::Picture {
        std::vector<char>(pointer, pointer + size),
        size
    };
    if (!frame->description().isEmpty()) {
        picture.description = frame->description().toCString(true);
    }
    return picture;
}

/// maybe builds `AudioMetadata::Picture` from `const TagLib::APE::Item item` and `const char* key` return wrapped in `std::optional`.
std::optional<AudioMetadata::Picture> AudioMetadata::Picture::create_from_APEPicture(const TagLib::APE::Item item, const char* key) {
    // From http://www.hydrogenaudio.org/forums/index.php?showtopic=40603&view=findpost&p=504669
    /*
     <length> 32 bit
     <flags with binary bit set> 32 bit
     <field name> "Cover Art (Front)"|"Cover Art (Back)"
     0x00
     <description> UTF-8 string (needs to be a file name to be recognized by AudioShell - meh)
     0x00
     <cover data> binary
     */
    auto binaryData = item.binaryData();
    auto pos = binaryData.find('\0');
    if (-1 != pos && 3 < binaryData.size()) {
        auto upos = static_cast<unsigned int>(pos);
        auto pointer = binaryData.mid(upos + 1).data();
        auto size = (binaryData.size() - upos - 1);
        auto description = TagLib::String(binaryData.mid(0, upos), TagLib::String::UTF8).toCString(true);
        auto type = strcasecmp(key, "Cover Art (Front)")
            ? AudioMetadata::Picture::Kind::frontCover
            : AudioMetadata::Picture::Kind::backCover;
        auto picture = AudioMetadata::Picture {
            std::vector<char>(pointer, pointer + size),
            size,
            description,
            type
        };
        return picture;
    } else {
        return std::nullopt;
    }
}
