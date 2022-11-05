#pragma once

#include <vector>

#include "rpc.hpp"
#include "balance_info.hpp"

namespace atomic_dex::mm2
{
    struct enable_eth_with_tokens_rpc
    {
        static constexpr auto endpoint = "enable_eth_with_tokens";
        static constexpr bool is_v2     = true;

        struct expected_request_type
        {
            struct erc20_token_request_t
            {
                std::string         ticker;
                std::optional<int>  required_confirmations;
            };
            struct utxo_merge_params_t
            {
                int merge_at;
                int check_every;
                int max_merge_at_once;
            };
            struct nodes_t
            {
                std::string                     url;
                std::optional<bool>             gui_auth{false};
            };

            std::string                         ticker;
            bool                                tx_history{true};
            std::optional<int>                  required_confirmations;
            std::optional<bool>                 requires_notarization;
            std::vector<nodes_t>                nodes;
            std::vector<erc20_token_request_t>  erc20_tokens_requests;
            std::optional<utxo_merge_params_t>  utxo_merge_params;
            const std::string                   erc_swap_contract_address{"0x24ABE4c71FC658C91313b6552cd40cD808b3Ea80"};
            const std::string                   erc_testnet_swap_contract_address{"0x6b5A52217006B965BB190864D62dc3d270F7AaFD"};
            const std::string                   erc_fallback_swap_contract_address{"0x8500AFc0bc5214728082163326C2FF0C73f4a871"};
            const std::string                   erc_testnet_fallback_swap_contract_address{"0x7Bc1bBDD6A0a722fC9bffC49c921B685ECB84b94"};
        };
        
        struct expected_result_type
        {
            struct derivation_method_t { std::string type; };
            struct eth_address_infos_t
            {
                derivation_method_t derivation_method;
                std::string         pubkey;
                balance_info        balances;
            };
            struct erc20_address_infos_t
            {
                derivation_method_t                             derivation_method;
                std::string                                     pubkey;
                std::unordered_map<std::string, balance_info>   balances;
            };

            std::size_t current_block;
            std::unordered_map<std::string, eth_address_infos_t> eth_addresses_infos;
            std::unordered_map<std::string, eth_address_infos_t> erc20_addresses_infos;
        };

        using expected_error_type = rpc_basic_error_type;

        expected_request_type                   request;
        std::optional<expected_result_type>     result;
        std::optional<expected_error_type>      error;
    };

    using enable_eth_with_tokens_request_rpc    = enable_eth_with_tokens_rpc::expected_request_type;
    using enable_eth_with_tokens_result_rpc     = enable_eth_with_tokens_rpc::expected_result_type;
    using enable_eth_with_tokens_error_rpc      = enable_eth_with_tokens_rpc::expected_error_type;

    void to_json(nlohmann::json& j, const enable_eth_with_tokens_request_rpc& in);
    void to_json(nlohmann::json& j, const enable_eth_with_tokens_request_rpc::nodes_t& in);
    void to_json(nlohmann::json& j, const enable_eth_with_tokens_request_rpc::erc20_token_request_t& in);
    void to_json(nlohmann::json& j, const enable_eth_with_tokens_request_rpc::utxo_merge_params_t& in);
    void from_json(const nlohmann::json& json, enable_eth_with_tokens_result_rpc& out);
    void from_json(const nlohmann::json& json, enable_eth_with_tokens_result_rpc::derivation_method_t& out);
    void from_json(const nlohmann::json& json, enable_eth_with_tokens_result_rpc::eth_address_infos_t& out);
    void from_json(const nlohmann::json& json, enable_eth_with_tokens_result_rpc::erc20_address_infos_t& out);
}