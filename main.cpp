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

  float max_distance = sqrt( static_cast<float>((imWidth/2.0F*imWidth/2.0F) + (imHeight/2.0F*imHeight/2.0F)) );

#pragma unroll
  for (unsigned int idx=0; idx<imHeight*imWidth; ++idx)
    {
      auto row = idx % imWidth;
      auto col = static_cast<size_t>( floor(idx / static_cast<float>(imWidth)) );

      // radial distance to edge of image
      float dist = sqrt( static_cast<float>((row - imWidth/2.0)*(row - imWidth/2.0) + (col - imHeight/2.0)*(col - imHeight/2.0)) ) / max_distance;

      glm::vec3 pixelColor(dist * 255, dist * 255, dist * 255);

      // The origin for indexing the height is in lower left...
      imData[col][row] = png::rgb_pixel(pixelColor[0],pixelColor[1],pixelColor[2] );
    }

  imData.write("gradient.png");

  exit(EXIT_SUCCESS);
}
