/*
** EPITECH PROJECT, 2019
** Babel
** File description:
** Created by antoine_dh,
*/

#include "HandlerService.hpp"


const std::map<int, HandlerService::Handler> HandlerService::_handlers = {
    {PacketFactory::PacketEnum::REGISTER, HandshakeHandler::registerHandler},
    {PacketFactory::PacketEnum::CONNECT, HandshakeHandler::loginHandler},
    {PacketFactory::PacketEnum::ADD_FRIEND, HandshakeHandler::addFriendHandler},
    {PacketFactory::PacketEnum::ACCEPT_FRIEND, HandshakeHandler::acceptFriendHandler},
};
