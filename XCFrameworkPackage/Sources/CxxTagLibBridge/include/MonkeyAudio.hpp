
#import "AbstractAudioFile.hpp"
#import <taglib/apefile.h>

namespace AudioFile {
    struct MonkeyAudio final: public AbstractAudioFile<TagLib::APE::File> {
    public:
        using AbstractAudioFile::AbstractAudioFile;
    protected:
        using FileType = TagLib::APE::File;

        void readMetadataImplementation(FileType &file, AudioMetadata *metadata) const {
            if (file.hasID3v1Tag()) {
                metadata->overlay(AudioMetadata::fromID3v1Tag(file.ID3v1Tag()));
            }
            if (file.hasAPETag()) {
                metadata->overlay(AudioMetadata::fromAPETag(file.APETag()));
            }
        }

        void writeMetadataImplementation(FileType &file, AudioMetadata *metadata) const {
            if (file.hasID3v1Tag()) {
                metadata->fillID3v1Tag(file.ID3v1Tag());
            }
            metadata->fillAPETag(file.APETag(true));
        }
    };
}
