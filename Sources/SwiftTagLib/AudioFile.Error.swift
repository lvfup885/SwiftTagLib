
import Foundation

public extension AudioFile {
    enum InitializationError: Error, LocalizedError {
        case unableToDetermineAudioFormat
        case unableToOpenFile
        case invalidFile
        case unknownError

        public var errorDescription: String? {
            switch self {
                case .unableToDetermineAudioFormat: "unable to determine audio format"
                case .unableToOpenFile: "unable to open file"
                case .invalidFile: "invalid file"
                case .unknownError: "unknown error"
            }
        }
    }

    enum MetadataWritingError: Error, LocalizedError {
        case unableToOpenFile
        case invalidFile
        case saveError
        case unknownError

        public var errorDescription: String? {
            switch self {
                case .unableToOpenFile: "unable to open file"
                case .invalidFile: "invalid file"
                case .saveError: "save error"
                case .unknownError: "unknown error"
            }
        }
    }
}

import CxxTagLibBridge

extension AudioFile.InitializationError {
    @usableFromInline static func throwIfNeeded(_ outcome: MetadataReadingOutcome) throws(Self) {
        switch outcome {
            case .success: return
            case .fileIsNotOpen: throw .unableToOpenFile
            case .invalidFile: throw .invalidFile
            @unknown default: throw .unknownError
        }
    }
}

extension AudioFile.MetadataWritingError {
    @usableFromInline static func throwIfNeeded(_ outcome: MetadataWritingOutcome) throws(Self) {
        switch outcome {
            case .success: return
            case .fileIsNotOpen: throw .unableToOpenFile
            case .invalidFile: throw .invalidFile
            case .saveError: throw .saveError
            @unknown default: throw .unknownError
        }
    }
}
