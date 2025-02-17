
#import "AbstractAudioFile.hpp"
#import <taglib/dsffile.h>

namespace AudioFile {
    struct DSF final: public AbstractAudioFile<TagLib::DSF::File> {
    public:
        using AbstractAudioFile::AbstractAudioFile;
    protected:
        using FileType = TagLib::DSF::File;

        void readMetadataImplementation(FileType &file, AudioMetadata *metadata) const {
            metadata->overlay(AudioMetadata::fromID3v2Tag(file.tag()));
        }

        void writeMetadataImplementation(FileType &file, AudioMetadata *metadata) const {
            metadata->fillID3v2Tag(file.tag());
        }
    };
}
