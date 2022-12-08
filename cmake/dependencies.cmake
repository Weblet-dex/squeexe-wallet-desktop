include(FetchContent)

if (WIN32)
    find_package(ZLIB)
    set(BUILD_SHARED_LIBS OFF CACHE BOOL "Override option" FORCE)
endif ()

find_package(EnTT REQUIRED)
find_package(fmt REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(range-v3 REQUIRED)
find_package(date REQUIRED)
find_package(doctest REQUIRED)
find_package(spdlog REQUIRED)
find_package(cpprestsdk REQUIRED)

if (APPLE)
    get_target_property(ACTUAL_VAR cpprestsdk::cpprest INTERFACE_LINK_LIBRARIES)
    message("Property of cpprestsdk::cpprest: ${ACTUAL_VAR}")
    set(NEW_INTERFACES "")
    foreach (CUR_LIB ${ACTUAL_VAR})
        #message(STATUS "CUR_LIB-> ${CUR_LIB}")
        if (CUR_LIB MATCHES "MacOSX")
            message(STATUS "NEED TO BE SKIPPED -> ${CUR_LIB}")
        else ()
            list(APPEND NEW_INTERFACES ${CUR_LIB})
            #message("KK-> ${NEW_INTERFACES}")
        endif ()
    endforeach ()
    set_target_properties(cpprestsdk::cpprest PROPERTIES INTERFACE_LINK_LIBRARIES "${NEW_INTERFACES}")
    get_target_property(KK_VAR cpprestsdk::cpprest INTERFACE_LINK_LIBRARIES)
    message("Property of cpprestsdk::cpprest: ${KK_VAR}")
endif ()

find_package(Boost COMPONENTS filesystem random system thread REQUIRED)
add_library(komodo-taskflow INTERFACE)
add_library(komodo-taskflow::taskflow ALIAS komodo-taskflow)

add_library(komodo-date INTERFACE)
target_link_libraries(komodo-date INTERFACE date::date-tz)
add_library(komodo-date::date ALIAS komodo-date)

find_package(Qt5 5.15 COMPONENTS Core Quick LinguistTools Svg Charts WebEngine WebEngineCore WebEngineWidgets Widgets REQUIRED)

set(BUILD_TESTING OFF CACHE BOOL "Override option" FORCE)

FetchContent_Declare(
        doom_st
        URL https://github.com/KomodoPlatform/strong_type/archive/1.0.2.tar.gz
)

FetchContent_Declare(
        doom_meta
        URL https://github.com/KomodoPlatform/meta/archive/master.zip
)

set(EXPECTED_ENABLE_TESTS OFF CACHE BOOL "Override option" FORCE)

FetchContent_Declare(
        expected
        URL https://github.com/Milerius/expected/archive/patch-1.zip
)

FetchContent_Declare(
        refl-cpp
        URL https://github.com/KomodoPlatform/refl-cpp/archive/v0.6.5.zip
)

FetchContent_MakeAvailable(doom_st refl-cpp doom_meta)

add_library(doctest INTERFACE)
target_link_libraries(doctest INTERFACE doctest::doctest)

add_library(antara_entt INTERFACE)
target_link_libraries(antara_entt INTERFACE EnTT::EnTT)
add_library(antara::entt ALIAS antara_entt)

add_library(refl-cpp INTERFACE)
target_include_directories(refl-cpp INTERFACE ${refl-cpp_SOURCE_DIR})
add_library(antara::refl-cpp ALIAS refl-cpp)

FetchContent_GetProperties(expected)
if (NOT expected_POPULATED)
    FetchContent_Populate(expected)
    add_subdirectory(${expected_SOURCE_DIR} ${expected_BINARY_DIR} EXCLUDE_FROM_ALL)
endif ()


## Sodium
add_library(komodo-sodium INTERFACE)
find_package(unofficial-sodium CONFIG REQUIRED)
target_link_libraries(komodo-sodium INTERFACE unofficial-sodium::sodium)
add_library(komodo-sodium::sodium ALIAS komodo-sodium)


## Unofficial BTC
add_library(unofficial-bitcoin INTERFACE)
if (WIN32)
    target_link_libraries(unofficial-bitcoin INTERFACE ${PROJECT_SOURCE_DIR}/wally/wally.lib)
    target_include_directories(unofficial-bitcoin INTERFACE ${PROJECT_SOURCE_DIR}/wally)
else ()
    find_library(unofficial-secp secp256k1)
    find_library(unofficial-wally wallycore)
    find_path(unofficial-wally-headers wally_core.h)
    target_link_libraries(unofficial-bitcoin INTERFACE ${unofficial-wally} ${unofficial-secp})
    target_include_directories(unofficial-bitcoin INTERFACE ${unofficial-wally-headers})
    message(STATUS "Found wally -> ${unofficial-wally} ${unofficial-wally-headers}")
endif ()
add_library(unofficial-btc::bitcoin ALIAS unofficial-bitcoin)