/*
** EPITECH PROJECT, 2019
** Babel
** File description:
** Created by antoine_dh,
*/

#include "PacketFactory.hpp"

const std::map<int, std::function<std::unique_ptr<IPacket>()>> PacketFactory::creatorMap = {
    { PacketEnum::ACCEPT_FRIEND, []() { return std::make_unique<AcceptFriendPacket>(); }},
    { PacketEnum::ADD_FRIEND, []() { return std::make_unique<AddFriendPacket>(); }},
    { PacketEnum::CALL, []() { return std::make_unique<CallPacket>(); }},
    { PacketEnum::CONNECT, []() { return std::make_unique<ConnectPacket>(); }},
    { PacketEnum::HANG_UP, []() { return std::make_unique<HangUpPacket>(); }},
    { PacketEnum::REGISTER, []() { return std::make_unique<RegisterPacket>(); }},
    { PacketEnum::REMOVE_FRIEND, []() { return std::make_unique<RemoveFriendPacket>(); }},
    { PacketEnum::FRIEND_ACCEPTED, []() { return std::make_unique<FriendAcceptedPacket>(); }},
    { PacketEnum::FRIEND_REMOVED, []() { return std::make_unique<FriendRemovedPacket>(); }},
    { PacketEnum::FRIEND_INFO, []() { return std::make_unique<FriendInfoPacket>(); }},
    { PacketEnum::RECEIVED_FRIEND_REQUEST, []() { return std::make_unique<ReceivedFriendRequestPacket>(); }},
    { PacketEnum::RESPONSE_PACKET, []() { return std::make_unique<ResponsePacket>(); }},
};
