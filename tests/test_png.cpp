#include <catch2/catch_test_macros.hpp>

#include "png++/png.hpp"

TEST_CASE( "Writing PNG Image" )
{
  int width = 10;
  int height = 10;
  png::image<png::rgb_pixel> imData(width, height);

  for (unsigned int idx=0; idx<imData.get_height()*imData.get_width(); ++idx)
    {
      size_t x = idx % imData.get_width();
      size_t y = static_cast<size_t>( floor(idx / static_cast<float>(imData.get_width())) );
      imData[y][x] = png::rgb_pixel( 255, 0, 128 );
    }

  std::string fname = "utest.png";
  imData.write(fname);

  png::image< png::rgb_pixel > readImageData;
  readImageData.read(fname);

  REQUIRE( readImageData.get_height() == height );
  REQUIRE( readImageData.get_width() == width );

  for (unsigned int idx=0; idx<readImageData.get_height()*readImageData.get_width(); ++idx)
    {
      size_t x = idx % readImageData.get_width();
      size_t y = static_cast<size_t>( floor(idx / static_cast<float>(readImageData.get_width())) );

      png::rgb_pixel texel;
      texel = readImageData[y][x];

      REQUIRE( texel.red == 255 );
      REQUIRE( texel.green == 0 );
      REQUIRE( texel.blue == 128 );
    }
}

