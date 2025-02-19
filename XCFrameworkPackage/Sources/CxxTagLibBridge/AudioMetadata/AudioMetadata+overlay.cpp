
#import "AudioMetadata.hpp"

/// convenience method to combine `AudioMetadata` as layers.
void AudioMetadata::overlay(const AudioMetadata layer) {
    using Type = AudioMetadata;
    // MARK: - overlay closures
    auto overlay_string = [this, &layer](std::string Type:: *memberPointer) {
        auto &property = this->*memberPointer;
        const auto &overlayProperty = layer.*memberPointer;
        if (property.empty() && !overlayProperty.empty()) {
            property = overlayProperty;
        }
    };
    auto overlay_int = [this, &layer](int Type:: *memberPointer) {
        auto &property = this->*memberPointer;
        const auto &overlayProperty = layer.*memberPointer;
        if (property <= 0 && overlayProperty > 0) {
            property = overlayProperty;
        }
    };
    // MARK: - Properties: std::string
    for (auto property: {
        &Type::title,
        &Type::albumTitle,
        &Type::artist,
        &Type::genre,
        &Type::releaseDate,
        &Type::comment,
        &Type::composer,
        &Type::albumArtist,
        &Type::lyrics,
        &Type::internationalStandardRecordingCode,
        &Type::mediaCatalogNumber,
        &Type::musicBrainzReleaseID,
        &Type::musicBrainzRecordingID,
    }) {
        overlay_string(property);
    }
    // MARK: - Properties: int
    for (auto property: {
        &Type::beatPerMinute,
        &Type::rating,
        &Type::trackNumber,
        &Type::trackTotal,
        &Type::discNumber,
        &Type::discTotal,
    }) {
        overlay_int(property);
    }
    // MARK: - Properties: bool
    if (!compilation && layer.compilation) {
        compilation = layer.compilation;
    }
    // MARK: - Attached Pictures
    if (!layer.attachedPictures.empty()) {
        attachedPictures.insert(
            attachedPictures.end(),
            std::make_move_iterator(layer.attachedPictures.begin()),
            std::make_move_iterator(layer.attachedPictures.end())
        );
    }
    // MARK: - Additional Metadata
    if (!layer.additional.empty()) {
        additional.insert(
            additional.end(),
            std::make_move_iterator(layer.additional.begin()),
            std::make_move_iterator(layer.additional.end())
        );
    }
}
