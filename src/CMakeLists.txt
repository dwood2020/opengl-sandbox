# Sub-level: src subdirectory
# ===========================


target_sources(${MAIN_TARGET_NAME} PRIVATE
    Lighting.cpp
    TextureData.cpp
    Texture.cpp
    sandbox.cpp)


add_subdirectory(camera)