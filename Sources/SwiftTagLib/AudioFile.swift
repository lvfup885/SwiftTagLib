
import struct Foundation.URL

/// Facade to easily read/write metadata to/from audio file.
public struct AudioFile {
    /// file url.
    public let url: URL
    /// file format, derived from file header and path extensions.
    public let format: Format
    /// attached metadata.
    public var metadata: Metadata

    /// attempts to create `AudioFile` from `URL`.
    public init(url: URL) throws(InitializationError) {
        guard let format = try Format.forFile(at: url) else { throw .unableToDetermineAudioFormat }
        self.url = url
        self.format = format
        self.metadata = try .read(from: url, format: format)
    }

    /// writes changes to `Metadata`.
    public func write() throws(MetadataWritingError) {
        try metadata.write(to: url, format: format)
    }
}
