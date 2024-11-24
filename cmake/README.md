# *ares* Build System Documentation

This document provides an overview of the general design and structure behind ares's CMake build system generator.

At a high level, all CMake code directly related to internal build system considerations (compiler/architecture configuration, project generation, dependency management, code signing, app bundling and installation) lives in this `cmake` folder. The tree of files that manage this functionality all branch off of `common/bootstrap.cmake` into various OS-specific and common files.

CMake code related to the actual generation and building of specific ares components lives in the CMakeLists.txt for each target, as well as auxiliary and OS-specific files for those targets where necessary.

Broadly, we try to conform to "modern CMake" best practices. There are plentiful resources on this subject; [An Introduction to Modern CMake](https://cliutils.gitlab.io/modern-cmake/README.html) is a good starting point. The primary philosophy behind these resources is that the build system code should be as modular and platform-agnostic as possible. Everything should be implemented as a target, and the build system's job is to describe and structure the relationships between these targets in a sound and logical way. `nall`'s Makefile this is not!

# Structure

> [!NOTE]
> When discussing this build system, we will refer to all components of ares (`nall`, `ruby`, `hiro`, etc.) as targets. Dependencies such as SDL and librashader are also targets, as are all of ruby's drivers and backends, and the UI frontends.

Broadly, there are three main important components to ares's build system:

* The target-level build code that defines sources, compile options, and link relationships.
* The recursive dependency resolver
* The platform-specific helper functions that deal with these dependencies appropriately

Our target-level build code is the "meat and potatoes" of ares's build sytem. It defines all of the relationships between our targets; what depends on what; which sources are to be compiled; what definitions does the code need in order to compile successfully; what information does the linker need to link our targets together; etc.

The recursive dependency resolver and the platform helper functions, meanwhile, are the "secret sauce" responsible for turning this structured web of relationships into functional applications that we can actually run on our supported platforms.

Taking the main `desktop-ui` target, as an example, our target-level build code will handle things like:

* `desktop-ui` needs to be statically linked directly with `hiro`'s `hiro.a`, because `hiro` contains all of the functions needed to create the UI
* `hiro` itself also depends on specific libraries depending on which UI backend it is using; add these backend libraries to the linker command for `desktop-ui` so hiro can be linked correctly.
* We're linking against the `nall` target, which creates an interface compile definition for our specific target platform; make sure `PLATFORM_MACOS` is defined in *all* of our targets since we're transitively linking against `nall`.

This target-level build code is generally enough to compile and link our targets successfully. At this point, the rest of our build system has the responsibility of constructing runnable applications out of the executables, libraries and data that we've assembled. This task is performed by platform-specific helper functions defined in `helpers.cmake`. On each platform, these functions have to consider problems such as:

* `desktop-ui` ultimately depends on a dozen libraries; which of these are system libraries, and which need to be bundled along with the ares executable to create a functional rundir or app bundle?
* On macOS, `ares` depends on MoltenVK, but only if we're building the N64 core and if MoltenVK is available; only consider it if these conditions are met.
* The final products of the build on macOS, Windows and Linux have very different directory structures; arrange the products appropriately depending on platform.
* Miscellaneous platform-specific concerns like code signing on macOS and library `rpath`s on Linux and macOS; Win32 binary designations on Windows.

The only way to handle these problems effectively and correctly (considering all platforms) is to recursively crawl the entire tree of dependencies for our targets and consider for each one what the appropriate course is with our final build product in mind. The complexity of this code means that it makes up a non-trivial portion of the build system. However, these parts are quite important, as they enable our target-level build code to be completely platform-agnostic and unconcerned with the details of packaging and bundle construction. If we need to bundle another library, it's a simple matter of defining it and linking it to the appropriate target, and then letting the build system handle the rest.

> [!NOTE]
> This overview simplifies or omits certain CMake and platform implementation details to deliver a more concise overview of the build system. For the nitty-gritty of why all of this is actually necessary, see [Dependencies.md].

# Further Documentation

## Supported link expressions

ares needs to assemble a complete tree of dependencies ad-hoc as part of the configuration process. It does this by checking the linked libraries and interface linked libraries of each target recursively and building a set. Because we can link libraries using CMake [generator expressions], the potential complexity of deriving a CMake target from a link expression can be very high. As such, some restrained usage of the `target_link_libraries` command is required. For targets that require special consideration by the dependency resolver (generally, this is any library bundled with ares), the following link expressions are supported:

[$<LINK_LIBRARY:<link-type>,<target>]

This generator expression specifies a link method; it is used to link to system-level Framework targets on macOS, as well as weakly linking library targets on macOS.

[$<$<BOOL:<bool>>:<target>]

The standard boolean generator expression; commonly used to link a target conditionally if the package for it has been located successfully.

[$<PLATFORM_ID:<platform>>:<target>] or [$<NOT:$<PLATFORM_ID:<platform>>:<target>>]

Generator expression used to link a library conditionally depending on target platform.

Other generator expressions may be used freely when linking if they do not require consideration by platform functions.

## In-source builds

ares does not support in-tree builds, because they contaminate the source tree and make cleanup difficult/infeasible. Trying to build in-source will result in configuration aborting. Always invoke CMake either from within or while specifying a build directory.

"Exceptions" to this principle include:

* `sourcery`'s generated `resource.cpp` and `resource.hpp` files
* The Qt UI's Meta-Object Compiler output
* Compiled shaders in the Metal backend

All of these files, however, are not tracked by the project. Any future generated source code or intermediate output that must live in-tree should be similarly added to the project `.gitignore`.

## Source file enumeration

A significant bulk of ares build system code by line count is devoted to enumerating source files. 

In principle, enumerating source files in CMake is the appropriate course of action (rather than "`GLOB`bing" them) to ensure build consistency, better tracking of file additions and subtractions, and to allow CMake to automatically detect changes in source files.

ares adds another small degree of complexity here. Since many targets in ares use a "top-down" structure, where only a top-level file is directly compiled, which then `#include`s the tree of source files beneath it, we have to explicitly declare all of these included files, unintuitively, as headers. This is so that the build system will not attempt to compile them directly.

> [!NOTE]
> "Intellisense" in Visual Studio is largely broken when used with ares, because it attempts to compile any `.cpp` file directly, even though ares treats many `.cpp` files as headers. It also has issues with unintuitive namespacing patterns that are common in ares.

> [!NOTE]
> We currently force CMake to suppress automatic build system regeneration, because our build process refreshes the contents of our generated `sourcery` sources, which then trips CMake's detection that our file contents have changed, excessively regenerating the entire build system on every build. Better `sourcery` behavior may be a "good first issue" when working on this build system.

## ares-deps

ares's build system pulls in some precompiled dependencies on macOS and Windows for libraries that have significant toolchain requirements or are otherwise cumbersome to build locally. Complete documentation on this subject is available in the [ares-deps] article.

## Compiler diagnostics

Compiler strictness requirements are a moving target in ares. The legacy build system does not compile ares particularly strictly, and improving code quality by mandating stricter requirements is a work in progress. Since GCC, Clang, AppleClang, and MSVC are all supported compilers for ares, finding something resembling parity in diagnostic flags between all compilers is a significant challenge. Each platform has a `compilerconfig.cmake` file that defines the diagnostic flags for supported compilers on that platform. TODO: More detail on strictness goals.

## Ccache

ares supports Ccache universally to increase compiler performance and lower compile times for successive builds of ares. The basic logic for this is located in `ccache.cmake` with extra logic present in `xcode.cmake` or Windows's `compilerconfig.cmake` for special handling in Visual Studio or Xcode.

## Precompiled headers

The `ares` target in the project includes the `ares/ares.hpp` header many times. By precompiling this header, we can significantly speed up ares's compile time. Since CMake makes supporting header precompilation fairly simple, we precompile the `ares.hpp` header when possible.

Header precompilation is currently disabled by default on Windows because the inclusion of generated `resource.hpp` files causes problems on successive builds when our resource files `mtime`s have a mismatch.
