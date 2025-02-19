
## SwiftTagLib

This library is meant as a **metadata** focused and distilled replacement for what [SFBAudioEngine](https://github.com/sbooth/SFBAudioEngine/) does. 
[SFBAudioEngine](https://github.com/sbooth/SFBAudioEngine/) utilizes [CXXTagLib](https://github.com/sbooth/CXXTagLib/) which wraps [taglib](https://github.com/taglib/taglib).

This library is done using [Swift C++ Interop](https://www.swift.org/documentation/cxx-interop/) (there are some [limitations](https://www.swift.org/documentation/cxx-interop/status/) to consider).
[Understanding Objective-C and Swift interoperability](https://rderik.com/blog/understanding-objective-c-and-swift-interoperability/). 
Currently supporting reading from most of the same types as [SFBAudioEngine](https://github.com/sbooth/SFBAudioEngine/) in C++ Bridge.



#### Notes:

- [WMA](https://en.wikipedia.org/wiki/Advanced_Systems_Format) file format is supported by taglib, but not `SFBAudioEngine`, can probably try to support it even though it's outdated.

#### Todo:

- [x] Refactor boilerplate macro as abstract class.
- [x] Make `AudioMetadata` properties optional in  `Swift`
- [ ] Check that `releaseDate` is being read correctly.
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
      - [ ] fix bugs in outliers
    - [ ] fill/erase all fields
    - [ ] trasnplanting metadata between formats
- [ ] Add code to catch `C++` errors/exceptions while reading/writing metadata.
- [ ] Additional metadata subscript interface?

#### Bugs:

- [ ] `aiff`:

  - [ ] `ID3v2`:
    - [ ] mcn 
      - [ ] not written

    - [ ] rating
      - [ ] not written, previous value stays

- [ ] `mp4`, `m4a`:

  - [ ] `MP4`:
    - [ ] albumTitle
      - [ ] not written, previous value?

      - [ ] not erased

    - [ ] comment
      - [ ] wrong value

    - [ ] lyrics
      - [ ] not written

    - [ ] isrc 
      - [ ] not written

    - [ ] mcn
      - [ ] not written

    - [ ] musicBrainzReleaseID
      - [ ] not written

    - [ ] musicBrainzRecordingID
      - [ ] not written

    - [ ] rating
      - [ ] not written

    - [ ] trackNumber
      - [ ] not written

    - [ ] trackTotal
      - [ ] not written

- [ ] `wav`

  - [ ] `AbstractTag`, `ID3v2`:
    - [ ] mcn
      - [ ] not written
    - [ ] releaseDate
      - [ ] not written, becomes 0
      - [ ] not erased
    - [ ] compilation
      - [ ] not written

- [ ] `mp3`

  - [ ] `APE`, `ID3v1`, `ID3v2`:
    - [ ] title
      - [ ] truncated
    - [ ] albumTitle
      - [ ] truncated
    - [ ] artist
      - [ ] truncated
    - [ ] comment
      - [ ] truncted
    - [ ] mcn 
      - [ ] not written
    - [ ] rating
      - [ ] either limited to 196 or not written
    - [ ] compilation
      - [ ] not written
    - [ ] releaseDate
      - [ ] not erased, becomes 0

- [ ] `opus.ogg`, `vorbis.ogg`:

  - [ ] `XIPHComment`:
    - [ ] title
      - [ ] not written
    - [ ] albumTitle
      - [ ] not written
      - [ ] not erased
    - [ ] artist
      - [ ] wrong value
    - [ ] genre
      - [ ] not written
    - [ ] comment
      - [ ] not written
    - [ ] composer
      - [ ] not written
    - [ ] albumArtist
      - [ ] not written
    - [ ] lyrics
      - [ ] not written
    - [ ] isrc 
      - [ ] not written
    - [ ] mcn
      - [ ] not written
    
    - [ ] musicBrainzReleaseID
      - [ ] not written
    
    - [ ] musicBrainzRecordingID
      - [ ] not written
    - [ ] bpm
      - [ ] not written
    - [ ] rating
      - [ ] not written
    - [ ] trackNumber
      - [ ] not written
    - [ ] trackTotal
      - [ ] not written
    - [ ] discNumber
      - [ ] not written
    - [ ] discTotal
      - [ ] not written
    - [ ] releaseDate
      - [ ] not written
    - [ ] releaseDate
      - [ ] not written
    - [ ] compilation
      - [ ] not written

- [ ] `flac`:

  - [ ] `ID3v1`, `ID3v2`, `XiphComment`:

    - [ ] title

      - [ ] not written
      - [ ] not erased

    - [ ] albumTitle

      - [ ] not written
      - [ ] not erased

    - [ ] artist

      - [ ] wrong value

    - [ ] comment

      - [ ] wrong value or not written
      - [ ] not erased

    - [ ] composer

      - [ ] wrong value or not written
      - [ ] not erased

    - [ ] albumArtist

      - [ ] wrong value or not written
      - [ ] not erased

    - [ ] lyrics

      - [ ] not written
      - [ ] not erased

    - [ ] isrc 

      - [ ] not written

    - [ ] mcn

      - [ ] not written

    - [ ] musicBrainzReleaseID

      - [ ] not written

    - [ ] musicBrainzRecordingID

      - [ ] not written

    - [ ] bpm

      - [ ] not written

    - [ ] trackNumber

      - [ ] not written
      - [ ] not erased

    - [ ] trackTotal

      - [ ] not written

    - [ ] discNumber

      - [ ] not written
      - [ ] not erased

    - [ ] discTotal

      - [ ] not written

    - [ ] releaseDate

      - [ ] not written or previous value
      - [ ] not erased

    - [ ] compilation

      - [ ] not written

    - [ ] attached pictures goes up by 1 after writing same metadata to file

      probably the problem is image being read from different containers and saved to each of them regardless

      maybe track where image was stored?
