#include <iostream>
#include <cmath>

#include "png++/png.hpp"
#include "GraphicsArgs.h"

#define GLM_FORCE_RADIANS
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

int main(int argc, char *argv[])
{
  GraphicsArgs args;
  args.process(argc, argv);

  int width = args.width;
  int height = args.height;
  png::image<png::rgb_pixel> imData(width, height);

#pragma unroll
  for (unsigned int idx=0; idx<imData.get_height()*imData.get_width(); ++idx)
    {
      size_t x = idx % width;
      size_t y = static_cast<size_t>( floor(idx / static_cast<float>(imData.get_width())) );

      // assert((y >= 0) && (y < h) && x >= 0 && x < w);

      // radial distance to edge of image
      float max_distance = sqrt( static_cast<float>((width/2.0*width/2.0) + (height/2.0*height/2.0)) );
      float dist = sqrt( static_cast<float>((x - width/2.0)*(x - width/2.0) + (y - height/2.0)*(y - height/2.0)) ) / max_distance;

      glm::vec3 c(static_cast<int>(dist * 255), 
		  static_cast<int>(dist * 255), 
		  static_cast<int>(dist * 255));

      // The origin for indexing the height is in lower left...
      imData[y][x] = png::rgb_pixel( c[0],
				     c[1],
				     c[2] );
    }

  imData.write("gradient.png");

  exit(EXIT_SUCCESS);
}
