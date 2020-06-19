#include "Texture.h"

using namespace engine;

void Texture::create(const char* path, unsigned int& textureId) {

	glGenTextures(1, &textureId);
	bind(textureId, GL_TEXTURE_2D);

	setParameters();

	int width, height, channel;

	stbi_set_flip_vertically_on_load(true);
	unsigned char* image = stbi_load(
		path, &width, &height, &channel, 0
	);

	if (image) {//if image loads correctly
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	stbi_image_free(image);
}

void Texture::create(unsigned int& textureId, Dimensions dim, unsigned int type) {
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, type,
		dim.width, dim.height, 0, type, GL_FLOAT, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}