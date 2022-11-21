#ifdef _WIN32
    #include <windows.h>
#elif defined __linux__
    #include <unistd.h>
    #include <sstream>
#elif defined __APPLE__
    #include <mach-o/dyld.h>
#endif

#include <string>

#ifdef _WIN32
    #define DIRECTORY_SEPARATOR '\\'
#else
    #define DIRECTORY_SEPARATOR '/'
#endif

std::filesystem::path get_binary_path(uint32_t max_path_size)
{
    char* directory = new char[max_path_size];

#if defined(_WIN32)
    ::GetModuleFileName(NULL, &directory[0], max_path_size);

#elif defined(__linux__)
    int pid = getpid(); // Get the process ID.

    /* Construct a path to the symbolic link pointing to the process executable.
    ** This is at /proc/<pid>/exe on Linux systems (we hope). */
    std::ostringstream oss;
    oss << "/proc/" << pid << "/exe";
    std::string link = oss.str();
    int count = readlink(link.c_str(), &directory[0], max_path_size); // Read the contents of the link.
    if (count == -1)
    {
        throw std::runtime_error("Could not read symbolic link");
    }
    directory[count] = '\0';

#elif defined(__APPLE__)
    if (_NSGetExecutablePath(directory, &max_path_size) != 0)
        throw std::runtime_error("Buffer size is too low.");

#endif
    auto result = std::filesystem::path(directory);
    delete[] directory;
    return result;
}

std::filesystem::path get_binary_dir(uint32_t max_path_size)
{
    auto binary_path = get_binary_path(max_path_size).string();
    auto pos = binary_path.find_last_of(DIRECTORY_SEPARATOR);
    return std::filesystem::path(binary_path.erase(pos + 1));
}

std::string get_binary_name(uint32_t max_path_size)
{
    auto path = get_binary_path(max_path_size).string();
    auto pos = path.find_last_of(DIRECTORY_SEPARATOR);
    return path.substr(pos + 1);
}