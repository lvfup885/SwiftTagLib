
#import "AbstractAudioFile.hpp"
#import <taglib/oggflacfile.h>

namespace AudioFile {
    struct OggFLAC final: public AbstractAudioFile<TagLib::Ogg::FLAC::File> {
    public:
        using AbstractAudioFile::AbstractAudioFile;
    protected:
        using FileType = TagLib::Ogg::FLAC::File;

        void read_metadata_implementation(FileType &file, AudioMetadata *metadata) const {
            if (file.tag()) {
                metadata->overlay(AudioMetadata::read_from_XiphComment(file.tag()));
            }
        }

        void write_metadata_implementation(FileType &file, AudioMetadata *metadata) const {
            metadata->write_to_XiphComment(file.tag());
        }
    };
}
