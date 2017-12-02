add_subdirectory(QuadrupedRobot_Choreonoid)

MAP_ADD_STR(hdrs "${PROJECT_NAME}/" headers)
set(headers ${headers} PARENT_SCOPE)
