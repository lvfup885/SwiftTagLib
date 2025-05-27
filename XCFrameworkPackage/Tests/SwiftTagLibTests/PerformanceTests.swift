
import XCTest
import Foundation
@testable import SwiftTagLib

/// While rudimentary it's still should be sensitive to changes
final class PerformanceTests: XCTestCase {
    func testMetadataReading() throws {
        let fileURLs = AudioSample.supported.map(\.url)
        try XCTSkipIf(fileURLs.isEmpty, "no file URLs for test")

        measure(metrics: [
            XCTClockMetric(),
            XCTMemoryMetric(),
            XCTCPUMetric(),
        ]) {
            for url in fileURLs {
                guard let _ = try? AudioFile(url: url) else {
                    XCTFail("failed to read file at: \(url.path)")
                    return
                }
            }
        }
    }

    func testMetadataReadingSkippingImages() throws {
        let fileURLs = AudioSample.supported.map(\.url)
        try XCTSkipIf(fileURLs.isEmpty, "no file URLs for test")

        measure(metrics: [
            XCTClockMetric(),
            XCTMemoryMetric(),
            XCTCPUMetric(),
        ]) {
            for url in fileURLs {
                guard let _ = try? AudioFile(url: url, options: [.skipImages]) else {
                    XCTFail("failed to read file at: \(url.path)")
                    return
                }
            }
        }
    }
}

// MARK: - Convenience
fileprivate extension PerformanceTests {
    func urls(
        in directoryPath: String,
        ignoredFileNames: Set<String> = [
            ".DS_Store",
            ".localized",
        ]
    ) throws -> [URL] {
        let fileManager: FileManager = .default
        var isDirectory: ObjCBool = false
        let directoryExists = fileManager.fileExists(atPath: directoryPath, isDirectory: &isDirectory)
        guard directoryExists, isDirectory.boolValue else {
            return []
        }
        let directoryURL = URL(fileURLWithPath: directoryPath)
        return try fileManager.contentsOfDirectory(atPath: directoryPath).map {
            directoryURL.appending(component: $0)
        }
    }
}
