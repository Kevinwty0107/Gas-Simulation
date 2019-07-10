#pragma once
#include "stdafx.h"

//����Ȩ���������С�
//��ҵת������ϵ���߻����Ȩ������ҵת����ע��������
//���ߣ�Milo Yip
//���ӣ�https ://www.zhihu.com/question/27768721/answer/38046311
//��Դ��֪��

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
