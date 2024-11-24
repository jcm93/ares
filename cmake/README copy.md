# ares-deps

To make it easier to get started with ares development, ares's build system will pull in some precompiled dependencies when generating the build system on macOS and Windows. These include:

* [librashader](https://github.com/SnowflakePowered/librashader)
* [MoltenVK](https://github.com/KhronosGroup/MoltenVK)
* [SDL](https://github.com/libsdl-org/SDL/tree/SDL2)
* [slang-shaders](https://github.com/libretro/slang-shaders)

Precompiling these dependencies is done for a few reasons. Primarily, it is for the convenience of getting started with a fresh ares development environment; it is somewhat cumbersome to require an entire Rust toolchain on all platforms and the extensive set of SPIR-V dependencies on macOS when nothing in ares itself uses them directly.

In order to exercise control over these prebuilt dependencies, and offer some degree of attestation for their builds, we use a dedicated repository [ares-deps] to build them. This is a small collection of shell scripts that configures, optionally patches, builds, and packages our dependency libraries for all applicable platforms and architectures.

After building, the dependencies are hashed and uploaded. When the primary ares repository pulls them in, we use the checksums to verify their integrity.

### Linux
On Linux, we do not try to provide prebuilt library dependencies. The general expectation on \*nix is that dependencies should be handled by the user's package manager, and due to the wide variety of distributions, it would be exceedingly complex to try to provide prebuilt dependencies for Linux in an appropriate way. That said, ares-deps does provide the librashader header on Linux, as this header is required to compile ares. We also offer the optional data dependency slang-shaders, because of the lack of upstream packaging currently available for this dependency.
