
@_implementationOnly import CxxTagLibBridge

extension AudioFile.Metadata {
    public struct AdditionalMetadataPair: CxxRepresentable, Hashable {
        public let key: String
        public let value: String

        @inlinable public init(key: String, value: String) {
            self.key = key
            self.value = value
        }

        init(_ pair: AudioMetadata.AdditionalMetadataPair) {
            self.key = String(pair.first);
            self.value = String(pair.second)
        }

        var cxxRepresentation: AudioMetadata.AdditionalMetadataPair {
            .init(first: std.string(key), second: std.string(value))
        }
    }
}
