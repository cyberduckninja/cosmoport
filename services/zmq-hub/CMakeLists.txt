set(CURRENT_TARGET zmq-hub)

set(${CURRENT_TARGET}_HEADERS
        zmq_hub.hpp
)

set(${CURRENT_TARGET}_SOURCES
        zmq_hub.cpp
)

add_library(cosmoport_${CURRENT_TARGET} STATIC
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
#    add_subdirectory(tests)
endif ()
