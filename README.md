
## SwiftTagLib

This library is meant as a **metadata** focused and distilled replacement for what [SFBAudioEngine](https://github.com/sbooth/SFBAudioEngine/) does. 
[SFBAudioEngine](https://github.com/sbooth/SFBAudioEngine/) utilizes [CXXTagLib](https://github.com/sbooth/CXXTagLib/) which wraps [taglib](https://github.com/taglib/taglib).

This library is done using [Swift C++ Interop](https://www.swift.org/documentation/cxx-interop/) (there are some [limitations](https://www.swift.org/documentation/cxx-interop/status/) to consider).
[Understanding Objective-C and Swift interoperability](https://rderik.com/blog/understanding-objective-c-and-swift-interoperability/). 
Currently supporting reading from most of the same types as [SFBAudioEngine](https://github.com/sbooth/SFBAudioEngine/) in C++ Bridge.



#### Notes:

- [WMA](https://en.wikipedia.org/wiki/Advanced_Systems_Format) file format is supported by taglib [here](https://taglib.org/api/namespaceTagLib_1_1ASF.html#details), but not `SFBAudioEngine`, can probably try to support it even though it's outdated.

#### Todo:

- [ ] Add some tests:
  - [x] Language boundary traversal for Metadata: `Swift` -> `C++` -> `Swift`:
    - [x] string properties
    - [x] int properties
    - [x] release date
    - [x] compilation
    - [ ] attached picture
    - [ ] additional metadata
  - [ ] Writing metadata:
    - [x] same self overwrite
    - [x] fill/erase all fields
    - [ ] trasnplanting metadata between formats
- [ ] Value limitations:
  - [ ] ~~cover MCN, ISRC & MusicBrains RecordID, TrackID with types~~
  - [ ] add validation functions for value limitations:
    - [ ] limited integers:
      - [ ] rating
      - [ ] bpm
      - [ ] disc number & total
      - [ ] track number & total

    - [ ] string limitations in mp3
- [ ] Additional metadata subscript interface?

#### Bugs:

- [ ] `ID3v2`:
  - [ ] either read or write are incorrect:
    - [ ] mediaCatalogNumber

    - [ ] trackTotal

  - [ ] `mp3` values are truncated at 30 characters:
    - [ ] title

    - [ ] albumTitle

    - [ ] artist

    - [ ] comment

- [ ] `MP4`:
  - [ ] either read or write are incorrect:
    - [ ] trackTotal
    - [ ] discTotal
    - [ ] compilation
