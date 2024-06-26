# Generated by BoostInstall.cmake for boost_hana-1.85.0

include(CMakeFindDependencyMacro)

if(NOT boost_config_FOUND)
  find_dependency(boost_config 1.85.0 EXACT)
endif()
if(NOT boost_core_FOUND)
  find_dependency(boost_core 1.85.0 EXACT)
endif()
if(NOT boost_fusion_FOUND)
  find_dependency(boost_fusion 1.85.0 EXACT)
endif()
if(NOT boost_mpl_FOUND)
  find_dependency(boost_mpl 1.85.0 EXACT)
endif()
if(NOT boost_tuple_FOUND)
  find_dependency(boost_tuple 1.85.0 EXACT)
endif()

include("${CMAKE_CURRENT_LIST_DIR}/boost_hana-targets.cmake")
