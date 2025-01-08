
import Foundation.NSURL

public struct AudioFile {
    public let url: URL
    public let format: Format
    public var metadata: Metadata

    @inlinable public init(url: URL) throws(InitializationError) {
        guard let format = try Format.forFile(at: url) else { throw .unableToDetermineAudioFormat }
        self.url = url
        self.format = format
        self.metadata = try .read(from: url, format: format)
    }

    @inlinable public func write() throws(MetadataWritingError) {
        try metadata.write(to: url, format: format)
    }
}
