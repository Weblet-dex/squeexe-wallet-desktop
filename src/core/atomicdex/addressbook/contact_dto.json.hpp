/******************************************************************************
* Copyright © 2013-2022 The Komodo Platform Developers.                      *
*                                                                            *
* See the AUTHORS, DEVELOPER-AGREEMENT and LICENSE files at                  *
* the top-level directory of this distribution for the individual copyright  *
* holder information and the developer policies on copyright and licensing.  *
*                                                                            *
* Unless otherwise agreed in a custom licensing agreement, no part of the    *
* Komodo Platform software, including this file may be copied, modified,     *
* propagated or distributed except according to the terms contained in the   *
* LICENSE file                                                               *
*                                                                            *
* Removal or modification of this copyright notice is prohibited.            *
*                                                                            *
******************************************************************************/

#pragma once

#include <nlohmann/json_fwd.hpp>

#include "../json.hpp"
#include "contact_dto.hpp"

namespace atomic_dex
{
    template <>
    [[nodiscard]]
    inline constexpr auto json_name_of<&contact_dto::addresses_entry::type>()
    {
        return "type";
    }
    
    template <>
    [[nodiscard]]
    inline constexpr auto json_name_of<&contact_dto::addresses_entry::addresses>()
    {
        return "addresses";
    }
    
    template <>
    [[nodiscard]]
    inline constexpr auto json_name_of<&contact_dto::name>()
    {
        return "name";
    }
    
    template <>
    [[nodiscard]]
    inline constexpr auto json_name_of<&contact_dto::addresses_entries>()
    {
        return "wallets_info";
    }
    
    template <>
    [[nodiscard]]
    inline constexpr auto json_name_of<&contact_dto::tags>()
    {
        return "categories";
    }
    
    inline void from_json(const nlohmann::json& in, contact_dto::addresses_entry& out)
    {
        out.type = in[json_name_of<&contact_dto::addresses_entry::type>()];
        out.addresses = in[json_name_of<&contact_dto::addresses_entry::addresses>()].get<decltype(out.addresses)>();
    }
    
    inline void from_json(const nlohmann::json& in, contact_dto& out)
    {
        out.name = in[json_name_of<&contact_dto::name>()];
        out.addresses_entries = in[json_name_of<&contact_dto::addresses_entries>()].get<decltype(out.addresses_entries)>();
        out.tags = in[json_name_of<&contact_dto::tags>()].get<decltype(out.tags)>();
    }
    
    inline void to_json(nlohmann::json& out, const contact_dto::addresses_entry& in)
    {
        out[json_name_of<&contact_dto::addresses_entry::type>()] = in.type;
        out[json_name_of<&contact_dto::addresses_entry::addresses>()] = in.addresses;
    }
    
    inline void to_json(nlohmann::json& out, const contact_dto& in)
    {
        out[json_name_of<&contact_dto::name>()] = in.name;
        out[json_name_of<&contact_dto::addresses_entries>()] = in.addresses_entries;
        out[json_name_of<&contact_dto::tags>()] = in.tags;
    }
}