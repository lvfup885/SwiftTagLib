
#import "AbstractAudioFile.hpp"
#import <taglib/aifffile.h>

namespace AudioFile {
    struct AIFF final: public AbstractAudioFile<TagLib::RIFF::AIFF::File> {
    public:
        using AbstractAudioFile::AbstractAudioFile;
    protected:
        using FileType = TagLib::RIFF::AIFF::File;

        void readMetadataImplementation(FileType &file, AudioMetadata *metadata) const {
            if (file.tag()) {
                metadata->overlay(AudioMetadata::fromID3v2Tag(file.tag()));
            }
        }

        void writeMetadataImplementation(FileType &file, AudioMetadata *metadata) const {
            metadata->fillID3v2Tag(file.tag());
        }
    };
}
