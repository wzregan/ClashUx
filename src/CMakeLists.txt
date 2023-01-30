set(SRC_LIST
        main.cpp ClashUx.cpp
        ../resource/app.qrc ../resource/resources.qrc inc/ClashUx.h ClashUx.ui ServiceWidgetItem.cpp inc/ServiceWidgetItem.h ServiceWidgetItem.ui SysUtil.cpp inc/SysUtil.h )
add_executable(ClashUX ${SRC_LIST})
add_executable(util SysUtil.cpp inc/SysUtil.h)
target_link_libraries(ClashUX ${QT_FRAMEWORK} components yaml-cpp)