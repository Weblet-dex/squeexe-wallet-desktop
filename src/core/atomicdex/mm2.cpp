#include "mm2.hpp"

std::string& mm2::get_rpc_password()
{
    static std::string password;
    return password;
}