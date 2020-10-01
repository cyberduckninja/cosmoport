set(CURRENT_TARGET log)

list(APPEND CURRENT_${TARGET_HEADERS}
        log.hpp
)

list(APPEND CURRENT_${TARGET_HEADERS}
        log.cpp
)


add_library(cosmoport_${CURRENT_TARGET} STATIC
            ${CURRENT_${TARGET_HEADERS}}
            ${CURRENT_${TARGET_HEADERS}}
)


add_library(cosmoport::${CURRENT_TARGET} ALIAS cosmoport_${CURRENT_TARGET})

set_property(TARGET cosmoport_${CURRENT_TARGET} PROPERTY EXPORT_NAME ${CURRENT_TARGET})

target_link_libraries(
        cosmoport_${CURRENT_TARGET} PRIVATE
        ${Boost_LIBRARIES}
        ${CONAN_LIBS}
)

target_include_directories(
        cosmoport_${CURRENT_TARGET}
        PUBLIC
        "../../../"
)

if(DEV_MODE)
    #add_subdirectory(test)
endif()

install(TARGETS
        cosmoport_${CURRENT_TARGET}

        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)
