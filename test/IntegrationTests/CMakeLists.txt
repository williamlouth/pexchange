add_executable(IntegrationTests
        MultiUserIntegrationTests.cpp
)

add_subdirectory(Dsl)


target_link_libraries(IntegrationTests Catch2::Catch2WithMain pexchangeLib)
