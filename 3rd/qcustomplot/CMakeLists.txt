add_library(qcustomplot STATIC
    ${CMAKE_CURRENT_LIST_DIR}/qcustomplot.cpp
)

target_include_directories(qcustomplot PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(qcustomplot PUBLIC
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::PrintSupport
)

set_target_properties(qcustomplot PROPERTIES
    AUTOMOC ON
    AUTOUIC OFF
    AUTORCC OFF
)
