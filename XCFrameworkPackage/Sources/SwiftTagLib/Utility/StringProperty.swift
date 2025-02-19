
@_implementationOnly import CxxTagLibBridge

public extension AudioFile.Metadata {
    @propertyWrapper
    struct StringProperty: Hashable, Equatable, CustomStringConvertible {
        public var wrappedValue: String? = .none

        public init() {}

        init(_ underlyingValue: std.string) {
            let value = String(underlyingValue)
            wrappedValue = !value.isEmpty ? value : .none
        }

        internal var underlyingValue: std.string {
            guard let wrappedValue else { return std.string() }
            return std.string(wrappedValue)
//            guard let data = wrappedValue.data(using: .utf8) else {
//                print("\n\n\n failed UTF8 conversion for string: \(wrappedValue)\n\n\n")
//                return std.string()
//            }
//            return data.withUnsafeBytes { buffer in
//                std.string(buffer.baseAddress!.assumingMemoryBound(to: CChar.self), buffer.count)
//            }
        }

        public var description: String {
            guard let wrappedValue else { return "nil" }
            return String(describing: wrappedValue)
        }
    }
}
