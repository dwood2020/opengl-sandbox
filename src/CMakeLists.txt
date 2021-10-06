# Sub-level: src subdirectory
# ===========================


target_sources(${MAIN_TARGET_NAME} PRIVATE
    Lighting.cpp
    TextureData.cpp
    Texture.cpp
    sandbox.cpp)


add_subdirectory(camera)
add_subdirectory(events)
add_subdirectory(glad)
add_subdirectory(material)
add_subdirectory(mesh)
add_subdirectory(renderer)