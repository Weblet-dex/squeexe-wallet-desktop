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

#include <utility>
#include <unordered_map>

#include <QJsonDocument>

#include "../pages/qt.portfolio.page.hpp"
#include "../utilities/qt.utilities.hpp"
#include "qt_contact_address_list_model.hpp"
#include "qt_contact_address_list_proxy_model.hpp"

namespace atomic_dex
{
    qt_contact_address_list_model::qt_contact_address_list_model(ag::ecs::system_manager& system_manager, QObject* parent) :
        QAbstractListModel(parent),
        system_manager(system_manager),
        proxy_model(new qt_contact_address_list_proxy_model(system_manager, this))
    {
        proxy_model->setDynamicSortFilter(true);
        proxy_model->setSourceModel(this);
        proxy_model->sort(0);
    }

    QVariant qt_contact_address_list_model::data(const QModelIndex& index, int role) const
    {
        if (!hasIndex(index.row(), index.column(), index.parent()))
        {
            return {};
        }

        const auto& element = model_data.at(index.row());
        switch (role)
        {
            case TypeRole:
                return element.type;
            case KeyRole:
                return element.key;
            case ValueRole:
                return element.value;
            case TypeAndKeyRole: // Used for address entry removal.
                return element.type + element.key;
            default:
                return {};
        }
    }

    int qt_contact_address_list_model::rowCount([[maybe_unused]] const QModelIndex& parent) const
    {
        return model_data.size();
    }

    QHash<int, QByteArray> qt_contact_address_list_model::roleNames() const
    {
        return 
        {
            {TypeRole, "type"},
            {KeyRole, "key"},
            {ValueRole, "value"}
        };
    }

    qt_contact_address_list_proxy_model* qt_contact_address_list_model::get_proxy_model() const
    {
        return proxy_model;
    }
    
    const QVector<qt_contact_address_list_model::element>& qt_contact_address_list_model::get_data() const
    {
        return model_data;
    }

    void qt_contact_address_list_model::populate(const std::vector<contact_dto::addresses_entry>& addresses_entries_vec)
    {
        beginResetModel();
        for (const auto& addresses_entry : addresses_entries_vec)
        {
            for (const auto& address : addresses_entry.addresses)
            {
                element elem
                {
                    .type = QString::fromStdString(addresses_entry.type),
                    .key = QString::fromStdString(address.first),
                    .value = QString::fromStdString(address.second)
                };
                model_data.push_back(std::move(elem));
            }
        }
        endResetModel();
    }

    void qt_contact_address_list_model::clear()
    {
        beginResetModel();
        model_data.clear();
        endResetModel();
    }

    void qt_contact_address_list_model::fill_std_vector(std::vector<contact_dto::addresses_entry>& out)
    {
        std::unordered_map<QString, std::vector<std::pair<std::string, std::string>>> model_data_by_address_type;
        for (const auto& elem : model_data)
        {
            model_data_by_address_type.at(elem.type).emplace_back(elem.key.toStdString(), elem.value.toStdString());
        }
        for (auto&[type, data] : model_data_by_address_type)
        {
            contact_dto::addresses_entry addresses_entry;

            addresses_entry.type = type.toStdString();
            addresses_entry.addresses = std::move(data);
            out.push_back(addresses_entry);
        }
    }

    bool qt_contact_address_list_model::addAddressEntry(QString type, QString key, QString value)
    {
        // Returns false if the given key already exists.
        auto res = match(index(0), TypeAndKeyRole, type + key, 1, Qt::MatchFlag::MatchExactly);
        if (not res.empty())
        {
            return false;
        }
    
        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        model_data.push_back(element
                             {
                                 .type = std::move(type),
                                 .key = std::move(key),
                                 .value = std::move(value)
                             });
        endInsertRows();
        return true;
    }
    
    void qt_contact_address_list_model::removeAddressEntry(const QString& type, const QString& key)
    {
        auto res = match(index(0), TypeAndKeyRole, type + key, 1, Qt::MatchFlag::MatchExactly);
    
        if (not res.empty())
        {
            beginRemoveRows(QModelIndex(), res.at(0).row(), res.at(0).row());
            model_data.removeAt(res.at(0).row());
            endRemoveRows();
        }
    }
} // namespace atomic_dex