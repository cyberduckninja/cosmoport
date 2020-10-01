set(CURRENT_TARGET runner)

list(APPEND CURRENT_${TARGET_HEADERS}
        process_manager.hpp
)

list(APPEND CURRENT_${TARGET_HEADERS}
        process_manager.cpp
)


add_library(cosmoport_${CURRENT_TARGET} STATIC
            ${CURRENT_${TARGET_HEADERS}}
            ${CURRENT_${TARGET_HEADERS}}
)


add_library(cosmoport::${CURRENT_TARGET} ALIAS cosmoport_${CURRENT_TARGET})

set_property(TARGET cosmoport_${CURRENT_TARGET} PROPERTY EXPORT_NAME ${CURRENT_TARGET})

target_link_libraries(
        cosmoport_${CURRENT_TARGET} PRIVATE
        ${CONAN_LIBS}
)

target_include_directories(
        cosmoport_${CURRENT_TARGET}
        PUBLIC
        "../../../"
)

add_subdirectory(test)

install(TARGETS
        cosmoport_${CURRENT_TARGET}

        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)
