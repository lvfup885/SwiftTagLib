
import Foundation.NSData
import CxxTagLibBridge

public extension AudioFile.Metadata {
    struct AttachedPicture: CxxRepresentable, Hashable {
        public let data: Data
        public let description: String
        public typealias Kind = AudioMetadata.Picture.Kind
        public let kind: Kind

        public init(data: Data, kind: Kind, description: String) {
            self.data = data
            self.kind = kind
            self.description = description
        }

        @usableFromInline internal init(_ picture: AudioMetadata.Picture) {
            data = Data(bytes: Array(picture.bytes), count: Int(picture.size))
            description = String(picture.description)
            kind = picture.kind
        }

        @usableFromInline var cxxRepresentation: AudioMetadata.Picture {
            var picture = AudioMetadata.Picture();
            #warning("this is rather slow & inefficient way to go from Data to [UInt8] to std::vector<char>")
            /// take a look at [pointers to C](https://github.com/swiftlang/swift/blob/main/docs/HowSwiftImportsCAPIs.md#pointers-to-data).
            var bytes = AudioMetadata.Picture.Bytes()
            data.forEach { bytes.push_back(Int8(bitPattern: $0)) }
            picture.bytes = bytes;
            picture.size = UInt32(bytes.count);
            picture.description = std.string(description)
            picture.kind = kind
            return picture;
        }
    }
}

// MARK: - AudioFile.Metadata.AttachedPicture + CGImage
import CoreImage
import UniformTypeIdentifiers

public extension AudioFile.Metadata.AttachedPicture {
    /// Attempts to construct `CGImage` from **raw** `Data`.
    @inlinable var image: CGImage? {
        guard
            let imageSource = CGImageSourceCreateWithData(data as CFData, .none),
            let image = CGImageSourceCreateImageAtIndex(imageSource, 0, nil)
        else { return .none }
        return image
    }
    /// Provides `UTType` of image in **raw** `Data`, presumably should only ever be `public.jpeg`.
    @inlinable var type: UTType? {
        guard
            let imageSource = CGImageSourceCreateWithData(data as CFData, .none),
            let identifier = CGImageSourceGetType(imageSource) as? String,
            let type = UTType(identifier)
        else { return .none }
        return type
    }
}

// MARK: - AudioFile.Metadata.AttachedPicture.Kind: CustomStringConvertible
extension AudioFile.Metadata.AttachedPicture.Kind: @retroactive CustomStringConvertible {
    public var description: String {
        switch self {
            case .other: "other"
            case .fileIcon: "file icon"
            case .otherFileIcon: "other file icon"
            case .frontCover: "front cover"
            case .backCover: "back cover"
            case .leafletPage: "leaflet page"
            case .media: "media"
            case .leadArtist: "lead artist"
            case .artist: "artist"
            case .conductor: "conductor"
            case .band: "band"
            case .composer: "composer"
            case .lyricist: "lyricist"
            case .recordingLocation: "recording location"
            case .duringRecording: "during recording"
            case .duringPerformance: "during performance"
            case .movieScreenCapture: "movie screen capture"
            case .colouredFish: "coloured fish"
            case .illustration: "illustration"
            case .bandLogo: "band logo"
            case .publisherLogo: "publisher logo"
            @unknown default: "@unknown default"
        }
    }
}

