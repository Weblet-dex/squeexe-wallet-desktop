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

#include <entt/core/attribute.h>
#include <antara/gaming/ecs/system.manager.hpp>

#include "qt_contact_address_list_proxy_model.hpp"
#include "contact_dto.hpp"
#include "contact_dto.json.hpp"

namespace atomic_dex
{
    class ENTT_API qt_contact_address_list_model final : public QAbstractListModel
    {
        // Tells QT this class uses signal/slots mechanisms and/or has GUI elements.
        Q_OBJECT
      
        friend class qt_contact_list_model;
    
      public:
        struct element
        {
            QString type;
            QString key;
            QString value;
        };
        
        enum roles
        {
            TypeRole = Qt::UserRole + 1,
            KeyRole,
            ValueRole,
            TypeAndKeyRole,
        };
        Q_ENUM(roles)

        explicit qt_contact_address_list_model(ag::ecs::system_manager& system_manager, QObject* parent = nullptr);
    
        // QAbstractListModel Functions
        [[nodiscard]] QVariant               data(const QModelIndex& index, int role) const final;
        [[nodiscard]] int                    rowCount(const QModelIndex& parent = QModelIndex()) const final;
        [[nodiscard]] QHash<int, QByteArray> roleNames() const final;
        
        [[nodiscard]]
        qt_contact_address_list_proxy_model* get_proxy_model() const;
        
        // Returns inner data.
        [[nodiscard]]
        const QVector<element>& get_data() const;
    
        // Fills model data `model_data` from a container of type `std::vector<contact_dto::addresses_entry>`.
        void populate(const std::vector<contact_dto::addresses_entry>& addresses_entries_vec);
        
        // Empties model data `model_data`.
        void clear();

        // Fills an `std::vector<contact_dto::addresses_entry>` from this model's data.
        void fill_std_vector(std::vector<contact_dto::addresses_entry>& out);
        
        // Adds an address entry to the current contact. Returns false if the key already exists in the given wallet type, false otherwise.
        Q_INVOKABLE bool addAddressEntry(QString type, QString key, QString value);
    
        // Removes an address entry from the current contact.
        Q_INVOKABLE void removeAddressEntry(const QString& type, const QString& key);
        
        Q_PROPERTY(qt_contact_address_list_proxy_model* proxyModel READ get_proxy_model NOTIFY proxyModelChanged)
        
      signals:
        void proxyModelChanged();

      private:
        ag::ecs::system_manager& system_manager;
        QVector<element> model_data;
        qt_contact_address_list_proxy_model* proxy_model;
    };
}