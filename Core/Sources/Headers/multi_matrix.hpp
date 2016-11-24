#pragma once
#include <vector>
#include <stdexcept>
#include "matrix.hpp"

namespace Convolutional {

class MultiMatrix {
public:
	using SubDimensionType = std::vector<Matrix>;

    explicit MultiMatrix(SubDimensionType subDimensions);

	auto GetDimensionCount() const noexcept { return subDimensions.size(); }
	auto GetElementCount() const -> std::size_t;
	auto GetSize() const -> Matrix::Size;

	auto begin() noexcept { return subDimensions.begin(); }
	auto begin() const noexcept { return subDimensions.begin(); }
	auto end() noexcept { return subDimensions.end(); }
	auto end() const noexcept { return subDimensions.end(); }

private:
	template<typename Lambda>
	auto GetMultidimensionalProperty(Lambda&& lambda) const {
		auto result = lambda(subDimensions.front());
		for (const auto& dimension : subDimensions) {
			if (result != lambda(static_cast<Matrix>(dimension)))
				throw std::logic_error("Property was not consistent between dimensions");
		}
		return result;
	}

private:
	SubDimensionType subDimensions;
};

}