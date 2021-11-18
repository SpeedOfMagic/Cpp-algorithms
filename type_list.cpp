struct NullType {};

template<class ...Args>
struct TypeList {
	using Head = NullType;
	using Tail = NullType;
	constexpr static size_t size = 0;
};

using EmptyTypeList = TypeList<>;

template<class T>
struct TypeList<T> {
	using Head = T;
	using Tail = EmptyTypeList;
	constexpr static size_t size = 1;
};

template<class T, class ...Args>
struct TypeList<T, Args...> {
	using Head = T;
	using Tail = TypeList<Args...>;
	constexpr static size_t size = 1 + Tail::size;
};
