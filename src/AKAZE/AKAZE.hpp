#ifndef DO_AKAZE_HPP
#define DO_AKAZE_HPP

#include <DO/Features.hpp>

namespace DO {

  class AKAZEFeatureDetector
  {
  public:
    AKAZEFeatureDetector()
      : firstOctave(0)
      , numOctaves(-1)
      , numScales(3)
    {}
    void setFirstOctave(int n) { firstOctave = n; }
    void setNumOctaves(int n) { numOctaves = n; }
    void setNumScales(int n) { numScales = n; }

    std::vector<OERegion> run(const Image<unsigned char>& image);

  private:
    int firstOctave;
    int numOctaves;
    int numScales;
  };

} /* namespace DO */

#endif /* DO_AKAZE_HPP */