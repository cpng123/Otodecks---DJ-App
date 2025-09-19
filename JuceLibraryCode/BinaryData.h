/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   bin2_png;
    const int            bin2_pngSize = 20561;

    extern const char*   disc_png;
    const int            disc_pngSize = 1363853;

    extern const char*   Expanse_otf;
    const int            Expanse_otfSize = 35156;

    extern const char*   Nero_otf;
    const int            Nero_otfSize = 6640;

    extern const char*   forward_png;
    const int            forward_pngSize = 5277;

    extern const char*   headset1_png;
    const int            headset1_pngSize = 3278;

    extern const char*   headset2_png;
    const int            headset2_pngSize = 11442;

    extern const char*   pause_png;
    const int            pause_pngSize = 4918;

    extern const char*   play_png;
    const int            play_pngSize = 5256;

    extern const char*   replay_png;
    const int            replay_pngSize = 5415;

    extern const char*   rewind_png;
    const int            rewind_pngSize = 5378;

    extern const char*   stop_png;
    const int            stop_pngSize = 4748;

    extern const char*   upload1_png;
    const int            upload1_pngSize = 6381;

    extern const char*   bin1_png;
    const int            bin1_pngSize = 17626;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 14;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Points to the start of a list of resource filenames.
    extern const char* originalFilenames[];

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes);

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding original, non-mangled filename (or a null pointer if the name isn't found).
    const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
}
