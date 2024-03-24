


add_library(pexchangeLib STATIC
        Exchange.cpp
        Room.cpp
        Order.cpp
        Decimal.h
        Types.h
)

target_link_libraries(pexchange pexchangeLib)
target_include_directories(pexchangeLib PUBLIC .)