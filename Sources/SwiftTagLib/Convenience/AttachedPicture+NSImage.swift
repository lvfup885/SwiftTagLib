
#if canImport(AppKit)
import AppKit

public extension AudioFile.Metadata.AttachedPicture {
    /// Creates `AttachedPicture` from `NSImage` with `kind` and `description`.
    @inlinable init(image: NSImage, kind: Kind, description: String) throws(ImageDataExtractionError) {
        guard let tiffRepresentation = image.tiffRepresentation else {
            throw .noTiffRepresentationBehindNSImage
        }
        guard let imageSource = CGImageSourceCreateWithData(tiffRepresentation as CFData, .none) else {
            throw .failedToCreateImageSource
        }
        guard let image = CGImageSourceCreateImageAtIndex(imageSource, 0, .none) else {
            throw .failedToCreateCGImage
        }
        try self.init(image: image, kind: kind, description: description)
    }
}
#endif
