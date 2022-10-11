#include <nlohmann/json.hpp>

#include "contact_dto.json.hpp"

namespace atomic_dex
{
    inline void from_json(const nlohmann::json& in, contact_dto::addresses_entry& out)
    {
        out.type = in[json_name_of<&contact_dto::addresses_entry::type>()];
        out.addresses = in[json_name_of<&contact_dto::addresses_entry::addresses>()].get<decltype(out.addresses)>();
    }
    
    inline void from_json(const nlohmann::json& in, contact_dto& out)
    {
        out.name = in[json_name_of<&contact_dto::name>()];
        out.addresses_entries = in[json_name_of<&contact_dto::addresses_entries>()].get<decltype(out.addresses_entries)>();
        out.tags = in[json_name_of<&contact_dto::tags>()].get<decltype(out.tags)>();
    }
    
    inline void to_json(nlohmann::json& out, const contact_dto::addresses_entry& in)
    {
        out[json_name_of<&contact_dto::addresses_entry::type>()] = in.type;
        out[json_name_of<&contact_dto::addresses_entry::addresses>()] = in.addresses;
    }
    
    inline void to_json(nlohmann::json& out, const contact_dto& in)
    {
        out[json_name_of<&contact_dto::name>()] = in.name;
        out[json_name_of<&contact_dto::addresses_entries>()] = in.addresses_entries;
        out[json_name_of<&contact_dto::tags>()] = in.tags;
    }
}