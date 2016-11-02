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
		Hash����
		@remarks
			����ȫ���������غ�������ָ�����͵ĺ�������Hashֵ
		@note
			����Ϊfrindȫ��ʱ�����Ժ��Դ���ǰ���������Ϊ����
	*/
	inline dword GetTypeHash( const word A )
	{
		return A;
	}
	
	inline dword GetTypeHash( const int A )
	{
		return A;
	}
	inline dword GetTypeHash( const dword A )
	{
		return A;
	}
	inline dword GetTypeHash( const qword A )
	{
		return (dword)A+((dword)(A>>32) * 23);
	}

	inline dword GetTypeHash( const wchar* s )
	{
		return CheckSum::StrHashNoCase( s );
	}

	inline dword GetTypeHash( const char* s )
	{
		return CheckSum::StrHashNoCase( s );
	}

	inline dword GetTypeHash( const AString& s )
	{
		return CheckSum::StrHashNoCase( s.c_str() );
	}

	inline dword GetTypeHash( const WString& s )
	{
		return CheckSum::StrHashNoCase( s.c_str() );
	}

	template<class T>
	inline dword PointerHash(const T* Key,dword C = 0)
	{
#define mix(a,b,c) \
		{ \
		a -= b; a -= c; a ^= (c>>13); \
		b -= c; b -= a; b ^= (a<<8); \
		c -= a; c -= b; c ^= (b>>13); \
		a -= b; a -= c; a ^= (c>>12);  \
		b -= c; b -= a; b ^= (a<<16); \
		c -= a; c -= b; c ^= (b>>5); \
		a -= b; a -= c; a ^= (c>>3);  \
		b -= c; b -= a; b ^= (a<<10); \
		c -= a; c -= b; c ^= (b>>15); \
	}

		dword A;
		dword B;
		A = B = 0x9e3779b9;
		A += (*(dword*)&Key);
		mix(A,B,C);
		return C;

#undef mix
	}

	/** 
		��̬Hash�����
	*/
	template< class TKey, class TValue , int INIT_HASH_COUNT = 8 > class map_base
	{
	protected:
		class TPair
		{
		public:
			int HashNext;
			TKey Key;
			TValue Value;
			TPair( TKey InKey, TValue InValue )
			: Key( InKey ), Value( InValue )
			{}
			TPair()
			{

			}
		};

		void rehash()
		{
			Assert(!(HashCount&(HashCount-1)));
			delete[] Hash;
			Hash = new int[HashCount];
			for( int i=0; i<HashCount; i++ )
			{
				Hash[i] = -1;
			}
			for( int i=0; i< (int)Pairs.size(); i++ )
			{
				TPair& Pair    = Pairs[i];
				int    iHash   = (GetTypeHash(Pair.Key) & (HashCount-1));
				Pair.HashNext  = Hash[iHash];
				Hash[iHash] = i;
			}
		}

		void allochash()
		{
			if(!Hash)
			{
				rehash();
			}
		}


		void relax()
		{
			while( HashCount>(int)Pairs.size()*2+INIT_HASH_COUNT )
			{
				HashCount /= 2;
			}
			rehash();
		}

		TValue& add( const TKey& InKey, const TValue& InValue )
		{			
			size_t beforesize = Pairs.size();
	
			Pairs.push_back( TPair() );

			TPair& Pair = Pairs.back();
			Pair.Key = InKey;
			Pair.Value = InValue;

			int    iHash  = (GetTypeHash(Pair.Key) & (HashCount-1));
			Pair.HashNext = Hash[iHash];
			Hash[iHash]   = beforesize;

			if( HashCount*2 + INIT_HASH_COUNT < (int)Pairs.size() )
			{
				HashCount *= 2;
				rehash();
			}
			return Pair.Value;
		}

		typedef std::vector<TPair> PairsArray;
		PairsArray Pairs;

		int* Hash;
		int HashCount;

	public:
		/** 
			���캯��
			@note
				ʹ��ģ�����INIT_HASH_COUNT���г�ʼhash����������
		*/
		map_base()
		:	Hash( null )
		,	HashCount( INIT_HASH_COUNT )
		{}
		
		/**
			�������캯��
		*/
		map_base( const map_base& Other )
		:	Pairs( Other.Pairs )
		,	Hash( null )
		,	HashCount( Other.HashCount )
		{
			rehash();
		}

		/**
			��������
		*/
		~map_base()
		{
			delete [] Hash;
			Hash = null;
			HashCount = 0;
		}

		map_base& operator=( const map_base& Other )
		{
			Pairs     = Other.Pairs;
			HashCount = Other.HashCount;
			rehash();
			return *this;
		}

		/**	
			�������Ԫ��
			@remarks
				�˺�����ɾ���ڴ�	
		*/
		void clear()
		{
			Assert(!(HashCount&(HashCount-1)));
			Pairs.clear();
			HashCount = INIT_HASH_COUNT;
			delete [] Hash;
			Hash = null;
		}

		/** 
			��������Ԫ��
			@remarks �˺�����������ڴ�����·���
		 */
		void reset()
		{
			Assert(!(HashCount&(HashCount-1)));
			Pairs.Reset();
			if( Hash )
			{
				for( int i=0; i<HashCount; i++ )
				{
					Hash[i] = -1;
				}
			}
		}

		/** 
			����HashԪ��
			@remark
				�˺�����ʹ��key��hash����ѡ��ۣ�������Ԫ��
			@param
				InKey key����ֵ
			@param
				InValue ����ֵ
		*/
		TValue& set( const TKey& InKey, const TValue& InValue )
		{
			allochash();
			if ( Pairs.size() > 0 )
			{
				for( int i=Hash[(GetTypeHash(InKey) & (HashCount-1))]; i!= -1; i=Pairs[i].HashNext )
				{
					if( Pairs[i].Key==InKey )
					{
						Pairs[i].Value=InValue;
						return Pairs[i].Value;
					}
				}
			}
			return add( InKey, InValue );
		}

		/** 
			ʹ��key�Ƴ�һ��hashԪ��
			@param
				InKey ����Key����ֵ
			@return
				����Key��Ӧ��HashԪ���Ƴ�����
			@note
				ע���ڱ�Ҫʱ�ṩkey��==����������
		*/
		int remove( const TKey& InKey )
		{
			int Count=0;
			for( int i=Pairs.size()-1; i>=0; i-- )
			{
				if( Pairs[i].Key==InKey )
				{
					Pairs.erase(Pairs.begin() + i); Count++;
				}
			}
			if( Count )
			{
				relax();
			}
			return Count;
		}

		/** 
			����Value����Key
			@param
				value ����ֵ
			@return
				δ�ҵ����ʱ������null����֮�����ؽ����ָ��
			@note
				�˺������ܽϲע��ʹ�û���
		*/
		TKey* findkey( const TValue& Value )
		{
			for( int i = 0 ; i < Pairs.size() ; ++i )
			{
				if( Pairs[i].Value == Value )
				{
					return &Pairs[i].Key;
				}
			}
			return null;
		}

		/** 
			����Value����const Key
			@param
				value ����ֵ
			@return
				δ�ҵ����ʱ������null����֮�����ؽ����ָ��
			@note
				�˺������ܽϲע��ʹ�û���
		*/
		const TKey* findkey( const TValue& Value ) const
		{
			for( int i = 0 ; i < Pairs.size() ; ++i )
			{
				if( Pairs[i].Value == Value )
				{
					return &Pairs[i].Key;
				}
			}
			return null;
		}

		/** 
			����Key����Value
			@param
				Key ��Ҫ����Keyֵ
			@return
				δ�ҵ����ʱ������null����֮�����ؽ����ָ��
		*/
		TValue* find( const TKey& Key )
		{
			if( Hash && Pairs.size() > 0 )
			{
				for( int i=Hash[(GetTypeHash(Key) & (HashCount-1))]; i!= -1; i=Pairs[i].HashNext )
				{
					if( Pairs[i].Key==Key )
					{
						return &Pairs[i].Value;
					}
				}
			}
			return null;
		}

		/** 
			����Key����Value������
			@param
				Key ��Ҫ����Keyֵ
			@return
				δ�ҵ����ʱ������null����֮���������Ϳ�
		*/
		TValue findref( const TKey& Key ) const
		{
			if( Hash && Pairs.size() > 0 )
			{
				for( int i=Hash[(GetTypeHash(Key) & (HashCount-1))]; i!= -1; i=Pairs[i].HashNext )
				{
					if( Pairs[i].Key==Key )
					{
						return Pairs[i].Value;
					}
				}
			}
			return (TValue) null;
		}

		/** 
			����Key����const Value
			@param
				Key ��Ҫ����Keyֵ
			@return
				δ�ҵ����ʱ������null����֮�����ؽ����ָ��
		*/
		const TValue* find( const TKey& Key ) const
		{
			if( Hash && Pairs.size() > 0 )
			{
				for( int i=Hash[(GetTypeHash(Key) & (HashCount-1))]; i!= -1; i=Pairs[i].HashNext )
				{
					if( Pairs[i].Key==Key )
					{
						return &Pairs[i].Value;
					}
				}
			}
			return null;
		}

		/** 
			���Key��Ӧ��Ԫ���Ƿ����
			@param
				Key ��Ҫ����Keyֵ
			@return
				����Ƿ����
		*/
		const bool exist( const TKey& Key ) const
		{
			bool bHasKey = false;
			if( Hash && Pairs.size() > 0 )
			{
				for( int i=Hash[(GetTypeHash(Key) & (HashCount-1))];
					i!= -1 && bHasKey == false; i=Pairs[i].HashNext )
				{
					bHasKey = Pairs[i].Key==Key;
				}
			}
			return bHasKey;
		}

		/// ������
		class iterator
		{
		public:
			/** 
				���������캯��
				@param
					InMap hashmap����ֱ�ӽ������ô���
			*/
			iterator( map_base& InMap ) : Map( InMap ), Pairs( InMap.Pairs ), Index( 0 ), Removed(0) {}


			/** 
				��������������
				@remark
					������ε�����Ԫ��ɾ��������������hash������
			*/
			~iterator()               { if( Removed ) Map.relax(); }

			/// ������ָ���ƶ�
			void operator++()          { ++Index; }

			/// �Ƴ�һ��Ԫ��
			void remove()       { Pairs.erase(Pairs.begin() + Index--); Removed++; }

			/// �������Ƿ���Ч
			operator bool() const     { return Index >=0 && Index < (int)Pairs.size() ; }

			/// ��ȡ��ǰ��key
			TKey& get_key() const            { return Pairs[Index].Key; }

			/// ��ȡ��ǰ��value
			TValue& get_value() const          { return Pairs[Index].Value; }
		private:
			map_base& Map;
			PairsArray& Pairs;
			int Index;
			int Removed;
		};

		/** 
			ֻ��������
			�μ� map_base::iterator
		*/
		class const_iterator
		{
		public:
			const_iterator( const map_base& InMap ) : Map(InMap), Pairs( InMap.Pairs ), Index( 0 ) {}
			~const_iterator() {}
			void operator++()          { ++Index; }
			operator bool() const     { return  Index >=0 && Index < (int)Pairs.size(); }
			const TKey& get_key() const      { return Pairs[Index].Key; }
			const TValue& get_value() const    { return Pairs[Index].Value; }
		private:
			const map_base& Map;
			const PairsArray& Pairs;
			int Index;
		};
		friend class iterator;
		friend class const_iterator;
	};

	/** 
		��̬hash��
		�μ� map_base
	*/
	template< class TKey, class TValue, int INIT_HASH_COUNT = 8  > class dynamic_hash : public map_base<TKey,TValue, INIT_HASH_COUNT>
	{
	public:
		dynamic_hash& operator=( const dynamic_hash& Other )
		{
			map_base<TKey,TValue>::operator=( Other );
			return *this;
		}

		int size() const
		{
			return this->Pairs.size();
		}
	};


	/** @} */
	/** @} */
}