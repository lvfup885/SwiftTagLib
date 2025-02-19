
@_implementationOnly import CxxTagLibBridge

public extension AudioFile {
    /// Aggregate metadata container built from `AuidoFile.Formt` specific combination of the following: `TagLib::Tag`, `TagLib:ID3v1::Tag`, `TagLib::ID3v2::Tag`, `TagLib::Ogg::XiphComment`, `TagLib::APE::Tag`, `TagLib::MP4::Tag`.
    struct Metadata: CxxRepresentable, Hashable {
        // MARK: - Basic Properties shared across ID3v1, ID3v2 and some other Tags
        @StringProperty public var title: String?
        @StringProperty public var albumTitle: String?
        @StringProperty public var artist: String?
        @StringProperty public var genre: String?
        @StringProperty public var releaseDate: String?
        @StringProperty public var comment: String?
        // MARK: - ID3v2 Properties
        @StringProperty public var composer: String?
        @StringProperty public var albumArtist: String?
        @IntProperty public var bpm: Int32?
        @IntProperty public var rating: Int32?
        @IntProperty public var trackNumber: Int32?
        @IntProperty public var trackTotal: Int32?
        @IntProperty public var discNumber: Int32?
        @IntProperty public var discTotal: Int32?
        @StringProperty public var lyrics: String?
        public var compilation: Bool = false
        /// International Standard Recording Code
        @StringProperty public var isrc: String?
        /// Media Catalog Number
        @StringProperty public var mcn: String?
        @StringProperty public var musicBrainzReleaseID: String?
        @StringProperty public var musicBrainzRecordingID: String?
        // MARK: - Attached Pictures
        public var attachedPictures: [AttachedPicture] = []
        // MARK: - Additional Metadata
        public var additional: [AdditionalMetadataPair] = []
        // MARK: - init
        public init() {}

        init(_ metadata: AudioMetadata) {
            _title = .init(metadata.title)
            _albumTitle = .init(metadata.albumTitle)
            _artist = .init(metadata.artist)
            _genre = .init(metadata.genre)
            _releaseDate = .init(metadata.releaseDate)
            _comment = .init(metadata.comment)
            _composer = .init(metadata.composer)
            _albumArtist = .init(metadata.albumArtist)
            _bpm = .init(metadata.beatPerMinute)
            _rating = .init(metadata.rating)
            _trackNumber = .init(metadata.trackNumber)
            _trackTotal = .init(metadata.trackTotal)
            _discNumber = .init(metadata.discNumber)
            _discTotal = .init(metadata.discTotal)
            _lyrics = .init(metadata.lyrics)
            compilation = metadata.compilation
            _isrc = .init(metadata.internationalStandardRecordingCode)
            _mcn = .init(metadata.mediaCatalogNumber)
            _musicBrainzReleaseID = .init(metadata.musicBrainzReleaseID)
            _musicBrainzRecordingID = .init(metadata.musicBrainzRecordingID)
            attachedPictures = metadata.attachedPictures.map(AttachedPicture.init)
            additional = metadata.additional.map(AdditionalMetadataPair.init)
        }

        var cxxRepresentation: AudioMetadata {
            var metadata = AudioMetadata()
            metadata.title = _title.underlyingValue
            metadata.albumTitle = _albumTitle.underlyingValue
            metadata.artist = _artist.underlyingValue
            metadata.genre = _genre.underlyingValue
            metadata.releaseDate = _releaseDate.underlyingValue
            metadata.comment = _comment.underlyingValue
            metadata.composer = _composer.underlyingValue
            metadata.albumArtist = _albumArtist.underlyingValue
            metadata.beatPerMinute = _bpm.underlyingValue
            metadata.rating = _rating.underlyingValue
            metadata.trackNumber = _trackNumber.underlyingValue
            metadata.trackTotal = _trackTotal.underlyingValue
            metadata.discNumber = _discNumber.underlyingValue
            metadata.discTotal = _discTotal.underlyingValue
            metadata.lyrics = _lyrics.underlyingValue
            metadata.compilation = compilation
            metadata.internationalStandardRecordingCode = _isrc.underlyingValue
            metadata.mediaCatalogNumber = _mcn.underlyingValue
            metadata.musicBrainzReleaseID = _musicBrainzReleaseID.underlyingValue
            metadata.musicBrainzRecordingID = _musicBrainzRecordingID.underlyingValue
            /// unfortunately this is the only way of converting Array of more complex types than int/bool/string
            /// to std::vector, generalization isn't possible yet. 22.11.2024
            var attachedPictures = AudioMetadata.AttachedPictures()
            self.attachedPictures.forEach { attachedPictures.push_back($0.cxxRepresentation) }
            metadata.attachedPictures = attachedPictures
            var additional = AudioMetadata.AdditionalMetadata()
            self.additional.forEach { additional.push_back($0.cxxRepresentation) }
            metadata.additional = additional
            return metadata
        }
    }
}

// MARK: - read
import struct Foundation.URL

extension AudioFile.Metadata {
    static func readMetadataAndProperties(
        from url: URL,
        format: AudioFile.Format
    ) throws(AudioFile.InitializationError) -> (metadata: Self, properties: AudioFile.Properties) {
        var metadata = AudioMetadata()
        var properties = AudioProperties()
        let implementation = format.implementationMetatype.init(std.string(url.path))
        let outcome = implementation.readMetadata(&metadata, &properties)
        try AudioFile.InitializationError.throwIfNeeded(outcome)
        return (.init(metadata), .init(properties))
    }
}

// MARK: - write
extension AudioFile.Metadata {
    func write(
        to url: URL,
        format: AudioFile.Format
    ) throws(AudioFile.MetadataWritingError) {
        let implementation = format.implementationMetatype.init(std.string(url.path))
        var metadata = cxxRepresentation
        let outcome = implementation.writeMetadata(&metadata)
        try AudioFile.MetadataWritingError.throwIfNeeded(outcome)
    }
}
