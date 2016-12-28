//
// Copyright (c) 2014 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
#pragma once

#include "GLES2.h"
#include <string>
#include <vector>

#define SHADER_SOURCE(...) #__VA_ARGS__

GLuint CompileShader(GLenum type, const std::string &source);

GLuint CompileShaderFromFile(GLenum type, const std::string &sourcePath);

GLuint
CompileProgramWithTransformFeedback(const std::string &vsSource,
                                    const std::string &fsSource,
                                    const std::vector<std::string> &transformFeedbackVaryings,
                                    GLenum bufferMode);

GLuint CompileProgram(const std::string &vsSource, const std::string &fsSource);

GLuint CompileProgramFromFiles(const std::string &vsPath, const std::string &fsPath);
