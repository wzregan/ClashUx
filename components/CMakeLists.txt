cmake_minimum_required(VERSION 3.24)
project(components)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(layouts)
include_directories(lib)
find_package(Qt6 COMPONENTS Core Gui Widgets StateMachine REQUIRED PATHS  /home/regan/Qt/6.4.2/gcc_64/lib/cmake/Qt6)
add_library(components
        layouts/qtmaterialsnackbarlayout.cpp
        layouts/qtmaterialsnackbarlayout.h
        layouts/qtmaterialsnackbarlayout_p.h
        lib/qtmaterialcheckable.cpp
        lib/qtmaterialcheckable.h
        lib/qtmaterialcheckable_internal.cpp
        lib/qtmaterialcheckable_internal.h
        lib/qtmaterialcheckable_p.h
        lib/qtmaterialoverlaywidget.cpp
        lib/qtmaterialoverlaywidget.h
        lib/qtmaterialripple.cpp
        lib/qtmaterialripple.h
        lib/qtmaterialrippleoverlay.cpp
        lib/qtmaterialrippleoverlay.h
        lib/qtmaterialstatetransition.cpp
        lib/qtmaterialstatetransition.h
        lib/qtmaterialstatetransitionevent.h
        lib/qtmaterialstyle.cpp
        lib/qtmaterialstyle.h
        lib/qtmaterialstyle_p.h
        lib/qtmaterialtheme.cpp
        lib/qtmaterialtheme.h
        lib/qtmaterialtheme_p.h
        qtmaterialappbar.cpp
        qtmaterialappbar.h
        qtmaterialappbar_p.h
        qtmaterialautocomplete.cpp
        qtmaterialautocomplete.h
        qtmaterialautocomplete_internal.cpp
        qtmaterialautocomplete_internal.h
        qtmaterialautocomplete_p.h
        qtmaterialavatar.cpp
        qtmaterialavatar.h
        qtmaterialavatar_p.h
        qtmaterialbadge.cpp
        qtmaterialbadge.h
        qtmaterialbadge_p.h
        qtmaterialcheckbox.cpp
        qtmaterialcheckbox.h
        qtmaterialcheckbox_p.h
        qtmaterialcircularprogress.cpp
        qtmaterialcircularprogress.h
        qtmaterialcircularprogress_internal.cpp
        qtmaterialcircularprogress_internal.h
        qtmaterialcircularprogress_p.h
        qtmaterialdialog.cpp
        qtmaterialdialog.h
        qtmaterialdialog_internal.cpp
        qtmaterialdialog_internal.h
        qtmaterialdialog_p.h
        qtmaterialdrawer.cpp
        qtmaterialdrawer.h
        qtmaterialdrawer_internal.cpp
        qtmaterialdrawer_internal.h
        qtmaterialdrawer_p.h
        qtmaterialfab.cpp
        qtmaterialfab.h
        qtmaterialfab_p.h
        qtmaterialflatbutton.cpp
        qtmaterialflatbutton.h
        qtmaterialflatbutton_internal.cpp
        qtmaterialflatbutton_internal.h
        qtmaterialflatbutton_p.h
        qtmaterialiconbutton.cpp
        qtmaterialiconbutton.h
        qtmaterialiconbutton_p.h
        qtmateriallist.cpp
        qtmateriallist.h
        qtmateriallist_p.h
        qtmateriallistitem.cpp
        qtmateriallistitem.h
        qtmateriallistitem_p.h
        qtmaterialmenu.cpp
        qtmaterialmenu.h
        qtmaterialmenu_internal.cpp
        qtmaterialmenu_internal.h
        qtmaterialmenu_p.h
        qtmaterialpaper.cpp
        qtmaterialpaper.h
        qtmaterialpaper_p.h
        qtmaterialprogress.cpp
        qtmaterialprogress.h
        qtmaterialprogress_internal.cpp
        qtmaterialprogress_internal.h
        qtmaterialprogress_p.h
        qtmaterialradiobutton.cpp
        qtmaterialradiobutton.h
        qtmaterialradiobutton_p.h
        qtmaterialraisedbutton.cpp
        qtmaterialraisedbutton.h
        qtmaterialraisedbutton_p.h
        qtmaterialscrollbar.cpp
        qtmaterialscrollbar.h
        qtmaterialscrollbar_internal.cpp
        qtmaterialscrollbar_internal.h
        qtmaterialscrollbar_p.h
        qtmaterialslider.cpp
        qtmaterialslider.h
        qtmaterialslider_internal.cpp
        qtmaterialslider_internal.h
        qtmaterialslider_p.h
        qtmaterialsnackbar.cpp
        qtmaterialsnackbar.h
        qtmaterialsnackbar_internal.cpp
        qtmaterialsnackbar_internal.h
        qtmaterialsnackbar_p.h
        qtmaterialtable.cpp
        qtmaterialtable.h
        qtmaterialtable_p.h
        qtmaterialtabs.cpp
        qtmaterialtabs.h
        qtmaterialtabs_internal.cpp
        qtmaterialtabs_internal.h
        qtmaterialtabs_p.h
        qtmaterialtextfield.cpp
        qtmaterialtextfield.h
        qtmaterialtextfield_internal.cpp
        qtmaterialtextfield_internal.h
        qtmaterialtextfield_p.h
        qtmaterialtoggle.cpp
        qtmaterialtoggle.h
        qtmaterialtoggle_internal.cpp
        qtmaterialtoggle_internal.h
        qtmaterialtoggle_p.h
        resources.qrc)
target_link_libraries(components Qt::Core Qt::Gui Qt::Widgets Qt::StateMachine)