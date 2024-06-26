# Generated by BoostInstall.cmake for boost_coroutine-1.85.0

include(CMakeFindDependencyMacro)

if(NOT boost_assert_FOUND)
  find_dependency(boost_assert 1.85.0 EXACT)
endif()
if(NOT boost_config_FOUND)
  find_dependency(boost_config 1.85.0 EXACT)
endif()
if(NOT boost_context_FOUND)
  find_dependency(boost_context 1.85.0 EXACT)
endif()
if(NOT boost_core_FOUND)
  find_dependency(boost_core 1.85.0 EXACT)
endif()
if(NOT boost_exception_FOUND)
  find_dependency(boost_exception 1.85.0 EXACT)
endif()
if(NOT boost_move_FOUND)
  find_dependency(boost_move 1.85.0 EXACT)
endif()
if(NOT boost_system_FOUND)
  find_dependency(boost_system 1.85.0 EXACT)
endif()
if(NOT boost_throw_exception_FOUND)
  find_dependency(boost_throw_exception 1.85.0 EXACT)
endif()
if(NOT boost_type_traits_FOUND)
  find_dependency(boost_type_traits 1.85.0 EXACT)
endif()
if(NOT boost_utility_FOUND)
  find_dependency(boost_utility 1.85.0 EXACT)
endif()

include("${CMAKE_CURRENT_LIST_DIR}/boost_coroutine-targets.cmake")
