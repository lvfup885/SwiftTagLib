
@testable import SwiftTagLib
import struct Foundation.UUID

extension AudioFile.Metadata {
    static var mocked: Self {
        var metadata = AudioFile.Metadata()
        /// string properties
        for keyPath in Self.stringProperties {
            let string = UUID().uuidString.replacingOccurrences(of: "-", with: "")
            metadata[keyPath: keyPath] = String(string.prefix(string.count / 2))
        }
        /// int propeties
        metadata.trackTotal = Int32.random(in: 1 ... 255) // or 200
        metadata.trackNumber = Int32.random(in: 1 ... metadata.trackTotal!)
        metadata.discTotal = Int32.random(in: 1 ... 99)
        metadata.discNumber = Int32.random(in: 1 ... metadata.discTotal!)
        metadata.rating = Int32.random(in: 1 ... 100)
        metadata.beatPerMinute = Int32.random(in: 1 ... 300) // or 250
        /// bool properties
        for keyPath in Self.boolProperties {
            metadata[keyPath: keyPath] = false//Bool.random()
        }
        /// date properties
        for keyPath in Self.dateProperties {
            metadata[keyPath: keyPath] = "\(Int.random(in: 1960 ... 2024))"
        }
        return metadata
    }
}
