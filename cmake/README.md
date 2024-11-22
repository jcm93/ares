### *ares* Build System

This document provides an overview of the general design and structure behind ares's CMake build system generator.

At a high level, all CMake code directly related to internal build system considerations (compiler/architecture configuration, project generation, dependency management, code signing, app bundling and installation) lives in this `cmake` folder. The tree of files that manage this functionality all branch off of `common/bootstrap.cmake` into various OS-specific and common files.

CMake code related to the actual generation and building of specific ares components lives in the CMakeLists.txt for each target, as well as auxiliary and OS-specific files for those targets where necessary.

Broadly, we try to conform to "modern CMake" best practices. There are plentiful resources on this subject; [An Introduction to Modern CMake](https://cliutils.gitlab.io/modern-cmake/README.html) is a good starting point. The primary philosophy behind these resources is that the build system code should be as modular and platform-agnostic as possible. Everything should be implemented as a target, and the build system's job is to describe and structure the relationships between these targets in a sound and logical way. `nall`'s Makefile this is not!

### Structure

> [!NOTE]
> When discussing this build system, we will refer to all components of ares (`nall`, `ruby`, `hiro`, etc.) as targets. Dependencies such as SDL and librashader are also targets, as are all of ruby's drivers and backends, and the UI frontends.

Broadly, there are three main important components to ares's build system:

* The target-level build code that defines sources, compile options, and link relationships.
* The recursive dependency resolver
* The platform-specific helper functions that deal with these dependencies appropriately

Our target-level build code is the "meat and potatoes" of ares's build sytem. It defines all of the relationships between our targets; what depends on what; which sources are to be compiled; what definitions does the code need in order to compile successfully; what information does the linker need to link our targets together; etc.

The recursive dependency resolver and the platform helper functions, meanwhile, are the "secret sauce" responsible for turning this structured web of relationships into functional applications that we can actually run on our supported platforms.

Taking the main `desktop-ui` target, as an example, our target-level build code will handle things like:

* `desktop-ui` needs to be statically linked directly with `hiro`'s `hiro.a`, because `hiro.a` contains all of the functions needed to create the UI
* `hiro` itself also depends on specific libraries depending on its UI backend; add these to the linker command for `desktop-ui` so hiro can be linked correctly.
* We're linking against the `nall` target, which creates an interface compile definition for our platform; make sure `PLATFORM_MACOS` is defined in *all* of our targets since we're transitively linking against `nall`'!

The recursive dependency resolver and platform helper functions then take over to handle such problems as:

* `desktop-ui` ultimately depends on a dozen libraries; which of these are system libraries, and which need to be bundled along with the ares executable to create a function rundir or app bundle?
* `ares` depends on MoltenVK on macOS, but only if we're building the N64 core and if MoltenVK is available; only consider it if these conditions are met.
* The final products of the build on macOS, Windows and Linux have radically different directory structures; arrange the products appropriately depending on platform

Unfortunately, the only way to handle these problems effectively and correctly (considering all platforms) is to recursively crawl the entire tree of dependencies for our targets and consider for each one what the appropriate course is with our final build product in mind.

The complexity of this code means that it makes up a non-trivial portion of the build system. However, these parts are quite important, as they enable our target-level build code to be completely platform-agnostic and unconcerned with the details of packaging and bundle construction. If we need to bundle another library, it's a simple matter of defining it and linking it to the appropriate target, so that the build system may handle the rest.

> [!NOTE]
> This overview simplifies or omits certain CMake and platform implementation details to deliver a more concise overview of the build system. For the nitty-gritty of why all of this is actually necessary, see [Dependencies.md].
