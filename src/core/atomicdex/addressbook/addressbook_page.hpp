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

#include <QObject>

#include "addressbook_model.hpp"

namespace atomic_dex
{
    class addressbook_page final : public QObject, public ag::ecs::pre_update_system<addressbook_page>
    {
        // Tells QT this class uses signal/slots mechanisms and/or has GUI elements.
        Q_OBJECT
    
        ag::ecs::system_manager& m_system_manager;
  
        addressbook_model* m_model{nullptr};
        
      public:
        explicit addressbook_page(entt::registry& registry, ag::ecs::system_manager& system_manager, QObject* parent = nullptr);
        ~addressbook_page() final = default;
 
        // ag::ecs::pre_update_system implem
        void update() final;

        void connect_signals();
        void disconnect_signals();

        // Handler that should be called when logged in to a wallet.
        void on_post_login([[maybe_unused]] const post_login& evt);

        void clear();

      private:
        Q_PROPERTY(addressbook_model* model READ get_model NOTIFY addressbookChanged)
        [[nodiscard]] addressbook_model* get_model() const;
        
      signals:
        void addressbookChanged();
    };
}

REFL_AUTO(type(atomic_dex::addressbook_page))