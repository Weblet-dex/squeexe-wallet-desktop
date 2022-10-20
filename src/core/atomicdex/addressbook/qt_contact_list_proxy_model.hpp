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

#include <QSortFilterProxyModel>

#include <antara/gaming/ecs/system.manager.hpp>

namespace ag = antara::gaming;

namespace atomic_dex
{
    // This proxy sorts model data of `qt_contact_list_proxy_model` by name.
    class qt_contact_list_proxy_model final : public QSortFilterProxyModel
    {
        Q_OBJECT

      public:
        qt_contact_list_proxy_model(ag::ecs::system_manager& system_manager, QAbstractItemModel* parent);

        // `QSortFilterProxyModel` functions
        [[nodiscard]] bool lessThan(const QModelIndex& source_left, const QModelIndex& source_right) const final; // Only if sort role equals addressbook_model::SubModelRole, sorts contacts by their name in ascending order.
        [[nodiscard]] bool filterAcceptsRow(int source_row, const QModelIndex& source_parent) const override; // Only if filter role equals addressbook_model::NameRoleAndCategoriesRole, accepts rows which match each word (not case-sensitive) of m_search_exp. Also filters contacts which have at least one address of type equivalent to the one specified by the member `m_filter_type`.

        // Returns the search expression of this proxy model.
        [[nodiscard]] const QString& get_search_exp() const;
        
        // Sets the search expression of this proxy model.
        void set_search_exp(QString expression);
        
        [[nodiscard]] const QString& get_address_type_filter() const;
        
        void set_address_type_filter(QString value);

        Q_PROPERTY(QString searchExp READ get_search_exp WRITE set_search_exp NOTIFY searchExpChanged)
        Q_PROPERTY(QString typeFilter READ get_address_type_filter WRITE set_address_type_filter NOTIFY addressTypeFilterChanged)

      signals:
        void searchExpChanged();
        void addressTypeFilterChanged();

      private:
        ag::ecs::system_manager& system_manager;

        QString search_expression;
    
        // Contains the address type that a contact should have on one of its addresses to validate the filtering.
        QString address_type_filter;
    };
} // namespace atomic_dex
