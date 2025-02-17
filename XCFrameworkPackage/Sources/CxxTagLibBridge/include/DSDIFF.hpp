
#import "AbstractAudioFile.hpp"
#import <taglib/dsdifffile.h>

namespace AudioFile {
    struct DSDIFF final: public AbstractAudioFile<TagLib::DSDIFF::File> {
    public:
        using AbstractAudioFile::AbstractAudioFile;
    protected:
        using FileType = TagLib::DSDIFF::File;

        void readMetadataImplementation(FileType &file, AudioMetadata *metadata) const {
            if (file.hasDIINTag()) {
                metadata->overlay(AudioMetadata::fromTag(file.DIINTag()));
            }
            if (file.hasID3v2Tag()) {
                metadata->overlay(AudioMetadata::fromID3v2Tag(file.ID3v2Tag()));
            }
        }

        void writeMetadataImplementation(FileType &file, AudioMetadata *metadata) const {
            metadata->fillTag(file.tag());
            metadata->fillID3v2Tag(file.ID3v2Tag());
        }
    };
}
