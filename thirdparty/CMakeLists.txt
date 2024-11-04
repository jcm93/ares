add_library(sljit STATIC
    sljit/sljit_src/sljitLir.c
)

target_include_directories(sljit PUBLIC ../thirdparty)
target_compile_definitions(sljit PUBLIC SLJIT_HAVE_CONFIG_PRE=1 SLJIT_HAVE_CONFIG_POST=1)

# lzma
add_library(
  lzma
  STATIC
    libchdr/deps/lzma-24.05/src/Alloc.c
    libchdr/deps/lzma-24.05/src/Bra86.c
    libchdr/deps/lzma-24.05/src/BraIA64.c
    libchdr/deps/lzma-24.05/src/CpuArch.c
    libchdr/deps/lzma-24.05/src/Delta.c
    libchdr/deps/lzma-24.05/src/LzFind.c
    libchdr/deps/lzma-24.05/src/Lzma86Dec.c
    libchdr/deps/lzma-24.05/src/LzmaDec.c
    libchdr/deps/lzma-24.05/src/LzmaEnc.c
    libchdr/deps/lzma-24.05/src/Sort.c
)

target_include_directories(lzma PRIVATE libchdr/deps/lzma-24.05/include)
target_compile_definitions(lzma PRIVATE Z7_ST)

add_library(
  zlib
  STATIC
    libchdr/deps/zlib-1.3.1/adler32.c
    libchdr/deps/zlib-1.3.1/compress.c
    libchdr/deps/zlib-1.3.1/crc32.c
    libchdr/deps/zlib-1.3.1/deflate.c
    libchdr/deps/zlib-1.3.1/infback.c
    libchdr/deps/zlib-1.3.1/inffast.c
    libchdr/deps/zlib-1.3.1/inflate.c
    libchdr/deps/zlib-1.3.1/inftrees.c
    libchdr/deps/zlib-1.3.1/trees.c
    libchdr/deps/zlib-1.3.1/uncompr.c
    libchdr/deps/zlib-1.3.1/zutil.c
)

target_compile_definitions(zlib PRIVATE _LARGEFILE64_SOURCE)

add_library(
  zstd
  STATIC
    libchdr/deps/zstd-1.5.6/lib/common/debug.c
    libchdr/deps/zstd-1.5.6/lib/common/entropy_common.c
    libchdr/deps/zstd-1.5.6/lib/common/error_private.c
    libchdr/deps/zstd-1.5.6/lib/common/fse_decompress.c
    libchdr/deps/zstd-1.5.6/lib/common/pool.c
    libchdr/deps/zstd-1.5.6/lib/common/threading.c
    libchdr/deps/zstd-1.5.6/lib/common/xxhash.c
    libchdr/deps/zstd-1.5.6/lib/common/zstd_common.c
    libchdr/deps/zstd-1.5.6/lib/decompress/huf_decompress.c
    libchdr/deps/zstd-1.5.6/lib/decompress/zstd_ddict.c
    libchdr/deps/zstd-1.5.6/lib/decompress/zstd_decompress.c
    libchdr/deps/zstd-1.5.6/lib/decompress/zstd_decompress_block.c
)

target_compile_definitions(zstd PRIVATE ZSTD_DISABLE_ASM)

list(APPEND CHDR_INCLUDES ${CMAKE_CURRENT_BINARY_DIR}/libchdr/include)

add_library(
  chdr-static
  STATIC
    libchdr/src/libchdr_bitstream.c
    libchdr/src/libchdr_cdrom.c
    libchdr/src/libchdr_chd.c
    libchdr/src/libchdr_flac.c
    libchdr/src/libchdr_huffman.c
)

target_include_directories(chdr-static PRIVATE libchdr/deps/zstd-1.5.6/lib)
target_include_directories(chdr-static PRIVATE libchdr/deps/lzma-24.05/include)

target_include_directories(chdr-static PUBLIC libchdr/include)
target_link_libraries(chdr-static PRIVATE lzma zlib zstd)
target_compile_options(chdr-static PRIVATE
  $<$<CXX_COMPILER_ID:Clang>:-Wno-unreachable-code -Wno-unused-function>
)


add_library(tzxfile STATIC
    TZXFile/TZXAudioGenerator.cpp
    TZXFile/TZXBlock.cpp
    TZXFile/TZXBlockArchiveInfo.cpp
    TZXFile/TZXBlockCustomInfo.cpp
    TZXFile/TZXBlockGroupEnd.cpp
    TZXFile/TZXBlockGroupStart.cpp
    TZXFile/TZXBlockHardwareType.cpp
    TZXFile/TZXBlockLoopEnd.cpp
    TZXFile/TZXBlockLoopStart.cpp
    TZXFile/TZXBlockMessage.cpp
    TZXFile/TZXBlockPause.cpp
    TZXFile/TZXBlockPulseSequence.cpp
    TZXFile/TZXBlockPureData.cpp
    TZXFile/TZXBlockPureTone.cpp
    TZXFile/TZXBlockStandardSpeedData.cpp
    TZXFile/TZXBlockStopTheTape48K.cpp
    TZXFile/TZXBlockTextDescription.cpp
    TZXFile/TZXBlockTurboSpeedData.cpp
    TZXFile/TZXFile.cpp
)

target_include_directories(tzxfile PUBLIC
    ../thirdparty/TZXFile
    )

add_library(ymfm STATIC
    ymfm/src/ymfm_adpcm.cpp
    ymfm/src/ymfm_misc.cpp
    ymfm/src/ymfm_opl.cpp
    ymfm/src/ymfm_opm.cpp
    ymfm/src/ymfm_opn.cpp
    ymfm/src/ymfm_opq.cpp
    ymfm/src/ymfm_opz.cpp
    ymfm/src/ymfm_pcm.cpp
    ymfm/src/ymfm_ssg.cpp
)

target_include_directories(ymfm PUBLIC
    ../thirdparty/ymfm/src
)

target_compile_options(ymfm PRIVATE $<$<CXX_COMPILER_ID:Clang>:-Wno-unreachable-code>)

set_target_properties(ymfm PROPERTIES FOLDER thirdparty PREFIX "")
set_target_properties(tzxfile PROPERTIES FOLDER thirdparty PREFIX "")
set_target_properties(chdr-static PROPERTIES FOLDER thirdparty PREFIX "")
set_target_properties(sljit PROPERTIES FOLDER thirdparty PREFIX "")
set_target_properties(zlib PROPERTIES FOLDER thirdparty PREFIX "")
set_target_properties(lzma PROPERTIES FOLDER thirdparty PREFIX "")
set_target_properties(zstd PROPERTIES FOLDER thirdparty PREFIX "")
