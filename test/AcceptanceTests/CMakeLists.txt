add_executable(AcceptanceTests
        ConnectionAcceptanceTests.cpp
)

add_subdirectory(Dsl)


target_link_libraries(AcceptanceTests Catch2::Catch2WithMain pexchangeLib)
