
extension AudioFile {
    public enum Format: CaseIterable {
        case aiff
        case dsdiff
        case dsf
        case flac
        case monkeysAudio
        case mp3
        case mp4
        case musepack
        case oggFlac
        case oggOpus
        case oggSpeex
        case oggVorbix
        case trueAudio
        case wave
        case wavPack
        /// should have no actual metadata
//        case shorten
        /// discared unknown/uncommon formats, have no *magic* binary number.
//        case impulseTrackerModule
//        case proTrackerModule
//        case screamTrackerModule3
//        case extendedModule
    }
}

// MARK: - AudioFormat Metatype & AudioFileImplementation Metatype
extension AudioFile.Format {
    var formatMetatype: any AudioFormat.Type {
        switch self {
            case .aiff: AIFF.self
            case .dsdiff: DSDIFF.self
            case .dsf: DSF.self
            case .flac: FLAC.self
            case .monkeysAudio: MonkeyAudio.self
            case .mp3: MP3.self
            case .mp4: MP4.self
            case .musepack: Musepack.self
            case .oggFlac: OggFLAC.self
            case .oggOpus: OggOpus.self
            case .oggSpeex: OggSpeex.self
            case .oggVorbix: OggVorbis.self
            case .trueAudio: TrueAudio.self
            case .wave: WAVE.self
            case .wavPack: WavPack.self
        }
    }

    var implementationMetatype: AudioFileImplementation.Type {
        formatMetatype.implementationMetatype
    }
}

// MARK: - AudioFile.Format forFile
import Foundation.NSURL
import Foundation.NSFileHandle

extension AudioFile.Format {
    @usableFromInline static func forFile(at url: URL) throws(AudioFile.InitializationError) -> Self? {
        let fileExtension = url.pathExtension.lowercased()
        guard let fileHandle = try? FileHandle(forReadingFrom: url) else { throw .unableToOpenFile }
        var score: Int = 10
        var format: Self? = .none
        for audioFormat in Self.allCases {
            let metatype = audioFormat.formatMetatype
            var formatScore: Int = 0
            if metatype.supportedPathExtensions.contains(fileExtension) {
                formatScore += 25
            }
            if metatype.isFormatSupported(fileHandle) {
                formatScore += 75
            }
            if formatScore > score {
                score = formatScore
                format = audioFormat
            }
        }
        try? fileHandle.close()
        return format
    }
}
