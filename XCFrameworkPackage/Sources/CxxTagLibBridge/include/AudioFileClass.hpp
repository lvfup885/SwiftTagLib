
// MARK: - Class definition macro
/// Macro to define `Audio File Class` avoiding `inheritance` and `boilerplate`.
#define AUDIO_FILE_CLASS(_class) \
    struct _class final { \
    public: \
        _class(std::string fileName): fileName(fileName) {}; \
        std::string fileName; \
        std::string getFileName() const SWIFT_COMPUTED_PROPERTY; \
        MetadataReadingOutcome readMetadata(AudioMetadata *metadata, AudioProperties *properties) const; \
        MetadataWritingOutcome writeMetadata(AudioMetadata *metadata) const; \
    };

// MARK: - Class methods implementation definition macro
#import <taglib/tfilestream.h>

/// Macro to define `Audio File Class` `readMetadata` **implementation** as `lambda function`.
#define AUDIO_FILE_METADATA_READ_IMPLEMENTATION(_class, _file, _lamda_implementation) \
    MetadataReadingOutcome _class::readMetadata(AudioMetadata *metadata, AudioProperties *properties) const { \
        TagLib::FileStream stream(fileName.c_str(), true); \
        if (!stream.isOpen()) { \
            return MetadataReadingOutcome::fileIsNotOpen; \
        } \
        _file file(&stream); \
        if (!file.isValid()) { \
            return MetadataReadingOutcome::invalidFile; \
        } \
        do { \
            _lamda_implementation(file); \
        } while (0); \
        if (file.audioProperties()) { \
            auto audioProperties = file.audioProperties(); \
            properties->fillFromProperties(*audioProperties); \
        } \
        return MetadataReadingOutcome::success; \
    }

/// Macro to define `Audio File Class` `writeMetadata` **implementation** as `lambda function`.
#define AUDIO_FILE_METADATA_WRITE_IMPLEMENTATION(_class, _file, _lamda_implementation) \
    MetadataWritingOutcome _class::writeMetadata(AudioMetadata *metadata) const { \
        TagLib::FileStream stream(fileName.c_str()); \
        if (!stream.isOpen()) { \
            return MetadataWritingOutcome::fileIsNotOpen; \
        } \
        _file file(&stream, false); \
        if (!file.isValid()) { \
            return MetadataWritingOutcome::invalidFile; \
        } \
        do { \
            _lamda_implementation(file); \
        } while (0); \
        if (!file.save()) { \
            return MetadataWritingOutcome::saveError; \
        } \
        return MetadataWritingOutcome::success; \
    }
