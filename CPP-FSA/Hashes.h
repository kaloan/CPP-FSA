#pragma once

template<typename T> void hash_combine(size_t & seed, T const& v) {
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
