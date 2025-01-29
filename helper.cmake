include(FetchContent)

function(load_enV5)
  message(NOTICE "load runtime.enV5")
  FetchContent_Declare(
    runtime_env5
    GIT_REPOSITORY https://github.com/es-ude/elastic-ai.runtime.enV5.git
    GIT_TAG v3.11.1)
  FetchContent_Populate(runtime_env5)

  message(NOTICE "add runtime.enV5 init scripts")
  include(${runtime_env5_SOURCE_DIR}/enV5_init.cmake)
endfunction()
