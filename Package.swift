// swift-tools-version: 5.10
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
    ],
    dependencies: [
        .package(url: "https://github.com/sbooth/CXXTagLib", .branch("main")),// .upToNextMajor(from: "2.0.2")),
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
                .product(name: "taglib", package: "CXXTagLib"),
            ],
            swiftSettings: [
                .interoperabilityMode(.Cxx),
            ]
            /// weirdly works just fine without explicitly stating header search path here
//            cSettings: [
//                .headerSearchPath("include"),
//            ],
//            cxxSettings: [
//                .headerSearchPath("include"),
//            ],
            /// unsure if it it really needs to be specified here.
//            linkerSettings: [
//                .linkedFramework("ImageIO"),
//            ]
        ),
        .testTarget(
            name: "SwiftTagLibTests",
            dependencies: [
                "SwiftTagLib",
            ],
            swiftSettings: [
                .interoperabilityMode(.Cxx),
            ]
        ),
    ],
    cxxLanguageStandard: .cxx20
)
