
set(src_dirs    network
                camera
                ".")

set(include_dirs    network
                    camera
                    ".")


idf_component_register(SRC_DIRS ${src_dirs} INCLUDE_DIRS ${include_dirs})
