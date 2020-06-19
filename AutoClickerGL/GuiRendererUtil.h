#pragma once

#include"GL/glew.h"

namespace engine::gui::util {

	struct Indirect {
		unsigned int count = 0;
		unsigned int instanceCount = 0;
		unsigned int first = 0;
		unsigned int baseInstance = 0;
	};
	struct Renderable {

		unsigned int vao = 0;
		unsigned int indirectBuffer = 0;
		unsigned int drawCount = 0;

	};
	struct SSBOData {
		unsigned int ssbo = 0;
		void* persistentMap = 0;
	};

	constexpr static unsigned int persistent_map_flags = GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT;

	template<typename T>
	inline void allocateSSBOSpace(unsigned int num_elements, const GLenum target = GL_SHADER_STORAGE_BUFFER, const void* initialData = NULL) {
		glBufferStorage(target, sizeof(T) * num_elements, initialData, persistent_map_flags);
	}

	template<typename T>
	[[nodiscard]] inline void* genSSBOPersistentMap(unsigned int num_elements, const GLenum target = GL_SHADER_STORAGE_BUFFER) {
		return glMapBufferRange(target, 0, sizeof(T) * num_elements, persistent_map_flags);
	}

	template<typename ARRAY_TYPE, typename SIZE>
	inline void updatePersistentMap(ARRAY_TYPE* persistentMap, void* ssboData, const unsigned int numDataToCpy, const unsigned int persistentMapStartPoint) {
		memcpy(&persistentMap[persistentMapStartPoint], ssboData, sizeof(SIZE) * numDataToCpy);
	}

};