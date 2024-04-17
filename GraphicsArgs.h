/*
 *  GraphicsArgs.h
 *
 *  Created by Pete Willemsen on 10/6/09.
 *  Copyright 2009 Department of Computer Science, University of Minnesota-Duluth. All rights reserved.
 *
 * This file is part of libSIVELab (libsivelab).
 *
 * libsivelab is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * libsivelab is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libsivelab.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <iostream>
#include <string>

#define GLM_FORCE_RADIANS
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "ArgumentParsing.h"

// Derived from the Argument parsing class so that each can add to
// this argument list.
class GraphicsArgs : public ArgumentParsing
{
public:
  GraphicsArgs();
  ~GraphicsArgs() = default;

  void process(int argc, char *argv[]);

  const int default_WindowSize = 200;

  bool verbose;

  int width;
  int height;

  glm::vec3 bgColor;

  std::string inputFileName;
  std::string outputFileName;
};
