cmake_minimum_required(VERSION 3.28)
project(project_esprit_model_C)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)

file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR})

# Set SFML_DIR (adjust this to your SFML installation path)
set(SFML_DIR "C:/Libraries/SFML-2.6.2/lib/cmake/SFML")

# Find SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Add the executable
add_executable(project_esprit_model_C
        main.cpp
        scripts/Character.cpp
        scripts/Character.h
        scripts/Bar.cpp
        scripts/Bar.h
        Testing/Testing.cpp
        data_structures/ForwardList.cpp
        Testing/Testing.h
        data_structures/ForwardList.h
        data_structures/Node.cpp
        data_structures/Node.h
        data_structures/PriorityQueue.cpp
        data_structures/PriorityQueue.h
        data_structures/BiNode.cpp
        data_structures/BiNode.h
        data_structures/DoubleList.cpp
        data_structures/DoubleList.h
        Visuals/window.cpp
        core/Command.cpp
        core/Command.h
        core/commands/UniCommands.cpp
        core/commands/UniCommands.h
        scripts/Helper.h
        scripts/Helper.cpp
        data_structures/HashTable.cpp
        data_structures/HashTable.h
        data_structures/XFastTrie.cpp
        data_structures/XFastTrie.h
        data_structures/BST.cpp
        data_structures/BST.h
        core/Config/Config.cpp
        core/Config/Config.h
        scripts/Item.h
        scripts/Item.cpp
        data_structures/XFastTrieBeta.h
        data_structures/XFastTrieBeta.cpp
        scripts/TestUnit.h
        data_structures/AVL.h
        data_structures/AVL.cpp
        data_structures/YFastTrie.h
        data_structures/YFastTrie.cpp
        data_structures/MockUpYFastTrie.h
        data_structures/MockUpYFastTrie.cpp
)

    target_link_libraries(project_esprit_model_C sfml-graphics sfml-window sfml-system)
