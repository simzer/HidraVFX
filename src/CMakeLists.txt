ADD_LIBRARY(hidra SHARED layer.c effects.c)
ADD_EXECUTABLE(hidravfx main.c options.c pnm.c)
TARGET_LINK_LIBRARIES(hidravfx m hidra)
INSTALL(
  TARGETS hidravfx hidra hidra
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)
INSTALL_FILES(/etc/bash_completion.d . hidravfx.completion)
INSTALL_FILES(/usr/include/hidravfx .h effects.h layer.h hidra.h)
ADD_CUSTOM_COMMAND(
   OUTPUT  effects.c effects.h
   COMMAND perl ../src/codegen.pl
   DEPENDS codegen.pl effects.pl)
  