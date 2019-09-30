/*
** EPITECH PROJECT, 2019
** Babel
** File description:
** Created by antoine_dh,
*/

#pragma once

#include "IPacket.hpp"

class HangUp : public IPacket {
    public:
        static constexpr int PacketId = 7;

        HangUp() = default;
        int getId() const override;
};
