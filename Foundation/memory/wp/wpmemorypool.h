/****************************************************************************
Copyright (c) 2011-2013,WebJet Business Division,CYOU
 
http://www.genesis-3d.com.cn

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#ifndef __ANDROIDMEMORYPOOL_H__
#define __ANDROIDMEMORYPOOL_H__

#include "core/types.h"

namespace Android
{
class AndroidMemoryPool
{
public:
	/// constructor
	AndroidMemoryPool();
	/// destructor
	~AndroidMemoryPool();
	/// compute the actual block size including alignment and management data
	static uint ComputeAlignedBlockSize(uint blockSize);
	/// setup the memory pool
	void Setup(Memory::HeapType heapType, uint blockSize, uint numBlocks);
	/// allocate a block from the pool (NOTE: returns 0 if pool exhausted!)
	void* Alloc();
	/// deallocate a block from the pool
	void Free(void* ptr);
	/// return true if block is owned by this pool
	bool IsPoolBlock(void* ptr) const;
	/// get number of allocated blocks in pool
	uint GetNumBlocks() const;
	/// get block size
	uint GetBlockSize() const;
	/// get aligned block size
	uint GetAlignedBlockSize() const;
	/// get pool size
	uint GetPoolSize() const;
	/// get current allocation count
#if NEBULA3_MEMORY_STATS
	uint GetAllocCount() const;
#endif
};


}

#endif
