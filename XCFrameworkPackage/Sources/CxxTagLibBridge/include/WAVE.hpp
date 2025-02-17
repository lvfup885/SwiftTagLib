
#import "AbstractAudioFile.hpp"
#import <taglib/wavfile.h>

namespace AudioFile {
    struct WAVE final: public AbstractAudioFile<TagLib::RIFF::WAV::File> {
    public:
        using AbstractAudioFile::AbstractAudioFile;
    protected:
        using FileType = TagLib::RIFF::WAV::File;

        void readMetadataImplementation(FileType &file, AudioMetadata *metadata) const {
            if (file.hasInfoTag()) {
                metadata->overlay(AudioMetadata::fromTag(file.InfoTag()));
            }
            if (file.hasID3v2Tag()) {
                metadata->overlay(AudioMetadata::fromID3v2Tag(file.ID3v2Tag()));
            }
        }

        void writeMetadataImplementation(FileType &file, AudioMetadata *metadata) const {
            if (file.hasInfoTag()) {
                metadata->fillTag(file.InfoTag());
            }
            metadata->fillID3v2Tag(file.ID3v2Tag());
        }
    };
}
