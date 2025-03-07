
#import "AbstractAudioFile.hpp"
#import <taglib/mp4file.h>

namespace AudioFile {
    struct MP4 final: public AbstractAudioFile<TagLib::MP4::File> {
    public:
        using AbstractAudioFile::AbstractAudioFile;
    protected:
        using FileType = TagLib::MP4::File;

        void read_metadata_implementation(FileType &file, AudioMetadata *metadata) const {
            if (file.tag()) {
                metadata->overlay(AudioMetadata::read_from_MP4_tag(file.tag()));
            }
        }

        void write_metadata_implementation(FileType &file, AudioMetadata *metadata) const {
            metadata->write_to_MP4_tag(file.tag());
        }
    };
}
