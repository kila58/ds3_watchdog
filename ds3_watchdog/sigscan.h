#pragma once

typedef uintptr_t ptr;
typedef unsigned int uint;
typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned long ulong;

ptr SigScan(const char* pattern, const char* module = NULL);

template <typename Ty>
class multiptr
{
private:
	std::vector<std::uintptr_t> offsets_;
	Ty default_;

public:
	multiptr(std::initializer_list<std::uintptr_t> offsets)
		: offsets_{ offsets }, default_{}
	{
	}

	operator Ty*()
	{
		std::uintptr_t pointee = 0;

		for (std::size_t i = 0; i < std::size(offsets_); ++i) {
			pointee = *reinterpret_cast<std::uintptr_t *>(pointee + offsets_[i]);
			if (!pointee) {
				return nullptr;
			}
		}

		return reinterpret_cast<Ty *>(pointee);
	}

	Ty* operator->()
	{
		auto result = operator Ty*();
		return result ? result : &default_;
	}
};