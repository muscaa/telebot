import platform

WINDOWS = "windows"
LINUX = "linux"
MACOS = "macos"

_system = platform.system().lower()
if _system == "windows":
    SYSTEM = WINDOWS
    EXT = ".exe"
    LIB_EXT = ".dll"
    VCPKG_TRIPLET = "x64-windows-release"
elif _system == "linux":
    SYSTEM = LINUX
    EXT = ""
    LIB_EXT = ".so"
    VCPKG_TRIPLET = "x64-linux-release"
elif _system == "darwin":
    SYSTEM = MACOS
    EXT = ""
    LIB_EXT = ".dylib"
    VCPKG_TRIPLET = "x64-osx-release"
else:
    SYSTEM = "unknown"
    EXT = ".unknown"
    LIB_EXT = ".unknown"
    VCPKG_TRIPLET = "unknown"

X64 = "x64"
ARM64 = "arm64"

_arch = platform.machine().lower()
if _arch in ("x86_64", "amd64"):
    ARCH = X64
elif _arch in ("arm64", "aarch64"):
    ARCH = ARM64
else:
    ARCH = "unknown"
