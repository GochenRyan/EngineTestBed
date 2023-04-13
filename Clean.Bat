IF EXIST lib (
  rmdir /s /q lib
) ELSE (
  echo lib does not exist.
)


IF EXIST .\\Vendor\\SDL\\build (
  rmdir /s /q .\\Vendor\\SDL\\build
) ELSE (
  echo Vendor\\SDL\\build does not exist.
)

IF EXIST .\\Vendor\\freetype\\build (
  rmdir /s /q .\\Vendor\\freetype\\build
) ELSE (
  echo Vendor\\freetype\\build does not exist.
)