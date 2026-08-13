#ifndef SHADER_UTILS_H
#define SHADER_UTILS_H

#include <glad/gl.h>
#include <stdbool.h>

const char *shader_type_as_cstr(GLenum shader_type);

bool compile_shader_source(const GLchar *source, GLenum shader_type,
                           GLuint *shader);

bool compile_shader_file(const char *file_path, GLenum shader_type,
                         GLuint *shader);

bool link_program(GLuint vert_shader, GLuint frag_shader, GLuint *program);

bool load_shaders_program(const char *vertex_file_path,
                          const char *fragment_file_path, GLuint *program);

#endif
