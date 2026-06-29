find_package(Eigen3 REQUIRED NO_MODULE)
find_package(Threads REQUIRED)
if (USE_SYS_SPDLOG)
  find_package(spdlog REQUIRED)
endif ()

add_library(xmSigma STATIC
    logging/src/ctrl_logger.cpp
    logging/src/default_logger.cpp
    logging/src/logger_vendor_spdlog.cpp)
target_include_directories(xmSigma PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/logging/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/types/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE logging/src)
target_link_libraries(xmSigma PUBLIC Eigen3::Eigen Threads::Threads)
if (ENABLE_LOGGING)
  target_compile_definitions(xmSigma PUBLIC ENABLE_LOGGING)
endif ()
if (USE_SYS_SPDLOG)
  target_link_libraries(xmSigma PUBLIC spdlog::spdlog)
else ()
  target_link_libraries(xmSigma PUBLIC spdlog)
endif ()
add_library(xmotion::xmSigma ALIAS xmSigma)

install(TARGETS xmSigma EXPORT xmSigmaTargets
    LIBRARY DESTINATION lib ARCHIVE DESTINATION lib RUNTIME DESTINATION bin
    INCLUDES DESTINATION include)
install(DIRECTORY logging/include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(DIRECTORY types/include/   DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

if (BUILD_TESTS)
  add_subdirectory(logging/test)
endif ()
if (BUILD_EXAMPLES OR XMOTION_DEV_MODE)
  add_subdirectory(logging/examples)
endif ()
