#pragma once

#include <filesystem>

// Gets the binary location.
//
// On Linux, this function uses 'readlink' so it may throw
// an 'std::runtime_error' exception in case 'readlink' fails.
//
// On MacOS, this function may throw an 'std::runtime_error' exception if
// the buffer size is to small.
std::filesystem::path get_binary_path(uint32_t max_path_size = 1024);

// Gets the current executed binary directory location.
std::filesystem::path get_binary_dir(uint32_t max_path_size = 1024);

// Gets the binary name.
std::string get_binary_name(uint32_t max_path_size = 1024);