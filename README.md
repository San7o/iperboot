# iperboot

A flexible bootloader.

The idea it to write a small bootloader which can boot literally *everywhere*,
and new targets can be added easily. This project builds upon my previous work
on the following projects:

- [povOS](https://github.com/San7o/povOS/tree/main/bootloader/x86_64)
- [rpi3b-OS](https://github.com/San7o/rpi3b-os)
- [hello-efi](https://github.com/San7o/hello-efi)

## Design

To make the bootloader work with multiple platforms and load many operating
systems, we need to design several abstractions:

- backend: the code that gets executed right after the firmware
- core: the internal API exposed by the backend and used by the frontend, and
  common code
- frontend: the frontend sets up the CPU in a well defined state for the OS.
  This is the API that is presented to the OS, and it must be architecture
  specific.

![boot-diagram](./boot-diagram.png)

This project also provides a fully custom frontend API,
[iperboot-protocol](./frontend/iperboot/README.md), inspired by multiboot and
Linux's boot protocol.

## Usage

```
git clone --recurse-submodules https://github.com/San7o/iperboot.git
cd iperboot
make
```
