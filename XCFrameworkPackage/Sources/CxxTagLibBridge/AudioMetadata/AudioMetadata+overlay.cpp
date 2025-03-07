
#import "AudioMetadata.hpp"

namespace MetadataOverlay {
    enum class CheckLevel: uint8_t {
        /// checks if value is already read, and if not replaces only with new its not `std::nullopt`.
        Graceful = 0,
        /// does not check if value is already read, replaces when new its not `std::nullopt`.
        Override = 1,
        /// no checks, newest value is written
        Regardless = 2,
    };
    static constexpr CheckLevel checkLevel = CheckLevel::Graceful;
}

/// convenience method to combine `AudioMetadata` as layers.
void AudioMetadata::overlay(const AudioMetadata layer) {
    using Type = AudioMetadata;
    tagSource |= layer.tagSource;

    auto overlay_optional = [this, &layer](auto Type:: *memberPointer) {
        auto &property = this->*memberPointer;
        const auto &overlayProperty = layer.*memberPointer;
        switch (MetadataOverlay::checkLevel) {
            default:
            case MetadataOverlay::CheckLevel::Graceful:
                if (!property.has_value() && overlayProperty.has_value()) {
                    property = overlayProperty;
                }
                break;
            case MetadataOverlay::CheckLevel::Override:
                if (overlayProperty.has_value()) {
                    property = overlayProperty;
                }
                break;
            case MetadataOverlay::CheckLevel::Regardless:
                property = overlayProperty;
                break;;
        }
    };

    // MARK: - Properties: std::optional<std::string>
    for (auto property: {
        &Type::title,
        &Type::albumTitle,
        &Type::artist,
        &Type::genre,
        &Type::comment,
        &Type::releaseDate,
        &Type::composer,
        &Type::albumArtist,
        &Type::lyrics,
        &Type::internationalStandardRecordingCode,
        &Type::mediaCatalogNumber,
        &Type::musicBrainzReleaseID,
        &Type::musicBrainzRecordingID,
    }) {
        overlay_optional(property);
    }

    // MARK: - Properties: std::optional<int>
    for (auto property: {
        &Type::trackNumber,
        &Type::trackTotal,
        &Type::discNumber,
        &Type::discTotal,
        &Type::beatPerMinute,
        &Type::rating,
    }) {
        overlay_optional(property);
    }

    overlay_optional(&Type::compilation);

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
