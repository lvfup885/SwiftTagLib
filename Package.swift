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
        .library(name: "SwiftTagLib", type: .static, targets: ["SwiftTagLib"]),
    ],
    dependencies: [
        .package(url: "https://github.com/sbooth/CXXTagLib", revision: "d729ec1"),
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
