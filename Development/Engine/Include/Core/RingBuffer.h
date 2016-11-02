#pragma once

namespace NekoEngine
{
	/** \addtogroup Core
	*  @{
	*/
	/** \addtogroup Basic
	*  @{
	*/


	/** 
		��״��������
		@remark
			�����ڵͷ��������������߳������ߣ�������ģ��
	*/
	class ringbuffer
	{
	public:

		/** 
			С�ͳ�ʼ�����캯��
			@param
				BufferSize ��Ҫ����Ļ����С���˻������ڱ���Ԫ�ؽ����ռ�
		 */
		ringbuffer(dword BufferSize)
		{
			mData = new _byte[BufferSize];
			mReadPointer = mWritePointer = mData;
			mEndPointer = mDataEnd = mData + BufferSize;
		}

		~ringbuffer( )
		{
			delete[] mData;
		}

		/** 
			��״����Ĵ洢��Ԫ����Ԫ����ʱ������д�����ύ
		 */
		class alloc_context
		{
		public:

			/**
			 * ����ʱ�� ��״���彫Ϊ����Ԫ����洢�ռ�
			 * @param
					InRingBuffer ���ڷ���Ļ�״����
			 * @param
					InAllocationSize ����Ĵ�С
			 */
			alloc_context(ringbuffer& InRingBuffer,dword InAllocationSize):
				mRingbuffer(InRingBuffer),
				mAllocationSize(InAllocationSize)
			{
				// Only allow a single AllocationContext at a time for the ring buffer.
				Assert(!mRingbuffer.mIsWriting);
				mRingbuffer.mIsWriting = true;

				// Check that the allocation will fit in the buffer.
				const dword BufferSize = (dword)(mRingbuffer.mDataEnd - InRingBuffer.mData);
				Assert(mAllocationSize < BufferSize);

				while(1)
				{
					// Capture the current state of ReadPointer.
					_byte* CurrentReadPointer = mRingbuffer.mReadPointer;

					if(CurrentReadPointer > mRingbuffer.mWritePointer && mRingbuffer.mWritePointer + mAllocationSize >= CurrentReadPointer)
					{
						// If the allocation won't fit in the buffer without overwriting yet-to-be-read data,
						// wait for the reader thread to catch up.
						continue;
					}

					if(mRingbuffer.mWritePointer + mAllocationSize > mRingbuffer.mDataEnd)
					{
						if(CurrentReadPointer == mRingbuffer.mData)
						{
							// Since ReadPointer == Data, don't set WritePointer=Data until ReadPointer>Data.  WritePointer==ReadPointer means
							// the buffer is empty.
							continue;
						}
						// If the allocation won't fit before the end of the buffer, move WritePointer to the beginning of the buffer.
						// Also set EndPointer so the reading thread knows the last byte of the buffer which has valid data.
						mRingbuffer.mEndPointer = mRingbuffer.mWritePointer;
						mRingbuffer.mWritePointer = mRingbuffer.mData;
						continue;
					}

					// Use the memory referenced by WritePointer for the allocation.
					mAllocation = mRingbuffer.mWritePointer;
					break;
				};
			}
			/** 
				�ύ�ڴ浽��״����
			 */
			void commit()
			{
				if(mAllocation)
				{
					// Use a memory barrier to ensure that data written to the ring buffer is visible to the reading thread before the WritePointer
					// update.
					//appMemoryBarrier();

					mRingbuffer.mWritePointer += mAllocationSize;

					// Reset the bIsWriting flag to allow other AllocationContexts to be created for the ring buffer.
					mRingbuffer.mIsWriting = false;

					// Clear the allocation pointer, to signal that it has been committed.
					mAllocation = null;
				}
			}
			/**
				����ʱ������ύû�б��ֶ�ȡ������Ԫ�����ύ
			 */
			~alloc_context()
			{
				commit();
			}

			/** 
				��ô洢��Ԫ���ڴ��ַ
			*/
			void* get_alloc() const { return mAllocation; }

		private:
			ringbuffer& mRingbuffer;
			void* mAllocation;
			const dword mAllocationSize;
		};

		/** 
			����Ƿ�����Ҫ����������
			@param
				OutReadPointer ��������ݿ��Զ����� ��ָ�뽫��Я������ָ��
			@param
				MaxReadSize �������ݿ��Զ�ȡʱ��������������ؿɶ����ݵĴ�С
			@return
				�����Ƿ������ݿ��Զ�ȡ
		 */
		bool begin_read(volatile void*& OutReadPointer,dword& OutReadSize)
		{
			_byte* CurrentWritePointer = mWritePointer;
			_byte* CurrentEndPointer = mEndPointer;

			// If the read pointer has reached the end of readable data in the buffer, reset it to the beginning of the buffer.
			if(CurrentWritePointer <= CurrentEndPointer && mReadPointer == CurrentEndPointer)
			{
				if(CurrentWritePointer < CurrentEndPointer)
				{
					// Only wrap the ReadPointer to the beginning of the buffer once the WritePointer has been wrapped.
					// If it's wrapped as soon as it reaches EndPointer, then it might be wrapped before the WritePointer.
					mReadPointer = mData;
				}
				else
				{
					return false;
				}
			}

			if(mReadPointer != CurrentWritePointer)
			{
				OutReadPointer = mReadPointer;
				if(CurrentWritePointer < mReadPointer)
				{
					// If WritePointer has been reset to the beginning of the buffer more recently than ReadPointer,
					// the buffer is readable from ReadPointer to EndPointer.
					OutReadSize = (dword)(CurrentEndPointer - mReadPointer);
				}
				else
				{
					// Otherwise, the buffer is readable from ReadPointer to WritePointer.
					OutReadSize = (dword)(CurrentWritePointer - mReadPointer);
				}
				return true;
			}
			else
			{
				return false;
			}
		}

		/**
		 * �ͷ��׸�ReadSize�ֽڵ�����
		 * @param
				ReadSize ��Ҫ�ͷŵ��ֽ���
		 */
		void finish_read(dword ReadSize)
		{
			mReadPointer += ReadSize;
		}

	private:

		/** The data buffer. */
		_byte* mData;

		/** The first byte after end the of the data buffer. */
		_byte* mDataEnd;

		/** The next byte to be written to. */
		_byte* volatile mWritePointer;

		/** If WritePointer < ReadPointer, EndPointer is the first byte after the end of readable data in the buffer. */
		_byte* volatile mEndPointer;

		/** true if there is an AllocationContext outstanding for this ring buffer. */
		bool mIsWriting;

		/** The next byte to be read from. */
		_byte* volatile mReadPointer;
	};

	/** @} */
	/** @} */
}
