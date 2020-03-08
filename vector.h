#pragma once

#include <cstddef>
#include <string>

#define INITIAL_CAPACITY (100)
#define ADDITIONAL_RESERVED_SPACE (100*sizeof(value_type))

namespace nstd // not std
{
	class exception
	{
	public:
		exception(std::string description)
		{
			this->description = description;
		}

		std::string what()
		{
			return description;
		}

	private:
		std::string description;
	};

	template <typename value_type>
	class vector
	{
	public:

		using size_type = size_t;
	
		class const_iterator : public std::iterator<std::random_access_iterator_tag, value_type>
		{
			friend class vector<value_type>;

		private:
			const_iterator(value_type* p) : p(p)
			{ }

		public:
			const_iterator(const const_iterator& it) : p(it.p)
			{ }

			bool operator!=(const_iterator const& other) const
			{
				if (other.p != this->p)
				{
					return true;
				}
				else
				{
					return false;
				}
			}

			bool operator==(const_iterator const& other) const
			{
				if (other.p == this->p)
				{
					return true;
				}
				else
				{
					return false;
				}
			}

			const_iterator operator++(int)
			{
				const_iterator tmpIt(*this);
				this->p++;
				return tmpIt;
			}

			const_iterator& operator++()
			{
				this->p++;
				return *this;
			}

			friend const_iterator operator+(const const_iterator& it, const ptrdiff_t n)
			{
				return (const_iterator(it.p + n));
			}
			friend const_iterator operator+(const ptrdiff_t n, const const_iterator& it)
			{
				return (it + n);
			}

			friend const_iterator operator-(const const_iterator& it, const ptrdiff_t n)
			{
				return (const_iterator(it.p - n));
			}

			const_iterator& operator-=(ptrdiff_t n)
			{
				(this->p) -= n;
				return *this;
			}

			const_iterator& operator +=(ptrdiff_t n)
			{
				(this->p) += n;
				return *this;
			}

			friend ptrdiff_t operator-(const const_iterator& it1, const const_iterator& it2)
			{
				return (it1.p - it2.p);
			}

			bool operator<(const const_iterator& it) const
			{
				if (this->p < it.p)
				{
					return true;
				}
				else
				{
					return false;
				}
			}

			bool operator>(const const_iterator& it) const
			{
				return (it < *this);
			}

			bool operator<=(const const_iterator& it) const
			{
				return !(*this > it);
			}

			bool operator>=(const const_iterator& it) const
			{
				return !(*this < it);
			}

			typename const const_iterator::reference operator*() const
			{
				return *(this->p);
			}

			value_type& operator[](size_type n) const
			{
				return *(this->p + n);
			}

		private:
			value_type* p;
		};

		class iterator : public std::iterator<std::random_access_iterator_tag, value_type>
		{
			friend class vector<value_type>;

		private:
			iterator(value_type* p) : p(p)
			{ }

		public:
			iterator(const iterator& it) : p(it.p)
			{ }

			operator const_iterator() const { return const_iterator(this->p); }

			bool operator!=(iterator const& other) const
			{
				if (other.p != this->p)
				{
					return true;
				}
				else
				{
					return false;
				}
			}

			bool operator==(iterator const& other) const
			{
				if (other.p == this->p)
				{
					return true;
				}
				else
				{
					return false;
				}
			}

			typename iterator::reference operator*() const
			{
				return *p;
			}

			iterator operator++(int)
			{
				iterator tmpIt(*this);
				this->p++;
				return tmpIt;
			}

			iterator& operator++()
			{
				this->p++;
				return *this;
			}

			friend iterator operator+(const iterator& it, const ptrdiff_t n)
			{
				return (iterator(it.p + n));
			}
			friend iterator operator+(const ptrdiff_t n, const iterator& it)
			{
				return (it + n);
			}

			friend iterator operator-(const iterator& it, const ptrdiff_t n)
			{
				return (iterator(it.p - n));
			}

			iterator& operator-=(ptrdiff_t n)
			{
				(this->p) -= n;
				return *this;
			}

			friend ptrdiff_t operator-(const iterator& it1, const iterator& it2)
			{
				return (it1.p - it2.p);
			}

			value_type& operator[](size_type n)
			{
				return *(this->p + n);
			}

			bool operator<(const iterator& it) const
			{
				if (this->p < it.p)
				{
					return true;
				}
				else
				{
					return false;
				}
			}

			bool operator>(const iterator& it) const
			{
				return (it < *this);
			}

			bool operator<=(const iterator& it) const
			{
				return !(*this > it);
			}

			bool operator>=(const iterator& it) const
			{
				return !(*this < it);
			}

		private:
			value_type* p;
		};

		class reverse_iterator : public std::iterator<std::bidirectional_iterator_tag, value_type>
		{
			friend class vector<value_type>;

		private:
			reverse_iterator(value_type* p) : p(p)
			{ }

		public:
			reverse_iterator(const reverse_iterator& it) : p(it.p)
			{ }

			bool operator!=(reverse_iterator const& other) const
			{
				if (other.p != this->p)
				{
					return true;
				}
				else
				{
					return false;
				}
			}

			bool operator==(reverse_iterator const& other) const
			{
				if (other.p == this->p)
				{
					return true;
				}
				else
				{
					return false;
				}
			}

			typename reverse_iterator::reference operator*() const
			{
				return *(this->p);
			}

			reverse_iterator& operator++()
			{
				this->p--;
				return *this;
			}

			reverse_iterator operator++(int)
			{
				auto tmp = *this;
				this->p--;
				return tmp;
			}

		private:
			value_type* p;
		};

	public:
		vector()
		{
			this->_pData = (value_type*)malloc(sizeof(value_type) * INITIAL_CAPACITY);
			if (this->_pData == NULL)
			{
				throw exception("ERROR: malloc returned NULL");
			}

			this->_capacity = INITIAL_CAPACITY;
			this->_size = 0;
		}
		vector(size_type count, const value_type& value)
		{
			this->_size = this->_capacity = count;

			this->_pData = (value_type*)malloc(sizeof(value_type) * (this->_capacity));
			if (_pData == NULL)
			{
				throw exception("ERROR: malloc returned NULL");
			}

			for (size_type i = 0; i < count; i++)
			{
				new (this->_pData + i) value_type(value);
			}
		}
		explicit vector(size_type count)
		{
			this->_size = this->_capacity = count;

			this->_pData = (value_type*)malloc(sizeof(value_type) * (this->_capacity));
			if (this->_pData == NULL)
			{
				throw exception("ERROR: malloc returned NULL");
			}

			for (size_type i = 0; i < count; i++)
			{
				new (this->_pData + i) value_type();
			}
		}
		vector(const vector& other)
		{
			this->_size = other.size();
			this->_capacity = other.capacity();
			this->_pData = (value_type*)malloc(this->_capacity * sizeof(value_type));
			if (this->_pData == NULL)
			{
				throw exception("ERROR: malloc returned NULL");
			}

			for (size_type i = 0; i < this->_size; i++)
			{
				new (this->_pData + i) value_type(other[i]);
			}
		}
		vector(vector&& other)
		{
			this->_pData = NULL;

			std::swap(this->_pData, other._pData);
			std::swap(this->_capacity, other._capacity);

			this->_size = other._size;
			other._size = 0;
		}
		vector(std::initializer_list<value_type> init)
		{
			this->_size = this->_capacity = init.size();

			this->_pData = (value_type*)malloc(sizeof(value_type) * (this->_capacity));
			if (this->_pData == NULL)
			{
				throw exception("ERROR: malloc returned NULL");
			}

			size_t i = 0;
			for (auto it = init.begin(); it != init.end(); it++)
			{
				new (this->_pData + i) value_type(*it);
				i++;
			}
		}
		template<typename ITER,
			std::enable_if_t<std::is_base_of_v<typename std::iterator_traits<ITER>::iterator_category,
			std::random_access_iterator_tag>, bool> = true>
		vector(ITER first, ITER last)
		{
			ptrdiff_t distance = last - first;
			if (distance < 0)
			{
				throw exception("ERROR: distance between iterators < 0");
			}

			this->_size = this->_capacity = distance;
			this->_pData = (value_type*)malloc(sizeof(value_type) * (this->_capacity));
			if (_pData == NULL)
			{
				throw exception("ERROR: malloc returned NULL");
			}

			for (size_type i = 0; i < this->_size; i++)
			{
				new (this->_pData + i) value_type(*first);
				first++;
			}
		}

		~vector()
		{
			if (this->_pData != NULL)
			{
				if (this->_size > 0)
				{
					DestructObjects(this->_pData, this->_size);
				}
				free(this->_pData);
			}
		}

		vector& operator=(const vector& other)
		{
			if (this != &other)
			{
				vector(other).swap(*this);
			}

			return *this;
		}
		vector& operator=(vector&& other)
		{
			if (this != &other)
			{
				vector(other).swap(*this);
			}

			return *this;
		}
		vector& operator=(std::initializer_list<value_type> ilist)
		{
			vector(ilist).swap(*this);
			return *this;
		}

		void assign(size_type count, const value_type& value)
		{
			vector(count, value).swap(*this);
		}
		void assign(std::initializer_list<value_type> ilist)
		{
			vector(ilist).swap(*this);
		}
		template< typename ITER,
			std::enable_if_t<std::is_base_of_v<typename std::iterator_traits<ITER>::iterator_category,
			std::random_access_iterator_tag>, bool> = true>
		void assign(ITER first, ITER last)
		{
			vector(first, last).swap(*this);
		}

		value_type& at(size_type pos)
		{
			if (pos > this->_size - 1)
			{
				throw exception("ERROR: element index out of range");
			}

			return this->_pData[pos];
		}
		const value_type& at(size_type pos) const
		{
			return this->at(pos);
		}

		value_type& operator[] (size_type pos)
		{
			return *(this->_pData + pos);
		}
		const value_type& operator[](size_type pos) const
		{
			return *(this->_pData + pos);
		}

		value_type& front()
		{
			return *(this->_pData);
		}
		const value_type& front() const
		{
			return *(this->_pData);
		}

		value_type& back()
		{
			return *(this->_pData + this->_size - 1);
		}
		const value_type& back() const
		{
			return *(this->_pData + this->size - 1);
		}

		value_type* data() noexcept
		{
			return this->_pData;
		}
		const value_type* data() const noexcept
		{
			return this->_pData;
		}

		iterator begin() noexcept
		{
			return iterator(this->_pData);
		}
		const_iterator cbegin()
		{
			return const_iterator(this->_pData);
		}

		iterator end() noexcept
		{
			return iterator(this->_pData + this->_size);
		}
		const_iterator cend() noexcept
		{
			return const_iterator(this->_pData + this->_size);
		}

		reverse_iterator rbegin() noexcept
		{
			return reverse_iterator(this->_pData + this->_size - 1);
		}

		reverse_iterator rend() noexcept
		{
			return reverse_iterator(this->_pData - 1);
		}

		bool empty() const noexcept
		{
			if (this->_size == 0)
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		size_type size() const noexcept
		{
			return this->_size;
		}

		size_type max_size() const noexcept
		{
			constexpr size_type size_type_max = (std::numeric_limits<size_type>::max)();
			constexpr ptrdiff_t ptrdiff_t_max = (std::numeric_limits<ptrdiff_t>::max)();

			if (size_type_max > ptrdiff_t_max)
			{
				return ptrdiff_t_max;
			}
			else
			{
				return size_type_max;
			}
		}

		void reserve(size_type new_cap)
		{
			if (new_cap <= this->_capacity)
			{
				return;
			}

			if (new_cap > this->max_size())
			{
				throw exception("ERROR: requested capacity > max possible capacity");
			}

			value_type* pTmp = (value_type*)realloc(this->_pData, new_cap);

			if (pTmp == NULL)
			{
				throw exception("ERROR: realloc returned NULL");
			}
			else
			{
				this->_pData = pTmp;
				this->_capacity = new_cap;
			}
		}

		size_type capacity() const noexcept
		{
			return this->_capacity;
		}

		void shrink_to_fit()
		{
			value_type* pTmp = (value_type*)malloc(this->_size * sizeof(value_type));
			if (pTmp != NULL)
			{
				this->DestructObjects(this->_pData + this->_size, this->_capacity - this->_size);
				this->_capacity = this->_size;
				memcpy(pTmp, this->_pData, this->_size * sizeof(value_type));
				free(this->_pData);
				this->_pData = pTmp;
			}
		}

		void clear() noexcept
		{
			if (this->_size > 0)
			{
				this->DestructObjects();
				this->_size = 0;
			}
		}

		iterator insert(const_iterator pos, const value_type& value)
		{
			ptrdiff_t index = pos.p - this->_pData;

			if (this->_capacity < this->_size + 1)
			{
				this->reserve(this->_capacity + ADDITIONAL_RESERVED_SPACE);
			}

			MoveArrayBlock(this->_pData + index, 1, 1);

			new (this->_pData + index) value_type(value);

			this->_size++;

			return iterator(pos.p);
		}
		iterator insert(const_iterator pos, value_type&& value)
		{
			ptrdiff_t index = pos.p - this->_pData;

			if (this->_capacity < this->_size + 1)
			{
				this->reserve(this->_capacity + ADDITIONAL_RESERVED_SPACE);
			}

			MoveArrayBlock(this->_pData + index, 1, 1);

			new (this->_pData + index) value_type(value);

			this->_size++;

			return iterator(pos.p);
		}
		iterator insert(const_iterator pos, size_type count, const value_type& value)
		{
			ptrdiff_t index = pos.p - this->_pData;

			iterator res = NULL;
			for (size_type i = 0; i < count; i++)
			{
				res = this->insert(const_iterator(this->begin() + index), value);
			}

			return res;
		}
		iterator insert(const_iterator pos, std::initializer_list<value_type> ilist)
		{
			ptrdiff_t index = pos.p - this->_pData;

			auto pElem = ilist.end() - 1;
			iterator res = NULL;
			for (size_type i = 0; i < ilist.size(); i++)
			{
				res = this->insert(const_iterator(this->begin() + index), *pElem);
				pElem--;
			}

			return res;
		}
		template< typename ITER,
			std::enable_if_t<std::is_base_of_v<typename std::iterator_traits<ITER>::iterator_category,
			std::random_access_iterator_tag>, bool> = true>
		iterator insert(const_iterator pos, ITER first, ITER last)
		{
			ptrdiff_t distance = last - first;
			if (distance < 0)
			{
				throw exception("ERROR: distance between iterators < 0");
			}

			ptrdiff_t index = pos.p - this->_pData;

			iterator res = NULL;
			for (size_type i = 0; i < distance; i++)
			{
				res = this->insert(const_iterator(this->begin() + index), *(last.p - 1 - i));
			}

			return res;
		}

		template< class... Args >
		iterator emplace(const_iterator pos, Args&&... args)
		{
			this->insert(pos, value_type(Args...));
		}

		void push_back(const value_type& value)
		{
			if (this->_capacity < this->_size + 1)
			{
				this->reserve(this->_capacity + ADDITIONAL_RESERVED_SPACE);
			}

			new (_pData + this->_size) value_type(value);

			this->_size++;
		}
		void push_back(value_type&& value)
		{
			if (this->_capacity < this->_size + 1)
			{
				this->reserve(this->_capacity + ADDITIONAL_RESERVED_SPACE);
			}

			new (_pData + this->_size) value_type(value);

			this->_size++;
		}

		template< class... Args >
		void emplace_back(Args&&... args)
		{
			if (this->_capacity < this->_size + 1)
			{
				this->reserve(this->_capacity + ADDITIONAL_RESERVED_SPACE);
			}

			new (_pData + this->_size) value_type(args...);

			this->_size++;
		}

		void pop_back()
		{
			if (this->_size > 0)
			{
				this->DestructObjects(this->_pData + this->_size - 1, 1);
				(this->_size)--;
			}
		}

		void resize(size_type count, const value_type& value = value_type())
		{
			if (count <= this->_size)
			{
				this->DestructObjects(this->_pData + count, this->_size - count);
				this->_size = count;
			}
			else
			{
				size_type old_size = this->_size;

				if (count > this->_capacity)
				{
					this->reserve(count);
					this->_size = count;
				}

				for (size_type i = old_size; i < count; i++)
				{
					new (this->_pData + i) value_type(value);
				}
			}
		}

		void swap(vector& other)
		{
			std::swap(this->_pData, other._pData);
			std::swap(this->_capacity, other._capacity);
			std::swap(this->_size, other._size);
		}

	private:
		void MoveArrayBlock(value_type* pFirst, size_t objectsQuantity, int offset)
		{
			size_t bytesToMove = sizeof(value_type) * (this->end() - pFirst);

			value_type* pTmp = (value_type*)malloc(bytesToMove);
			if (pTmp == NULL)
			{
				throw exception("ERROR: realloc returned NULL");
			}

			memcpy(pTmp, pFirst, bytesToMove);
			memcpy(pFirst + offset, pTmp, bytesToMove);

			free(pTmp);
		}
		void DestructObjects(value_type* pObjects, size_t count)
		{
			for (size_t i = 0; i < count; i++)
			{
				pObjects[i].~value_type();
			}
		}
		void DestructObjects()
		{
			DestructObjects(this->_pData, this->_size);
		}

	private:
		value_type* _pData;
		size_type _size;
		size_type _capacity;
	};
}