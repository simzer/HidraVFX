ADD_LIBRARY(hidra SHARED layer.c colorfx.c blending.c conform.c)
ADD_EXECUTABLE(hidravfx main.c options.c pnm.c)
TARGET_LINK_LIBRARIES(hidravfx m hidra)
INSTALL(TARGETS hidravfx hidra hidra
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)