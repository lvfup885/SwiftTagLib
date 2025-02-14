
#import "AudioMetadata.hpp"
#import "AudioProperties.hpp"
#import "AudioFileClass.hpp"

/// Tells the API consumer the outcome of `readMetadata` method.
enum class MetadataReadingOutcome: uint8_t {
    fileIsNotOpen,
    invalidFile,
    success
};

/// Tells the API consumer the outcome of `writeMetadata` method.
enum class MetadataWritingOutcome: uint8_t {
    fileIsNotOpen,
    invalidFile,
    saveError,
    success
};

/// The goal here is wrapping the [following](https://taglib.org/api/classTagLib_1_1File.html) in same kind of interface.
namespace AudioFile {
    AUDIO_FILE_CLASS(FLAC);
    AUDIO_FILE_CLASS(MP3);
    AUDIO_FILE_CLASS(MP4);
    AUDIO_FILE_CLASS(AIFF);
    AUDIO_FILE_CLASS(WAVE);
    AUDIO_FILE_CLASS(Musepack);
    AUDIO_FILE_CLASS(MonkeyAudio);
    AUDIO_FILE_CLASS(OggFLAC);
    AUDIO_FILE_CLASS(OggOpus);
    AUDIO_FILE_CLASS(OggSpeex);
    AUDIO_FILE_CLASS(OggVorbis);
    AUDIO_FILE_CLASS(WavPack);
    AUDIO_FILE_CLASS(TrueAudio);
    AUDIO_FILE_CLASS(DSDIFF);
    AUDIO_FILE_CLASS(DSF);
//    AUDIO_FILE_CLASS(ExtendedModule);
//    AUDIO_FILE_CLASS(ImpulseTrackerModule);
//    AUDIO_FILE_CLASS(ProTrackerModule);
//    AUDIO_FILE_CLASS(ScreamTracker3Module);
};
