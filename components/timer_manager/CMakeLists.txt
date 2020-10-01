set(CURRENT_TARGET timer_manager)

list(APPEND CURRENT_TARGET_HEADERS
        timer_manager.hpp

)

list(APPEND CURRENT_TARGET_SOURCES
        timer_manager.cpp
)


add_library(cosmoport_${CURRENT_TARGET} STATIC
            ${CURRENT_TARGET_HEADERS}
            ${CURRENT_TARGET_SOURCES}
)


add_library(cosmoport::${CURRENT_TARGET} ALIAS cosmoport_${CURRENT_TARGET})

set_property(TARGET cosmoport_${CURRENT_TARGET} PROPERTY EXPORT_NAME ${CURRENT_TARGET})

target_link_libraries(
        cosmoport_${CURRENT_TARGET} PRIVATE
        goblin-engineer
        cosmoport::network
        ${Boost_LIBRARIES}
        ${CONAN_LIBS}
)

target_include_directories(
        cosmoport_${CURRENT_TARGET}
        PUBLIC
        "${PROJECT_SOURCE_DIR}/components/timer_manager"
)

install(TARGETS
        cosmoport_${CURRENT_TARGET}

        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)

if (DEV_MODE)
    add_subdirectory(test)
endif()
