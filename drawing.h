#pragma once

#include <vector>
#include <array>
#include <boost/type_index.hpp>

namespace borsuk {

	struct Vertex2D
	{
		Vertex2D(float x, float y) noexcept
			: x_{ x }, y_{ y }
		{
		}

		float x_;
		float y_;
		float z_ = 0;
	};

	struct Vertex2DCol : public Vertex2D
	{
		Vertex2DCol(float x, float y, float r = 0.0f, float g = 0.0f, float b = 0.0) noexcept
			: Vertex2D{ x, y }, red_{ r }, green_{ g }, blue_{ b }
		{
		}

		float red_;
		float green_;
		float blue_;
	};

namespace shapes {
	constexpr float triangle2d_elem_count = 9; // 3 vertices * 3 positions each
	constexpr float triangle2dcol_elem_count = triangle2d_elem_count * 3; // +3 values of colors for each vertex

	class Shape
	{
	public:
		template<typename... V2D>
		Shape(V2D... vertices)
		{
			unpack_Vertex(vertices...);
		}

		virtual const std::vector<float>& Vertices() const = 0;
	private:
		template<typename Coords, typename... Args>
		void unpack_Vertex(Coords coords, Args... args)
		{
			unpack_Vertex(coords);
			unpack_Vertex(args...);
		}

		template<>
		void unpack_Vertex<Vertex2D>(Vertex2D coords)
		{
			vertices_.push_back(coords.x_);
			vertices_.push_back(coords.y_);
			vertices_.push_back(coords.z_);
			return;
		}

		template<>
		void unpack_Vertex<Vertex2DCol>(Vertex2DCol coords)
		{
			unpack_Vertex<Vertex2D>(coords);
			vertices_.push_back(coords.red_);
			vertices_.push_back(coords.green_);
			vertices_.push_back(coords.blue_);
		}
	protected:
		std::vector<float> vertices_;

	};

	class Square : public Shape
	{
	public:
		template<typename V2D/*, typename = std::enable_if<boost::typeindex::type_info == Vertex2D ||
			boost::typeindex::type_info == Vertex2DCol>::type*/>
		Square(V2D a, V2D b, V2D c, V2D d)
			: Shape{ a,b,c,d }
		{
		}

		const std::vector<float>& Vertices() const { return vertices_; }
	private:

	};

} // namespace shapes
} // namespace borsuk
