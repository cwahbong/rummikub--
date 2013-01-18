FUNCTION(ADD_GTEST_TEST target_name)

  ExternalProject_Get_Property(googletest source_dir)
  INCLUDE_DIRECTORIES(${source_dir}/include)

  ADD_EXECUTABLE(${target_name}Test ${ARGN})

  ExternalProject_Get_Property(googletest binary_dir)
  TARGET_LINK_LIBRARIES(${target_name}Test
    ${binary_dir}/${CMAKE_STATIC_LIBRARY_PREFIX}gtest_main${CMAKE_STATIC_LIBRARY_SUFFIX}
    ${binary_dir}/${CMAKE_STATIC_LIBRARY_PREFIX}gtest${CMAKE_STATIC_LIBRARY_SUFFIX}
    pthread
  )

  ADD_TEST(${target_name}Test ${target_name}Test)

ENDFUNCTION()

