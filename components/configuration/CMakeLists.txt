set(CURRENT_TARGET configuration)

list(APPEND CURRENT_${TARGET_HEADERS}
        configuration.hpp
)

#list(APPEND CURRENT_${TARGET_HEADERS}
#)


add_library(cosmoport_${CURRENT_TARGET} INTERFACE
#            ${CURRENT_${TARGET_HEADERS}}
#            ${CURRENT_${TARGET_HEADERS}}
)


add_library(cosmoport::${CURRENT_TARGET} ALIAS cosmoport_${CURRENT_TARGET})

set_property(TARGET cosmoport_${CURRENT_TARGET} PROPERTY EXPORT_NAME ${CURRENT_TARGET})

target_link_libraries(
        cosmoport_${CURRENT_TARGET}
        INTERFACE
        #PRIVATE
        #${Boost_LIBRARIES}
        #${CONAN_LIBS}
)

target_include_directories(
        cosmoport_${CURRENT_TARGET}
        INTERFACE
        "../.."
)


install(TARGETS
        cosmoport_${CURRENT_TARGET}

        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)
