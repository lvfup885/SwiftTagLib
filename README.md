
## SwiftTagLib

This library is meant as a **metadata** focused and distilled replacement for what [SFBAudioEngine](https://github.com/sbooth/SFBAudioEngine/) does. 
[SFBAudioEngine](https://github.com/sbooth/SFBAudioEngine/) utilizes [CXXTagLib](https://github.com/sbooth/CXXTagLib/) which wraps [taglib](https://github.com/taglib/taglib).

This library is done using [Swift C++ Interop](https://www.swift.org/documentation/cxx-interop/) (there are some [limitations](https://www.swift.org/documentation/cxx-interop/status/) to consider).
[Understanding Objective-C and Swift interoperability](https://rderik.com/blog/understanding-objective-c-and-swift-interoperability/). 
Currently supporting reading from most of the same types as [SFBAudioEngine](https://github.com/sbooth/SFBAudioEngine/) in C++ Bridge.



#### Notes:

- [WMA](https://en.wikipedia.org/wiki/Advanced_Systems_Format) file format is supported by taglib, but not `SFBAudioEngine`, can probably try to support it even though it's outdated.
