#pragma once

template<typename T> 
void hash_combine(size_t & seed, T const& v) {
	seed ^= stdext::hash_value(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

template<typename T, typename U>
struct hash_pair {
	size_t operator()(const std::pair<T, U> &rhs) const noexcept
	{
		size_t retval = stdext::hash_value<T>(rhs.first);
		hash_combine(retval, rhs.second);
		return retval;
	}
};

template<typename T, typename U, typename V>
struct hash_triple {
	size_t operator()(const std::tuple<T, U, V> &rhs) const noexcept
	{
		size_t retval = stdext::hash_value<T>(std::get<0>(rhs));
		hash_combine(retval, std::get<1>(rhs));
		hash_combine(retval, std::get<2>(rhs));
		return retval;
	}
};

template<typename... TupleTypes>
struct hash_tuple {
	size_t operator()(const std::tuple<TupleTypes...> &tuple) const noexcept
	{
		size_t tupleSize = std::tuple_size<std::tuple<TupleTypes...>>;
		size_t retval = stdext::hash_value(std::get<0>(tuple));
		for (int i = 1; i < tupleSize; i++) 
		{
			hash_combine(retval, std::get<i>(tuple));

		}
		return retval;
	}
};

