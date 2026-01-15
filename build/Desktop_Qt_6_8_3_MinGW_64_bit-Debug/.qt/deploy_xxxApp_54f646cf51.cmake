include("D:/xxxapp/xxxApp/build/Desktop_Qt_6_8_3_MinGW_64_bit-Debug/.qt/QtDeploySupport.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/xxxApp-plugins.cmake" OPTIONAL)
set(__QT_DEPLOY_I18N_CATALOGS "qtbase")

qt6_deploy_runtime_dependencies(
    EXECUTABLE D:/xxxapp/xxxApp/build/Desktop_Qt_6_8_3_MinGW_64_bit-Debug/xxxApp.exe
    GENERATE_QT_CONF
)
