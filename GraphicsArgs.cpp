/*
 *  handleGraphicsArgs.cpp
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

#include "GraphicsArgs.h"

GraphicsArgs::GraphicsArgs()
  : verbose(false),
    width(default_WindowSize), height(default_WindowSize),
    bgColor(0.0, 0.0, 0.0),
    outputFileName("default.png")
{
  reg("help",  ArgumentParsing::NONE, "help/usage information",'?');
  reg("verbose",  ArgumentParsing::NONE, "turn on verbose output",'v');
  reg("inputfile",  ArgumentParsing::STRING, "input file name to use", 'i');
  reg("outputfile",  ArgumentParsing::STRING, "output file name to use",'o');
  reg("width",  ArgumentParsing::INT, "width of output image (default is 100)",'w');
  reg("height",  ArgumentParsing::INT, "height of output image (default is 100)",'h');
}

void GraphicsArgs::process(int argc, char *argv[])
{
  processCommandLineArgs(argc, argv);

  if (isSet("help")) {
    printUsage();
    exit(EXIT_SUCCESS);
  }

  verbose = isSet("verbose");
  if (verbose) { std::cout << "Verbose Output: ON\n"; }

  isSet("width", width);
  if (verbose) { std::cout << "Setting width to " << width << '\n'; }

  isSet("height", height);
  if (verbose) { std::cout << "Setting height to " << height << '\n'; }

  isSet("inputfile", inputFileName);
  if (verbose) { std::cout << "Setting inputFileName to " << inputFileName << '\n'; }

  isSet("outputfile", outputFileName);
  if (verbose) { std::cout << "Setting outputFileName to " << outputFileName << '\n'; }
}
