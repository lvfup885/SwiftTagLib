
#import "AbstractAudioFile.hpp"
#import <taglib/flacfile.h>

namespace AudioFile {
    struct FLAC final: public AbstractAudioFile<TagLib::FLAC::File> {
    public:
        using AbstractAudioFile::AbstractAudioFile;
    protected:
        using FileType = TagLib::FLAC::File;

        void readMetadataImplementation(FileType &file, AudioMetadata *metadata) const {
            if (file.hasID3v1Tag()) {
                metadata->overlay(AudioMetadata::fromID3v1Tag(file.ID3v1Tag()));
            }
            if (file.hasID3v2Tag()) {
                metadata->overlay(AudioMetadata::fromID3v2Tag(file.ID3v2Tag()));
            }
            if (file.hasXiphComment()) {
                metadata->overlay(AudioMetadata::fromXiphComment(file.xiphComment()));
            }
        }

        void writeMetadataImplementation(FileType &file, AudioMetadata *metadata) const {
            if (file.hasID3v1Tag()) {
                metadata->fillID3v1Tag(file.ID3v1Tag());
            }
            if (file.hasID3v2Tag()) {
                metadata->fromID3v2Tag(file.ID3v2Tag());
            }
            metadata->fillXiphComment(file.xiphComment());
            /// attaching pictures to the file itself
            file.removePictures();
            if (!metadata->attachedPictures.empty()) {
                for (auto picture: metadata->attachedPictures) {
                    file.addPicture(picture.asFlacPicture());
                }
            }
        }
    };
}
