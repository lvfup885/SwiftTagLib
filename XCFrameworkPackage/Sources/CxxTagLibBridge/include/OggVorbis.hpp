
#import "AbstractAudioFile.hpp"
#import <taglib/vorbisfile.h>

namespace AudioFile {
    struct OggVorbis final: public AbstractAudioFile<TagLib::Ogg::Vorbis::File> {
    public:
        using AbstractAudioFile::AbstractAudioFile;
    protected:
        using FileType = TagLib::Ogg::Vorbis::File;

        void read_metadata_implementation(
            FileType &file,
            AudioMetadata *metadata,
            const MetadataOverlayStrategy overlayStrategy
        ) const {
            if (file.tag()) {
                metadata->overlay(AudioMetadata::read_from_XiphComment(file.tag()), overlayStrategy);
            }
        }

        void write_metadata_implementation(FileType &file, AudioMetadata *metadata) const {
            metadata->write_to_XiphComment(file.tag());
        }
    };
}
