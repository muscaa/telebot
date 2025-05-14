# VCPKG packages
find_package(SDL3 CONFIG REQUIRED)
find_package(Stb REQUIRED)
find_package(libzippp CONFIG REQUIRED)
find_package(Boost REQUIRED COMPONENTS
    system
    dll
    json
)
