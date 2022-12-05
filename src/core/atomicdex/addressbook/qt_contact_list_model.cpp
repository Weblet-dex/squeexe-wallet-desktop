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

#include <QJsonArray>

#include "addressbook_filesystem_loader.hpp"
#include "atomicdex/utilities/qt.utilities.hpp"
#include "qt_contact_list_model.hpp"

namespace atomic_dex
{
    qt_contact_list_model::qt_contact_list_model(ag::ecs::system_manager& system_manager, QObject* parent)  :
        QAbstractListModel(parent),
        system_manager(system_manager),
        proxy_model(new qt_contact_list_proxy_model(system_manager, this))
    {
        proxy_model->setDynamicSortFilter(true);
        proxy_model->setSourceModel(this);
        proxy_model->sort(0);
    }

    qt_contact_list_model::~qt_contact_list_model()
    {
        clear();
    }

    int atomic_dex::qt_contact_list_model::rowCount([[maybe_unused]] const QModelIndex& parent) const
    {
        return model_data.size();
    }
    
    QVariant atomic_dex::qt_contact_list_model::data(const QModelIndex& index, int role) const
    {
        if (!hasIndex(index.row(), index.column(), index.parent()))
        {
            return {};
        }

        switch (static_cast<roles>(role))
        {
            case NameRole:
                return model_data.at(index.row()).name;
            case TagsRole:
                return model_data.at(index.row()).tags;
            case NameWithTagsRole:
            {
                const auto& contact = model_data.at(index.row());
                return contact.name + ' ' + contact.tags.join(' ');
            }
            case AddressListModelRole:
                return QVariant::fromValue(model_data.at(index.row()).address_list_model);
            default:
                return {};
        }
    }

    bool qt_contact_list_model::setData(const QModelIndex& index, const QVariant& value, int role)
    {
        element& item = model_data[index.row()];

        switch (static_cast<roles>(role))
        {
            case NameRole:
                item.name = value.toString();
                break;
            case PushTagArgRole:
            {
                auto tag = value.toString();
                if (item.tags.contains(value.toString()))
                    return false;
                item.tags.push_back(tag);
                emit dataChanged(index, index, {TagsRole});
                return true;
            }
            case RemoveTagArgRole:
            {
                if (!item.tags.removeOne(value.toString()))
                    return false;
                emit dataChanged(index, index, {TagsRole});
                return true;
            }
            default:
                return false;
        }

        emit dataChanged(index, index, {role});
        return true;
    }
    
    QHash<int, QByteArray> qt_contact_list_model::roleNames() const
    {
        return
        {
            {NameRole, "name"},
            {TagsRole, "tags"},
            {PushTagArgRole, "pushTagArg"},
            {RemoveTagArgRole, "removeTagArg"},
            {NameWithTagsRole, "nameWithTags"},
            {AddressListModelRole, "addressListModel"}
        };
    }
    
    void qt_contact_list_model::populate(const std::vector<contact_dto>& contact_vec)
    {
        beginResetModel();
        for (const auto& contact : contact_vec)
        {
            element element
            {
                .name = QString::fromStdString(contact.name),
                .tags = vector_std_string_to_qt_string_list(contact.tags),
                .address_list_model = new qt_contact_address_list_model(system_manager)
            };
            element.address_list_model->populate(contact.addresses_entries);
            model_data.push_back(element);
        }
        endResetModel();
    }
    
    void qt_contact_list_model::fill_std_vector(std::vector<contact_dto>& out)
    {
        for (const auto& element : model_data)
        {
            contact_dto contact;
            contact.name = element.name.toStdString();
            for (const auto& element_tag : element.tags)
            {
                contact.tags.push_back(element_tag.toStdString());
            }
            element.address_list_model->fill_std_vector(contact.addresses_entries);
            out.push_back(contact);
        }
    }
    
    void qt_contact_list_model::clear()
    {
        beginResetModel();
        for (const auto& element : model_data)
        {
            delete element.address_list_model;
        }
        model_data.clear();
        endResetModel();
    }

    qt_contact_list_proxy_model* qt_contact_list_model::get_proxy_model() const
    {
        return proxy_model;
    }

    void qt_contact_list_model::removeContact(const QString& name)
    {
        auto res = match(index(0), NameRole, name, 1, Qt::MatchFlag::MatchExactly);

        if (not res.empty())
        {
            beginRemoveRows(QModelIndex(), res.at(0).row(), res.at(0).row());
            delete model_data.at(res.at(0).row()).address_list_model;
            model_data.removeAt(res.at(0).row());
            endRemoveRows();
        }
    }
    
    bool qt_contact_list_model::addContact(const QString& name)
    {
        auto res = match(index(0), NameRole, name, 1, Qt::MatchFlag::MatchExactly);
        
        if (not res.empty())
        {
            return false;
        }
        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        element contact{.name = name, .address_list_model = new qt_contact_address_list_model(system_manager)};
        model_data.push_back(contact);
        endInsertRows();
        return true;
    }
} // namespace atomic_dex
