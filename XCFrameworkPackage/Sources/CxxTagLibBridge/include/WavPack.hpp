
#import "AbstractAudioFile.hpp"
#import <taglib/wavpackfile.h>

namespace AudioFile {
    struct WavPack final: public AbstractAudioFile<TagLib::WavPack::File> {
    public:
        using AbstractAudioFile::AbstractAudioFile;
    protected:
        using FileType = TagLib::WavPack::File;

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
