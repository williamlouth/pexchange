# Generated by BoostInstall.cmake for boost_charconv-1.85.0

include(CMakeFindDependencyMacro)

if(NOT boost_config_FOUND)
  find_dependency(boost_config 1.85.0 EXACT)
endif()
if(NOT boost_assert_FOUND)
  find_dependency(boost_assert 1.85.0 EXACT)
endif()
if(NOT boost_core_FOUND)
  find_dependency(boost_core 1.85.0 EXACT)
endif()

include("${CMAKE_CURRENT_LIST_DIR}/boost_charconv-targets.cmake")
