
#import "AudioMetadata.hpp"

/// constructor for `AudioMetadata` from **abstract** `TagLib::Tag`.
AudioMetadata AudioMetadata::fromTag(const TagLib::Tag *tag) {
    return {
        .title = tag->title().toCString(true),
        .albumTitle = tag->album().toCString(true),
        .artist = tag->artist().toCString(true),
        .genre = tag->genre().toCString(true),
        .comment = tag->comment().toCString(),
        .releaseDate = std::to_string(tag->year()),
        .trackNumber = static_cast<int>(tag->track()),
    };
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
