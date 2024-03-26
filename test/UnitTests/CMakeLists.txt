

add_executable(UnitTests
        RoomUnitTests.cpp
        UserUnitTests.cpp
)


target_link_libraries(UnitTests Catch2::Catch2WithMain pexchangeLib)