// swift-tools-version: 5.9
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

// MARK: - Convenience
extension Target {
    var asDependency: Dependency { .target(name: name) }
    var asLibrary: Product { .library(name: name, targets: [name]) }
}

// MARK: - Configuration
let swiftSettings: [SwiftSetting] = [
    .interoperabilityMode(.Cxx),
//    .define("ImageDataTransformationEnabled"),
]

// MARK: - Targets
/// borrowed from .package(url: "https://github.com/sbooth/CXXTagLib", revision: "d729ec1")
let taglib = Target.target(
    name: "taglib",
    cxxSettings: [
        .headerSearchPath("include/taglib"),
        .headerSearchPath("utfcpp/source"),
        .headerSearchPath("."),
        .headerSearchPath("mod"),
        .headerSearchPath("riff"),
        .headerSearchPath("toolkit"),
    ]
)
/// C++ intermediate layer replacing AudioMetadata class hierarchy from SFBAudioEngine.
let taglibBridge = Target.target(
    name: "CxxTagLibBridge",
    dependencies: [
        taglib.asDependency,
    ],
    swiftSettings: swiftSettings
)
/// Swift facade
let swiftTagLib = Target.target(
    name: "SwiftTagLib",
    dependencies: [
        taglibBridge.asDependency,
    ],
    swiftSettings: swiftSettings
)

let tests = Target.testTarget(
    name: "SwiftTagLibTests",
    dependencies: [
        swiftTagLib.asDependency,
    ],
    swiftSettings: swiftSettings
)

// MARK: - Package
let package = Package(
    name: "SwiftTagLib",
    platforms: [
        .iOS(.v17),
        .macOS(.v14),
    ],
    products: [
        taglib.asLibrary, taglibBridge.asLibrary, swiftTagLib.asLibrary,
    ],
    targets: [
        taglib, taglibBridge, swiftTagLib, tests
    ],
    cxxLanguageStandard: .cxx2b //.cxx20
)
