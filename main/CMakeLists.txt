set(embed_files "network/www/index.html.gz")

set(src_dirs    network
                camera
                lcd
                face_recog
                button
                lcd/assets
                ".")

set(include_dirs    network
                    camera
                    lcd
                    face_recog
                    button
                    lcd/assets
                    ".")


idf_component_register(SRC_DIRS ${src_dirs} INCLUDE_DIRS ${include_dirs} EMBED_FILES ${embed_files})
