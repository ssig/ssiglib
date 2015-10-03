/*L*************************************************************************************************
*
*  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
* 
*  By downloading, copying, installing or using the software you agree to this license. If you do 
*  not agree to this license, do not download, install, copy or use the software.
*
*                            Software License Agreement (BSD License)
*                               For Smart Surveillance Framework
*                                 http://ssig.dcc.ufmg.br/ssf/
*
*  Copyright (c) 2013, Smart Surveillance Interest Group, all rights reserved.
*  
*  Redistribution and use in source and binary forms, with or without modification, are permitted 
*  provided that the following conditions are met:
*
*    1. Redistributions of source code must retain the above copyright notice, this list of 
*       conditions and the following disclaimer.
*
*    2. Redistributions in binary form must reproduce the above copyright notice, this list of 
*       conditions and the following disclaimer in the documentation and/or other materials 
*       provided with the distribution.
*
*    3. Neither the name of the copyright holder nor the names of its contributors may be used to 
*       endorse or promote products derived from this software without specific prior written 
*       permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR 
*  IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY 
*  AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
*  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
*  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
*  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY 
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
*  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
*  POSSIBILITY OF SUCH DAMAGE.
*************************************************************************************************L*/

#ifndef _SSF_ALGORITHMS_DESCRIPTOR_INTERFACE_HPP_
#define _SSF_ALGORITHMS_DESCRIPTOR_INTERFACE_HPP_

#include <forward_list>
#include "alg_defs.hpp"
#include "algorithm.hpp"
#include <opencv2/core.hpp>

namespace cv{
class Mat;
}

namespace ssf{

class DescriptorInterface : public ssf::Algorithm{

public:
  DescriptorInterface(const cv::Mat& input);

  DescriptorInterface(
    const cv::Mat& input,
    const cv::Rect& patch);

  DescriptorInterface(
    const cv::Mat& input,
    const std::forward_list<cv::Rect>& patchesBegin);

  virtual ~DescriptorInterface(void) = default;

  /**
  @return true if there is a patch to process and false otherwise.
  */
  virtual bool hasNext() =0;
  /**
  On the first call to this function it returns the feature vector
  of the mat set up in the constructor call.
  @param out The matrix that will contain the feature vector for the current patch.
  */
  virtual void nextFeatureVector(cv::Mat& out) = 0;
protected:
  std::forward_list<cv::Rect> mPatches;
  cv::Mat mImage;
};

}

#endif // !_SSF_ALGORITHMS_DESCRIPTOR_INTERFACE_HPP_

