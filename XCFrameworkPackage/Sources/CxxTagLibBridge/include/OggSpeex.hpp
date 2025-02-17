
#import "AbstractAudioFile.hpp"
#import <taglib/speexfile.h>

namespace AudioFile {
    struct OggSpeex final: public AbstractAudioFile<TagLib::Ogg::Speex::File> {
    public:
        using AbstractAudioFile::AbstractAudioFile;
    protected:
        using FileType = TagLib::Ogg::Speex::File;

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
