## Development Setup

ColossOS is currently built on Windows using **MSYS2**.

### 1. Install MSYS2

Install MSYS2, then open the **MSYS2 MSYS** shell.

### 2. Clone the repository

```bash
git clone <repository-url>
cd ColossOS
```

### 3. Run the setup script

```bash
chmod +x setup.sh
./setup.sh
```

The script installs the required development tools:

* NASM
* Make and build utilities
* QEMU
* GCC/Binutils build dependencies

It also builds and installs the `i686-elf` cross-toolchain used to compile the kernel.

> The first setup may take several minutes because GCC and Binutils are compiled from source.

### 4. Build and run

Restart the MSYS2 MSYS shell (or run `source ~/.bashrc`), then:

```bash
cd /c/path/to/ColossOS
make run
```

After the initial setup, normal development only requires:

```bash
make run
```
