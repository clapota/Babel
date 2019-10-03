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
#include "Packets/HangUpPacket.hpp"
#include "Packets/RegisterPacket.hpp"
#include "Packets/RemoveFriendPacket.hpp"
#include "Packets/FriendAcceptedPacket.hpp"
#include "Packets/FriendInfoPacket.hpp"
#include "Packets/FriendRemovedPacket.hpp"
#include "Packets/ReceivedFriendRequestPacket.hpp"
#include "Packets/ResponsePacket.hpp"
#include "Packets/CallingPacket.hpp"

class PacketFactory {
public:
	enum PacketEnum : int {
		ACCEPT_FRIEND = AcceptFriendPacket::PacketId,
		ADD_FRIEND = AddFriendPacket::PacketId,
		CALL = CallPacket::PacketId,
		CONNECT = ConnectPacket::PacketId,
		HANG_UP = HangUpPacket::PacketId,
		REGISTER = RegisterPacket::PacketId,
		REMOVE_FRIEND = RemoveFriendPacket::PacketId,
		FRIEND_ACCEPTED = FriendAcceptedPacket::PacketId,
		FRIEND_REMOVED = FriendRemovedPacket::PacketId,
		FRIEND_INFO = FriendInfoPacket::PacketId,
		RECEIVED_FRIEND_REQUEST = ReceivedFriendRequestPacket::PacketId,
		RESPONSE_PACKET = ResponsePacket::PacketId,
		CALLING_PACKET = CallingPacket::PacketId
	};

	static std::unique_ptr<IPacket> instantiate(int packetId)
	{
		if (creatorMap.find(packetId) == creatorMap.end())
			throw std::runtime_error("Unknown Packet ID: " + std::to_string(packetId));
		return creatorMap.at(packetId)();
	}

private:
	using Creator = std::function<std::unique_ptr<IPacket>()>;

	static const std::map<int, std::function<std::unique_ptr<IPacket>()>> creatorMap;
};
