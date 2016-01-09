#include "Renderer.hpp"
#include "SDL/RendererSDL.hpp"

namespace Galatea
{
	namespace Display
	{
		Renderer* Renderer::Create()
		{
			return new RendererSDL();
		}
	}
}
