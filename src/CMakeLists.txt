ADD_LIBRARY(hidra SHARED layer.c colorfx.c)
ADD_EXECUTABLE(hidravfx main.c options.c pnm.c)
TARGET_LINK_LIBRARIES(hidravfx m hidra)