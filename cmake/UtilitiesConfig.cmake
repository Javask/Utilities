include(GNUInstallDirs)


install(TARGETS Utilities
    EXPORT Utilities-export
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(EXPORT Utilities-targets
  FILE
  UtilitiesTargets.cmake
  NAMESPACE
  Utilities::
  DESTINATION
    ${CMAKE_INSTALL_LIBDIR}/cmake/Utilities
)

get_filename_component(Utilities_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
include(CMakeFindDependencyMacro)

if(NOT TARGET Utilities::Utilities)
    include("${Utilities_CMAKE_DIR}/UtilitiesTargets.cmake")
endif()