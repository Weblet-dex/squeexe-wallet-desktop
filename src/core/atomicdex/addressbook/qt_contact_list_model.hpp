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

#include <QAbstractListModel>
#include <QObject>

#include <antara/gaming/ecs/system.manager.hpp>

#include "contact_dto.hpp"
#include "qt_contact_address_list_model.hpp"
#include "qt_contact_list_proxy_model.hpp"

namespace ag = antara::gaming;

namespace atomic_dex
{
    class qt_contact_list_model final : public QAbstractListModel
    {
        // Tells QT this class uses signal/slots mechanisms and/or has GUI elements.
        Q_OBJECT
        
        // The data type represented by this model.
        struct element
        {
            QString     name;
            QStringList tags;
            qt_contact_address_list_model* address_list_model;
        };

      public:
        enum roles
        {
            NameRole = Qt::UserRole + 1,
            TagsRole,
            PushTagArgRole,
            RemoveTagArgRole,
            NameWithTagsRole,
            AddressListModelRole
        };
        Q_ENUM(roles);

        explicit qt_contact_list_model(ag::ecs::system_manager& system_registry, QObject* parent = nullptr);
        ~qt_contact_list_model();
        
        // `QAbstractListModel` functions
        [[nodiscard]] QVariant                data(const QModelIndex& index, int role) const final;
        bool                                  setData(const QModelIndex &index, const QVariant &value, int role) final;
        [[nodiscard]] int                     rowCount(const QModelIndex& parent = QModelIndex()) const final;
        [[nodiscard]] QHash<int, QByteArray>  roleNames() const final;

        // Fills model data `model_data` from a container of type `std::vector<contact_dto>`.
        void populate(const std::vector<contact_dto>& contact_vec);
        
        // Empties model data `model_data`.
        void clear();
        
        // Fills an `std::vector<contact_dto>` from this model's data.
        void fill_std_vector(std::vector<contact_dto>& out);
        
        // Returns the proxy of this model.
        [[nodiscard]] qt_contact_list_proxy_model* get_proxy_model() const;
        
        Q_INVOKABLE bool addContact(const QString& name);
        Q_INVOKABLE void removeContact(const QString& name);

        Q_PROPERTY(qt_contact_list_proxy_model* proxyModel READ get_proxy_model NOTIFY proxyModelChanged);
        
      signals:
        void proxyModelChanged();

      private:
        ag::ecs::system_manager& system_manager;
        qt_contact_list_proxy_model* proxy_model;
        QVector<element> model_data;
    };
} // namespace atomic_dex
