set(CURRENT_TARGET test_runner)

add_executable(${CURRENT_TARGET} main.cpp)

target_link_libraries(
        ${CURRENT_TARGET} PRIVATE
        ${CONAN_LIBS}
        cosmoport::runner
)

