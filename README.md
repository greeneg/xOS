# xOS

An experimental amd64 architecture operating system. See the [Overview](Documentation/Design/Overview.md) for more information about xOS, and its design.

## Layout of This Repository

The GitHub repository of xOS is laid out as follows:

```
 /build
 /Documentation
 /kernel
 /utils
```

### The `build` Directory

This part of the repository is used to build test ISOs or bootable test images of the operating system.

### The `Documentation` Directory

This directory contains all the design and operational documentation of xOS. Eventually, it will include the man pages and HTML documentation for the OS

### The `kernel` Directory

This directory contains all the sources, Makefiles, and README files for the core of the xOS operating system, `kernel.exe` and the driver servers that are spawned by it, including the `vfs.daemon`, `namespace.daemon`, etc.

### The `libraries` Diretory

This directory contains all the user-land libraries bundled with xOS.

### The `utils` Directory

This directory contains all the user-land utilities bundled with xOS. These include the typical UNIX utilities `ls`, `cp`, etc. along with operating system specific tools, like `namespacectl`, `mountctl`, etc.

### A Note About the `3rd-Party` Sub-Directories

The code of the xOS operating system itself, is under the GNU Lesser General Public License version 2.1, and each component that is developed by YggdrasilSoft will have a LICENSE file in the component sub-directory with the terms of the LGPL v2.1.

However, in the `library` and `utils` directories, a `3rd-Party` subdirectory exists that contains libraries or utilities that are NOT developed by YggdrasilSoft, and may be under stricter or more permissive licenses, such as the GPL v3 or the BSD or MIT licenses. These components are included to extend the functionality of the operating system.

When modifying or redistributing these components, please adhere to the spirit and letter of their respective licenses.

## Building the Software

The xOS operating system is a complete system including the kernel, libraries, and utilities. Each component has a Makefile in the component's source tree. Each Makefile contains the following targets:

- make: build the binary
- make brinstall: install the binary inside the `build/amd64/` tree
- make bootimage: generate a bootable image for use with Qemu's `qemu-system-x86_64` tool
- make clean: clear out compiled artifacts from the source tree

To build any component, in a terminal, enter the component's directory and issue the following commands to build and install the component into the build tree:

```sh
make && make brinstall
```

To test it out, use the `make bootimage` target to create a Qemu compatible boot image.
