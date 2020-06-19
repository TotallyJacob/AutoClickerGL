#pragma once
#include"GL/glew.h"

#define STB_IMAGE_IMPLEMENTATION
#include"stb.h"

#include<iostream>

#pragma once

namespace engine {

	class Texture
	{
	public:

		struct Dimensions {
			unsigned int width;
			unsigned int height;
		};

		inline static void setParameters() {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		}
		inline static void setToSlot(unsigned int& slot) {

			glActiveTexture(GL_TEXTURE0 + slot);
		}
		inline static void bind(unsigned int& textureId, unsigned int textureType = GL_TEXTURE_2D) {
			glBindTexture(textureType, textureId);
		}

		static void create(const char* path, unsigned int& textureId);

		static void create(unsigned int& textureID, Dimensions dim, unsigned int type = GL_DEPTH_COMPONENT);

	};
};


