
import Foundation.NSURL

enum Sample {
    static var aac: URL { sample("aac") }
    static var ac3: URL { sample("ac3") }
    static var aiff: URL { sample("aiff") }
    static var flac: URL { sample("flac") }
    static var m4a: URL { sample("m4a") }
    static var mp3: URL { sample("mp3") }
    static var mp4: URL { sample("mp4") }
    static var ogg: URL { sample("ogg") }
    static var ts: URL { sample("ts") }
    static var wav: URL { sample("wav") }
    static var wma: URL { sample("wma") }
    static var opus: URL { sample("opus.ogg") }

    private static func sample(_ format: String) -> URL {
        URL(fileURLWithPath: rootDirectoryPath())
            .appending(path: "Audio")
            .appending(path: "sample." + format)
    }

    private static func rootDirectoryPath(file: String = #file) -> String {
        guard let path = file.components(separatedBy: "Tests").first else {
            fatalError("specify correct common parent directory for this file")
        }
        return path
    }
}
