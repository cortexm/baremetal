# cmake script for generating binary and hex format and for flashing

add_custom_command(OUTPUT ${PROJECT_NAME}.srec
    DEPENDS ${PROJECT_NAME}
    COMMAND ${CMAKE_OBJCOPY} -Osrec ${PROJECT_NAME} ${PROJECT_NAME}.srec
)
add_custom_command(OUTPUT ${PROJECT_NAME}.hex
    DEPENDS ${PROJECT_NAME}
    COMMAND ${CMAKE_OBJCOPY} -Oihex ${PROJECT_NAME} ${PROJECT_NAME}.hex
)
add_custom_command(OUTPUT ${PROJECT_NAME}.bin
    DEPENDS ${PROJECT_NAME}
    COMMAND ${CMAKE_OBJCOPY} -Obinary ${PROJECT_NAME} ${PROJECT_NAME}.bin
)
add_custom_command(OUTPUT ${PROJECT_NAME}.lst
    DEPENDS ${PROJECT_NAME}
    COMMAND ${CMAKE_OBJDUMP} -S ${PROJECT_NAME} > ${PROJECT_NAME}.lst
)
add_custom_command(OUTPUT ${PROJECT_NAME}.sym
    DEPENDS ${PROJECT_NAME}
    COMMAND ${CMAKE_NM} -C -l -n -S ${PROJECT_NAME} > ${PROJECT_NAME}.sym
)

add_custom_target(srec
    DEPENDS ${PROJECT_NAME}.srec
)
add_custom_target(hex
    DEPENDS ${PROJECT_NAME}.hex
)
add_custom_target(bin
    DEPENDS ${PROJECT_NAME}.bin
)
add_custom_target(lst
    DEPENDS ${PROJECT_NAME}.lst
)
add_custom_target(sym
    DEPENDS ${PROJECT_NAME}.sym
)
add_custom_target(flash
    pystlink flash:erase:verify:${PROJECT_NAME}.srec
    DEPENDS ${PROJECT_NAME}.srec
)
