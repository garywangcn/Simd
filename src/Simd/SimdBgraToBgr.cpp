/*
* Simd Library.
*
* Copyright (c) 2011-2013 Yermalayeu Ihar.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy 
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell 
* copies of the Software, and to permit persons to whom the Software is 
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in 
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/
#include "Simd/SimdEnable.h"
#include "Simd/SimdMemory.h"
#include "Simd/SimdInit.h"
#include "Simd/SimdBgraToBgr.h"

namespace Simd
{
	namespace Base
	{
		void BgraToBgr(const uchar *bgra, size_t size, uchar *bgr, bool lastRow)
		{
			for(size_t i = (lastRow ? 1 : 0); i < size; ++i, bgr += 3, bgra += 4)
			{
				*(int32_t*)bgr = (*(int32_t*)bgra);
			}
			if(lastRow)
			{
				bgr[0] = bgra[0];
				bgr[1] = bgra[1];
				bgr[2] = bgra[2];
			}
		}

		void BgraToBgr(const uchar *bgra, size_t width, size_t height, size_t bgraStride, uchar *bgr, size_t bgrStride)
		{
			for(size_t row = 1; row < height; ++row)
			{
				BgraToBgr(bgra, width, bgr, false);
				bgr += bgrStride;
				bgra += bgraStride;
			}
			BgraToBgr(bgra, width, bgr, true);
		}
	}

	void BgraToBgr(const View & bgra, View & bgr)
	{
		assert(bgra.width == bgr.width && bgra.height == bgr.height);
		assert(bgra.format == View::Bgra32 && bgr.format == View::Bgr24);

		BgraToBgr(bgra.data, bgra.width, bgra.height, bgra.stride, bgr.data, bgr.stride);
	}
}