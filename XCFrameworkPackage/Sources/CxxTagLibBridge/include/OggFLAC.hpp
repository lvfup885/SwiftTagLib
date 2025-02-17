
#import "AbstractAudioFile.hpp"
#import <taglib/oggflacfile.h>

namespace AudioFile {
    struct OggFLAC final: public AbstractAudioFile<TagLib::Ogg::FLAC::File> {
    public:
        using AbstractAudioFile::AbstractAudioFile;
    protected:
        using FileType = TagLib::Ogg::FLAC::File;

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
