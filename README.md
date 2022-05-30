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

### The `utils` Directory

This directory contains all the user-land utilities bundled with xOS. These include the typical UNIX utilities `ls`, `cp`, etc. along with operating system specific tools, like `namespacectl`, `mountctl`, etc.

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
