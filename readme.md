# Renderer
This is a learning project designed to render meshes, and eventually render materials.

# Usage
To pull and build:
```
git clone https://github.com/PeterDaGrape/Renderer.git
cd Renderer
mkdir build
cd build
cmake -G "Ninja" ..
cmake --build .
```
run with
```
./renderer
```

Currently expects to run from build, and will navigate to the meshes folder from build, modify path in `globals.h` if you wish to load from elsewhere or use custom models.


# Features:
Render any .obj file 
- Tested with Blender (file/export/Wavefront ().obj then set forward axis to z-)
- Draw a wireframe of the objects with backface culling
- Apply camera rotation to scene


