
#import "AbstractAudioFile.hpp"
#import <taglib/mpcfile.h>

namespace AudioFile {
    struct Musepack final: public AbstractAudioFile<TagLib::MPC::File> {
    public:
        using AbstractAudioFile::AbstractAudioFile;
    protected:
        using FileType = TagLib::MPC::File;

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
