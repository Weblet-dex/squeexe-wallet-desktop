#pragma once

namespace atomic_dex
{
    // Specializes this function to set the json key of a type member.
    // Returns the json key of a type member.
    template <auto MemberPtr>
    constexpr auto json_name_of() = delete;
}