struct GeometryInfo {
    unsigned int num_verts;
    unsigned int floatsToStartOfGeometry;
    const char *geometryName;
};

constexpr unsigned int vertexDataSize = 18;
float vertData[vertexDataSize]{ 1,0,1,-1,0,-1,-1,0,1,1,0,1,1,0,-1,-1,0,-1};

constexpr unsigned int geometryInfoSize = 1;
GeometryInfo geometryInfo[geometryInfoSize] = { 
GeometryInfo{0,18,"square.obj"}
};
