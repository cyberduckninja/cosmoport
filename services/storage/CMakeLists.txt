set(CURRENT_TARGET storage)

set(${CURRENT_TARGET}_HEADERS
        storage_engine.hpp
        hash_storage.hpp
        storage.hpp
)

set(${CURRENT_TARGET}_SOURCES
        storage_engine.cpp
        hash_storage.cpp
        storage.cpp
)

add_library(
        cosmoport_${CURRENT_TARGET}
        STATIC
        ${${CURRENT_TARGET}_HEADERS}
        ${${CURRENT_TARGET}_SOURCES}
)


add_library(cosmoport::${CURRENT_TARGET} ALIAS cosmoport_${CURRENT_TARGET})

set_property(TARGET cosmoport_${CURRENT_TARGET} PROPERTY EXPORT_NAME ${CURRENT_TARGET})

target_link_libraries(
        cosmoport_${CURRENT_TARGET} PRIVATE
        cosmoport::log
        ${CONAN_LIBS}
)

target_include_directories(cosmoport_${CURRENT_TARGET} PUBLIC "")

if (DEV_MODE)
    add_subdirectory(tests)
endif ()
