
#import <CxxTagLibBridge/AbstractAudioFile.hpp>
#import <taglib/mpegfile.h>
#import <taglib/id3v2tag.h>
#import <taglib/id3v2framefactory.h>

namespace AudioFile {
    struct MP3 final: public AbstractAudioFile<TagLib::MPEG::File> {
    public:
        using AbstractAudioFile::AbstractAudioFile;
    protected:
        using FileType = TagLib::MPEG::File;

        void read_metadata_implementation(
            FileType &file,
            AudioMetadata *metadata,
            const MetadataReadingOptions options,
            const MetadataOverlayStrategy overlayStrategy
        ) const {
            if (file.hasAPETag()) {
                metadata->overlay(AudioMetadata::read_from_APE_tag(file.APETag(), options), overlayStrategy);
            }
            if (file.hasID3v1Tag()) {
                metadata->overlay(AudioMetadata::read_from_ID3v1_tag(file.ID3v1Tag(), options), overlayStrategy);
            }
            if (file.hasID3v2Tag()) {
                metadata->overlay(AudioMetadata::read_from_ID3v2_tag(file.ID3v2Tag(), options), overlayStrategy);
            }
        }

        void write_metadata_implementation(FileType &file, AudioMetadata *metadata) const {
            // we do not care about other tags, since they're stripped upon saving.
            // we just create ID3v2 tag and write to it.
            if (auto tag = file.ID3v2Tag(true)) {
                tag->frameFactory()->setDefaultTextEncoding(TagLib::String::UTF8);
                metadata->write_to_ID3v2_tag(tag);
            }
        }
    };
}
