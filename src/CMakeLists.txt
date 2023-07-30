

set(This BinaryTree)

project(${This})

set(Headers
    ${This}.hpp
)

set(Sources
    ${This}.cpp
)

add_library(${This} STATIC ${Sources} ${Headers})
#target_include_directories(${This} PUBLIC include)