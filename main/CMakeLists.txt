
set(src_dirs    network
                camera
                lcd
                face_recog
                button
                fingerprint
                sdcard
                usb_msc
                sqlite_db
                utils
                lcd/asset
                ".")

set(include_dirs    network
                    camera
                    lcd
                    face_recog
                    button
                    fingerprint
                    sdcard
                    usb_msc
                    sqlite_db
                    utils
                    lcd/asset
                    ".")


idf_component_register(SRC_DIRS ${src_dirs} INCLUDE_DIRS ${include_dirs})

