
add_executable(replacer replacer.cpp replacer.h)

install(TARGETS replacer
        RUNTIME DESTINATION bin)
