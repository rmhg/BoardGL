#ifndef IMPL_VECTOR_H
#define IMPLE_VECTOR_H

namespace IMPL {
	namespace std {
		template<typename type>
		class vector {
			unsigned int size;
			type* vec;
		public:
			vector();
			vector(unsigned int);
			~vector();
			void push_back(type);
			void emplace_back(type);
			void pop_back();
			type& operator[](unsigned int);
			void replace(unsigned int, type);
		};
	}

}



#endif
