add_executable(aerosoft main.c)

add_library(AVLTree AVLTree.c)

target_link_libraries(aerosoft PRIVATE AVLTree)
