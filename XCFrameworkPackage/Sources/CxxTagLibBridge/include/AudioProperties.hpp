
#import <swift/bridging>
#import <taglib/audioproperties.h>

struct AudioProperties final {
    /// Macro to escape writing boilerplate for `getter` and `setter` for `Swift` & `C++` **Interoperability**.
    #define AUDIO_PROPERTIES_PROPERTY(_type, _accessor, _property) \
        _type _accessor; \
        _type get##_property() const SWIFT_COMPUTED_PROPERTY { return _accessor; } \
        void set##_property(const _type newValue) SWIFT_COMPUTED_PROPERTY { _accessor = newValue; }
public:
    // MARK: - Properties
    AUDIO_PROPERTIES_PROPERTY(int, lengthInSeconds, LengthInSeconds);
    AUDIO_PROPERTIES_PROPERTY(int, channels, Channels);
    AUDIO_PROPERTIES_PROPERTY(int, sampleRate, SampleRate);
    AUDIO_PROPERTIES_PROPERTY(int, bitrate, Bitrate);
    // MARK: - Utility
    void fillFromProperties(const TagLib::AudioProperties &properties) {
        lengthInSeconds = properties.lengthInSeconds();
        channels = properties.channels();
        sampleRate = properties.sampleRate();
        bitrate = properties.bitrate();
    }
};
