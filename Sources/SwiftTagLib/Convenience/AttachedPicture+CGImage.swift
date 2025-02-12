
import CoreImage
import UniformTypeIdentifiers

public extension AudioFile.Metadata.AttachedPicture {
    /// Creates `AttachedPicture` from `CGImage` with `kind` and `description`.
    @inlinable init(image: CGImage, kind: Kind, description: String) throws(ImageDataExtractionError) {
        guard let dataProvider = image.dataProvider else {
            throw .noDataProvider
        }
        guard let data = dataProvider.data as? Data else {
            throw .noDataInDataProvider
        }
        self.init(data: data, kind: kind, description: description)
    }
}

public extension AudioFile.Metadata.AttachedPicture {
    /// Attempts to construct `CGImage` from **raw** `Data`.
    @inlinable var image: CGImage? {
        guard
            let imageSource = CGImageSourceCreateWithData(data as CFData, .none),
            let image = CGImageSourceCreateImageAtIndex(imageSource, 0, nil)
        else {
            return .none
        }
        return image
    }
    /// Provides `UTType` of image in **raw** `Data`, presumably should only ever be `public.jpeg`.
    @inlinable var type: UTType? {
        guard
            let imageSource = CGImageSourceCreateWithData(data as CFData, .none),
            let identifier = CGImageSourceGetType(imageSource) as? String,
            let type = UTType(identifier)
        else {
            return .none
        }
        return type
    }
}

public extension AudioFile.Metadata.AttachedPicture {
    /// Descrbies error occuring when creating `AttachedPicture` from either `CGImage`, `NSImage` or `UIImage`.
    enum ImageDataExtractionError: Swift.Error, LocalizedError {
        // CGImage:
        case noDataProvider
        case noDataInDataProvider
        // UIImage:
        case noCGImageBehindUIImage
        // NSImage:
        case noTiffRepresentationBehindNSImage
        case failedToCreateImageSource
        case failedToCreateCGImage

        public var errorDescription: String? {
            switch self {
                case .noDataProvider: "no CGDataProvider in CGImage"
                case .noDataInDataProvider: "no Data in CGDataProvider"
                case .noCGImageBehindUIImage: "no CGImage behind UIImage"
                case .noTiffRepresentationBehindNSImage: "no TIFF representation behind NSImage"
                case .failedToCreateImageSource: "failed to create CGImageSource"
                case .failedToCreateCGImage: "failed to create CGImage"
            }
        }
    }
}
