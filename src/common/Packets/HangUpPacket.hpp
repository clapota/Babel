/*
** EPITECH PROJECT, 2019
** Babel
** File description:
** Created by antoine_dh,
*/

#pragma once

#include "IPacket.hpp"

class HangUpPacket : public IPacket {
    public:
        static constexpr int PacketId = 7;

        HangUpPacket() = default;
        int getId() const override;
};
