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

#include "qt_contact_list_proxy_model.hpp"
#include "qt_contact_list_model.hpp"
#include "../pages/qt.portfolio.page.hpp"

namespace atomic_dex
{
    qt_contact_list_proxy_model::qt_contact_list_proxy_model(ag::ecs::system_manager& system_manager, QAbstractItemModel* parent) :
        QSortFilterProxyModel(parent), system_manager(system_manager)
    {
    }

    bool qt_contact_list_proxy_model::lessThan(const QModelIndex& source_left, const QModelIndex& source_right) const
    {
        auto lname = sourceModel()->data(source_left, qt_contact_list_model::NameRole).toString();
        auto rname = sourceModel()->data(source_right, qt_contact_list_model::NameRole).toString();
        return lname.toLower() < rname.toLower();
    }
    
    bool qt_contact_list_proxy_model::filterAcceptsRow(int source_row, const QModelIndex& source_parent) const
    {
        QModelIndex idx = sourceModel()->index(source_row, 0, source_parent);
        assert(sourceModel()->hasIndex(idx.row(), 0));
    
        QStringList search_pattern = search_expression.split(' ', Qt::SplitBehaviorFlags::SkipEmptyParts);
        QString     data           = idx.data(qt_contact_list_model::NameWithTagsRole).toString();
        for (const auto& word : search_pattern)
        {
            if (!data.contains(word, Qt::CaseInsensitive))
            {
                return false;
            }
        }
        
        // If a type filter exists, checks if the contact has at least one address of equivalent type.
        //  - If the contact address' type is a coin type (e.g. ERC20), checks if the filter type corresponds to this coin type (e.g. SmartChain and KMD).
        //  - If type filter is a coin type (e.g. ERC20), checks if the contact address' type belongs to this coin type.
        if (!address_type_filter.isEmpty())
        {
            const auto& glb_coins_cfg = system_manager.get_system<portfolio_page>().get_global_cfg();
            const auto& addresses     = qobject_cast<qt_contact_address_list_model*>(
                                            qvariant_cast<QObject*>(idx.data(qt_contact_list_model::AddressListModelRole))
                                        )->get_data();
            
            if (std::find_if(addresses.begin(), addresses.end(),
                             [this, glb_coins_cfg](const auto& address)
                             {
                                 if (glb_coins_cfg->is_coin_type(address.type))
                                 {
                                     return address.type == address_type_filter ||
                                            glb_coins_cfg->get_coin_info(address_type_filter.toStdString()).type ==
                                            address.type.toStdString();
                                 }
                                 if (glb_coins_cfg->is_coin_type(address_type_filter))
                                 {
                                     return address.type == address_type_filter ||
                                            glb_coins_cfg->get_coin_info(address.type.toStdString()).type ==
                                            address_type_filter.toStdString();
                                 }
                                 return address.type == address_type_filter;
                             }) == addresses.end())
            {
                return false;
            }
        }
        return QSortFilterProxyModel::filterAcceptsRow(source_row, source_parent);
    }

    const QString& qt_contact_list_proxy_model::get_search_exp() const
    {
        return search_expression;
    }
    
    void qt_contact_list_proxy_model::set_search_exp(QString expression)
    {
        search_expression = std::move(expression);
        invalidateFilter();
    }
    
    const QString& qt_contact_list_proxy_model::get_address_type_filter() const
    {
        return address_type_filter;
    }
    
    void qt_contact_list_proxy_model::set_address_type_filter(QString value)
    {
        address_type_filter = std::move(value);
        invalidateFilter();
    }
}