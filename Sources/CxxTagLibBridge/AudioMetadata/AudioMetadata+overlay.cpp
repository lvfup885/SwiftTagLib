
#import "AudioMetadata.hpp"

/// convenience method to combine `AudioMetadata` as layers.
void AudioMetadata::overlay(AudioMetadata layer) {
    /// saving just a little bit of boilerplate.
    #define STRING_OVERLAY(_overlay, _accessor) if (!_overlay._accessor.empty()) { _accessor = _overlay._accessor; }
    STRING_OVERLAY(layer, title);
    STRING_OVERLAY(layer, albumTitle);
    STRING_OVERLAY(layer, artist);
    STRING_OVERLAY(layer, genre);
    STRING_OVERLAY(layer, releaseDate);
    STRING_OVERLAY(layer, track);
    STRING_OVERLAY(layer, comment);
    STRING_OVERLAY(layer, composer);
    STRING_OVERLAY(layer, albumArtist);
    if (layer.beatPerMinute != 0) { beatPerMinute = layer.beatPerMinute; }
    if (layer.rating != 0) { rating = layer.rating; }
    if (!trackNumber) { trackNumber = layer.trackNumber; }
    if (!trackTotal) { trackTotal = layer.trackTotal; }
    if (!discNumber) { discNumber = layer.discNumber; }
    if (!discTotal) { discTotal = layer.discTotal; }
    STRING_OVERLAY(layer, lyrics);
    if (!compilation) { compilation = layer.compilation; }
    STRING_OVERLAY(layer, internationalStandardRecordingCode);
    STRING_OVERLAY(layer, mediaCatalogNumber);
    STRING_OVERLAY(layer, musicBrainzReleaseID);
    STRING_OVERLAY(layer, musicBrainzRecordingID);
    if (!layer.attachedPictures.empty()) {
        attachedPictures.insert(
            attachedPictures.end(),
            std::make_move_iterator(layer.attachedPictures.begin()),
            std::make_move_iterator(layer.attachedPictures.end())
        );
    }
    if (!layer.additional.empty()) {
        additional.insert(
            additional.end(),
            std::make_move_iterator(layer.additional.begin()),
            std::make_move_iterator(layer.additional.end())
        );
    }
}
