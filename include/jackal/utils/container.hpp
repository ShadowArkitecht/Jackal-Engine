#ifndef __JACKAL_CONTAINER_HPP__
#define __JACKAL_CONTAINER_HPP__

namespace jackal {
	template<typename T>
	class Container final {
	private:
		int m_count;
		int m_capacity;
		T*  m_pData;

	private:
		void grow();
		void grow(int newCapacity);

	public:
		explicit Container();
		explicit Container(int capacity);
		~Container();

		void operator+=(const Container<T>& bag);

		T get(int index) const;
		bool set(int index, T o);

		int getCapacity() const;
		bool isEmpty() const;
		int getCount() const;

		void add(T o);
		void addAll(const Container<T>& bag);
		bool remove(T o);
		T remove(int index);
		T removeLast();
		bool contains(T o) const;

		void clear();
		void deleteData();
	};

	template <typename T>
	Container<T>::Container()
		: Container<T>(64) {

	}

	template <typename T>
	Container<T>::Container(int capacity)
		: m_count(0), m_capacity(capacity), m_pData(new T[capacity]) {
		this->clear();
	}

	template <typename T>
	Container<T>::~Container() {
		if (m_pData) {
			delete[] m_pData;
			m_pData = nullptr;
		}
	}

	template <typename T>
	void Container<T>::grow() {
		this->grow(static_cast<int>((m_capacity * 3.0f) * 0.5f + 1.0f));
	}

	template <typename T>
	void Container<T>::grow(int newCapacity) {
		T* currentData = m_pData;
		int c = m_count;
		m_pData = new T[newCapacity];
		m_capacity = newCapacity;
		this->clear();
		m_count = c;
		for (int i = 0; i < m_capacity; i++) {
			m_pData[i] = currentData[i];
		}
	}

	template <typename T>
	void Container<T>::add(T o) {
		if (m_capacity == m_count) {
			this->grow();
		}

		m_pData[m_count++] = o;
	}

	template <typename T>
	void Container<T>::addAll(const Container<T>& bag) {
		for (int i = 0; i < bag.m_capacity; i++) {
			this->add(bag.m_pData[i]);
		}
	}

	template <typename T>
	void Container<T>::clear() {
		for (int i = 0; i < m_capacity; i++) {
			m_pData[i] = nullptr;
		}

		m_count = 0;
	}

	template <typename T>
	bool Container<T>::contains(T o) const {
		for (int i = 0; i < m_count; i++) {
			if (o == m_pData[i]) {
				return true;
			}
		}

		return false;
	}

	template <typename T>
	T Container<T>::get(int index) const {
		return (T)m_pData[index];
	}

	template <typename T>
	int Container<T>::getCapacity() const {
		return m_capacity;
	};

	template <typename T>
	bool Container<T>::isEmpty() const {
		return m_count == 0;
	};

	template <typename T>
	int Container<T>::getCount() const {
		return m_count;
	};

	template <typename T>
	bool Container<T>::remove(T o) {
		for (int i = 0; i < m_count; i++) {
			if (o == m_pData[i]) {
				this->remove(i);
				return true;
			}
		}

		return false;
	}

	template <typename T>
	T Container<T>::remove(int index) {
		if (m_count == 0) {
			return nullptr;
		}

		T object = m_pData[index];
		m_pData[index] = m_pData[m_count - 1];
		m_pData[m_count - 1] = nullptr;
		m_count--;
		return (T)object;
	}

	template <typename T>
	T Container<T>::removeLast() {
		if (!this->isEmpty()) {
			T object = m_pData[m_count - 1];
			m_pData[m_count - 1] = nullptr;
			--m_count;
			return (T)object;
		}

		return nullptr;
	}

	template <typename T>
	bool Container<T>::set(int index, T o) {
		if (index >= m_capacity) {
			this->grow(index * 2);
		}

		if (o == nullptr && m_pData[index]) {
			m_count--;
		}
		else if (o != nullptr && !m_pData[index]) {
			m_count++;
		};

		m_pData[index] = o;
		return true;
	}

	template <typename T>
	void Container<T>::operator+=(const Container<T>& bag) {
		this->addAll(bag);
	}

	template <typename T>
	void Container<T>::deleteData() {
		for (int i = 0; i < m_capacity; i++) {
			delete m_pData[i];
			m_pData[i] = nullptr;
		}
		m_count = 0;
	}

} // namespace jackal

#endif//__JACKAL_CONTAINER_HPP__
