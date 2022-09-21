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

namespace atomic_dex
{
    struct contact_dto
    {
        struct addresses_entry
        {
            std::vector<std::pair<std::string, std::string>> addresses;

            // Coin name or protocol name (e.g. BTC, KMD, Smart Chain, ERC-20)
            std::string type;
        };

        std::string name;
        std::vector<addresses_entry> addresses_entries;
        std::vector<std::string> tags;
    };
}