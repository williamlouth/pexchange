


add_library(pexchangeLib STATIC
        Exchange.cpp
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
        Messages/NewOrderSingle.cpp
        Messages/CancelOrder.cpp
)

target_link_libraries(pexchange pexchangeLib)
target_include_directories(pexchangeLib PUBLIC . ../external/websocketpp ../external/json/include)