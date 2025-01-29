# add your own executable
add_executable(main ${CMAKE_CURRENT_LIST_DIR}/Main.c)
target_include_directories(main PUBLIC ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(
  main
  pico_stdlib
  pico_bootrom
  hardware_watchdog
  freeRtosUtils
  common_lib
  enV5_hw_controller)
create_env5_executable(main)
