//
// Created by will on 29/03/24.
//
#include <MessageParser.h>
#include <catch2/catch_test_macros.hpp>
#include <nlohmann/json.hpp>
#include <Messages/NewOrderSingle.h>
#include <Messages/CancelOrder.h>

auto emptyCallback = [](const auto&,const auto&){return "";};

websocketpp::connection_hdl emptyHandle;
std::string logonMessage = nlohmann::json{{"type","LogOn"},{"Username","user"}}.dump();

TEST_CASE("ShouldErrorIfParseError", "[MessageParsing]")
{
	pex::MessageParser parser{emptyCallback,emptyCallback};
	REQUIRE(parser.onRawMessage(emptyHandle,"") == "parse error of incoming message");
}

TEST_CASE("ShouldErrorIfMissingType", "[MessageParsing]")
{
	pex::MessageParser parser{emptyCallback,emptyCallback};
	REQUIRE(parser.onRawMessage(emptyHandle,"{\"hi\" : \"ho\"}") == "message is missing type");
}

TEST_CASE("ShouldErrorIfNotLoggedIn", "[MessageParsing]")
{
	pex::MessageParser parser{emptyCallback,emptyCallback};
	REQUIRE(parser.onRawMessage(emptyHandle,"{\"type\" : \"ho\"}") == "Not Logged In");
}

TEST_CASE("ShouldLogIn", "[MessageParsing]")
{
	pex::MessageParser parser{emptyCallback,emptyCallback};
	REQUIRE(parser.onRawMessage(emptyHandle,logonMessage) == "Logon successfull");
}

TEST_CASE("ShouldErrorIfUnrecognisedType", "[MessageParsing]")
{
	pex::MessageParser parser{emptyCallback,emptyCallback};
	parser.onRawMessage(emptyHandle, logonMessage);
	nlohmann::json message;
	message["type"] = "bla";
	REQUIRE(parser.onRawMessage(emptyHandle,message.dump()) == "Unsupported message type: bla");
}

TEST_CASE("ShouldParseNewOrderSingleCorrectly", "[MessageParsing]")
{
	auto newOrderSingleCallback = [](const auto& user, const auto& newOrderSingle)
	{
		REQUIRE(user == "user");
		REQUIRE(newOrderSingle.px == 100);
		REQUIRE(newOrderSingle.sz == 10);
		REQUIRE(newOrderSingle.clOrdId == 1);
		REQUIRE(newOrderSingle.roomId == "dogecoin");
		return "success";
	};
	pex::MessageParser parser{newOrderSingleCallback,emptyCallback};
	parser.onRawMessage(emptyHandle, logonMessage);

	nlohmann::json message;
	message["type"] = "NewOrderSingle";
	message["price"] = "100";
	message["size"] = "10";
	message["instrument"] = "dogecoin";
	message["ClOrdId"] = 1;

	SECTION("Everything")
	{
		REQUIRE(parser.onRawMessage(emptyHandle,message.dump()) == "success");
	}
	SECTION("NoPrice")
	{
		message.erase("price");
		REQUIRE(parser.onRawMessage(emptyHandle,message.dump()) == "NewOrderSingle missing price");
	}
	SECTION("NoSize")
	{
		message.erase("size");
		REQUIRE(parser.onRawMessage(emptyHandle,message.dump()) == "NewOrderSingle missing size");
	}
	SECTION("NoInstrument")
	{
		message.erase("instrument");
		REQUIRE(parser.onRawMessage(emptyHandle,message.dump()) == "NewOrderSingle missing instrument");
	}
	SECTION("NoClOrdId")
	{
		message.erase("ClOrdId");
		REQUIRE(parser.onRawMessage(emptyHandle,message.dump()) == "NewOrderSingle missing ClOrdId");
	}
}

TEST_CASE("ShouldParseCancelOrdersCorrectly", "[MessageParsing]")
{
	auto cancelOrderCallback = [](const auto& user, const auto& cancelOrder)
	{
		REQUIRE(user == "user");
		REQUIRE(cancelOrder.clOrdId == 1);
		return "success";
	};
	pex::MessageParser parser{emptyCallback,cancelOrderCallback};
	parser.onRawMessage(emptyHandle, logonMessage);

	nlohmann::json message;
	message["type"] = "CancelOrder";
	message["ClOrdId"] = 1;

	SECTION("Everything")
	{
		REQUIRE(parser.onRawMessage(emptyHandle,message.dump()) == "success");
	}
	SECTION("NoClOrdId")
	{
		message.erase("ClOrdId");
		REQUIRE(parser.onRawMessage(emptyHandle,message.dump()) == "CancelOrder missing ClOrdId");
	}
}