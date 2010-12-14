ADD_LIBRARY(hidra SHARED coloreffects.c)
ADD_EXECUTABLE(hidravfx main.c)
TARGET_LINK_LIBRARIES(hidravfx hidra)