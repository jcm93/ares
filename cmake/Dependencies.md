# Dependencies

This document provides an extensive overview of how dependencies work in the ares build system with a little bit of overall contextual information about dependencies in CMake in general.

## The Link Interface

In modern CMake, each independent component of the build system is meant to be thought of as a target. For ares, this means `hiro`, `nall`, `ruby`, etc. all constitute different CMake targets underneath the `ares` namespace. We might link two targets together like so:
```cmake
target_link_libraries(ares::hiro PRIVATE ares::nall)
```
By doing this, we have created a *dependency* of hiro on `nall`. Thus when building `hiro`, CMake will know that the build system needs to build `nall` as well, plus that the two libraries need to be linked by the linker, and so it will pass that information on to the chosen build system at configure time.

> [!IMPORTANT]  
> Not only will `hiro` link against `nall`, it will also become aware of any `PUBLIC` OR `INTERFACE` properties in nall. For example, we might have the following properties:
> ```cmake
> target_compile_definitions(ares::nall PUBLIC PLATFORM_MACOS)
> target_compile_definitions(ares::nall INTERFACE USING_NALL)
> ```
> If a property on a linked target is declared `PUBLIC` or `INTERFACE`, then any targets that link to it have those properties propagated to them. So `hiro` will have both `PLATFORM_MACOS` and `USING_NALL` defined.

CMake will also automatically create a dependency graph, and recognize transitive dependencies. Later on in the `ares` build process, we link the `desktop-ui` target to `hiro` with `target_link_libraries(ares::desktop-ui PRIVATE ares::hiro)`. The magic here is that `desktop-ui` does not need to care about `nall` at all; rather, all we need to do is establish the logical relationship between `desktop-ui` and `hiro` and CMake will do the rest, informing the build system that it needs to link `nall` in the final output. Furthermore, all `INTERFACE` and `PUBLIC` properties in nall are further propagated to `desktop-ui` automatically.

> [!NOTE]
> A property declared as `PRIVATE` under target `our_target` is known only to `our_target`. A property marked `PUBLIC` will be propagated to any target that either directly or transitively links against `our_target`. A property declared `INTERFACE` will be known to all targets that directly or transitively link against `our_target`, but not to `our_target` itself.

The same logic applies for dependencies outside of the ares tree. A dependency is just another target. Depending on how `ares` is configured, `ruby` and `hiro` may depend on a number of different libraries; some of these may be built-in system libraries, while others such as librashader or SDL may need to come from a package manager or be otherwise supplied by the user. In either case, CMake needs to locate these dependencies' libraries, headers, version information, and any information required successfully link against them when building our final product.

In an ideal world, this would be as simple as calling `find_package(SDL)` and then, if it's found, linking our target against `SDL`. However, we do not live in an ideal world! In fact, the world is so un-ideal that we will sometimes find ourselves having to construct a CMake Find Module.

## FindHelp.cmake

In locating a dependency, a build system generally needs to know four important things about that dependency to be certain that it can link with it correctly:

* The library's binary file locations and names (possibly not all in the same directory)
* All of the library's relevant header files locations (often not all in the same directory)
* Any compile options required to compile the library's headers.
* Version information, so we know if we're looking at a version of the library that we are actually able to build with.

Our problem is that we need to have logic that can find all of that information, on every platform (macOS, Windows, Linux broadly). Between all of these platforms, for any particular dependency, this information might be found approximately literally anywhere.

CMake tries to wrest order from disorder with the `find_package` command. This command takes a package name as a single argument, and is intended to provide you in return with a CMake target that implicitly contains all of this information.

At this point, it gets somewhat complicated. On Linux, there is a tool that roughly serves this purpose, `pkg-config`, which may be queried from within CMake to find compile and linker flags information for a particular library. CMake also provides comands such as `find_path`, `find_library`, and `find_package_handle_standard_args`, that make up a complicated platform-dependent toolset that can makes educated guesses about where a library may be found. 

> [!NOTE]
> CMake recognizes two distinct modes of operation for locating dependencies with `find_package`; Config and Module mode. In Config mode, the default, CMake will scour the system for a "Config module" for a particular package. A Config module is meant to be provided by the upstream package to your particular platform. Unfortunately, Config modules often do not exist for packages on every platform, and we cannot guarantee their existence. In rare cases, they can even be defined in a way that doesn't conform with our usage requirements (foreshadowing). The fallback mode is the Find Module.
> A CMake Find module is provided by the downstream consumer of the package (us), and is meant to supply all logic necessary to determine if a package exists on the system and, if it does, what we need in order to build against it (the four sets of information above).

The main point is, after locating the information we need for each dependency, we need to create a CMake target for our package. Once we have this target, we can define various `PUBLIC` or `INTERFACE` properties on it in order to propagate include directories and compile definitions to targets that depend on it.

By creating a CMake target with the proper set of public or interface properties, we have made the job of the build system dramatically easier. In ares, if we have an appropriately created package target, all we need to do is link against it, and all include directories, compile definitions and version information are automatically propagated to the build system.

Being able to find these libraries in order to build ares is all well and good. Unfortunately, the fact that we also need to be able to run ares makes the situation more complicated. Not all libraries are system libraries, and on non-Linux platforms, it's not reasonable to ask users to install a bunch of libraries before they try to run ares. Just because a dependency is here at build-time, does not mean it's going to be on a user's machine. That means that, in some cases, on some platforms, we will need to package some libraries along with ares.

### Pre-built Suffering
