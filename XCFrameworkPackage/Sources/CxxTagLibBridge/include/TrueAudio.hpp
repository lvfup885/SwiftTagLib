
#import "AbstractAudioFile.hpp"
#import <taglib/trueaudiofile.h>

namespace AudioFile {
    struct TrueAudio final: public AbstractAudioFile<TagLib::TrueAudio::File> {
    public:
        using AbstractAudioFile::AbstractAudioFile;
    protected:
        using FileType = TagLib::TrueAudio::File;

        void readMetadataImplementation(FileType &file, AudioMetadata *metadata) const {
            if (file.hasID3v1Tag()) {
                metadata->overlay(AudioMetadata::fromID3v1Tag(file.ID3v1Tag()));
            }
            if (file.hasID3v2Tag()) {
                metadata->overlay(AudioMetadata::fromID3v2Tag(file.ID3v2Tag()));
            }
        }

        void writeMetadataImplementation(FileType &file, AudioMetadata *metadata) const {
            if (file.hasID3v1Tag()) {
                metadata->fillID3v1Tag(file.ID3v1Tag());
            }
            metadata->fillID3v2Tag(file.ID3v2Tag(true));
        }
    };
}
