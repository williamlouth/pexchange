

add_executable(UnitTests
    RoomUnitTests.cpp
)


target_link_libraries(UnitTests Catch2::Catch2WithMain pexchangeLib)