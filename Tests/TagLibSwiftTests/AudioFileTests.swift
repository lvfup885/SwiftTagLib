
import Foundation
import Testing
@testable import SwiftTagLib

/// Just a bare bones validation that it does not fail spectacularly
@Suite("Audio File Tests", .serialized)
struct AudioFileTests {
    @Test(arguments: [
        Sample.aiff,
        Sample.flac,
        Sample.mp3,
        Sample.mp4,
        Sample.m4a,
        Sample.ogg,
        Sample.wav,
        Sample.opus,
        /// not supported/covered
//        Sample.aac,
//        Sample.ac3,
//        Sample.ts,
//        Sample.wma,

    ])
    func metadataReading(url: URL) throws {
        let file = try AudioFile(url: url)
        print("\n\n", file.url, "\n", file.metadata, "\n\n")
        #expect(true)
    }

    @Test(arguments: [
        Sample.aiff,
        Sample.flac,
        Sample.mp3,
        Sample.mp4,
        Sample.m4a,
        Sample.ogg,
        Sample.wav,
        Sample.opus,
        /// not supported/covered
//        Sample.aac,
//        Sample.ac3,
//        Sample.ts,
//        Sample.wma,
    ])
    func writingMetadata(targetURL: URL) throws {
        let source = try AudioFile(url: Sample.mp3)
        var file = try AudioFile(url: targetURL)
        file.metadata = source.metadata
        try file.write()
    }
}
