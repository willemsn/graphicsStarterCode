#include <cmath>

#include "glm/glm.hpp"

#include "png++/png.hpp"
#include "GraphicsArgs.h"

int main(int argc, char *argv[])
{
  GraphicsArgs args;
  args.process(argc, argv);

  png::image<png::rgb_pixel> imData(args.width, args.height);

  const auto imWidth = imData.get_width();
  const auto imHeight = imData.get_height();

#pragma unroll
  for (unsigned int idx=0; idx<imHeight*imWidth; ++idx)
    {
      auto row = idx % imWidth;
      auto col = static_cast<size_t>( floor(idx / static_cast<float>(imWidth)) );

      // image plane dimensional information
      float l = -0.5;
      float r = 0.5;
      float b = -0.5;
      float t = 0.5;

      // Camera basis vectors - orthonormal
      glm::vec3 U(1,0,0);
      glm::vec3 V(0,1,0);
      glm::vec3 W(0,0,1);

      // relative location of the ray on the image plane
      float j = (float)row;
      float u = l + (r - l)*(col+0.5F)/imWidth;
      float v = b + (t - b)*(j+0.5F)/imHeight;

      glm::vec3 origin(0.0, 0.0, 0.0);
      glm::vec3 direction = -W + u*U + v*V;

      direction /= glm::length(direction);
      glm::vec3 mapToRGB = direction / 2.0F + glm::vec3(0.5, 0.5, 0.5);

      glm::vec3 pixelColor(mapToRGB.r * 255, mapToRGB.g * 255, mapToRGB.b * 255);

      // The origin for indexing the height is in lower left...
      imData[col][row] = png::rgb_pixel(pixelColor[0],pixelColor[1],pixelColor[2] );
    }

  imData.write( args.outputFileName);

  exit(EXIT_SUCCESS);
}
