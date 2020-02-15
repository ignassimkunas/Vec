# Vector
Custom std::vector class.


# Pavyzdžiai:

- erase:

```
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
```
```
Vector<int> v1;
	for (auto i = 0; i < 8; ++i){
		v1.push_back(i+1);
	}
	v1.erase(v1.begin()+1);
	for (auto i = 0; i < v1.size(); ++i){
		std::cout << v1[i];
	}
  
  
1345678
```
- shrink_to_fit:

```
void shrink_to_fit(){
		pointer temp = allocator.allocate(sz);
		std::copy(elem, elem+sz, temp);
		delete[] elem;
		elem = temp;
		cpct = sz;
	}
  
```
```
Vector<int> v1;
	for (auto i = 0; i < 10; ++i){
		v1.push_back(i+1);
	}
	std::cout << v1.capacity() << "\n";
	v1.shrink_to_fit();
	std::cout << v1.capacity();
  
  16
  10
```

- assign:

```
void assign(iterator element, iterator lastElem){
		size_type count = 0;
		for(auto i = element; i != lastElem; i++){
			elem[count] = *i;
			count++;
			sz++;
		}
	}
```

```
Vector<int> v1;
	Vector<int> v2;
	for (auto i = 0; i < 5; ++i){
		v1.push_back(i+1);
	}
	v2.assign(v1.begin(), v1.end());
	for (auto i = 0; i < v2.size(); ++i){
		std::cout << v2[i];
	}
  
12345
```

- operator=:

```
Vector& operator=(const Vector& v){
		sz = v.sz;
		cpct= v.cpct;
		if (cpct < v.cpct){elem = allocator.allocate(v.cpct);}
		for (auto i = 0; i < v.sz; ++i){elem[i] = v.elem[i];}
	}
```
```
Vector<int> v1;
	Vector<int> v2;
	for (auto i = 0; i < 5; ++i){
		v1.push_back(i+1);
	}
	v2 = v1;
	for (auto i = 0; i < v2.size(); ++i){
		std::cout << v2[i];
	}
  12345
```

- reserve:

```
void reserve(size_type val) {
		if (val > cpct){
			cpct = val;
			pointer temp = allocator.allocate(cpct);
			std::copy(elem, elem + sz, temp);
			delete[] elem;
			elem = temp;
		}
	}
```

```
Vector<int> v1;
	for (auto i = 0; i < 5; ++i){
		v1.push_back(i+1);
	}
	std::cout << v1.capacity() << "\n";
	v1.reserve(50);
	std::cout << v1.capacity();
  
  8
  50
```

# Laiko matavimas

- 10000 elementų:
```
std::vector užpildymo laikas su 10000 int elementų.0.000252229
Vector užpildymo laikas su 10000 int elementų.0.000167087
```

- 100000 elementų:
```
std::vector užpildymo laikas su 100000 int elementų.0.00210143
Vector užpildymo laikas su 100000 int elementų.0.00130014
```
- 1000000 elementų:
```
std::vector užpildymo laikas su 1000000 int elementų.0.0172255
Vector užpildymo laikas su 1000000 int elementų.0.0114977
```
- 10000000 elementų:
```
std::vector užpildymo laikas su 10000000 int elementų.0.0685323
Vector užpildymo laikas su 10000000 int elementų.0.0454282
```
- 100000000 elementų:
```
std::vector užpildymo laikas su 100000000 int elementų.0.486892
Vector užpildymo laikas su 100000000 int elementų.0.355825
```
# Atminties perskirstymai

```
std::vector atminties perskirstymai: 27
Vector atminties perskirstymai: 27
```
