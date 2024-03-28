# Generated by BoostInstall.cmake for boost_iostreams-1.85.0

include(CMakeFindDependencyMacro)

if(NOT boost_assert_FOUND)
  find_dependency(boost_assert 1.85.0 EXACT)
endif()
if(NOT boost_config_FOUND)
  find_dependency(boost_config 1.85.0 EXACT)
endif()
if(NOT boost_core_FOUND)
  find_dependency(boost_core 1.85.0 EXACT)
endif()
if(NOT boost_detail_FOUND)
  find_dependency(boost_detail 1.85.0 EXACT)
endif()
if(NOT boost_function_FOUND)
  find_dependency(boost_function 1.85.0 EXACT)
endif()
if(NOT boost_integer_FOUND)
  find_dependency(boost_integer 1.85.0 EXACT)
endif()
if(NOT boost_iterator_FOUND)
  find_dependency(boost_iterator 1.85.0 EXACT)
endif()
if(NOT boost_mpl_FOUND)
  find_dependency(boost_mpl 1.85.0 EXACT)
endif()
if(NOT boost_preprocessor_FOUND)
  find_dependency(boost_preprocessor 1.85.0 EXACT)
endif()
if(NOT boost_random_FOUND)
  find_dependency(boost_random 1.85.0 EXACT)
endif()
if(NOT boost_range_FOUND)
  find_dependency(boost_range 1.85.0 EXACT)
endif()
if(NOT boost_regex_FOUND)
  find_dependency(boost_regex 1.85.0 EXACT)
endif()
if(NOT boost_smart_ptr_FOUND)
  find_dependency(boost_smart_ptr 1.85.0 EXACT)
endif()
if(NOT boost_static_assert_FOUND)
  find_dependency(boost_static_assert 1.85.0 EXACT)
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
find_dependency(ZLIB)
find_dependency(BZip2)
find_dependency(LibLZMA)
find_dependency(zstd)
if(NOT boost_numeric_conversion_FOUND)
  find_dependency(boost_numeric_conversion 1.85.0 EXACT)
endif()

include("${CMAKE_CURRENT_LIST_DIR}/boost_iostreams-targets.cmake")
