// swift-tools-version: 5.9
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(
    name: "SwiftTagLib",
    platforms: [
        .iOS(.v17),
        .macOS(.v14),
    ],
    products: [
        .library(name: "SwiftTagLib", targets: ["SwiftTagLib"]),
        .library(name: "CxxTagLibBridge", targets: ["CxxTagLibBridge"]),
        .library(name: "taglib", targets: ["taglib"]),
    ],
    targets: [
        .target(
            name: "SwiftTagLib",
            dependencies: [
                .byName(name: "CxxTagLibBridge"),
            ],
            swiftSettings: [
                .interoperabilityMode(.Cxx),
            ]
        ),
        .target(
            name: "CxxTagLibBridge",
            dependencies: [
                .byName(name: "taglib"),
            ],
            swiftSettings: [
                .interoperabilityMode(.Cxx),
            ]
        ),
        /// borrowed from .package(url: "https://github.com/sbooth/CXXTagLib", revision: "d729ec1")
        .target(
            name: "taglib",
            cxxSettings: [
                .headerSearchPath("include/taglib"),
                .headerSearchPath("utfcpp/source"),
                .headerSearchPath("."),
                .headerSearchPath("mod"),
                .headerSearchPath("riff"),
                .headerSearchPath("toolkit"),
            ]
        ),
//        .testTarget(
//            name: "SwiftTagLibTests",
//            dependencies: [
//                "SwiftTagLib",
//            ],
//            swiftSettings: [
//                .interoperabilityMode(.Cxx),
//            ]
//        ),
    ],
    cxxLanguageStandard: .cxx2b //.cxx20
)
