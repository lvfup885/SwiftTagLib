
#import <stdint.h>

/// Tells the API consumer the outcome of `readMetadata` method.
enum class MetadataReadingOutcome: uint8_t {
    fileIsNotOpen,
    invalidFile,
    success
};

/// Tells the API consumer the outcome of `writeMetadata` method.
enum class MetadataWritingOutcome: uint8_t {
    fileIsNotOpen,
    invalidFile,
    saveError,
    success
};

#import "AudioMetadata.hpp"
#import "AudioProperties.hpp"
#import <taglib/tfilestream.h>
#import <taglib/tfile.h>

namespace AudioFile {
    /// Abstracts away specific interaction with `TagLib::FileStream` type for descendants while requiring them to
    /// specify `FileType`(which must inherit from `TagLib::File`) and allows to manipulate file directly
    /// when `reading/writing` from `protected virtual` methods.
    template <typename FileType>
        requires std::is_base_of_v<TagLib::File, FileType>
    struct AbstractAudioFile {
    protected:
        std::string fileName;
    public:
        /// Designated constructor.
        explicit AbstractAudioFile(std::string fileName): fileName(std::move(fileName)) {}
        /// Destructor.
        virtual ~AbstractAudioFile() = default;
        /// Reads `AudioMetadata` & `AudioProperties` from file.
        MetadataReadingOutcome readMetadata(AudioMetadata *metadata, AudioProperties *properties) const {
            TagLib::FileStream stream(fileName.c_str(), true);
            if (!stream.isOpen()) {
                return MetadataReadingOutcome::fileIsNotOpen;
            }
            FileType file(&stream);
            if (!file.isValid()) {
                return MetadataReadingOutcome::invalidFile;
            }
            readMetadataImplementation(file, metadata);
            if (file.audioProperties()) {
                properties->fillFromProperties(*file.audioProperties());
            }
            return MetadataReadingOutcome::success;
        }
        /// Writes `AudioMetadata` to the audio file.
        MetadataWritingOutcome writeMetadata(AudioMetadata *metadata) const {
            TagLib::FileStream stream(fileName.c_str());
            if (!stream.isOpen()) {
                return MetadataWritingOutcome::fileIsNotOpen;
            }
            FileType file(&stream, false);
            if (!file.isValid()) {
                return MetadataWritingOutcome::invalidFile;
            }
            writeMetadataImplementation(file, metadata);
            if (!file.save()) {
                return MetadataWritingOutcome::saveError;
            }
            return MetadataWritingOutcome::success;
        }
    protected:
        /// Format specific internal `read` implementation.
        virtual void readMetadataImplementation(FileType &file, AudioMetadata *metadata) const = 0;
        /// Format specific internal `write` implementation.
        virtual void writeMetadataImplementation(FileType &file, AudioMetadata *metadata) const = 0;
    };
}
