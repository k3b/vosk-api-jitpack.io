# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.10.2)

# Declares and names the project.

project("hello_cmake2")

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library.
             native-lib

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             native-lib.cpp )

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
                       native-lib

                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib} )
#-----------------------------------------------------

if(true)
    # parameter from build-vosk.sh
    # make -C OpenBLAS TARGET=... ONLY_CBLAS=1 AR=$AR CC=$CC HOSTCC=gcc ARM_SOFTFP_ABI=1 USE_THREAD=0 NUM_THREADS=1 -j4
    set(ONLY_CBLAS 1)
    set(HOSTCC gcc)
    set(ARM_SOFTFP_ABI 1)
    set(USE_THREAD 0)
    set(NUM_THREADS 1)
    if(${ANDROID_ABI} STREQUAL "armeabi-v7a")
        set(TARGET ARMV7)
        set(AR arm-linux-androideabi-ar)
        set(HOST arm-linux-androideabi)
        set(CC armv7a-linux-androideabi21-clang)
        set(CXX armv7a-linux-androideabi21-clang++)
        set(ARCHFLAGS "-mfloat-abi=softfp -mfpu=neon")
    endif()
    if(${ANDROID_ABI} STREQUAL "arm64-v8a")
        set(TARGET ARMV8)
        set(HOST aarch64-linux-android)
        set(AR aarch64-linux-android-ar)
        set(CC aarch64-linux-android21-clang)
        set(CXX aarch64-linux-android21-clang++)
        set(ARCHFLAGS "")
    endif()
    if(${ANDROID_ABI} STREQUAL "x86_64")
        set(TARGET ATOM)
        set(HOST x86_64-linux-android)
        set(AR x86_64-linux-android-ar)
        set(CC x86_64-linux-android21-clang)
        set(CXX x86_64-linux-android21-clang++)
        set(ARCHFLAGS "")
    endif()
    if(${ANDROID_ABI} STREQUAL "x86")
        set(TARGET ATOM)
        set(HOST i686-linux-android)
        set(AR i686-linux-android-ar)
        set(CC i686-linux-android21-clang)
        set(CXX i686-linux-android21-clang++)
        set(ARCHFLAGS "")
    endif()

    set( prj_root_dir ../../..)
            # message(FATAL_ERROR "hello world ")
    # Sets lib_src_DIR to the path of the target CMake project.
    set( lib_src_DIR "${prj_root_dir}/cloned-repositories/OpenBLAS" )


    # Sets lib_build_DIR to the path of the desired output directory.
    set( lib_build_DIR "${lib_src_DIR}/build/OpenBLAS/${ANDROID_ABI}" )
    file(MAKE_DIRECTORY ${lib_build_DIR})

    message(AUTHOR_WARNING "lib_src_DIR=${lib_src_DIR} ")
    message(AUTHOR_WARNING "lib_build_DIR=${lib_build_DIR}")
    set(PROJECT_BINARY_DIR ${lib_build_DIR})
    message(AUTHOR_WARNING "PROJECT_BINARY_DIR=${PROJECT_BINARY_DIR}")

    # Adds the CMakeLists.txt file located in the specified directory
    # as a build dependency.
    add_subdirectory( # Specifies the directory of the CMakeLists.txt file.
            ${lib_src_DIR}

            # Specifies the directory for the build outputs.
            ${lib_build_DIR} )

    # Adds the output of the additional CMake build as a prebuilt static
    # library and names it lib_gmath.
    add_library( lib_gmath STATIC IMPORTED )
    set_target_properties( lib_gmath PROPERTIES IMPORTED_LOCATION
            ${lib_build_DIR}/${ANDROID_ABI}/lib_gmath.a )
    include_directories( ${lib_src_DIR}/include )

    # Links the top-level CMake build output against lib_gmath.
    target_link_libraries( native-lib ... lib_gmath )
endif()
