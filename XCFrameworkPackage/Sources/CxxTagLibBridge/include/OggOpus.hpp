
#import "AbstractAudioFile.hpp"
#import <taglib/opusfile.h>

namespace AudioFile {
    struct OggOpus final: public AbstractAudioFile<TagLib::Ogg::Opus::File> {
    public:
        using AbstractAudioFile::AbstractAudioFile;
    protected:
        using FileType = TagLib::Ogg::Opus::File;

        void readMetadataImplementation(FileType &file, AudioMetadata *metadata) const {
            if (file.tag()) {
                metadata->overlay(AudioMetadata::fromXiphComment(file.tag()));
            }
        }

        void writeMetadataImplementation(FileType &file, AudioMetadata *metadata) const {
            metadata->fillXiphComment(file.tag());
        }
    };
}
