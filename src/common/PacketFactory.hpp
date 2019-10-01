/*
** EPITECH PROJECT, 2019
** Babel
** File description:
** Created by antoine_dh,
*/

#pragma once

#include <memory>
#include <functional>
#include <map>
#include "Packets/AcceptFriendPacket.hpp"
#include "Packets/AddFriendPacket.hpp"
#include "Packets/CallPacket.hpp"
#include "Packets/ConnectPacket.hpp"
#include "Packets/HangUp.hpp"
#include "Packets/RegisterPacket.hpp"
#include "Packets/RemoveFriendPacket.hpp"

class PacketFactory {
public:
	enum class PacketEnum : int {
		ACCEPT_FRIEND = AcceptFriendPacket::PacketId,
		ADD_FRIEND = AddFriendPacket::PacketId,
		CALL = CallPacket::PacketId,
		CONNECT = ConnectPacket::PacketId,
		HANG_UP = HangUp::PacketId,
		REGISTER = RegisterPacket::PacketId,
		REMOVE_FRIEND = RemoveFriendPacket::PacketId
	};

	static std::unique_ptr<IPacket> PacketFactory::instantiate(int packetId)
	{
		return creatorMap.at(packetId);
	}

private:
	using Creator = std::function<std::unique_ptr<IPacket>()>;

	static std::map<int, Creator> creatorMap = {
		{PacketEnum::ACCEPT_FRIEND, []() { return std::make_unique<AcceptFriendPacket>(); }}
	};
};
