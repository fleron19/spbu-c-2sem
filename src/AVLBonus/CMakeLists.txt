add_executable(mainAVL mainAVL.c)
add_executable(mainList mainList.c)

add_library(AVLTreeN AVLTree.c)
add_library(AVLTests AVLTests.c)
add_library(stackN stack.c)

add_library(LinkedList LinkedList.c)
add_library(ListTests ListTests.c)

target_link_libraries(mainAVL PRIVATE AVLTreeN)
target_link_libraries(mainList PRIVATE LinkedList)

target_link_libraries(AVLTests PRIVATE AVLTreeN)
target_link_libraries(ListTests PRIVATE LinkedList)

target_link_libraries(AVLTreeN PRIVATE stackN)
target_link_libraries(AVLTreeN PRIVATE m)

target_link_libraries(mainAVL PRIVATE AVLTests)
target_link_libraries(mainList PRIVATE ListTests)
