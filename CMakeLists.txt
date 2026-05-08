cmake_minimum_required(VERSION 3.16...3.21)
project(MSCScattering LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Geant4 package
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

# Setup Geant4 include directories and compile definitions
include(${Geant4_USE_FILE})

# Locate sources and headers for this project
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
file(GLOB sources ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hh)

# Add the executable
add_executable(mscScattering mscScattering.cc ${sources} ${headers})
target_link_libraries(mscScattering ${Geant4_LIBRARIES})

# Copy all scripts to the build directory
set(MSCSCATTERING_SCRIPTS
  init_vis.mac
  run.mac
  vis.mac
  )

foreach(_script ${MSCSCATTERING_SCRIPTS})
  configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/${_script}
    ${CMAKE_CURRENT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()
