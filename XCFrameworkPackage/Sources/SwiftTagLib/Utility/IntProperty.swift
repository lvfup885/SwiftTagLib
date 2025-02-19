
@_implementationOnly import CxxTagLibBridge

public extension AudioFile.Metadata {
    @propertyWrapper
    struct IntProperty: Hashable, Equatable, CustomStringConvertible {
        public var wrappedValue: Int32? = .none

        public init() {}

        init(_ underlyingValue: Int32) {
            wrappedValue = underlyingValue > 0 ? underlyingValue : .none
        }

        internal var underlyingValue: Int32 {
            guard let wrappedValue, wrappedValue > 0 else { return 0 }
            return wrappedValue
        }

        public var description: String {
            guard let wrappedValue else { return "nil" }
            return "\(wrappedValue)"
        }
    }
}
