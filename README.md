# JEX OS README

Welcome to **JEX OS**, a custom operating system designed to operate at Ring 0 for low-level programming and system development. This README will guide you through the installation prerequisites and setup instructions.

## Table of Contents
1. [Prerequisites](#prerequisites)
2. [Installation Steps](#installation-steps)
3. [Building JEX OS](#building-jex-os)
4. [Running JEX OS](#running-jex-os)
5. [Contributing](#contributing)
6. [License](#license)

## Prerequisites

Before you can build and run JEX OS, ensure you have the following tools installed on your development machine:

1. **Basic C Build Essentials**: Required for compiling C source files.
   - On Ubuntu/Debian: 
     ```bash
     sudo apt-get install build-essential
     ```

2. **NASM**: An assembler for x86 architecture.
   - On Ubuntu/Debian:
     ```bash
     sudo apt-get install nasm
     ```

3. **QEMU or VirtualBox**: For virtual machine emulation.
   - **QEMU**:
     ```bash
     sudo apt-get install qemu
     ```
   - **VirtualBox**: [Download from the VirtualBox website](https://www.virtualbox.org/).

4. **LD (Linker)**: Used for linking compiled object files.
   - Typically included with build-essential, but can be installed separately if needed.
   - On Ubuntu/Debian:
     ```bash
     sudo apt-get install binutils
     ```

5. **Genisoimage**: For creating ISO images of the OS.
   - On Ubuntu/Debian:
     ```bash
     sudo apt-get install genisoimage
     ```

## Installation Steps

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/username/jex-os.git
   cd jex-os
   ```

2. **Install the Prerequisites** (as mentioned above).

3. **Set Up the Build Environment**: Follow any specific setup instructions in the repository if applicable.

## Building JEX OS

To build JEX OS, run the following command in the project directory:

```bash
make
```

This will compile the necessary files and create an ISO image of the operating system.

## Running JEX OS

You can run JEX OS using either QEMU or VirtualBox.

### Using QEMU

To run JEX OS with QEMU, use the following command:

```bash
qemu-system-x86_64 -cdrom jex.iso
```

### Using VirtualBox

1. Open VirtualBox and create a new virtual machine.
2. Set the type to "Linux" and version to "Other Linux (64-bit)".
3. Allocate memory and create a new virtual hard disk (optional).
4. Under "Storage", add the `jex-os.iso` file as a virtual optical disk.
5. Start the virtual machine.

## Contributing

Contributions are welcome! Please fork the repository and submit a pull request for any enhancements or bug fixes.

## License

This project is licensed under the BSD 3-Clause License. See the [LICENSE](LICENSE) file for details.

---

For any issues or questions, feel free to open an issue in the GitHub repository. Enjoy exploring JEX OS!
