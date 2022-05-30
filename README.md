# xOS

An experimental amd64 architecture operating system. See the [Overview](Documentation/Design/Overview.md) for more information about xOS, and its design.

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
