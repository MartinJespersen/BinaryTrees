set(This BinaryTreeTests)

set(Sources
    ${This}.cpp

)
include(GoogleTest)
add_executable(${This} ${Sources})

target_link_libraries(${This} PRIVATE
    gtest_main
    BinaryTree 

)
gtest_discover_tests(${This})

add_test(
    NAME TestCase1
    COMMAND ${This}
)


