template <typename T>
class Allocator {
public:
	T* allocate(size_t num){return new T[num];}
};
template <typename T>
class Vector {
private:
	unsigned int sz, cpct;
	T* elem;
	Allocator<T> allocator;
public:
	typedef T value_type;
	typedef Allocator<T> allocator_type;
	typedef const T const_value_type;
	typedef value_type& reference;
	typedef const_value_type& const_reference;
	typedef value_type* pointer;
	typedef const_value_type* const_pointer;
	typedef ptrdiff_t difference_type;
	typedef size_t size_type;
	//constructs the vector
	Vector() : sz(0), cpct(0), elem{allocator.allocate(cpct)} {}
	//constructs the vector with given capacity
	Vector(int size): sz(0),cpct(size), elem{allocator.allocate(size)}{}
	//copy constructor
	Vector(const Vector& v): sz(v.sz), cpct(v.cpct), elem{allocator.allocate(v.cpct)}{ 
	  for (auto i=0; i!=v.sz; ++i)
		elem[i] = v.elem[i];
	}
	//destructor
	~Vector(){delete[] elem;}
	//iterator class
	class Iterator : public std::iterator<std::random_access_iterator_tag, T, std::ptrdiff_t, T*, T&>{
	private:
		pointer ptr;
	public:
		//assign value to iterator
		void setPointer(pointer value){ptr = value;}
		Iterator& operator=(const Iterator& it){ptr = it.ptr;}
		Iterator& operator=(T value){*ptr = value;}
		friend std::ostream& operator<<(std::ostream& out, const Iterator &it){out << it.ptr;}
		reference operator*() const {return *ptr;}
		pointer operator->() const {return ptr;}
		Iterator operator++(int val){++ptr; return *this;}
		Iterator operator++(){++ptr; return *this;}
		Iterator operator--(int val){--ptr; return *this;}
		Iterator operator+(int val){
			for (auto i = 0; i < val; ++i)
				++ptr;
			return *this;
		}
		Iterator operator-(Iterator it){
			ptr -= it;
			return *this;
		}
		bool operator==(Iterator a){return a.ptr == ptr;}
		bool operator!=(Iterator a){return a.ptr != ptr;}
		bool operator==(pointer val){return val == ptr;}
		bool operator!=(pointer val){return val != ptr;}
	};
	//const iterator
	class ConstIterator{
	private:
		pointer ptr;
	public:
		//assigns value to const iterator
		void setPointer(pointer value){ptr = value;}
		ConstIterator& operator=(const ConstIterator& it) const{ptr = it.ptr;}
		friend std::ostream& operator<<(std::ostream& out, const ConstIterator &it){out << it.ptr;}
		const_reference operator*() const {return *ptr;}
		const_pointer operator->() const {return ptr;}
		ConstIterator operator++(int val){++ptr; return *this;}
		ConstIterator operator--(int val){--ptr; return *this;}
		ConstIterator operator+(int val){
			for (auto i = 0; i < val; ++i)
				++ptr;
			return *this;
		}
		ConstIterator operator-(int val){
			for (auto i = 0; i < val; ++i)
				--ptr;
			return *this;
		}
		bool operator==(ConstIterator a){return a.ptr == ptr;}
		bool operator!=(ConstIterator a){return a.ptr != ptr;}
		bool operator==(const_pointer val){return val == ptr;}
		bool operator!=(const_pointer val){return val != ptr;}
		
	};
	//reverse iterator
	class ReverseIterator{
	private:
		pointer ptr;
	public:
		//assigns value to reverse iterator
		void setPointer(pointer value){ptr = value;}
		ReverseIterator& operator=(const ReverseIterator& it){ptr = it.ptr;}
		ReverseIterator& operator=(value_type value){*ptr = value;}
		friend std::ostream& operator<<(std::ostream& out, const ReverseIterator &it){out << it.ptr;}
		reference operator*() const {return *ptr;}
		pointer operator->() const {return ptr;}
		ReverseIterator operator++(int val){--ptr; return *this;}
		ReverseIterator operator--(int val){++ptr; return *this;}
		ReverseIterator operator+(int val){
			for (auto i = 0; i < val; ++i)
				--ptr;
			return *this;
		}
		ReverseIterator operator-(int val){
			for (auto i = 0; i < val; ++i)
				++ptr;
			return *this;
		}
		bool operator==(ReverseIterator a){return a.ptr == ptr;}
		bool operator!=(ReverseIterator a){return a.ptr != ptr;}
		bool operator==(pointer val){return val == ptr;}
		bool operator!=(pointer val){return val != ptr;}
	};
	//const reverse iterator
	class ConstReverseIterator{
	private:
		pointer ptr;
	public:
		//assigns value to const reverse iterator
		void setPointer(pointer value){ptr = value;}
		ConstReverseIterator& operator=(const ConstReverseIterator& it)const {ptr = it.ptr;}
		friend std::ostream& operator<<(std::ostream& out, const ConstReverseIterator &it){out << it.ptr;}
		const_reference operator*() const {return *ptr;}
		const_pointer operator->() const {return ptr;}
		ConstReverseIterator operator++(int val){--ptr; return *this;}
		ConstReverseIterator operator--(int val){++ptr; return *this;}
		ConstReverseIterator operator+(int val){
			for (auto i = 0; i < val; ++i)
				--ptr;
			return *this;
		}
		ConstReverseIterator operator-(int val){
			for (auto i = 0; i < val; ++i)
				++ptr;
			return *this;
		}
		bool operator==(ConstReverseIterator a){return a.ptr == ptr;}
		bool operator!=(ConstReverseIterator a){return a.ptr != ptr;}
		bool operator==(pointer val){return val == ptr;}
		bool operator!=(pointer val){return val != ptr;}
	};

	typedef Iterator iterator;
	typedef ConstIterator const_iterator;
	typedef ReverseIterator reverse_iterator;
	typedef ConstReverseIterator const_reverse_iterator;
	//assigns values to the container
	Vector& operator=(const Vector& v){
		sz = v.sz;
		cpct= v.cpct;
		if (cpct < v.cpct){elem = allocator.allocate(v.cpct);}
		for (auto i = 0; i < v.sz; ++i){elem[i] = v.elem[i];}
	}
	//assigns values to the container by given value and index
	void assign(int num, value_type value){
		for(auto i = 0; i < num; ++i){
			elem[i] = value;
			sz++;
		}
	}
	//assigns values to the container by given iterator range
	void assign(iterator element, iterator lastElem){
		size_type count = 0;
		for(auto i = element; i != lastElem; i++){
			elem[count] = *i;
			count++;
			sz++;
		}
	}
	//returns the associated allocator
	allocator_type get_allocator(){
		return allocator;
	}
	//access specified element
	value_type operator[](size_type ind){
		if (ind >= sz) {throw std::out_of_range("Out of scope");}
		else {return elem[ind];}
	}
	//access specified element
	reference at(size_type index){
		if (index < sz){return elem[index];}
		else {throw std::out_of_range("Out of scope");}
	}
	//access first element
	reference front(){return elem[0];}
	//access last element
	reference back(){return elem[sz-1];}
	//direct access to the underlying array
	pointer data(){return elem;}
	//returns an iterator to the beginning
	iterator begin(){
		iterator it;
		it.setPointer(&elem[0]);
		return it;
	}
	//returns an iterator to the end
	iterator end(){
		iterator it;
		if(sz == 0){it.setPointer(&elem[0]);}
		else {it.setPointer(&elem[sz]);}
		return it;
	}
	//returns an iterator to the begining
	const_iterator cbegin(){
		const_iterator it;
		it.setPointer(&elem[0]);
		return it;
	}
	const_iterator cend(){
		const_iterator it;
		if(sz == 0){it.setPointer(&elem[0]);}
		else {it.setPointer(&elem[sz]);}
		return it;
	}
	reverse_iterator rbegin(){
		reverse_iterator it;
		if(sz == 0){it.setPointer(&elem[0]);}
		else {it.setPointer(&elem[sz]);}
		return it;
	}
	reverse_iterator rend(){
		reverse_iterator it;
		it.setPointer(&elem[0]);
		return it;
	}
	const_reverse_iterator crbegin(){
		const_reverse_iterator it;
		if(sz == 0){it.setPointer(&elem[0]);}
		else {it.setPointer(&elem[sz]);}
		return it;
	}
	const_reverse_iterator crend(){
		const_reverse_iterator it;
		it.setPointer(&elem[0]);
		return it;
	}
	bool empty() {
		return (begin() == end());
	}
	size_type size() const{return sz;}
	size_type max_size() const{
		value_type temp;
		return std::numeric_limits<Vector<int>::size_type>::max() / sizeof(temp);
	}
	void reserve(size_type val) {
		if (val > cpct){
			cpct = val;
			pointer temp = allocator.allocate(cpct);
			std::copy(elem, elem + sz, temp);
			delete[] elem;
			elem = temp;
		}
	}
	size_type capacity()const {return cpct;}
	void shrink_to_fit(){
		pointer temp = allocator.allocate(sz);
		std::copy(elem, elem+sz, temp);
		delete[] elem;
		elem = temp;
		cpct = sz;
	}
	iterator erase(iterator it){
		size_t count = 1;
		iterator i = begin();
		while (i != it){
			i++;
			count++;
		}
		pointer temp = allocator.allocate(sz - 1);
		std::copy(elem, elem + count, temp);
		std::copy(elem + count, elem+sz, temp + count -1);
		delete[] elem;
		elem = temp;
		sz--;
		return i;
	}
	iterator erase(iterator b, iterator e){
		size_t count = 0, count_begin = 0;
		iterator t = begin();
		while (t != b){
			count_begin++;
			t++;
		}
		while (b != e){
			b++;
			count++;
		}
		pointer temp = allocator.allocate(sz - count);
		std::copy(elem, elem + count_begin, temp);
		std::copy(elem+count_begin+count, elem +sz, temp +count_begin);
		delete[] elem;
		elem = temp;
		sz -= count;
		return b;
	}
	void clear(){
		pointer temp = allocator.allocate(cpct);
		delete[] elem;
		elem = temp;
		sz = 0;
	}
	iterator insert(iterator pos, value_type val){
		iterator it = begin();
		size_type count = 0;
		while(it != pos){
			it++;
			count++;
		}
		if (count > sz){throw std::out_of_range("Out of scope");}
		pointer temp = allocator.allocate(sz + 1);
		std::copy(elem, elem + count, temp);
		temp[count] = val;
		std::copy(elem + count, elem+sz, temp + count + 1);
		delete[] elem;
		elem = temp;
		sz++;
		pos = temp[count];
		return pos;
	}
	void push_back(value_type x){
		if (sz < cpct){
			elem[sz] = x;
			sz++;
		}
		else if (sz == cpct){
			if (cpct == 0){cpct = 1;}
			else{cpct *= 2;}
			pointer temp = allocator.allocate(cpct);
			std::copy(elem, elem + cpct/2, temp);
			delete[] elem;
			elem = temp;
			elem[sz] = x;
			sz++;
		}
	}
	void pop_back(){
		if (sz > 0){
			pointer temp = allocator.allocate(sz - 1);
			std::copy(elem, elem + sz - 1, temp);
			delete[] elem;
			elem = temp;
			sz--;
		}
	}
	void resize(size_type new_sz){
		if (sz < new_sz){
			pointer temp = allocator.allocate(new_sz);
			std::copy(elem, elem+sz, temp);
			delete[] elem;
			elem = temp;
		}
		else {sz = new_sz;}
	}
	void swap(Vector& vector){
		Vector* temp;
		temp->sz = vector.sz;
		temp->cpct = vector.cpct;
		temp->allocator = vector.allocator;
		temp->elem = vector.elem;
		vector.sz = sz;
		vector.cpct = cpct;
		vector.elem = elem;
		vector.allocator = allocator;
		sz = temp->sz;
		cpct = temp->cpct;
		allocator = temp->allocator;
		elem = temp->elem;
	}
	friend bool operator==(Vector& v, Vector& t){
		if (v.sz != t.sz){return false;}
		else{
			for (auto i = 0; i < t.sz; ++i)
				if(v.elem[i] != t.elem[i])
					return false;
			return true;
		}
	}
	friend bool operator!=(Vector& v, Vector& t){return !(v==t);}
	friend bool operator<(Vector& v, Vector& t){
		if (v.sz < t.sz){return true;}
		else if (v.sz > t.sz){return false;}
		else {
			for (auto i = 0; i < v.sz; ++i){
				if (v.elem[i] < t.elem[i])
					return true;
				else if (v.elem[i] > t.elem[i])
					return false;
			}
		}
	}
	friend bool operator<=(Vector& v, Vector& t){if (v == t){return true;}else {return v < t;}}
	friend bool operator>(Vector& v, Vector& t){return !(v < t);}
	friend bool operator>=(Vector& v, Vector& t){if (v == t){return true;}else {return !(v < t);}}
};


