
#import "AbstractAudioFile.hpp"
#import <taglib/vorbisfile.h>

namespace AudioFile {
    struct OggVorbis final: public AbstractAudioFile<TagLib::Ogg::Vorbis::File> {
    public:
        using AbstractAudioFile::AbstractAudioFile;
    protected:
        using FileType = TagLib::Ogg::Vorbis::File;

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
