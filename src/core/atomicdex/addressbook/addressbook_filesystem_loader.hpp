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

#include <vector>

#include <nlohmann/json_fwd.hpp>

#include "contact_dto.hpp"

namespace atomic_dex
{    
    [[nodiscard]]
    nlohmann::json load_addressbook_json_from_filesystem(const std::string& wallet_name);
    
    [[nodiscard]]
    std::vector<contact_dto> load_addressbook_from_filesystem(const std::string& wallet_name);
    
    void save_addressbook_to_filesystem(const std::vector<contact_dto>& contacts, const std::string& wallet_name);

    void save_addressbook_json_to_filesystem(const nlohmann::json& json, const std::string& wallet_name);
}