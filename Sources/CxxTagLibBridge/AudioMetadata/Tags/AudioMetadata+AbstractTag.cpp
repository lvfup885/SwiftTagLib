
#import "AudioMetadata.hpp"

///// constructor for `AudioMetadata` from **abstract** `TagLib::Tag`.
AudioMetadata AudioMetadata::fromTag(const TagLib::Tag *tag) {
    AudioMetadata metadata = {
        tag->title().toCString(true),
        tag->album().toCString(true),
        tag->artist().toCString(true),
        tag->genre().toCString(true),
        std::to_string(tag->year()).c_str(),
        std::to_string(tag->track()).c_str(),
        tag->comment().toCString()
    };
    return metadata;
}

#import <charconv>

/// fills **abstract** `TagLib::Tag` from `AudioMetadata`.
void AudioMetadata::fillTag(TagLib::Tag *tag) const {
    tag->setTitle(TagLib::String(title));
    tag->setAlbum(TagLib::String(albumTitle));
    tag->setArtist(TagLib::String(artist));
    tag->setGenre(TagLib::String(genre));
    tag->setComment(TagLib::String(comment));
    std::string releaseDate = releaseDate;
    if (!releaseDate.empty()) {
        unsigned int year;
        auto [unused, errorCode] = std::from_chars(releaseDate.data(), releaseDate.data() + releaseDate.size(), year);
        if (errorCode == std::errc()) {
            tag->setYear(year);
        }
    } else {
        tag->setYear(0);
    }
    tag->setTrack(trackNumber);
}
