cmake_minimum_required(VERSION 3.10.2)
   project(ur_description)
   find_package(ament_cmake REQUIRED)

   install(DIRECTORY meshes DESTINATION "share/${PROJECT_NAME}")
   install(DIRECTORY urdf DESTINATION "share/${PROJECT_NAME}")
   ament_package()
