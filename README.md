# xOS

An experimental amd64 architecture operating system

## Introduction

This code originally started life as a fork of [David Callanan's os-series simple kernel](https://github.com/davidcallanan/os-series). While working through the example code, the idea started to coalesce in my head to write a simple 64-bit operating system on amd64 (x86_64) to tinker with as a study guide to low level concepts, like hardware interaction, device driver implementation, filesystem design and other concepts, along with really sitting down and learning the C programming language (and a smattering of Assembly).

XOS isn't aiming at cloning UNIX, or Windows, or any other OS, really. It's aim is to teach and maybe along the way, create something new for others that want to learn along with me.

Primary features:
- 64-bit: Very early in boot, xOS transitions to 64-bit instructions, so low-level 8 or 16-bit code is unable to be used
- Namespaces: All pathing and subsystems will be accessible via Namespaces
- Namespace Aliasing: Namespaces can have aliases assigned to them
- Single-tasking (for now): While Pre-emptive Multitasking would be preferred, being a simple OS, xOS will start with a very rudimentary process model to learn from and extend as xOS is further developed
- Single-seat Multiuser: In the beginning, xOS won't have network login support, nor multiplexing teletype-like terminals, simplifying the user model to allowing only one user to login at a time

## What Will xOS' Runtime Be like

Something new, likely.

The aim is to add ideas from various systems, and see how they work, or don't, together. The world has Linux for a UNIX clone, not to mention the various *BSD UNIX OS' that are fully open, free, and are real UNIX systems. There are other OS' that clone other platforms, like Haiku (BeOS), MorphOS (AmigaOS), ReactOS (Windows), and there's also FreeDOS for those that want to work with 16-bit OS code. That said, let's try some "new" ideas.

The system aims to be console only for now, so no graphical desktops like KDE Plasma or GNOME. The command pallet will have similarities to GNU-like environments, with `ls`, `cd`, etc. as commands, where things start differing from Linux and other Unix-like platforms is the lack of a single root heirarchy, using "Namespaces" and "Namespace Aliases" instead.

## What Are Namespaces?

Namespaces are how a user accesses different storage, network, or virtual location in xOS. Akin to DOS-like operating systems, Namespaces are distinguished by a prefix, like `<NAMESPACE>://`. Unlike DOS-like systems, however, the separators are not backslashes, rather like Unix-like systems, it is the forward-slash. An example of namespaces:

- namespaces://devices
- devices://disks
- disks://0/1
- network://localhost/
- printers://MyExamplePrinter
- processes://0/cmdline

As likely surmised, all Namespaces except for the `namespaces://` root are really Namespace Aliases.

### Namespace Aliases

As shown earlier, all other Namespaces, except the root `namespaces://`, are actually Namespace Aliases. Namespace Aliases make accessing and organizing Namespaces more easy to understand for a user of the system. There are two types of Namespace Aliases, system-defined and user-defined.

System-defined Namespace Aliases are the ones that are stood up by xOS' kernel, and cannot be unallocated, nor overriden by users of the system. In the current design, these are:

- devices: a hierarchy of files to interact with the devices on the system, akin to the `/dev` tree on UNIX and Unix-like systems
- diskN: where N is a number from 0 to however many disk partitions are present in the system. This is derived from the `disks` paths. The allocation of N is discussed later, in regards to systems with multiple storage devices attached to it
- disks: The hierarchy of disks and their partitions allotted on the system. This is derived from the `devices://disks` path
- netdisks: The hierarchy of mounted externally accessible storage media. This is derived from the `network://$HOST/$PROTOCOL/example_shared_volume` path, and is only available if network hardware is present and started on mounting network storage
- network: a 'Network Neighborhood` alike, that is accessible easily from command line. This location is only available if network hardware is present and started. Items under this Namespace Alias are defined by periodic network probes to create virtual directories under this location
- printers: a virtual location of printers that can be interacted with via the command line. This location is only available if printing hardware is present and configured
- processes: a virtual location that exports the system process table as directories and files describing a process being run, including it's command-line flags, etc. Akin to the Linux `/proc` filesystem
- rootfs: the Namespace Alias for the primary mounted filesystem specified on the kernel command line

User defined aliases are Namespace Aliases that a user of the system defines using the `namespacectl` command to make access to a location easier to traverse to. For example, if a user is normally used to having their primary OS disk called `C://`, they can do so using an alias to the `rootfs://` Namespace Alias, which in cases where xOS is installed as the only operating system, would be another alias to `devices://disks/0/1`, and is ultimately an alias that points to `namespaces://devices/disks/0/1`.

```sh
namespacectl mkalias rootfs: c:
```

User defined aliases can only be defined as a one-to-one mapping from alias to a storage location.

### Mounting a Namespace Alias Path to a Directory

Additionally, to allow ease of use, Namespace Aliaes and a path underneath them can be mounted to a directory, like UNIX and Unix-like systems using the `mountctl` command:

```sh
mountctl --mount disk1: rootfs://example_directory
```

