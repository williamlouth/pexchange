# Generated by BoostInstall.cmake for boost_compat-1.85.0

include(CMakeFindDependencyMacro)

if(NOT boost_assert_FOUND)
  find_dependency(boost_assert 1.85.0 EXACT)
endif()

include("${CMAKE_CURRENT_LIST_DIR}/boost_compat-targets.cmake")
