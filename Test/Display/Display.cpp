#include "../Galatea.hpp"
using namespace Galatea;
using namespace Galatea::Display;

extern Bool BubbleTest(RendererImpl renderer);
extern Bool ZoneTest(RendererImpl renderer);
extern Bool SpriteTest(RendererImpl renderer);

Bool DisplayTest()
{
	Bool result = true;

	for(auto& impl : {RendererImpl::SDL, RendererImpl::OpenGL})
	{
		CHECK BubbleTest(impl);
		CHECK ZoneTest(impl);
		CHECK SpriteTest(impl);
	}

	return true;
}
