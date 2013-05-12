#ifndef TextureEffect_h
#define TextureEffect_h

#include "Effect.h"
#include "Util.h"
class TextureEffect: public Effect{
private:
    GLuint image;
    GLuint ramp;
public:
    virtual void draw()
	{
        glUseProgram(programID);
		glActiveTexture(GL_TEXTURE1);
		LoadGLTexture("image.png");
        glUniform1i(image, 1);
		glActiveTexture(GL_TEXTURE2);
		LoadGLTexture("rampTexture2.bmp");
        glUniform1i(ramp, 2);
		glActiveTexture(GL_TEXTURE0);
        Effect::draw();
	}
    TextureEffect(int screenWidth, int screenHeight):Effect("texture_effect_shader.frag",&screenWidth, &screenHeight)
	{
        ramp = glGetUniformLocation(programID, "ramp");
        if (ramp < 0) {
            fprintf(stderr, "Could not bind attribute %s\n", "ramp");
        }
		image = glGetUniformLocation(programID, "image");
        if (image < 0) {
            fprintf(stderr, "Could not bind attribute %s\n", "image");
        }

    }
};

#endif
