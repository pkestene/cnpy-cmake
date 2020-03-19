# setting CMAKE_SYSTEM_NAME will trigger cmake to
# define variable CMAKE_CROSSCOMPILING and set it true
#
# Please note that valid system names are list in cmake
# sources:
# /usr/share/cmake-3.10/Modules/Platform
#
# For embedded system targets (no OS), it is safe to use
# Generic
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR sparc)

# set target architecture variable
set(MY_CROSS_COMPILE_TARGET sparc-gaisler-elf)

set(CMAKE_C_COMPILER        ${MY_CROSS_COMPILE_TARGET}-gcc)
set(CMAKE_C_COMPILER_TARGET ${MY_CROSS_COMPILE_TARGET})
set(CMAKE_CXX_COMPILER        ${MY_CROSS_COMPILE_TARGET}-g++)
set(CMAKE_CXX_COMPILER_TARGET ${MY_CROSS_COMPILE_TARGET})

# Optionally here setup target specific flags
# or even compiler specific flags (GNU, clang, ...)
