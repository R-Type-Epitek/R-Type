//
// Created by Xavier VINCENT on 08/01/2024.
//

#include <gtest/gtest.h>
#include "RTypeNetwork.hpp"

TEST(ClientTest, Constructor)
{
  Network::Client client;
  EXPECT_EQ(client.getId(), -1);
  EXPECT_EQ(client.getName(), "");
  EXPECT_EQ(client.getRoomId(), -1);
  EXPECT_FALSE(client.getIsInGame());
}

TEST(ClientTest, SetAndGetId)
{
  Network::Client client;
  client.setId(42);
  EXPECT_EQ(client.getId(), 42);
}

TEST(ClientTest, SetAndGetName)
{
  Network::Client client;
  client.setName("TestClient");
  EXPECT_EQ(client.getName(), "TestClient");
}

TEST(ClientTest, SetAndGetRoomId)
{
  Network::Client client;
  client.setRoomId(123);
  EXPECT_EQ(client.getRoomId(), 123);
}

TEST(ClientTest, SetAndGetIsInGame)
{
  Network::Client client;
  client.setIsInGame(true);
  EXPECT_TRUE(client.getIsInGame());
}
