/*L*****************************************************************************
*
*  Copyright (c) 2015, Smart Surveillance Interest Group, all rights reserved.
*
*  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
*
*  By downloading, copying, installing or using the software you agree to this
*  license. If you do not agree to this license, do not download, install, copy
*  or use the software.
*
*                Software License Agreement (BSD License)
*             For Smart Surveillance Interest Group Library
*                         http://ssig.dcc.ufmg.br
*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions are met:
*
*    1. Redistributions of source code must retain the above copyright notice,
*       this list of conditions and the following disclaimer.
*
*    2. Redistributions in binary form must reproduce the above copyright
*       notice, this list of conditions and the following disclaimer in the
*       documentation and/or other materials provided with the distribution.
*
*    3. Neither the name of the copyright holder nor the names of its
*       contributors may be used to endorse or promote products derived from
*       this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
*  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
*  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
*  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
*  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
*  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
*  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
*  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
*  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
*  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
*  POSSIBILITY OF SUCH DAMAGE.
*****************************************************************************L*/

#ifndef _SSIG_DESCRIPTORS_GLCM_FEATURES_HPP_
#define _SSIG_DESCRIPTORS_GLCM_FEATURES_HPP_

#include <opencv2/core.hpp>

#include "descriptor_2d.hpp"

namespace ssig {
class GrayLevelCoOccurrence : public Descriptor2D {
 public:
  DESCRIPTORS_EXPORT explicit GrayLevelCoOccurrence(const cv::Mat& input);
  DESCRIPTORS_EXPORT explicit GrayLevelCoOccurrence(
    const cv::Mat& input,
    const GrayLevelCoOccurrence& descriptor);
  DESCRIPTORS_EXPORT explicit GrayLevelCoOccurrence(
    const GrayLevelCoOccurrence& descriptor);

  DESCRIPTORS_EXPORT virtual ~GrayLevelCoOccurrence(void) = default;

  DESCRIPTORS_EXPORT int getLevels() const;
  DESCRIPTORS_EXPORT int getBins() const;

  DESCRIPTORS_EXPORT void setLevels(const int levels);
  DESCRIPTORS_EXPORT void setBins(const int bins);

  // Set the direction to count the co-occurrence
  DESCRIPTORS_EXPORT void setDirection(int x, int y);

 protected:
  DESCRIPTORS_EXPORT void read(const cv::FileNode& fn) override;
  DESCRIPTORS_EXPORT void write(cv::FileStorage& fs) const override;
  DESCRIPTORS_EXPORT void beforeProcess() override;
  DESCRIPTORS_EXPORT void extractFeatures(const cv::Rect& patch,
                                          cv::Mat& output) override;

 private:
  // private members
  // the number of levels of intensity
  int mLevels = 256;
  int mBins = 8;

  int mDi = 0, mDj = 1;

  cv::Mat mGreyImg;
  static int isValidPixel(int i, int j, int rows, int cols);
};
}  // namespace ssig
#endif  // !_SSIG_DESCRIPTORS_GLCM_FEATURES_HPP_
