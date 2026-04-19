add_executable(mainAVL mainAVL.c)
add_executable(mainList mainList.c)

add_library(AVLTree AVLTree.c)
add_library(AVLTests AVLTests.c)
add_library(stack stack.c)

add_library(LinkedList LinkedList.c)
add_library(ListTests ListTests.c)

target_link_libraries(mainAVL PRIVATE AVLTree)
target_link_libraries(mainList PRIVATE LinkedList)

target_link_libraries(AVLTests PRIVATE AVLTree)
target_link_libraries(ListTests PRIVATE LinkedList)

target_link_libraries(AVLTree PRIVATE stack)
target_link_libraries(AVLTree PRIVATE m)

target_link_libraries(mainAVL PRIVATE AVLTests)
target_link_libraries(mainList PRIVATE ListTests)
