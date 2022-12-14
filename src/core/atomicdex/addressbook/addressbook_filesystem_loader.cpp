#include <QFile>

#include <nlohmann/json.hpp>

#include "addressbook_filesystem_loader.hpp"
#include "../utilities/global.utilities.hpp"
#include "../utilities/qt.utilities.hpp"
#include "contact_dto.json.hpp"

namespace atomic_dex
{
    nlohmann::json load_addressbook_json_from_filesystem(const std::string& wallet_name)
    {
        const auto      source_folder{utils::get_atomic_dex_addressbook_folder()};
        const auto      in_path      {source_folder / wallet_name};
        QFile           ifs;
        QString         content;
        nlohmann::json  out;
        
        utils::create_if_doesnt_exist(source_folder);
        {
            ifs.setFileName(std_path_to_qstring(in_path));
            try
            {
                ifs.open(QIODevice::ReadOnly | QIODevice::Text);
                content = ifs.readAll();
                ifs.close();
                out = nlohmann::json::parse(content.toStdString());
                SPDLOG_INFO("Addressbook configuration file read.");
            }
            catch ([[maybe_unused]] nlohmann::json::parse_error& ex)
            {
                SPDLOG_WARN("Addressbook config file was invalid, use empty configuration: {}. Content was: {}", ex.what(), content.toStdString());
                out = nlohmann::json::array();
            }
            catch (const std::exception& ex)
            {
                SPDLOG_ERROR(ex.what());
                out = nlohmann::json::array();
            }
            return out;
        }
    }
    
    std::vector<contact_dto> load_addressbook_from_filesystem(const std::string& wallet_name)
    {
        return load_addressbook_json_from_filesystem(wallet_name).get<std::vector<contact_dto>>();
    }
    
    void save_addressbook_to_filesystem(const std::vector<contact_dto>& contacts, const std::string& wallet_name)
    {
        nlohmann::json json = contacts;
        save_addressbook_json_to_filesystem(json, wallet_name);
    }

    void save_addressbook_json_to_filesystem(const nlohmann::json& json, const std::string& wallet_name)
    {
        const auto out_folder{utils::get_atomic_dex_addressbook_folder()};
        const auto out_path{out_folder / wallet_name};
        QFile output;
        
        utils::create_if_doesnt_exist(out_folder);
        {
            output.setFileName(std_path_to_qstring(out_path));
            try
            {
                output.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text);
                output.write(QString::fromStdString(json.dump()).toUtf8());
                SPDLOG_INFO("Addressbook data successfully wrote in persistent data !");
            }
            catch (std::exception& ex)
            {
                SPDLOG_ERROR(ex.what());
            }
        }
    }
}