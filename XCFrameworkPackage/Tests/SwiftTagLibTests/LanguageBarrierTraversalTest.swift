
import Foundation
import Testing
@testable import SwiftTagLib

/// Just a sanity check to confirm correct conversion of Metadata aggregate from Swift to C++ and back to Swift.
@Suite("Language Barrier Traversal Test")
struct LanguageBarrierTraversalTest {
    @Test
    func emptyMetadataRemainsEmpty() {
        let metadata = AudioFile.Metadata()
        let converted = AudioFile.Metadata(cxxRepresentation: metadata.cxxRepresentation)
        #expect(metadata == converted)
    }

    @Test(arguments: AudioFile.Metadata.stringProperties)
    func stringPropertyChangePersists(property: WritableKeyPath<AudioFile.Metadata, String?>) {
        /// some
        var metadata = AudioFile.Metadata()
        metadata[keyPath: property] = UUID().uuidString
        var converted = AudioFile.Metadata(cxxRepresentation: metadata.cxxRepresentation)
        #expect(metadata[keyPath: property] == converted[keyPath: property], "\(property)")
        /// none
        metadata[keyPath: property] = .none
        converted = AudioFile.Metadata(cxxRepresentation: metadata.cxxRepresentation)
        #expect(metadata[keyPath: property] == converted[keyPath: property], "\(property)")
    }

    @Test(arguments: AudioFile.Metadata.intProperties)
    func intPropertyChangePersists(property: WritableKeyPath<AudioFile.Metadata, Int32?>) {
        /// some
        var metadata = AudioFile.Metadata()
        metadata[keyPath: property] = Int32.random(in: Int32(UInt16.min) ... Int32(UInt16.max))
        var converted = AudioFile.Metadata(cxxRepresentation: metadata.cxxRepresentation)
        #expect(metadata[keyPath: property] == converted[keyPath: property])
        /// none
        metadata[keyPath: property] = .none
        converted = AudioFile.Metadata(cxxRepresentation: metadata.cxxRepresentation)
        #expect(metadata[keyPath: property] == converted[keyPath: property])
    }

    @Test
    func releaseDateChangePersists() {
        /// some
        var metadata = AudioFile.Metadata()
        metadata.releaseDate = "1993"
        var converted = AudioFile.Metadata(cxxRepresentation: metadata.cxxRepresentation)
        #expect(metadata.releaseDate == converted.releaseDate)
        /// none
        metadata.releaseDate = .none
        converted = AudioFile.Metadata(cxxRepresentation: metadata.cxxRepresentation)
        #expect(metadata.releaseDate == converted.releaseDate)
    }

    @Test func compilationChangePersists() {
        var metadata = AudioFile.Metadata()
        metadata.compilation = true
        var converted = AudioFile.Metadata(cxxRepresentation: metadata.cxxRepresentation)
        #expect(metadata.compilation == converted.compilation)
        metadata.compilation = false
        converted = AudioFile.Metadata(cxxRepresentation: metadata.cxxRepresentation)
        #expect(metadata.compilation == converted.compilation)
    }

    @Test
    func attachedPicturesChangePersists() {

    }

    @Test
    func additionalMetadataChangePersists() {

    }
}
