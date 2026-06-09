add_executable(print_ip main.cpp)

if (MSVC)
    target_compile_options(print_ip PRIVATE /W4)
else()
    target_compile_options(print_ip PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

# Installation

install(TARGETS print_ip RUNTIME DESTINATION bin)