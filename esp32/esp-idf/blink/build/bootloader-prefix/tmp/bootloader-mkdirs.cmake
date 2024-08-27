# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/guest_rclabs/esp/v5.3/esp-idf/components/bootloader/subproject"
  "D:/Abhi_local_folder/ESP32/ESP_IDF_Projects/blink/build/bootloader"
  "D:/Abhi_local_folder/ESP32/ESP_IDF_Projects/blink/build/bootloader-prefix"
  "D:/Abhi_local_folder/ESP32/ESP_IDF_Projects/blink/build/bootloader-prefix/tmp"
  "D:/Abhi_local_folder/ESP32/ESP_IDF_Projects/blink/build/bootloader-prefix/src/bootloader-stamp"
  "D:/Abhi_local_folder/ESP32/ESP_IDF_Projects/blink/build/bootloader-prefix/src"
  "D:/Abhi_local_folder/ESP32/ESP_IDF_Projects/blink/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/Abhi_local_folder/ESP32/ESP_IDF_Projects/blink/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "D:/Abhi_local_folder/ESP32/ESP_IDF_Projects/blink/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
