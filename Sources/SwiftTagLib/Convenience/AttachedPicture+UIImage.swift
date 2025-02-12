
#if canImport(UIKit)
import UIKit

public extension AudioFile.Metadata.AttachedPicture {
    /// Creates `AttachedPicture` from `UIImage` with `kind` and `description`.
    @inlinable init(image: UIImage, kind: Kind, description: String) throws(ImageDataExtractionError) {
        guard let image = image.cgImage else {
            throw .noCGImageBehindUIImage
        }
        try self.init(image: image, kind: kind, description: description)
    }
}
#endif
