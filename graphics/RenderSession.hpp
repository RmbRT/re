#ifndef __re_graphics_rendersession_hpp_defined
#define __re_graphics_rendersession_hpp_defined

#include "ShaderProgram.hpp"
#include "../math/Vector.hpp"
#include "../math/Matrix.hpp"
#include "../types.hpp"
#include <stack>

namespace re
{
	namespace graphics
	{
		/*Used for storing the shader values of a render session and prevents 
		Includes a color stack and a matrix stack.*/
		class RenderSession
		{
			/*The matrix stack.*/
			std::stack<math::fmat4x4> matrices;
			/*The color stack.*/
			std::stack<math::fvec4> colors;

			/*Stores the currently passed color. Used for reducing GPU overhead.*/
			mutable math::fvec4 passed_color;
			/*Stores the currently passed matrix. Used for reducing GPU overhead.*/
			mutable math::fmat4x4 passed_matrix;

			/*The shader to push the stored values to.*/
			strong_handle<ShaderProgram> shader;
			/*The uniform locations to push the stored values to.*/
			ShaderProgram::uniform_t color_uniform, mvp_uniform;
		public:

			RenderSession();

			/*Pushes the given matrix onto the matrix stack.*/
			void push_matrix(const math::fmat4x4 &mat);
			/*Pushes the given color onto the color stack.*/
			void push_color(const math::fvec4 &color);
			/*Pops the top matrix of the matrix stack.*/
			void pop_matrix();
			/*Pops the top color of the color stack.*/
			void pop_color();

			/*Returns the current top color of the color stack.*/
			const math::fvec4 &color() const;
			/*Returns the current top matrix of the matrix stack.*/
			const math::fmat4x4 &matrix() const;

			/*Sets the shader and he needed uniform locations so that values can be passed.*/
			void set_shader(const strong_handle<ShaderProgram> &shader, ShaderProgram::uniform_t color_uniform, ShaderProgram::uniform_t mvp_uniform);

			/*Passes the matrix and color to the GPU if the values were changed since last passing.*/
			void pass_values() const;
		};
	}
}

#endif