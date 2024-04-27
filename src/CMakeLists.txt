


add_library(pexchangeLib STATIC
        Exchange.cpp
        ExchangeInternal.cpp
        Room.cpp
        Order.cpp
        Decimal.h
        Types.h
        UserManager.cpp
        User.cpp
        OrderIdGenerator.cpp
        UserOrder.cpp
        Server.cpp
        MessageParser.cpp
)

target_link_libraries(pexchange pexchangeLib)
target_link_libraries(pexchangeLib ${CMAKE_THREAD_LIBS_INIT})
target_include_directories(pexchangeLib PUBLIC . ../external/websocketpp ../external/json/include)