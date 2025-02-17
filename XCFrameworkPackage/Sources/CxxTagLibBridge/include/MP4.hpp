
#import "AbstractAudioFile.hpp"
#import <taglib/mp4file.h>

namespace AudioFile {
    struct MP4 final: public AbstractAudioFile<TagLib::MP4::File> {
    public:
        using AbstractAudioFile::AbstractAudioFile;
    protected:
        using FileType = TagLib::MP4::File;

        void readMetadataImplementation(FileType &file, AudioMetadata *metadata) const {
            if (file.tag()) {
                metadata->overlay(AudioMetadata::fromMP4Tag(file.tag()));
            }
        }

        void writeMetadataImplementation(FileType &file, AudioMetadata *metadata) const {
            metadata->fillMP4Tag(file.tag());
        }
    };
}
