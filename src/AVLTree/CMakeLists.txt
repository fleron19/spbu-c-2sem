add_executable(aerosoft main.c)

add_library(AVLTree AVLTree.c)
add_library(stack stack.c)
add_library(tests tests.c)

target_link_libraries(aerosoft PRIVATE AVLTree)
target_link_libraries(tests PRIVATE AVLTree)
target_link_libraries(AVLTree PRIVATE stack)
target_link_libraries(AVLTree PRIVATE m)
target_link_libraries(aerosoft PRIVATE tests)
