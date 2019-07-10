#pragma once
#include "stdafx.h"

//著作权归作者所有。
//商业转载请联系作者获得授权，非商业转载请注明出处。
//作者：Milo Yip
//链接：https ://www.zhihu.com/question/27768721/answer/38046311
//来源：知乎

class LCG {
public:
	LCG(uint32_t seed) : mSeed(seed) {}
	float operator()() {
		mSeed = mSeed * 214013 + 2531011;
		union {
			uint32_t u;
			float f;
		}u = { (mSeed >> 9) | 0x3F800000 };
		return u.f - 1.0f;
	}
private:
	uint32_t mSeed;
};
