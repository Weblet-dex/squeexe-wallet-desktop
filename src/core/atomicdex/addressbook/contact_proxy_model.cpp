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

#include "contact_proxy_model.hpp"                       //> addressbook_contact_proxy_filter_model
#include "atomicdex/pages/qt.portfolio.page.hpp"         //> portfolio_page::get_global_cfg
#include "contact_model.hpp"                             //> addressbook_contact_model::AddressTypeRole/AddressKeyRole/AddressTypeAndKeyRole/AddressValueRole

namespace atomic_dex
{
    contact_proxy_model::contact_proxy_model(ag::ecs::system_manager& system_manager, QObject* parent) :
        QSortFilterProxyModel(parent), m_system_manager(system_manager)
    {}
}

namespace atomic_dex
{
    bool
    contact_proxy_model::filterAcceptsRow(int source_row, const QModelIndex& source_parent) const
    {
        QModelIndex idx = sourceModel()->index(source_row, 0, source_parent);
        assert(sourceModel()->hasIndex(idx.row(), 0));
        const auto address_type = idx.data(contact_model::AddressTypeRole).toString();
        
        // Checks if type filter corresponds to address entry's type.
        //  - Returns false if type filter and address' type are not equal.
        //  - Returns false if type filter is a coin type (e.g. ERC20) and address' type does not belong or is not equal to this coin type.
        //  - Returns false if address type is a coin type (e.g. ERC20) and type filter does not belong or is not equal to this coin type.
        if (!m_filter_type.isEmpty())
        {
            const auto& glb_coins_cfg = m_system_manager.get_system<portfolio_page>().get_global_cfg();

            if (glb_coins_cfg->is_coin_type(m_filter_type))
            {
                if (m_filter_type != address_type &&
                    glb_coins_cfg->get_coin_info(address_type.toStdString()).type != m_filter_type.toStdString())
                {
                    return false;
                }
            }
            else if (glb_coins_cfg->is_coin_type(address_type))
            {
                if (m_filter_type != address_type &&
                    glb_coins_cfg->get_coin_info(m_filter_type.toStdString()).type != address_type.toStdString())
                {
                    return false;
                }
            }
            else if (m_filter_type != address_type)
            {
                return false;
            }
        }
        
        // Checks if search expression corresponds to address entry.
        if (m_search_expression.isEmpty())
        {
            return true;
        }
        return idx.data(contact_model::AddressKeyRole).toString().contains(m_search_expression, Qt::CaseInsensitive) ||
               idx.data(contact_model::AddressValueRole).toString().contains(m_search_expression, Qt::CaseInsensitive) ||
               address_type.contains(m_search_expression, Qt::CaseInsensitive) ||
               idx.data(contact_model::AddressTypeAndKeyRole).toString().contains(m_search_expression, Qt::CaseInsensitive);
    }
    
    bool
    contact_proxy_model::lessThan(const QModelIndex& source_left, const QModelIndex& source_right) const
    {
        QVariant left_data  = sourceModel()->data(source_left, contact_model::AddressTypeAndKeyRole);
        QVariant right_data = sourceModel()->data(source_right, contact_model::AddressTypeAndKeyRole);
        
        return left_data.toString().toLower() < right_data.toString().toLower();
    }
} // namespace atomic_dex

namespace atomic_dex
{
    const QString&
    contact_proxy_model::get_search_expression() const
    {
        return m_search_expression;
    }
    
    void
    contact_proxy_model::set_search_expression(QString value)
    {
        m_search_expression = std::move(value);
        invalidateFilter();
    }
    
    const QString&
    contact_proxy_model::get_filter_type() const
    {
        return m_filter_type;
    }
    
    void
    contact_proxy_model::set_filter_type(QString value)
    {
        m_filter_type = std::move(value);
        invalidateFilter();
    }
}