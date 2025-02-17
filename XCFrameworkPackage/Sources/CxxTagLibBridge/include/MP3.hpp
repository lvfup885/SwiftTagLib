
#import "AbstractAudioFile.hpp"
#import <taglib/mpegfile.h>

namespace AudioFile {
    struct MP3 final: public AbstractAudioFile<TagLib::MPEG::File> {
    public:
        using AbstractAudioFile::AbstractAudioFile;
    protected:
        using FileType = TagLib::MPEG::File;

        void readMetadataImplementation(FileType &file, AudioMetadata *metadata) const {
            if (file.hasAPETag()) {
                metadata->overlay(AudioMetadata::fromAPETag(file.APETag()));
            }
            if (file.hasID3v1Tag()) {
                metadata->overlay(AudioMetadata::fromID3v1Tag(file.ID3v1Tag()));
            }
            if (file.hasID3v2Tag()) {
                metadata->overlay(AudioMetadata::fromID3v2Tag(file.ID3v2Tag()));
            }
        }

        void writeMetadataImplementation(FileType &file, AudioMetadata *metadata) const {
            if (file.hasAPETag()) {
                metadata->fillAPETag(file.APETag(true));
            }
            if (file.hasID3v1Tag()) {
                metadata->fillID3v1Tag(file.ID3v1Tag());
            }
            metadata->fillID3v2Tag(file.ID3v2Tag(true));
        }
    };
}
