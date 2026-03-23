add_executable(aerosoft main.c)

add_library(AVLTree AVLTree.c)
add_library(stack stack.c)

target_link_libraries(aerosoft PRIVATE AVLTree)
target_link_libraries(AVLTree PRIVATE stack)
