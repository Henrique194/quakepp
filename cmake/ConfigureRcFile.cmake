function(configure_rc_file rc_name rc_dir)
  string(CONCAT RC_VERSION
      "${PROJECT_VERSION_MAJOR}, "
      "${PROJECT_VERSION_MINOR}, "
      "${PROJECT_VERSION_PATCH}, "
      "0"
  )
  set(RC_INPUT_FILE "${rc_dir}/${rc_name}.in")
  set(RC_OUTPUT_FILE "${CMAKE_CURRENT_BINARY_DIR}/${rc_name}")

  configure_file(${RC_INPUT_FILE} ${RC_OUTPUT_FILE})
  target_sources(${PACKAGE_TARNAME} PUBLIC ${RC_OUTPUT_FILE})
endfunction()
