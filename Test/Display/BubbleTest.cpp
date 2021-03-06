#include "../Galatea.hpp"

using namespace Galatea;
using namespace Display;
using namespace Geometry;

extern void GetPngBubbleData(const UInt8*& png_sample_data, Int& size);

namespace
{
	class Bubble
	{
		Rectangle container;
		Motion motion;
		Image* img;
		Point img_offset;
		Vector direction;

		public:
		Bubble(Image* img, int width, int height);
		void Update();
		void Render(const Image* target) const;
	};

	Bubble::Bubble(Image* img, int width, int height) : img{img}
	{
		container.SetPosition({width / 4, height / 4});
		container.SetSize({width / 2, height / 2});

		int x = Math::Random(container.x1, container.Width());
		int y = Math::Random(container.y1, container.Height());
		motion.SetPosition(Point{x, y}.ToVector());

		img_offset.x = -img->Width() / 2;
		img_offset.y = -img->Height() / 2;

		direction = {Math::Random(0, 10) / 10.0, Math::Random(0, 10) / 10.0};
		if(Math::Random(1, 2) == 1) direction.x = -direction.x;
		if(Math::Random(1, 2) == 1) direction.y = -direction.y;
	}

	void Bubble::Update()
	{
		motion.Impulse(direction, .1);
		motion.Update();

		Point p = motion.Position().ToPoint();

		if(p.x < container.x1 && direction.x < 0 || p.x > container.x2 && direction.x > 0)
			direction.x = -direction.x;

		if(p.y < container.y1 && direction.y < 0 || p.y > container.y2 && direction.y > 0)
			direction.y = -direction.y;
	}

	void Bubble::Render(const Image* target) const
	{
		Point p = motion.Position().ToPoint() + img_offset;
		target->DrawImage(p, img);
	}
}

Bool BubbleTest(RendererImpl renderer)
{
	const int width{320}, height{240};
	auto wnd = CreateWindow(renderer, Text("Bubble Test"), width, height);

	if(!wnd)
		return false;

	Image* blue = wnd->CreateImage(width, height);
	for(int it{20}; it <= 120; it += 10)
		blue->DrawRect({Point{it, it}, Size{width - it - it, height - it - it}}, {0, 0, static_cast<UInt8>(it)});

	const UInt8* png_sample_data;
	Int png_sample_size;
	GetPngBubbleData(png_sample_data, png_sample_size);
	Image* png = wnd->CreateImage(png_sample_data, png_sample_size);

	const int bubble_count = 10;
	Bubble* bubbles[bubble_count];
	for(auto& bubble : bubbles)
		bubble = new Bubble(png, width, height);

	while(wnd->Update())
	{
		for(auto& bubble : bubbles)
			bubble->Update();

		wnd->BeginDraw();

		wnd->DrawImage({}, blue);
		for(auto& bubble : bubbles)
			bubble->Render(wnd);

		wnd->EndDraw();
	}

	for(auto& bubble : bubbles)
		delete bubble;

	delete png;
	delete blue;
	delete wnd;

	return true;
}
