#ifndef G2D_BASIC_BASIC_H_
#define G2D_BASIC_BASIC_H_

#pragma once

#include <algorithm>
#include <string>
#include <iostream>
#include <cassert>
#include <cstring>
#include <iosfwd>
#include <iomanip>
#include <vector>
#include <sstream>
#include <memory>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace g2d
{
	namespace basic
	{
		template<class... T>
		void unused(T&&...);

		template<typename T, typename M>
		T to(M src);

		template<typename T>
		std::vector<T> explode(const std::string& src, const char delimeter);

		template<typename T>
		std::vector<T> slice(const std::vector<T>& org, std::size_t begin, std::size_t end);

		template <typename T, typename N>
		std::vector<T> slice(const std::vector<N>& src, std::size_t begin, std::size_t end);

		template<typename T>
		void swap(const std::vector<T>& org, std::vector<T>& dst, std::size_t begin);

		template<typename T>
		bool repeated(const std::vector<T>& org, T element);

		template<typename T, typename N>
		bool repeated(const std::vector<T>& org, N element);

		template<typename T>
		bool repeated(const std::vector<T>& org);

		template <typename T, std::size_t N>
		constexpr std::size_t array_size(T (&)[N]);

		template <typename T, std::size_t N>
		T* array_begin(T (&array)[N]);

		template <typename T, std::size_t N>
		T* array_end(T (&array)[N]);

		template <typename T>
		std::string to_monetary(T org);

		std::string to_hex_string(int value, std::size_t length = 2);

		std::vector<std::string> explode(const std::string& src, const char delimeter);

		std::string replace(const std::string& src, const char org, const char dst);
	}
}

#include "basic.inl"

#endif /* G2D_BASIC_BASIC_H_ */

