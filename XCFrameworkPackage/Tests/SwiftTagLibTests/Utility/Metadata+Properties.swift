
@testable import SwiftTagLib

extension AudioFile.Metadata {
    static var stringProperties: [WritableKeyPath<Self, String?>] {[
        \.title,
        \.albumTitle,
        \.artist,
        \.genre,
        \.comment,
        \.composer,
        \.albumArtist,
        \.lyrics,
        \.isrc,
        \.mcn,
        \.musicBrainzReleaseID,
        \.musicBrainzRecordingID,
    ]}

    static var dateProperties: [WritableKeyPath<Self, String?>] {[
        \.releaseDate,
    ]}

    static var intProperties: [WritableKeyPath<Self, Int32?>] {[
        \.bpm,
        \.rating,
        \.trackNumber,
        \.trackTotal,
        \.discNumber,
        \.discTotal,
    ]}

    static var boolProperties: [WritableKeyPath<Self, Bool>] {[
        \.compilation,
    ]}
}

import struct Foundation.UUID

extension AudioFile.Metadata {
    static var mocked: Self {
        var metadata = AudioFile.Metadata()
        for keyPath in Self.stringProperties {
            metadata[keyPath: keyPath] = UUID().uuidString
        }
        for keyPath in Self.intProperties {
            metadata[keyPath: keyPath] = Int32.random(in: Int32(UInt16.min) ... Int32(UInt16.max))
        }
        for keyPath in Self.boolProperties {
            metadata[keyPath: keyPath] = Bool.random()
        }
        for keyPath in Self.dateProperties {
            metadata[keyPath: keyPath] = "1993"
        }
        return metadata
    }
}

extension AudioFile.Metadata.AttachedPicture: Comparable {
    public static func < (lhs: Self, rhs: Self) -> Bool {
        lhs.hashValue < rhs.hashValue
    }
}
