
#import <swift/bridging>
#import <tuple>
#import <optional>
#import <taglib/tag.h>
#import <taglib/id3v1tag.h>
#import <taglib/id3v2tag.h>
#import <taglib/xiphcomment.h>
#import <taglib/apetag.h>
#import <taglib/mp4tag.h>
#import <taglib/attachedpictureframe.h>

/// Attempts to combine different [Tags](https://taglib.org/api/classTagLib_1_1Tag.html) into single interace.
struct AudioMetadata final {
    /// Macro to escape writing boilerplate for `getter` and `setter` for `Swift` & `C++` **Interoperability**.
    #define AUDIO_METADATA_PROPERTY(_type, _accessor, _property) \
        _type _accessor; \
        _type get##_property() const SWIFT_COMPUTED_PROPERTY { return _accessor; } \
        void set##_property(const _type newValue) SWIFT_COMPUTED_PROPERTY { _accessor = newValue; }
public:
    // MARK: - Basic Properties shared across ID3v1, ID3v2 and some other Tags
    AUDIO_METADATA_PROPERTY(std::string, title, Title);
    AUDIO_METADATA_PROPERTY(std::string, albumTitle, AblumTitle);
    AUDIO_METADATA_PROPERTY(std::string, artist, Artist);
    AUDIO_METADATA_PROPERTY(std::string, genre, Genre);
    AUDIO_METADATA_PROPERTY(std::string, releaseDate, ReleaseDate);
    AUDIO_METADATA_PROPERTY(std::string, comment, Comment);
    // MARK: - ID3v2 Properties
    AUDIO_METADATA_PROPERTY(std::string, composer, Composer);
    AUDIO_METADATA_PROPERTY(std::string, albumArtist, AlbumArtist);
    AUDIO_METADATA_PROPERTY(int, beatPerMinute, BeatPerMinute);
    AUDIO_METADATA_PROPERTY(int, rating, Rating);
    AUDIO_METADATA_PROPERTY(int, trackNumber, TrackNumber);
    AUDIO_METADATA_PROPERTY(int, trackTotal, TrackTotal);
    AUDIO_METADATA_PROPERTY(int, discNumber, DiscNumber);
    AUDIO_METADATA_PROPERTY(int, discTotal, DiscTotal);
    AUDIO_METADATA_PROPERTY(std::string, lyrics, Lyrics);
    AUDIO_METADATA_PROPERTY(bool, compilation, Compilation);
    AUDIO_METADATA_PROPERTY(std::string, internationalStandardRecordingCode, InternationalStandardRecordingCode);
    AUDIO_METADATA_PROPERTY(std::string, mediaCatalogNumber, MediaCatalogNumber);
    AUDIO_METADATA_PROPERTY(std::string, musicBrainzReleaseID, MusicBrainzReleaseID);
    AUDIO_METADATA_PROPERTY(std::string, musicBrainzRecordingID, MusicBrainzRecordingID);
    // MARK: - Attached Pictures
    /// `Picture`: raw `bytes`, `size`, `kind`, `description` and `type`.
    struct Picture final {
    public:
        using Bytes = std::vector<char>;
        AUDIO_METADATA_PROPERTY(Bytes, bytes, Bytes);
        AUDIO_METADATA_PROPERTY(unsigned int, size, Size);
        AUDIO_METADATA_PROPERTY(std::string, description, Description);
        enum class Kind: unsigned int {
            /// A type not otherwise enumerated
            other = 0x00,
            /// 32x32 PNG image that should be used as the file icon
            fileIcon = 0x01,
            /// File icon of a different size or format
            otherFileIcon = 0x02,
            /// Front cover image of the album
            frontCover = 0x03,
            /// Back cover image of the album
            backCover = 0x04,
            /// Inside leaflet page of the album
            leafletPage = 0x05,
            /// Image from the album itself
            media = 0x06,
            /// Picture of the lead artist or soloist
            leadArtist = 0x07,
            /// Picture of the artist or performer
            artist = 0x08,
            /// Picture of the conductor
            conductor = 0x09,
            /// Picture of the band or orchestra
            band = 0x0A,
            /// Picture of the composer
            composer = 0x0B,
            /// Picture of the lyricist or text writer
            lyricist = 0x0C,
            /// Picture of the recording location or studio
            recordingLocation = 0x0D,
            /// Picture of the artists during recording
            duringRecording = 0x0E,
            /// Picture of the artists during performance
            duringPerformance = 0x0F,
            /// Picture from a movie or video related to the track
            movieScreenCapture = 0x10,
            /// Picture of a large, coloured fish
            colouredFish = 0x11,
            /// Illustration related to the track
            illustration = 0x12,
            /// Logo of the band or performer
            bandLogo = 0x13,
            /// Logo of the publisher (record company)
            publisherLogo = 0x14,
        };
        AUDIO_METADATA_PROPERTY(Kind, kind, Kind);
        // MARK: - ImageIO computed properties
        using MIMEType = std::string;
        MIMEType mimeType();
        /// `(MIME type, pixel width, pixel height, color depth)`.
        using Properties = std::tuple<std::string, int, int, int>;
        Properties properties();
        // MARK: - Attached Picture: Format specific builders
        using FLACPicture = TagLib::FLAC::Picture *;
        FLACPicture asFlacPicture();
        using MP4Picture = TagLib::MP4::CoverArt;
        MP4Picture asMP4Picture();
        using ID3v2Picture = TagLib::ID3v2::AttachedPictureFrame *;
        ID3v2Picture asID3v2Picture();
        using APEPicture = std::optional<std::tuple<std::string, TagLib::ByteVector>>;
        APEPicture asAPEPicture();
        // MARK: - AttachedPicture: builders from specific format
        static Picture fromFLACPicture(const TagLib::FLAC::Picture *flacPicture);
        static Picture fromMP4Picture(const TagLib::MP4::CoverArt coverArt);
        static Picture fromID3v2Picture(const TagLib::ID3v2::AttachedPictureFrame *frame);
        static std::optional<Picture> fromAPEPicture(const TagLib::APE::Item item, const char*key);
    };
    using AttachedPictures = std::vector<Picture>;
    AUDIO_METADATA_PROPERTY(AttachedPictures, attachedPictures, AttachedPictures);
    // MARK: - Additional Metadata
    using AdditionalMetadataPair = std::pair<std::string, std::string>;
    using AdditionalMetadata = std::vector<AdditionalMetadataPair>;
    AUDIO_METADATA_PROPERTY(AdditionalMetadata, additional, Additional);
    // MARK: - Abstract Tag
    static AudioMetadata fromTag(const TagLib::Tag *tag);
    void fillTag(TagLib::Tag * tag) const;
    // MARK: - ID3v1 Tag
    static AudioMetadata fromID3v1Tag(const TagLib::ID3v1::Tag *tag);
    void fillID3v1Tag(TagLib::ID3v1::Tag *tag) const;
    // MARK: - ID3v2 Tag
    static AudioMetadata fromID3v2Tag(const TagLib::ID3v2::Tag *tag);
    void fillID3v2Tag(TagLib::ID3v2::Tag *tag) const;
    // MARK: - Xiph Comment
    static AudioMetadata fromXiphComment(const TagLib::Ogg::XiphComment *tag);
    void fillXiphComment(TagLib::Ogg::XiphComment *tag) const;
    // MARK: - APE Tag
    static AudioMetadata fromAPETag(const TagLib::APE::Tag *tag);
    void fillAPETag(TagLib::APE::Tag *tag) const;
    // MARK: - MP4 Tag
    static AudioMetadata fromMP4Tag(const TagLib::MP4::Tag *tag);
    void fillMP4Tag(TagLib::MP4::Tag *tag) const;
    // MARK: - Utility
    void overlay(AudioMetadata layer);
};
